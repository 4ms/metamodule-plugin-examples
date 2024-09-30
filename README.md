# Example MetaModule Plugins using the SDK

Here are examples of mostly VCV Rack plugins being compiled as MetaModule plugins, using the MetaModule Plugin SDK.

The goal of the SDK is to make it as easy as possible to compile existing VCV Rack plugin source code 
and produce a MetaModule-compatible plugin. The SDK also supports "native" plugins, which are not based 
on VCV Rack plugins (read below).

Some of these plugins are using the original, unaltered Rack source code. Some are using a fork or branch of the code with
(minor) changes made in order to work as a MetaModule plugin.

In some cases, certain modules are omitted from the MetaModule plugin.

## Requirements

  - cmake v3.24 or later
  - ninja (not required if you configure cmake to use a different generator) 
  - arm-none-eabi-gcc toolchain 12.2 or 12.3
      - Download here: https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads
          - Make sure you get the package for your host computer that ends in `arm-none-eabi`
  - python 3.6 or later

Hints:
  - Make sure `arm-none-eabi-gcc` is on your PATH (this is the "bin" folder in the
`arm-non-eabi` distribution).
  - For Windows, The PATH that `arm-none-eabi` is installed to *must not* contain
any spaces. By default, running the `arm-none-eabi` installer (the download
that ends in ".exe"), installs to "C:\Program Files (x86)\\..." which contains
spaces. It is much easier to download the file ending in ".zip", which allows
you to place the binaries wherever you want. As an example, you could unzip the
files to "C:\arm-none-eabi" or similar.


## Building the examples

To use, clone this repo and make sure to clone the submodules:

```
git clone https://github.com/4ms/metamodule-plugin-examples
cd metamodule-plugin-examples
git submodule update --init --recursive
```

To build all the plugins (brands):

```
cmake -B build -G Ninja
cmake --build build
```

Building will put the build artifacts into a directory called
`metamodule-plugins` in the top-level directory of the repo. Inside this will
be a subdirectory for each brand you built. Inside each subdirectory is a
shared object (.so) file, which is the plugin. Also there will be all the PNG
files (graphical assets) needed.

If you want to just build one brand:

```
cd Bogaudio
cmake -B build -G Ninja
cmake --build build
```

This will also install the plugin in the top-level `metamodule-plugins` directory.


## Building a MetaModule plugin from an existing VCV Rack plugin

To build your existing VCV Rack plugin as a MetaModule plugin:

