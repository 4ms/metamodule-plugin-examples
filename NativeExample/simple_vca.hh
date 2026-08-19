#pragma once
#include "CoreModules/CoreHelper.hh"
#include "CoreModules/CoreProcessor.hh"
#include "simple_vca_info.hh"

class SimpleVCA : public CoreProcessor, MetaModule::CoreHelper<SimpleVCAInfo> {
	using enum SimpleVCAInfo::Elem;

public:
	void update() override {
		out = in * (knob + cv);
	}

	void set_param(int param_id, float val) override {
		if (param_id == param_idx<GainKnob>)
			knob = val;
	}

	float get_param(int param_id) const override {
		if (param_id == param_idx<GainKnob>)
			return knob;
		else
			return 0;
	}

	void set_samplerate(float sr) override {
	}

	void set_input(int input_id, float val) override {
		if (input_id == input_idx<AudioInput>)
			in = val;

		if (input_id == input_idx<CVInput>)
			cv = val / 10.f;
	}

	float get_output(int output_id) const override {
		if (output_id == output_idx<AudioOutput>)
			return out;
		else
			return 0;
	}

	float get_led_brightness(int led_id) const override {
		if (led_id == light_idx<GainLight>)
			return (knob + cv);
		else
			return 0;
	}

private:
	float in = 0;
	float out = 0;
	float knob = 0.5f;
	float cv = 0.f;
};
