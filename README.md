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

To build all the plugins (brands): (takes a while!)

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


## Creating a MetaModule plugin from an existing VCV Rack plugin

Read the documentation in the plugin-sdk repo: [Basic Example for Converting a Rack Plugin](https://github.com/4ms/metamodule-plugin-sdk/tree/main?tab=readme-ov-file#basic-example-for-converting-a-rack-plugin)


## Creating a native plugin

Plugins do not need to be based on VCV Rack. For examples, see NativeExample
and Airwindows in this repo.

Read the full documentation in the plugin-sdk: [Native Plugins](https://github.com/4ms/metamodule-plugin-sdk/tree/main/docs/native-plugin.md)


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

See documentation in the plugin SDK: [Text Displays](https://github.com/4ms/metamodule-plugin-sdk/tree/main/docs/text-displays.md)


## Images

See documentation in the plugin SDK: [Graphics](https://github.com/4ms/metamodule-plugin-sdk/tree/main/docs/graphics.md)

