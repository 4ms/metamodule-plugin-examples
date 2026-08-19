#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

struct SimpleVCAInfo : MetaModule::ModuleInfoBase {
	static constexpr std::string_view slug{"SimpleVCA"};
	static constexpr std::string_view description{"A simple VCA module example"};
	static constexpr uint32_t width_hp = 10;
	static constexpr std::string_view png_filename{"NativeExample/simple_vca.png"};

	using enum MetaModule::Coords;

	static constexpr std::array<MetaModule::Element, 5> Elements{{
		MetaModule::Knob{{{{{20.f, 15.f, Center, "Gain"}, "NativeExample/components/knob.png"}}}},
		MetaModule::JackInput{{{{20.f, 50.f, Center, "Audio In"}, "NativeExample/components/jack.png"}}},
		MetaModule::JackInput{{{{20.f, 70.f, Center, "CV In"}, "NativeExample/components/jack.png"}}},
		MetaModule::JackOutput{{{{20.f, 90.f, Center, "Autio Out"}, "NativeExample/components/jack.png"}}},
		MetaModule::MonoLight{{{{20.f, 35.f, Center, "Gain LED"}, "NativeExample/components/led.png"}},
							  Colors565::Blue},
	}};

	enum class Elem {
		// The order of these needs to match the order of the Elements array above
		GainKnob,
		AudioInput,
		CVInput,
		AudioOutput,
		GainLight,
	};
};
