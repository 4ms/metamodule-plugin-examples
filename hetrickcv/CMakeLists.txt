cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(hetrickcvMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "hetrickcv Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(HetrickCV STATIC)

set(HETRICKCV_DIR ${CMAKE_CURRENT_LIST_DIR}/hetrickcv)

target_sources(HetrickCV
    PRIVATE
    ${HETRICKCV_DIR}/src/ASR.cpp
    ${HETRICKCV_DIR}/src/AnalogToDigital.cpp
    ${HETRICKCV_DIR}/src/BinaryGate.cpp
    ${HETRICKCV_DIR}/src/BinaryNoise.cpp
    ${HETRICKCV_DIR}/src/Bitshift.cpp
    ${HETRICKCV_DIR}/src/Boolean3.cpp
    ${HETRICKCV_DIR}/src/Chaos1Op.cpp
    ${HETRICKCV_DIR}/src/Chaos2Op.cpp
    ${HETRICKCV_DIR}/src/Chaos3Op.cpp
    ${HETRICKCV_DIR}/src/ChaoticAttractors.cpp
    ${HETRICKCV_DIR}/src/ClockedNoise.cpp
    ${HETRICKCV_DIR}/src/Contrast.cpp
    ${HETRICKCV_DIR}/src/Crackle.cpp
    ${HETRICKCV_DIR}/src/DigitalToAnalog.cpp
    ${HETRICKCV_DIR}/src/Dust.cpp
    ${HETRICKCV_DIR}/src/Exponent.cpp
    ${HETRICKCV_DIR}/src/FBSineChaos.cpp
    ${HETRICKCV_DIR}/src/FlipFlop.cpp
    ${HETRICKCV_DIR}/src/FlipPan.cpp
    ${HETRICKCV_DIR}/src/GateDelay.cpp
    ${HETRICKCV_DIR}/src/GateJunction.cpp
    ${HETRICKCV_DIR}/src/GateJunctionExp.cpp
    ${HETRICKCV_DIR}/src/Gingerbread.cpp
    ${HETRICKCV_DIR}/src/LogicCombine.cpp
    ${HETRICKCV_DIR}/src/MidSide.cpp
    ${HETRICKCV_DIR}/src/MinMax.cpp
    ${HETRICKCV_DIR}/src/PhaseDrivenSequencer.cpp
    ${HETRICKCV_DIR}/src/PhaseDrivenSequencer32.cpp
    ${HETRICKCV_DIR}/src/PhasorAnalyzer.cpp
    ${HETRICKCV_DIR}/src/PhasorBurstGen.cpp
    ${HETRICKCV_DIR}/src/PhasorDivMult.cpp
    ${HETRICKCV_DIR}/src/PhasorEuclidean.cpp
    ${HETRICKCV_DIR}/src/PhasorGates.cpp
    ${HETRICKCV_DIR}/src/PhasorGates32.cpp
    ${HETRICKCV_DIR}/src/PhasorGates64.cpp
    ${HETRICKCV_DIR}/src/PhasorGen.cpp
    ${HETRICKCV_DIR}/src/PhasorGeometry.cpp
    ${HETRICKCV_DIR}/src/PhasorHumanizer.cpp
    ${HETRICKCV_DIR}/src/PhasorOctature.cpp
    ${HETRICKCV_DIR}/src/PhasorQuadrature.cpp
    ${HETRICKCV_DIR}/src/PhasorRandom.cpp
    ${HETRICKCV_DIR}/src/PhasorRanger.cpp
    ${HETRICKCV_DIR}/src/PhasorReset.cpp
    ${HETRICKCV_DIR}/src/PhasorRhythmGroup.cpp
    ${HETRICKCV_DIR}/src/PhasorShape.cpp
    ${HETRICKCV_DIR}/src/PhasorShift.cpp
    ${HETRICKCV_DIR}/src/PhasorStutter.cpp
    ${HETRICKCV_DIR}/src/PhasorSubstepShape.cpp
    ${HETRICKCV_DIR}/src/PhasorSwing.cpp
    ${HETRICKCV_DIR}/src/PhasorTimetable.cpp
    ${HETRICKCV_DIR}/src/PhasorToClock.cpp
    ${HETRICKCV_DIR}/src/PhasorToLFO.cpp
    ${HETRICKCV_DIR}/src/PhasorToWaveforms.cpp
    ${HETRICKCV_DIR}/src/XYToPolar.cpp
    ${HETRICKCV_DIR}/src/Probability.cpp
    ${HETRICKCV_DIR}/src/Scanner.cpp
    ${HETRICKCV_DIR}/src/2To4.cpp
    ${HETRICKCV_DIR}/src/VectorMix.cpp
    ${HETRICKCV_DIR}/src/Waveshaper.cpp

    ${HETRICKCV_DIR}/src/HetrickUtilities.cpp
    ${HETRICKCV_DIR}/Gamma/src/arr.cpp
    ${HETRICKCV_DIR}/Gamma/src/DFT.cpp
    ${HETRICKCV_DIR}/Gamma/src/Domain.cpp
    ${HETRICKCV_DIR}/Gamma/src/FFT_fftpack.cpp
    ${HETRICKCV_DIR}/Gamma/src/fftpack++1.cpp
    ${HETRICKCV_DIR}/Gamma/src/fftpack++2.cpp
    ${HETRICKCV_DIR}/Gamma/src/scl.cpp

    # We do not support:
    # BlankPanel, Comparator, DataCompander, Delta, PhasorMixer, RandomGates, Rotator, Rungler

    # Here notice that we build our own HetrickCV.cpp, not the one in hetrickcv/src/
    # This is because we want to exclude the above modules from the plugin
    HetrickCV.cpp
)

file(GLOB DSP_SOURCES
    ${HETRICKCV_DIR}/src/DSP/*.cpp
    ${HETRICKCV_DIR}/src/DSP/Phasors/*.cpp
)
target_sources(HetrickCV PRIVATE ${DSP_SOURCES})

target_include_directories(HetrickCV PRIVATE ${HETRICKCV_DIR}/Gamma ${HETRICKCV_DIR}/src)

set_property(TARGET HetrickCV PROPERTY CXX_STANDARD 20)

target_compile_options(HetrickCV
    PRIVATE 
    # Fixes for warnings with Gamma:
    -Wno-misleading-indentation
    -Wno-unused-but-set-variable
    -Wno-unused-function
    # Fixes for warnings with DSP and main source:
    -Wno-unused-variable
)

target_sources(HetrickCV PRIVATE ${CMAKE_CURRENT_LIST_DIR}/HetrickCV.cpp)

#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      HetrickCV                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     hetrickcv                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/hetrickcv # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
