#include "simple_gain.hh"

void SimpleGain::update() {
    out = in * gain;
}

void SimpleGain::set_param(int param_id, float val) {
    if (param_id == GainKnobID)
        gain = val;
}

void SimpleGain::set_samplerate(float sr) {
}

void SimpleGain::set_input(int input_id, float val) {
    if (input_id == InputJackID)
        in = val;
}

float SimpleGain::get_output(int output_id) const {
    if (output_id == OutputJackID)
        return out;
    else
        return 0;
}

float SimpleGain::get_led_brightness(int led_id) const {
    if (led_id == GainLightID)
        return gain;
    else
        return 0;
}
