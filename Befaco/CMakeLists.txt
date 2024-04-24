cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(BefacoMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Befaco Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(Befaco STATIC)

# convenient variable pointing to the VCV Rack repo
set(BEFACO_DIR ${CMAKE_CURRENT_LIST_DIR}/Befaco)

target_sources(Befaco
    PRIVATE
    ${BEFACO_DIR}/src/EvenVCO.cpp
    ${BEFACO_DIR}/src/DualAtenuverter.cpp
    ${BEFACO_DIR}/src/SpringReverb.cpp
    ${BEFACO_DIR}/src/ABC.cpp
    ${BEFACO_DIR}/src/ADSR.cpp
    ${BEFACO_DIR}/src/ChoppingKinky.cpp
    ${BEFACO_DIR}/src/HexmixVCA.cpp
    ${BEFACO_DIR}/src/Kickall.cpp
    ${BEFACO_DIR}/src/Mixer.cpp
    ${BEFACO_DIR}/src/Morphader.cpp
    ${BEFACO_DIR}/src/MotionMTR.cpp
    ${BEFACO_DIR}/src/Percall.cpp
    ${BEFACO_DIR}/src/PonyVCO.cpp
    ${BEFACO_DIR}/src/Rampage.cpp
    ${BEFACO_DIR}/src/STMix.cpp
    ${BEFACO_DIR}/src/SamplingModulator.cpp
    ${BEFACO_DIR}/src/SlewLimiter.cpp
    ${BEFACO_DIR}/src/StereoStrip.cpp
    # Note we do not support:
    # Muxlicer, Mex, NoisePlethora

    # Note that we build our own plugin.cpp, not the one in Befaco/src/
    # This is because we want to exclude the above modules from the plugin
    plugin.cpp 
)

target_include_directories(Befaco PRIVATE ${BEFACO_DIR}/src .)

target_compile_options(Befaco PRIVATE -Wno-double-promotion $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>)

set_property(TARGET Befaco PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      Befaco                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Befaco                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Befaco # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
