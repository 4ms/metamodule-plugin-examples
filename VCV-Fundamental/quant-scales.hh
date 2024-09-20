#pragma once
#include <array>
#include <string_view>

namespace MetaModule::RackClone
{

struct QuantScale {
	std::string_view name;
	std::string_view scale;
};

constexpr inline std::array<QuantScale, 3> QuantScales{{
	{"Ionian (Major)",
	 R"({
    "enabledNotes": [
      true,
      false,
      true,
      false,
      true,
      true,
      false,
      true,
      false,
      true,
      false,
      true
    ]
  }
)"},
	{"Dorian",
	 R"({
    "enabledNotes": [
      true,
      false,
      true,
      true,
      false,
      true,
      false,
      true,
      false,
      true,
      true,
      false
    ]
  }
)"},

	{"Phrygian",
	 R"({
    "enabledNotes": [
      true,
      true,
      false,
      true,
      false,
      true,
      false,
      true,
      true,
      false,
      true,
      false
    ]
  }
)"},

}};

} // namespace MetaModule::RackClone