1. Create and enter a new directory: MyPlugin
2. Either add your VCV Rack plugin source code as a submodule inside this dir
   (like the examples do), or take note of where on your computer the source
   code resides (you'll need to enter that path into your CMakeLists file)
3. Add a CMakeLists.txt file. Use the example CMakeLists files as a template. 
4. Add your sources and any compile flags needed, using the example CMakeLists
   as a guide.
5. Copy the contents of your VCV Rack plugin's `res/` dir to an `assets/` dir
   inside `MyPlugin/`.
6. Convert all SVG files in the asset dir to 47 DPI PNGs (more details on this
   below). Keep the same file names and directory layout. Remove the source SVG
   files
7. Add any other files you need to make your plugin build. See the example
   projects, for instance, most of them have their own plugin.cpp file to omit
   certain modules.
8. Build as done above.


## Native plugins

Plugins do not need to be based on VCV Rack. For examples, see NativeExample
and Airwindows.

At minimum, a plugin must define an init() function, but there is nothing else
required. 

- When a plugin is loaded, first all the assets are copied to the internal RAM
  drive into a subdirectory.

- Next, the `.so` file is parsed (as an elf file) and all dynamic relocations are performed. If there are unresolved symbols, they are reported and it
  aborts.

- Next, the global static constructors are called

- Finally, the init() function is called. Both `init()` and
  `init(rack::Plugin::plugin *)` are searched, with the latter taking
  precedence.

A plugin's job is to intialize plugin-wide data (if any) and register its
modules. This is usually done in init() but also can be done in the global
constructors.

In a typical VCV Rack plugin, modules are registered with calls to
`p->addModel(modelName)` in `init(plugin*)`. In the more general case, modules
can be registered using the function `register_module()`, declared in
`metamodule-core-interface` in `CoreModules/register_module.hh`:

```c++
using CreateModuleFunc = std::function<std::unique_ptr<CoreProcessor>()>;

bool register_module(std::string_view brand_name,
					 std::string_view typeslug,
					 CreateModuleFunc funcCreate,
					 ModuleInfoView const &info,
					 std::string_view faceplate_filename);
```

The `brand_name` and `typeslug` are the plugin name and the module name. These 
must match what's present in VCV Rack if you want your users to be able to create
patches in VCV Rack using your modules.

The full path to the faceplate is specified in the last parameter.

`ModuleInfoView const &info` is a view into the module's elements (knobs, jacks, etc).
Since only a view is passed to the MetaModule core interface, the actual data
must live statically for the entire duration of the plugin. There are various ways to
store data statically:
- VCV plugins use global `Model` variables.
- The NativeExample project uses `static` variables in the module init function.
- The Airwindows project uses a global vector which allocates on the heap.

`funcCreate` is a factory function that returns a unique_ptr to a
`CoreProcessor` module. The `CoreProcessor` class is a virtual base class which
is the base of all MetaModule modules:

```c++
class CoreProcessor {
public:
	virtual void update() = 0;
	virtual void set_samplerate(float sr) = 0;
	virtual void set_param(int param_id, float val) = 0;
	virtual void set_input(int input_id, float val) = 0;
	virtual float get_output(int output_id) const = 0;
	virtual float get_led_brightness(int led_id) { return 0; }
	virtual size_t get_display_text(int display_id, std::span<char> text) { return 0; }
	virtual void mark_all_inputs_unpatched() {}
	virtual void mark_input_unpatched(int input_id) {}
	virtual void mark_input_patched(int input_id) {}
	virtual void mark_all_outputs_unpatched() {}
	virtual void mark_output_unpatched(int output_id) {}
	virtual void mark_output_patched(int output_id) {}
	virtual void load_state(std::string_view state_data) {}
	virtual std::string save_state() { return ""; }
};
```

Putting it all together, the NativeExample plugin demonstrates how it works
with a very simple module that provies gain to an audio signal (with an LED to show the gain).

The method used in `simple_gain_elements.cc` to generate all the elements
(jacks, knob, etc), is just for this toy example. For large sets of modules you
would probably want to generate the X,Y positions and various values either at
runtime (using a grid perhaps), or with scripts. For the 4ms modules, we use a
python script to parse SVGs and generate a c++ header file with a constexpr
array of elements. 

One "gotcha" is that if the strings are not backed by static storage (that is,
they are dynamically generated on the stack or heap), then you will need to
provide the strings in some sort of static container. The reason is that
Element type and module registry only contain string_views.
See the Airwindows `module_creator.cc` for an example.


## Installing a plugin

After building, copy the top-level metamodule-plugins dir to an SD Card or USB
drive.

```
cd ..  # Root of this repo
cp -R metamodule-plugins/ /Volumes/SDCard-or-USBDrive/

```


Make sure the metamodule-plugins/ dir itself resides in the root-level of
the SD Card. That is, copy the entire folder, not just the contents.

Then insert the SD Card or USB drive into your MetaModule. Follow the
MetaModule docs to load the plugins.

## Text Screens (Displays)

Plugin API v1.3 supports screens on modules that display text only.

Plugins have control over the font and color.
To create a display using the VCV Rack interface, create a `MetaModule::VCVTextDisplay` object
(or a class that dervives from this). See OrangeLine and CountModula for several examples.

A brief example:
```c++
// Most VCV Modules have something like this already:
enum LightIds {
    SOMEVCVLIGHT1,
    SOMEVCVLIGHT2,
    NUM_LIGHTS
};

// Add this:
enum DisplayIds {
    MY_TEXT_DISPLAY = NUM_LIGHTS, // DisplayIds must not overlap with LightIds
    MY_NUMERIC_DISPLAY
};

// VCV Rack modules that have screens ususally define their own display widget class.
// To work on MM, this class needs to derive from VCVTextDisplay, which itself derives
// from rack::LightWidget.
// You could use an #ifdef or adjust your class to work as a LightWidget.
struct MyDisplay : MetaModule::VCVTextDisplay {
    //... nothing in here usually needs to change
};

struct MyModuleWidget : rack::ModuleWidget {
    MyModuleWidget() {
        //...
        // Something like this probably already exists
        // for the VCV Rack plugin:
        auto display = new MyDisplay;
        display->box = Vec(...);
        display->pos = Vec(...);

        // Add this to set the font and color for MetaModule
        display->font = "Default_12";            // see fonts.hh for all built-in fonts
        display->color = Colors565::Green;       // see cpputil/util/colors_565.hh
        display->firstLightId = MY_TEXT_DISPLAY; // must be a unique ID for each display and LIGHT
    }
};
```

To have the text drawn, you need to provide an overridden function in your Module class like this:
```c++
struct MyModule : rack::Module {
    //...

	size_t get_display_text(int led_id, std::span<char> text) override {
        // The GUI engine calls this function, giving it an LED Id that refers
        // to the display that we want the text for.
        // The function should populate the text parameter with characters to display,
        // and return the number of bytes written.

        // Here's one way to write chars to a display:
		if (led_id == MY_TEXT_DISPLAY) {
            // This is the text we want to display:
			std::string someText = myModuleGetSomeText();

            // Make sure we don't overrun the buffer:
			size_t chars_to_copy = std::min(someText.size(), text.length());

            // Copy chars from `someText` to `text`
            std::copy(someText.data(), someText.data() + chars_to_copy, text.begin());

		}

        // Here's a way to write numbers to a display:
        else if (led_id == MY_NUMERIC_DISPLAY) {
			int chars_written = snprintf(text.data(), text.size(), "%03d", someValue);
			return chars_written < 0 ? 0: chars_written;
        }

        // Returning 0 tells the engine not to update anything
		else 
            return 0;
	}
};
```

Notice that you specify a font with a string.
A list of built-in fonts is in `metamodule-plugin-sdk/fonts.hh`.

You can specify an exact color in a few ways:
```c++
display->Color = RGB565{(uint8_t)0xFF, 0x80, 0x40};
display->Color = RGB565{1.f, 0.5f, 0.2f}; //pretty much the same as above
display->Color = RGB565::Orange;
```

### Custom fonts

You can specify a custom font by passing in the path to the font like this:
```c++
    display->font = "PluginName/font_name.bin";
```

To generate `font_name.bin`, load a .ttf or .woff font file into the LVGL font conversion tool.
There is an online version of this at (https://lvgl.io/tools/fontconverter)[https://lvgl.io/tools/fontconverter].

For the settings:
- Name: by convention use FontName followed by an underscore and then the size: `FontName_14`
- Size: set the height in pixels (10 is about the smallest legible font size. 48 is about 25mm high on the virtual panel)
- Bpp: 4 bit-per-pixel
- Fallback: leave blank
- Output format: Binary
- Uncheck Font compression, Horizontal subpixel, and Try to use glyph color info
- Range: by default use `0x20-0x7f`, which is the normal ASCII chars. You are welcome to use any values you want here if you are displaying other characters/emojis/icons/etc
- Symbols: this is another way to input the characters to include

Click submit, and save the resulting .bin file in your assets/ dir:
```
MyPlugin/
 |___ assets/
      |___ my_font.bin
      |___ rad_panel.png
      |___ large_knob.png
      |___ ...
```

To access this font (my_font), you

## Images

The MetaModule uses PNGs for images. The DPI is about 47.4 DPI because Eurorack 
modules are 5.059 inches high, and MetaModule modules are 240px high (240/5.059=47.44).
PNGs with transparency can be used for components.

The CMakeLists file will copy all PNG assets from the `assets/` dir to the plugin dir.
Only one level of subdirectories is supported at this time (API v0.14.x).
For example, this is a typical way of structuring the assets:

```
assets/
    components/
        knob-blue.png
        knob-red.png
        ...
    faceplates/
        VCF.png
        VCO.png
        ...
```

You cannot have any more nested subdirectories that the above (that is, no `assets/components/extra-sub-dir/knob.png`)

The CMakeLists build will copy this directory to the metamodule-plugins dir like this:

```
metamodule-plugins/
    MyPluginBrand/
        MyPluginBrand.so
        components/
            knob-blue.png
            knob-red.png
            ...
        faceplates/
            VCF.png
            VCO.png
    OtherBrand/
        OtherBrand.so
        other_module.png
```

On plugin load, all files will be copied to the internal RAM Disk. Space is limited and shared amongst all plugins,
so make efforts to remove any unused files.

### Converting VCV Rack SVGs to PNGs
If you are converting a VCV Rack plugin, you need to convert the SVG assets to PNG format.

Typically all SVGs are kept in a `res/`
directory for VCV Rack plugins. For MetaModule plugins, the `res/` dir is
omitted, but otherwise the directory structure and file base names are kept the
same. Before building your plugin, convert all the SVGs to PNGs and put them
into the `assets/` dir in your plugin folder. This `assets/` dir is refered to
by CMakeLists in the call to `create_plugin()`, so if you want to use a
different directory, just change it there. The Cmake script will simply copy
the contents of the `assets/` dir to the plugin dir.

There is a helper script that can convert a directory of SVGs to PNGs:
`scripts/SvgToPng.py`. Running `scripts/SvgToPng.py -h` will display the help
with available options. The script requires that you have inkscape installed
and the `inkscape` executable on your PATH. Version 1.2.2 has been tested to
work.

You can use it to convert directories, one at a time (it does not recursively
scan sub-dirs):

``` 
cd MyPlugin

mkdir assets 
mkdir assets/panels 
mkdir assets/components

# Convert res/panels/*.svg ==>> assets/panels/*.png: 
../metamodule-plugin-sdk/scripts/SvgToPng.py --input MyPluginVCV/res/panels/ --output assets/panels

# Convert res/components/*.svg ==>> assets/components/*.png:
../metamodule-plugin-sdk/scripts/SvgToPng.py --input MyPluginVCV/res/components/ --output assets/components

```

The script is not sophisticated, and will try to figure out the SVG's DPI but
may get it wrong. If you need to, use the `--height=240` option when
converting faceplates to force them to be 240px. You can also specify this option
for component artwork if the script is making them the wrong size by default.

If you want to disable transparency, then add the `--white` option.

Sometimes, you may wish to not use the script at all and just generate your own
PNG files that are better suited for the low-resolution screen of the MetaModule.
This will produce the best results, but of course is time-consuming.

Certain special effects like shadows, subtle gradients, thin lines will not look
good on the MetaModule screen, so keep that in mind as you convert your artwork.

The screen is 240px x 320px, about 144 ppi. We use 16-bit color (RGB565).
Modules are displayed 240px high when viewed full-screen and 180px high when zoomed-out.
We may add future options to zoom out to 120px when zoomed-out.

### Special cases for Images

The MetaModule only uses a single image for a knob. On the other hand, VCV Rack sometimes
uses multiple SVG images for a knob.

For example, `rack::componentlibrary::Rogan` knobs have two `SvgWidget` members: `bg` and `fg`.
The class also derives from `SvgWidget` so there is a third SVG:

```c++
struct Rogan6PSWhite : Rogan {
	Rogan6PSWhite() {
		setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan6PSWhite.svg")));
		bg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan6PS_bg.svg")));
		fg->setSvg(Svg::load(asset::system("res/ComponentLibrary/Rogan6PSWhite_fg.svg")));
	}
};
```

To accomodate the MetaModule, the easiest thing to do is to just include the main image (`Rogan6PSWhite.png`)
and remove the `bg` and `fg` images. MetaModule will just ignore the missing images and use the one it found.
Visually, you may want to combine the `fg` and main SVGs into a single combined image, and then export that
as a PNG with the same name. That is, use Inkscape to place `Rogan6PSWhite_fg.svg` on top of `Rogan6PSWhite.svg`
and export this as `Rogan6PSWhite.png`, and making sure to not have any file named `Rogan6PS_bg.png` or `Rogan6PSWhite_fg.png`
in the assets dir.

There is a special-case: Rack component library and the Befaco VCV plugin (and probably other plugins) use 
the `BefacoTinyKnob` class to define a knob whose SVG is just a dot (white or black). The child `bg` SVG is the
knob body color. There is no `fg` SVG. In this case, you need to manually combine the two SVGs and save them as the
file name of the `bg` image. Also, the main image file (the dot) needs to be present in order to determine the size
of the widget for placement, although it's not drawn.

