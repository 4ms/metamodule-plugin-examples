#include "CoreModules/CoreProcessor.hh"

enum { GainKnobID };
enum { InputJackID };
enum { OutputJackID };
enum { GainLightID };

class SimpleGain : public CoreProcessor {
public:
    void update() override;
    void set_param(int param_id, float val) override;
    void set_samplerate(float sr) override;
    void set_input(int input_id, float val) override;
    float get_output(int output_id) const override;
    float get_led_brightness(int led_id) const override;

private:
    float in = 0;
    float out = 0;
    float gain = 1.f;
};
