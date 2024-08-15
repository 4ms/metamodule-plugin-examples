cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(VenomMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Venom Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(Venom STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/VenomModules)

target_sources(Venom
    PRIVATE

    ${SOURCE_DIR}/src/AuxClone.cpp
    ${SOURCE_DIR}/src/BenjolinOsc.cpp
    ${SOURCE_DIR}/src/BernoulliSwitch.cpp
    ${SOURCE_DIR}/src/BernoulliSwitchExpander.cpp
    ${SOURCE_DIR}/src/CloneMerge.cpp
    ${SOURCE_DIR}/src/HQ.cpp
    ${SOURCE_DIR}/src/Knob5.cpp
    ${SOURCE_DIR}/src/LinearBeats.cpp
    ${SOURCE_DIR}/src/LinearBeatsExpander.cpp
    ${SOURCE_DIR}/src/Logic.cpp
    ${SOURCE_DIR}/src/Mix4.cpp
    ${SOURCE_DIR}/src/Mix4Stereo.cpp
    ${SOURCE_DIR}/src/MixFade.cpp
    ${SOURCE_DIR}/src/MixFade2.cpp
    ${SOURCE_DIR}/src/MixMute.cpp
    ${SOURCE_DIR}/src/MixOffset.cpp
    ${SOURCE_DIR}/src/MixPan.cpp
    ${SOURCE_DIR}/src/MixSend.cpp
    ${SOURCE_DIR}/src/MixSolo.cpp
    ${SOURCE_DIR}/src/MultiMerge.cpp
    ${SOURCE_DIR}/src/MultiSplit.cpp
    #${SOURCE_DIR}/src/NORS-IQ.cpp
    ${SOURCE_DIR}/src/NORSIQChord2Scale.cpp
    ${SOURCE_DIR}/src/PolyClone.cpp
    ${SOURCE_DIR}/src/PolyOffset.cpp
    ${SOURCE_DIR}/src/PolySHASR.cpp
    ${SOURCE_DIR}/src/PolyScale.cpp
    ${SOURCE_DIR}/src/PolyUnison.cpp
    ${SOURCE_DIR}/src/Push5.cpp
    ${SOURCE_DIR}/src/Recurse.cpp
    ${SOURCE_DIR}/src/RecurseStereo.cpp
    ${SOURCE_DIR}/src/Reformation.cpp
    ${SOURCE_DIR}/src/RhythmExplorer.cpp
    ${SOURCE_DIR}/src/ShapedVCA.cpp
    ${SOURCE_DIR}/src/VCAMix4.cpp
    ${SOURCE_DIR}/src/VCAMix4Stereo.cpp
    ${SOURCE_DIR}/src/VenomBlank.cpp
    #${SOURCE_DIR}/src/WidgetMenuExtender.cpp
    ${SOURCE_DIR}/src/WinComp.cpp

	# Note that we build our own plugin.cpp, not the one in VenomModules/src/
    # This is because we want to exclude the above modules from the plugin
    plugin.cpp 
)

target_include_directories(Venom PRIVATE 
	# ${SOURCE_DIR}/src 
	# ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(Venom 
	PRIVATE 
	-Wno-deprecated # for warnings about deprecated use of = in lambda capture (should use explicit `this`)
	-Wno-nonnull  # for warnings about this pointer being null (MetaModule does not support context menus)
)

set_property(TARGET Venom PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      Venom                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Venom                  # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json 
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
