#pragma once
#include "AirwinRegistry.h"
#include "CoreModules/CoreProcessor.hh"
#include "airwin_consolidated_base.h"
#include "util/input_output_buffer.hh"
#include <algorithm>
#include <array>
#include <memory>

namespace MetaModuleAirwindows
{

// Use the same param/input/output indices as Airwin2Rack,
// so that patches made on VCV work on MM.

static constexpr unsigned maxParams = 10;
// PARAM_0..OUT_LEVEL keep the Airwin2Rack indices (see above). MONO_POLY is a
// MetaModule-only AltParam, so it takes a fresh index past the shared ones.
enum ParamIds { PARAM_0 = 0, ATTEN_0 = 11, IN_LEVEL = 22, OUT_LEVEL, MONO_POLY, NUM_PARAMS };
enum InputIds { INPUT_L, INPUT_R, CV_0, NUM_INPUTS = CV_0 + maxParams };
enum OutputIds { OUTPUT_L, OUTPUT_R, NUM_OUTPUTS };

// MONO_POLY AltParam choices (index = round(val)):
enum PolyMode { Monophonic = 0, Polyphonic = 1 };

// Polyphonic stereo Airwindows effect.
// The L and R audio jacks are polyphonic; the CV jacks are mono.
// The number of voices processed is the max of the L and R channel counts.
// If one audio jack has fewer channels than the other, its highest channel is
// copied up to the remaining voices; if R is unpatched it mirrors L (as in the
// original mono code). Each voice has its own effect instance so that the
// effect's internal state (filters, delays, reverb tails) does not bleed
// between voices.
struct Module : CoreProcessorPoly {
	static constexpr size_t BlockSize = 32;
	static constexpr unsigned MaxChans = MaxPolyChannels;

	Module(unsigned registry_idx) {
		auto &reg = AirwinRegistry::registry[registry_idx];
		for (auto &f : fx)
			f = reg.generator();
		num_params = std::min<unsigned>(reg.nParams, maxParams);

		// Default to Monophonic, matching the AltParam default, in case the host
		// does not push the default value before the first update().
		params[MONO_POLY] = float(PolyMode::Monophonic);
	}

	void update() override {
		const float gain = params[IN_LEVEL] * 0.2f;
		const bool mono = params[MONO_POLY] <= 0.5f;

		const unsigned in_chans = std::clamp<unsigned>(std::max(insL_chans, insR_chans), 1, MaxChans);
		const unsigned num_chans = mono ? 1u : in_chans;
		outL_chans = num_chans;
		outR_chans = num_chans;

		// Accumulate one input sample per voice into the block buffers. All
		// MaxChans buffers are advanced every update so that  a change in
		// voice count or mode never desyncs the per-voice blocks.
		if (mono) {
			// Sum every input channel of each jack into a single mono pair.
			// The same summed signal is written to every
			// voice buffer so the lockstep above is preserved.
			float sumL = 0.f;
			for (unsigned c = 0; c < insL_chans; c++)
				sumL += insL[c];
			float sumR = 0.f;
			if (insR_chans)
				for (unsigned c = 0; c < insR_chans; c++)
					sumR += insR[c];
			else
				sumR = sumL;

			for (unsigned c = 0; c < MaxChans; c++) {
				inL_buf[c].put(sumL * gain);
				inR_buf[c].put(sumR * gain);
			}
		} else {
			// Polyphonic: per-voice, padding the lower-count jack with copies of
			// its highest channel; an unpatched R mirrors L.
			for (unsigned c = 0; c < MaxChans; c++) {
				float l = insL_chans ? insL[std::min<unsigned>(c, insL_chans - 1)] : 0.f;
				float r = insR_chans ? insR[std::min<unsigned>(c, insR_chans - 1)] : l;
				inL_buf[c].put(l * gain);
				inR_buf[c].put(r * gain);
			}
		}

		if (inL_buf[0].full()) {
			// Mono mode processes only voice 0; poly mode processes every voice.
			const unsigned num_proc = mono ? 1 : num_chans;

			for (auto i = 0u; i < num_params; i++) {
				auto param = params[PARAM_0 + i];

				if (input_patched[CV_0 + i]) {
					auto cv = ins[CV_0 + i] * 0.4f * (params[ATTEN_0 + i] - 0.5f);
					param = std::clamp(param + cv, 0.f, 1.f);
				}

				for (unsigned c = 0; c < num_proc; c++)
					fx[c]->setParameter(i, param);
			}

			for (unsigned c = 0; c < num_proc; c++) {
				float *in[2] = {inL_buf[c].data(), inR_buf[c].data()};
				float *out[2] = {outL_buf[c].data(), outR_buf[c].data()};
				fx[c]->processReplacing(in, out, BlockSize);
			}

			for (unsigned c = 0; c < MaxChans; c++) {
				inL_buf[c].reset();
				inR_buf[c].reset();
				outL_buf[c].reset();
				outR_buf[c].reset();
			}
		}

		const float out_gain = 5.f * params[OUT_LEVEL];
		if (mono) {
			outsL[0] = outL_buf[0].get() * out_gain;
			outsR[0] = outR_buf[0].get() * out_gain;
		} else {
			for (unsigned c = 0; c < num_chans; c++) {
				outsL[c] = outL_buf[c].get() * out_gain;
				outsR[c] = outR_buf[c].get() * out_gain;
			}
		}
	}

