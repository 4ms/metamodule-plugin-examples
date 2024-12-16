#pragma once
#include "CoreModules/elements/element_info.hh"
#include <array>

namespace MetaModule::RackClone
{

struct Trimpot : Knob {
	constexpr Trimpot(BaseElement b, float defaultValue = 0.5f)
		: Knob{{{b, "rack-lib/Trimpot.png"}}} {
		default_value = defaultValue;
	}
};

struct SmallLEDButton : MomentaryButtonRGB {
	constexpr SmallLEDButton(BaseElement b)
		: MomentaryButtonRGB{{{b}}} {
		image = "rack-lib/TL1105_0.png";
		pressed_image = "rack-lib/TL1105_1.png";
	}
};

struct JackIn : JackInput {
	constexpr JackIn(BaseElement b)
		: JackInput{b, "rack-lib/PJ301M.png"} {
	}
};

struct JackOut : JackOutput {
	constexpr JackOut(BaseElement b)
		: JackOutput{b, "rack-lib/PJ301M.png"} {
	}
};

struct QuantInfo : ModuleInfoBase {
	static constexpr std::string_view slug{"Quantizer"};
	static constexpr std::string_view description{"Quantizer"};
	static constexpr uint32_t width_hp = 4;
	static constexpr std::string_view svg_filename{""};
	static constexpr std::string_view png_filename{"Fundamental/Quant.png"};

	using enum Coords;

	static constexpr std::array<Element, 15> Elements{{
		Trimpot{{to_mm<72>(28.92), to_mm<72>(258.63), Center, "Pre-offset", ""}, 0.5f},
		SmallLEDButton{{to_mm<72>(24.83), to_mm<72>(230.07), Center, "C", ""}},
		SmallLEDButton{{to_mm<72>(11.76), to_mm<72>(211.5), Center, "C#", ""}},
		SmallLEDButton{{to_mm<72>(24.83), to_mm<72>(192.93), Center, "D", ""}},
		SmallLEDButton{{to_mm<72>(11.76), to_mm<72>(174.36), Center, "D#", ""}},
		SmallLEDButton{{to_mm<72>(24.83), to_mm<72>(155.8), Center, "E", ""}},
		SmallLEDButton{{to_mm<72>(24.83), to_mm<72>(137.23), Center, "F", ""}},
		SmallLEDButton{{to_mm<72>(11.76), to_mm<72>(118.66), Center, "F#", ""}},
		SmallLEDButton{{to_mm<72>(24.83), to_mm<72>(100.09), Center, "G", ""}},
		SmallLEDButton{{to_mm<72>(11.76), to_mm<72>(81.52), Center, "G#", ""}},
		SmallLEDButton{{to_mm<72>(24.83), to_mm<72>(62.95), Center, "A", ""}},
		SmallLEDButton{{to_mm<72>(11.76), to_mm<72>(44.38), Center, "A#", ""}},
		SmallLEDButton{{to_mm<72>(24.83), to_mm<72>(25.81), Center, "B", ""}},
		JackIn{{to_mm<72>(39.15), to_mm<72>(304.27), Center, "V/oct In", ""}},
		JackOut{{to_mm<72>(39.83), to_mm<72>(340.66), Center, "V/oct Out", ""}},
	}};

	enum class Elem {
		OffsetKnob,
		BButton,
		AsharpButton,
		AButton,
		GsharpButton,
		GButton,
		FsharpButton,
		FButton,
		EButton,
		DsharpButton,
		DButton,
		CsharpButton,
		CButton,
		In,
		Out,
	};

	enum ParamId {
		OffsetKnob,
		BButton,
		AsharpButton,
		AButton,
		GsharpButton,
		GButton,
		FsharpButton,
		FButton,
		EButton,
		DsharpButton,
		DButton,
		CsharpButton,
		CButton,
	};

	enum InputId { In };

	enum OutputId { Out };

	enum LightId {
		BRed,
		BGreen,
		BBlue,
		AsharpRed,
		AsharpGreen,
		AsharpBlue,
		ARed,
		AGreen,
		ABlue,
		GsharpRed,
		GsharpGreen,
		GsharpBlue,
		GRed,
		GGreen,
		GBlue,
		FsharpRed,
		FsharpGreen,
		FsharpBlue,
		FRed,
		FGreen,
		FBlue,
		ERed,
		EGreen,
		EBlue,
		DsharpRed,
		DsharpGreen,
		DsharpBlue,
		DRed,
		DGreen,
		DBlue,
		CsharpRed,
		CsharpGreen,
		CsharpBlue,
		CRed,
		CGreen,
		CBlue,
	};
};
} // namespace MetaModule::RackClone
