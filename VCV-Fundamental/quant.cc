#include "quant.hh"
#include "CoreModules/elements/element_info_view.hh"
#include "CoreModules/register_module.hh"
#include "quant_info.hh"
#include <rack.hpp>

namespace MetaModule::RackClone
{

Quant::Quant() {
	onReset();
}

void Quant::onReset() {
	for (int i = 0; i < 12; i++) {
		enabledNotes[i] = true;
		lastButtonState[i] = false;
	}
	updateRanges();
}

void Quant::onRandomize() {
	for (int i = 0; i < 12; i++) {
		enabledNotes[i] = (rack::random::uniform() < 0.5f);
	}
	updateRanges();
}

void Quant::update() {
	std::array<bool, 12> playingNotes = {};

	float pitch = input;
	pitch += offset_knob;
	int range = std::floor(pitch * 24);
	int octave = rack::math::eucDiv(range, 24);
	range -= octave * 24;
	int note = ranges[range] + octave * 12;
	playingNotes[rack::math::eucMod(note, 12)] = true;
	pitch = float(note) / 12;
	output = pitch;

	std::memcpy(this->playingNotes.data(), playingNotes.data(), sizeof(playingNotes));
}

void Quant::updateRanges() {
	// Check if no notes are enabled
	bool anyEnabled = false;
	for (int note = 0; note < 12; note++) {
		if (enabledNotes[note]) {
			anyEnabled = true;
			break;
		}
	}
	// Find closest notes for each range
	for (int i = 0; i < 24; i++) {
		int closestNote = 0;
		int closestDist = INT_MAX;
		for (int note = -12; note <= 24; note++) {
			int dist = std::abs((i + 1) / 2 - note);
			// Ignore enabled state if no notes are enabled
			if (anyEnabled && !enabledNotes[rack::math::eucMod(note, 12)]) {
				continue;
			}
			if (dist < closestDist) {
				closestNote = note;
				closestDist = dist;
			} else {
				// If dist increases, we won't find a better one.
				break;
			}
		}
		ranges[i] = closestNote;
	}
}

void Quant::rotateNotes(int delta) {
	delta = rack::math::eucMod(-delta, 12);
	std::rotate(&enabledNotes[0], &enabledNotes[delta], &enabledNotes[12]);
	updateRanges();
}

json_t *Quant::dataToJson() {
	json_t *rootJ = json_object();

	json_t *enabledNotesJ = json_array();
	for (int i = 0; i < 12; i++) {
		json_array_insert_new(enabledNotesJ, i, json_boolean(enabledNotes[i]));
	}
	json_object_set_new(rootJ, "enabledNotes", enabledNotesJ);

	return rootJ;
}

void Quant::dataFromJson(json_t *rootJ) {
	json_t *enabledNotesJ = json_object_get(rootJ, "enabledNotes");
	if (enabledNotesJ) {
		for (int i = 0; i < 12; i++) {
			json_t *enabledNoteJ = json_array_get(enabledNotesJ, i);
			if (enabledNoteJ)
				enabledNotes[i] = json_boolean_value(enabledNoteJ);
		}
	}
	updateRanges();
}

void Quant::set_param(int param_id, float val) {
	if (param_id == QuantInfo::OffsetKnob) {
		offset_knob = val * 2.f - 1.f; //0..1 => -1..1
	}

	else if (param_id <= 12)
	{
		auto note = param_id - 1;
		if (val > 0.55f) {
			if (lastButtonState[note] == false) {
				lastButtonState[note] = true;
				enabledNotes[note] ^= true;
				updateRanges();
			}
		} else if (val < 0.45f) {
			lastButtonState[note] = false;
		}
	}
}

void Quant::set_samplerate(float sr) {
}

void Quant::set_input(int input_id, float val) {
	if (input_id == QuantInfo::In)
		input = val;
}

float Quant::get_output(int output_id) const {
	if (output_id == QuantInfo::Out)
		return output;
	else
		return 0;
}

float Quant::get_led_brightness(int led_id) const {
	unsigned note = led_id / 3;
	if (note > 11)
		return 0;

	auto type = led_id - (note * 3);

	const unsigned EnabledType = 0;
	const unsigned PlayingType = 1;

	if (type == EnabledType) {
		return enabledNotes[note] ? 1.f : 0.f;

	} else if (type == PlayingType) {
		return playingNotes[note] ? 1.f : 0.f;

	} else
		return 0;
}

// Boiler plate from Module.cpp:
void Quant::load_state(std::string_view state_data) {
	if (state_data.size() == 0)
		return;

	json_error_t err;

	json_t *root = json_loadb((char *)state_data.data(), state_data.size(), 0, &err);
	if (!root) {
		printf("JSON decode error: %d:%d %s\n", err.line, err.column, err.text);
		return;
	}

	dataFromJson(root);

	json_decref(root);
}

std::string Quant::save_state() {
	json_t *dataJ = dataToJson();

	if (!dataJ)
		return {};

	std::string state_data;
	auto sz = json_dumpb(dataJ, nullptr, 0, JSON_COMPACT);
	if (sz > 0) {
		state_data.resize(sz);
		json_dumpb(dataJ, (char *)state_data.data(), sz, JSON_COMPACT);
	}

	json_decref(dataJ);

	return state_data;
}

void Quant::register_module() {
	using Info = QuantInfo;

	MetaModule::register_module(
		"Fundamental",
		Info::slug,
		[]() { return std::make_unique<Quant>(); },
		MetaModule::ModuleInfoView::makeView<Info>(),
		Info::png_filename);
}

} // namespace MetaModule::RackClone
