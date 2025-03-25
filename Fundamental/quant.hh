#include "CoreModules/CoreProcessor.hh"

struct json_t;

namespace MetaModule::RackClone
{

class Quant : public CoreProcessor {
public:
	Quant();
	void update() override;
	void set_param(int param_id, float val) override;
	float get_param(int param_id) const override;
	void set_samplerate(float sr) override;
	void set_input(int input_id, float val) override;
	float get_output(int output_id) const override;
	float get_led_brightness(int led_id) const override;

	void load_state(std::string_view state_data) override;
	std::string save_state() override;

	static void register_module();

private:
	void onReset();
	void onRandomize();
	void updateRanges();
	void rotateNotes(int delta);
	json_t *dataToJson();
	void dataFromJson(json_t *rootJ);

	std::array<bool, 12> enabledNotes;
	std::array<bool, 12> lastButtonState;

	// Intervals [i / 24, (i+1) / 24) V mapping to the closest enabled note
	std::array<int, 24> ranges;
	std::array<bool, 12> playingNotes;

	float input{0};
	float offset_knob{0};
	float output{0};
};

} // namespace MetaModule::RackClone