	void set_samplerate(float sr) override {
		for (auto &f : fx)
			f->setSampleRate(sr);
	}

	void set_param(int param_id, float val) override {
		if ((unsigned)param_id < params.size()) {
			params[param_id] = val;
		}
	}

	float get_param(int param_id) const override {
		if ((unsigned)param_id < params.size()) {
			return params[param_id];
		}
		return 0;
	}

	// Mono sources write channel 0; poly sources write the buffers directly
	void set_input(int input_id, float val) override {
		switch (input_id) {
			case INPUT_L:
				insL[0] = val;
				break;
			case INPUT_R:
				insR[0] = val;
				break;
			default:
				if ((unsigned)input_id < NUM_INPUTS)
					ins[input_id] = val;
				break;
		}
	}

	float get_output(int output_id) const override {
		// Voltages are already scaled in update(); return voice 0 for mono hosts.
		switch (output_id) {
			case OUTPUT_L:
				return outsL[0];
			case OUTPUT_R:
				return outsR[0];
			default:
				return 0.f;
		}
	}

	PolyPortBuffer get_poly_input_buffer(int input_id) override {
		switch (input_id) {
			case INPUT_L:
				return {insL.data(), &insL_chans};
			case INPUT_R:
				return {insR.data(), &insR_chans};
		}
		return {};
	}

	PolyPortBuffer get_poly_output_buffer(int output_id) override {
		switch (output_id) {
			case OUTPUT_L:
				return {outsL.data(), &outL_chans};
			case OUTPUT_R:
				return {outsR.data(), &outR_chans};
		}
		return {};
	}

	void mark_all_inputs_unpatched() override {
		insL_chans = 0;
		insR_chans = 0;
		insL = {};
		insR = {};
		input_patched = {};
	}

	void mark_input_patched(int input_id) override {
		// 0 -> 1 channel; a poly source will then raise the count itself
		switch (input_id) {
			case INPUT_L:
				if (insL_chans == 0) {
					insL_chans = 1;
					insL = {};
				}
				break;
			case INPUT_R:
				if (insR_chans == 0) {
					insR_chans = 1;
					insR = {};
				}
				break;
			default:
				if ((unsigned)input_id < NUM_INPUTS)
					input_patched[input_id] = true;
				break;
		}
	}

	void mark_input_unpatched(int input_id) override {
		switch (input_id) {
			case INPUT_L:
				insL_chans = 0;
				insL = {};
				break;
			case INPUT_R:
				insR_chans = 0;
				insR = {};
				break;
			default:
				if ((unsigned)input_id < NUM_INPUTS)
					input_patched[input_id] = false;
				break;
		}
	}

	unsigned num_params{};
	std::array<std::unique_ptr<AirwinConsolidatedBase>, MaxChans> fx;

private:
	std::array<float, NUM_PARAMS> params{};
	std::array<float, NUM_INPUTS> ins{};
	std::array<bool, NUM_INPUTS> input_patched{};

	// Poly audio port storage (current sample per voice) and channel counts:
	std::array<float, MaxChans> insL{};
	std::array<float, MaxChans> insR{};
	std::array<float, MaxChans> outsL{};
	std::array<float, MaxChans> outsR{};
	uint8_t insL_chans = 0;
	uint8_t insR_chans = 0;
	uint8_t outL_chans = 1;
	uint8_t outR_chans = 1;

	// Per-voice block accumulators:
	std::array<InputBuffer<float, BlockSize>, MaxChans> inL_buf{};
	std::array<InputBuffer<float, BlockSize>, MaxChans> inR_buf{};
	std::array<OutputBuffer<float, BlockSize>, MaxChans> outL_buf{};
	std::array<OutputBuffer<float, BlockSize>, MaxChans> outR_buf{};
};

} // namespace MetaModuleAirwindows
