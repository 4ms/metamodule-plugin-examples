cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(ChowDSPMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "ChowDSP Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(ChowDSP STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ChowDSP-VCV)

target_sources(ChowDSP
    PRIVATE

    # Chorus crashes when trying to run. Haven't looked into it.
    # ${SOURCE_DIR}/src/ChowChorus/BBDDelayLine.cpp
    # ${SOURCE_DIR}/src/ChowChorus/ChowChorus.cpp

    ${SOURCE_DIR}/src/ChowDer/ChowDer.cpp
    ${SOURCE_DIR}/src/ChowDer/BaxandallEQ.cpp
    ${SOURCE_DIR}/src/ChowModal/ChowModal.cpp
    ${SOURCE_DIR}/src/ChowPhaser/ChowPhaserFB.cpp
    ${SOURCE_DIR}/src/ChowPhaser/ChowPhaserMod.cpp
    ${SOURCE_DIR}/src/ChowPulse/ChowPulse.cpp

    # RNN compiles but crashes when trying to run modul: haven't looked into why
    # ${SOURCE_DIR}/src/ChowRNN/ChowRNN.cpp
    # ${SOURCE_DIR}/src/ChowRNN/LayerJSON.cpp
    # ${SOURCE_DIR}/src/ChowRNN/LayerRandomiser.cpp

    ${SOURCE_DIR}/src/ChowTape/compression/ChowTapeCompression.cpp
    ${SOURCE_DIR}/src/ChowTape/degrade/ChowTapeChew.cpp
    ${SOURCE_DIR}/src/ChowTape/degrade/ChowTapeDegrade.cpp
    ${SOURCE_DIR}/src/ChowTape/loss/ChowTapeLoss.cpp
    ${SOURCE_DIR}/src/ChowTape/tape/ChowTape.cpp
    ${SOURCE_DIR}/src/ChowTape/tape/HysteresisProcessing.cpp
    ${SOURCE_DIR}/src/Warp/Warp.cpp
    ${SOURCE_DIR}/src/Warp/WarpFilter.cpp
    ${SOURCE_DIR}/src/Werner/GenSVF.cpp
    ${SOURCE_DIR}/src/Werner/Werner.cpp

    ${SOURCE_DIR}/src/shared/SineWave.cpp
    ${SOURCE_DIR}/src/shared/delay_line.cpp

    # r8lib has heavy use of iostream (cerr), won't compile
    # ${SOURCE_DIR}/src/ChowFDN/ChowFDN.cpp
    # ${SOURCE_DIR}/src/ChowFDN/fdn.cpp
    # ${SOURCE_DIR}/lib/r8lib/r8lib.cpp
    # ${SOURCE_DIR}/lib/r8lib/matrix_exponential.cpp

    # Note that we build our own plugin.cpp, not the one in ChowDSP/src/
    plugin.cpp 
)

target_include_directories(ChowDSP PRIVATE 
    ${SOURCE_DIR}/src
    .
    ${SOURCE_DIR}/lib
    ${SOURCE_DIR}/lib/chowdsp_utils/modules/chowdsp_dsp/WDF
)

target_compile_definitions(ChowDSP PRIVATE USE_EIGEN)

target_compile_options(ChowDSP PRIVATE 
    -fexceptions
    -Wno-deprecated-enum-enum-conversion
)

set_property(TARGET ChowDSP PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      ChowDSP                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     ChowDSP                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/ChowDSP # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
