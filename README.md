# Example projects for MetaModule Plugin SDK

```
cd Befaco
cmake -B build -G Ninja
cmake --build build

cd ../AudibleInstruments
cmake -B build -G Ninja
cmake --build build

# etc. for each brand

cd ..
cp -R metamodule-plugins/ /Volumes/SDCard-or-USBDrive/

```

Then insert the SD Card or USB drive into your MetaModule. Follow the MetaModule docs to load the plugins.
