# Example MetaModule Plugins using the SDK

Here are examples of VCV Rack plugins that are compiled as MetaModule plugins, using the MetaModule Plugin SDK.

The goal of the SDK is to make it as easy as possible to compile existing VCV Rack plugin source code 
and produce a MetaModule-compatible plugin.

Some of these plugins are using the original, unaltered Rack source code. Some are using a fork or branch of the code with
(minor) changes made in order to work as a MetaModule plugin.

In some cases, certain modules are omitted from the MetaModule plugin.

Note that all of these plugins are already built into MetaModule firmware. So loading the plugins into stock MetaModule
firmware will have no effect. The goal of this is to merely demonstrate how plugins can be built.

## Building the examples

To use, clone this repo and make sure to clone the submodules:

```
git clone https://github.com/4ms/metamodule-plugin-examples
cd metamodule-plugin-examples
git submodule update --init --recursive
```

Then, build any/all of the brands you are interested in:

```
cd Befaco
cmake -B build -G Ninja
cmake --build build

cd ../AudibleInstruments
cmake -B build -G Ninja
cmake --build build

# etc. for each brand
```

Building will put the build artifacts into a directory called `metamodule-plugins` in the top-level directory of the repo.
Inside this will be a subdirectory for each brand you built. Inside each subdirectory is a shared object (.so) file, which
is the plugin. Also there will be all the PNG files (graphical assets) needed.

## Building your own plugin


To build your existing VCV Rack plugin code as a MetaModule plugin:

1. Create and enter a new directory: MyPlugin
2. Either add your VCV Rack plugin source code as a submodule inside this dir (like the examples do), or
   take note of where on your computer the source code resides (you'll need to enter that path into your CMakeLists file)
3. Add a CMakeLists.txt file. Use the example CMakeLists files as a template. 
4. Add your sources and any compile flags needed, using the example CMakeLists as a guide.
5. Copy the contents of your VCV Rack plugin's `res/` dir to an `assets/` dir inside `MyPlugin/`.
6. Convert all SVG files in the asset dir to 47 DPI PNGs (more details on this below). Keep the same file names and directory layout. Remove the source SVG files
7. Add any other files you need to make your plugin build. See the example projects, for instance, most of them have their own plugin.cpp file to omit certain modules.
8. Build as done above.


## Installing a plugin

After building, copy the top-level metamodule-plugins dir to an SD Card or USB drive.

```
cd ..
cp -R metamodule-plugins/ /Volumes/SDCard-or-USBDrive/

```
Make sure the metamodule-plugins/ dir itself resides in the root-level of the SD Card. That is, copy the entire folder, not just the contents.

Then insert the SD Card or USB drive into your MetaModule. Follow the MetaModule docs to load the plugins.


## Images

TODO
