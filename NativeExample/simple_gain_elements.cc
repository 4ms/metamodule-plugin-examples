#include "CoreModules/CoreProcessor.hh"
#include "CoreModules/elements/element_counter.hh"
#include "CoreModules/elements/elements.hh"
#include "CoreModules/register_module.hh"
#include "simple_gain.hh"

void init_simple_gain() {
  static std::array<MetaModule::Element, 4> elements;
  static std::array<ElementCount::Indices, 4> indices;

  MetaModule::Knob gain;
  gain.x_mm = 10;
  gain.y_mm = 20;
  gain.image = "NativeExample/components/knob.png";
  gain.short_name = "Gain";
  elements[0] = gain;
  indices[0] = {.param_idx = GainKnobID};

  MetaModule::JackInput injack;
  injack.x_mm = 10;
  injack.y_mm = 60;
  injack.image = "NativeExample/componentss/jack.png";
  injack.short_name = "Input";
  elements[1] = injack;
  indices[1] = {.input_idx = InputJackID};

  MetaModule::JackOutput outjack;
  outjack.x_mm = 10;
  outjack.y_mm = 80;
  outjack.image = "NativeExample/componentss/jack.png";
  outjack.short_name = "Output";
  elements[2] = outjack;
  indices[2] = {.output_idx = OutputJackID};

  MetaModule::MonoLight light;
  light.x_mm = 10;
  light.y_mm = 30;
  light.image = "NativeExample/componentss/led.png";
  light.short_name = "Gain LED";
  elements[3] = light;
  indices[3] = {.light_idx = GainLightID};

  MetaModule::ModuleInfoView info{
      .description = "A simple gain module",
      .width_hp = 10,
      .elements = elements,
      .indices = indices,
  };

  MetaModule::register_module(
      "NativeExample", "SimpleGain",
      []() { return std::make_unique<SimpleGain>(); }, info,
      "Brandname/simple_gain.png");
}
