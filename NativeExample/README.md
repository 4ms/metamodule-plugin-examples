## Native Example plugin

This is an example of a native MetaModule plugin. It provides one module: SimpleVCA.

Let's look at how it's built.

Source code:
- plugin.cc: 
- simple_vca.hh
- simple_vca_info.hh

Metadata:
- plugin.json
- plugin-mm.json

Graphics:
- assets/simple_vca.png
- assets/components/*.png

Build system:
- CMakeLists.txt


## Source code

`plugin.cc` is very simple, it only defines one function: `init()`. This `init()` function is required for every plugin. The MetaModule firmware will call it once, when the plugin is loaded.

```c++
extern "C" void init() {
	MetaModule::register_module<SimpleVCA, SimpleVCAInfo>("NativeExample");
}
```


The `register_module<MyModule, MyModuleInfo>("MyBrandName")` registers the module with the MetaModule firmware so that it can be used in patches. The string "NativeExample" is the brand slug, which must match what's in the json files (see below).

Let's look at what `SimpleVCA` is, in simple_vca.hh. Here's a simplified version:

```c++
#include "CoreModules/CoreHelper.hh"
#include "CoreModules/CoreProcessor.hh"
#include "simple_vca_info.hh"

class SimpleVCA : public CoreProcessor, MetaModule::CoreHelper<SimpleVCAInfo> {
public:
	void update() override {
		//..
    }

	void set_param(int param_id, float val) override {
		//..
	}

	float get_param(int param_id) const override {
		//..
	}

	void set_samplerate(float sr) override {
	}

	void set_input(int input_id, float val) override {
		//..
	}

	float get_output(int output_id) const override {
		//..
	}

	float get_led_brightness(int led_id) const override {
		//..
	}

private:
	float in = 0;
	float out = 0;
	float knob = 0.5f;
	float cv = 0.f;
};
```

`SimpleVCA` is a class that derives from `CoreProcessor`. All modules must
derive from this base class.

`CoreProcessor` is an abstract virtual base class that contains all the
functions a module must implement. Some are optional (for example, in SimpleVCA
we didn't define `mark_output_patched()` because we don't care about detecting
whether an output jack is patched). Take a look at
`metamodule-plugin-sdk/CoreModules/CoreProcessor.hh` if you want to see all the
functions.

The `update()` function is the most important, as it gets called each audio frame, and
is usually where the processing happens.

```c++
void update() override {
    out = in * (knob + cv);
}
```

`set_param()` is also called once per audio frame, and is how the firmware 
tells your modules what the knobs, buttons, etc are doing:

```c++
void set_param(int param_id, float val) override {
    if (param_id == param_idx<GainKnob>)
        knob = val;
}
```

Here we see a new thing: `param_idx<GainKnob>`. Let's take a detour and look at what
that is. 
`GainKnob` is defined in our `SimpleVCAInfo` class, in `simple_vca_info.hh`:

```c++
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
```

The `SimpleVCAInfo` class defines the GUI aspects of the module. 
The `GainKnob` constant we saw in `set_param()` above is defined near the bottom
in the `Elem` enum class. 

Notice `GainKnob` is the first element in `Elem`. This matches the first
element in `Elements`. `Elem` and `Elements` are always kept in the same order,
which is how the GUI and DSP stay in sync.


Going back to `set_param()` in our `SimpleVCA` class, we now know what `GainKnob` is,
but what is `param_idx`? 
This is a template variable defined in `CoreHelper` (core-interface/CoreModules/CoreHelper.hh).
This is not required to be used, but it helps keep your code clean and simple. 

`param_idx<ElemName>` converts the raw Elem name to the parameter index, which is
what the MetaModule passes into `set_param()`. `param_idx` is safer than using 
raw indices because it does compile-time checks for the right type: e.g. if you
tried to do `param_idx<GainLight>`, you would get an error when you compile (versus if 
you use raw IDs then your plugin would compile and load but you'd get hard to
debug strange behavior when you used it)

Similar to `param_idx`, the other functions in `SimpleVCA` use `input_idx<>`, `output_idx<>`,
and `light_idx<>`:

```c++
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

	float get_param(int param_id) const override {
		if (param_id == param_idx<GainKnob>)
			return knob;
		else
			return 0;
	}

```


`get_led_brightness()` and `get_param()` are called from the MetaModule GUI
whenever it needs to draw your module on screen.

In `get_param()`, typically you just return back the last thing `set_param()`
sent, but in some cases you might have changed the value and should report
the new value. For example if your module has a knob that selects a scale 
by toggling a bunch of switches, or if press a button disables a 
a different parameter, etc., then the only way the MetaModule can know that 
your module changed one of its own parameters is when it calls `get_param()`.

That's it for the source files. Next let's look at the metadata.

## Metadata

The two metadata files are `plugin.json` and `plugin-mm.json`

The `plugin.json` is in a format defined by VCV Rack. We require it for native plugins, too, to streamline the way slugs are handled. 

```json
{
  "slug": "NativeExample",
  "name": "NativeExample",
  "brand": "NativeExample",
  "version": "1.0.0",
  "license": "GPL-3.0-or-later",
  "author": "Dan Green",
  "modules": [
    {
      "slug": "SimpleVCA",
      "name": "SimpleVCA",
      "description": "Example plugin",
      "tags": [ 
		  "VCA"
      ]
    }
  ]
}

```

Above is a minimal example. Typically the fields `slug`, `name`, and `brand`
will all be the same. This is known as your "brand slug". The brand slug is
used to identify your plugin, so if you ever change it, then patch files using
your modules will break. Once a plugin is released, you should never change
your brand slug for that reason.

You must list out all modules in the `modules` section. The tags are optional
but helpful for users to find a your modules.

The `plugin-mm.json` is similar:

```json
{
	"MetaModuleBrandName": "Native Example",
	"MetaModulePluginMaintainer": "4ms Company",
	"MetaModulePluginMaintainerEmail": "4ms@4mscompany.com",
	"MetaModulePluginMaintainerUrl": "https://metamodule.info",
	"MetaModuleDescription": "Example project for a MetaModule plugin",
    "MetaModuleIncludedModules": [
    {
      "slug": "SimpleVCA",
      "name": "Simple VCA"
    }
	]
}
```

The important things here are:
- `MetaModuleBrandName` is the display name on the MetaModule website and on
  the MetaModule hardware screen. It does not have to match the brand slug, but
  try to make it close or else it's confusing to users.
- `MetaModuleIncludedModules` is usually the same as the `modules` field in
  `plugin.json` but it can a subset. You might want to have it be a subset if
  you build this plugin for VCV and have a different set of modules available
  for VCV vs. MetaModule.
- The "Maintainer" fields refer to the MetaModule plugin maintainer. In the
  case that this projects was ported from another project, the MetaModule plugin
  maintainer might be different than the other project's maintainer. 
- The `MetaModuleDescription` field shows up on the plugins page on our
  website, and nowhere else.

There is a [detailed discussion about the `plugin-mm.json` file here](https://github.com/4ms/metamodule-plugin-sdk/blob/main/docs/plugin-mm-json.md)


## Graphics

Graphics are all PNG files, and must be in the `assets/` dir. In your info
file, you reference the path to PNGs, by using your brand slug instead of
`assets/`. So, if you plugin brand slug is `CoolBrand`, then you would load the
file `assets/faceplate.png` with `CoolBrand/faceplate.png`. 

See the `SimpleVCAInfo` class above for examples.

Faceplates must be 240px high, and must have a non-transparent background.
Other images can be any size and are allowed to use transparency.

## Build files

Then to build it, put this CMakeLists.txt in the same directory:

```cmake
cmake_minimum_required(VERSION 3.22)

if(NOT "${METAMODULE_SDK_DIR}" STREQUAL "")
    message("METAMODULE_SDK_DIR set by CMake variable ${METAMODULE_SDK_DIR}")
elseif (DEFINED ENV{METAMODULE_SDK_DIR})
    set(METAMODULE_SDK_DIR "$ENV{METAMODULE_SDK_DIR}")
    message("METAMODULE_SDK_DIR set by environment variable ${METAMODULE_SDK_DIR}")
else()
    set(METAMODULE_SDK_DIR "${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk")
    message("METAMODULE_SDK_DIR set to default: ${METAMODULE_SDK_DIR}")
endif()

include(${METAMODULE_SDK_DIR}/plugin.cmake)

project(NativeExample 
    VERSION 0.1 
    DESCRIPTION "Example Native Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(NativeExample STATIC)
target_include_directories(NativeExample PRIVATE . )

target_sources(NativeExample PRIVATE
    plugin.cc
)

if("${INSTALL_DIR}" STREQUAL "")
    set(INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins)
endif()

# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      NativeExample
    PLUGIN_NAME     NativeExample
    PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/plugin.json           # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${INSTALL_DIR}  # Dir where plugin .mmplugin file should be put
)
```

This is mostly boilerplate which you should copy into every project. The only
places you will customize for each project are the name ("NativeExample" in
`add_library()`, `project()`, and `create_plugin()`), the list of source files
("plugin.cc" in `target_sources()`), and possibly adding directories to
`target_include_directories()` and adding build flags in
`target_compile_options()`.

## Building

To build, first configure it:

```
cmake --fresh -B build
```

Then build:

```
cmake --build build
```

Look in `metamodule-plugins/` for your `.mmplugin` file.

If you want to specify the path to the SDK (which is what that boilerplate
at the top of CMakeLists is all about), do this when configuring:

```
cmake --fresh -B build -DMETAMODULE_SDK_DIR=path/to/metamodule-plugin-sdk
```

You also can set that as an environment variable if you get tired of typing it
for each project (i.e. put `export METAMODULE_SDK_DIR=path/to/metamodule-plugin-sdk`
in your .bashrc or .zshrc)

If you want to use a particular arm-gcc toolchain, add
`-DTOOOLCHAIN_BASE_DIR=path/to/arm/bin` to the configuration command.

