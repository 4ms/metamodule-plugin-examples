# Example MetaModule Plugins using the SDK

Here are examples of VCV Rack plugins being compiled as MetaModule plugins, using the MetaModule Plugin SDK.

There are also two native plugins: Airwindows, and NativeExample.

The SDK contains a VCV Rack SDK wrapper, whose goal is to make it as easy as
possible to compile existing VCV Rack plugin source code and produce a
MetaModule-compatible plugin. The SDK also supports "native" plugins, which are
not based on VCV Rack plugins and just use the MetaModule core interface
directly.

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

To build all the plugins (brands) -- warning: this takes a while! See below for how to build just one brand.

```
cmake --fresh -B build -G Ninja
cmake --build build
```

Building will create a `.mmplugin` file for each brand and put it in the
`metamodule-plugins` directory in the top-level of the repo. 

If you want to just build one brand:

```
# To configure the build:
cd Bogaudio
cmake --fresh -B build -G Ninja

# To build or re-build:
cmake --build build
```

This will install the plugin project's directory (`Bogaudio/metamodule-plugins/` in this case).

If you want to use a different installation of the plugin sdk, you can pass it to cmake:

```
# To configure the build:
cd Bogaudio
cmake --fresh -B build -G Ninja -DMETAMODULE_SDK_DIR=/path/to/sdk

# To build or re-build:
cmake --build build
```

## Installing a plugin

After building, copy the top-level metamodule-plugins dir to an SD Card or USB
drive.

```
cd ..  # Root of this repo
cp -R metamodule-plugins /Volumes/SDCard-or-USBDrive/

```


Make sure the metamodule-plugins/ dir itself resides in the root-level of
the SD Card. That is, copy the entire folder, not just the contents.

Then insert the SD Card or USB drive into your MetaModule. Follow the
MetaModule docs to load the plugins.


## SDK Documentation

The MetaModule plugin SDK is documented in the SDK repo:
[MetaModule plugin SDK README](https://github.com/4ms/metamodule-plugin-sdk/tree/main?tab=readme-ov-file#metamodule-plugin-sdk)

The docs include such topics as:
- Creating a MetaModule plugin from an existing VCV Rack plugin
- Creating a native plugin
- Text screens and displays
- Graphics guide
- Plugin format
- Limitations
- Tips

