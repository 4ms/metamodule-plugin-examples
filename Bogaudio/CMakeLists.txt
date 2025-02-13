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

project(BogaudioModules 
    VERSION 0.1 
    DESCRIPTION "Bogaudio Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(BogaudioModules STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/BogaudioModules)


file(GLOB DSP_SOURCES 
    ${SOURCE_DIR}/src/dsp/*cpp 
    ${SOURCE_DIR}/src/dsp/filters/*cpp
)

target_sources(BogaudioModules PRIVATE
    ${SOURCE_DIR}/src/metamodule-plugin.cpp

    ${SOURCE_DIR}/src/AD.cpp
    ${SOURCE_DIR}/src/ADSR.cpp
    ${SOURCE_DIR}/src/AMRM.cpp
    ${SOURCE_DIR}/src/ASR.cpp
    ${SOURCE_DIR}/src/Additator.cpp
    ${SOURCE_DIR}/src/AddrSeq.cpp
    ${SOURCE_DIR}/src/AddrSeqX.cpp
    ${SOURCE_DIR}/src/Chirp.cpp
    ${SOURCE_DIR}/src/Clpr.cpp
    ${SOURCE_DIR}/src/CmpDist.cpp
    ${SOURCE_DIR}/src/DADSRH.cpp
    ${SOURCE_DIR}/src/DADSRHPlus.cpp
    ${SOURCE_DIR}/src/DGate.cpp
    ${SOURCE_DIR}/src/EQ.cpp
    ${SOURCE_DIR}/src/EQS.cpp
    ${SOURCE_DIR}/src/Edge.cpp
    ${SOURCE_DIR}/src/EightFO.cpp
    ${SOURCE_DIR}/src/EightOne.cpp
    ${SOURCE_DIR}/src/FFB.cpp
    ${SOURCE_DIR}/src/FMOp.cpp
    ${SOURCE_DIR}/src/Follow.cpp
    ${SOURCE_DIR}/src/FourFO.cpp
    ${SOURCE_DIR}/src/LFO.cpp
    ${SOURCE_DIR}/src/LLFO.cpp
    ${SOURCE_DIR}/src/LLPG.cpp
    ${SOURCE_DIR}/src/LPG.cpp
    ${SOURCE_DIR}/src/LVCF.cpp
    ${SOURCE_DIR}/src/LVCO.cpp
    ${SOURCE_DIR}/src/Lmtr.cpp
    ${SOURCE_DIR}/src/Matrix18.cpp
    ${SOURCE_DIR}/src/Matrix44.cpp
    ${SOURCE_DIR}/src/Matrix44Cvm.cpp
    ${SOURCE_DIR}/src/Matrix81.cpp
    ${SOURCE_DIR}/src/Matrix88.cpp
    ${SOURCE_DIR}/src/Matrix88Cv.cpp
    ${SOURCE_DIR}/src/Matrix88M.cpp
    ${SOURCE_DIR}/src/MegaGate.cpp
    ${SOURCE_DIR}/src/Mix1.cpp
    ${SOURCE_DIR}/src/Mix2.cpp
    ${SOURCE_DIR}/src/Mix4.cpp
    ${SOURCE_DIR}/src/Mix4x.cpp
    ${SOURCE_DIR}/src/Mix8.cpp
    ${SOURCE_DIR}/src/Mix8x.cpp
    ${SOURCE_DIR}/src/Mumix.cpp
    ${SOURCE_DIR}/src/Mute8.cpp
    ${SOURCE_DIR}/src/Noise.cpp
    ${SOURCE_DIR}/src/Nsgt.cpp
    ${SOURCE_DIR}/src/OneEight.cpp
    ${SOURCE_DIR}/src/PEQ.cpp
    ${SOURCE_DIR}/src/PEQ14.cpp
    ${SOURCE_DIR}/src/PEQ14XF.cpp
    ${SOURCE_DIR}/src/PEQ14XR.cpp
    ${SOURCE_DIR}/src/PEQ14XV.cpp
    ${SOURCE_DIR}/src/PEQ6.cpp
    ${SOURCE_DIR}/src/PEQ6XF.cpp
    ${SOURCE_DIR}/src/Pan.cpp
    ${SOURCE_DIR}/src/Pgmr.cpp
    ${SOURCE_DIR}/src/PgmrX.cpp
    ${SOURCE_DIR}/src/Pressor.cpp
    ${SOURCE_DIR}/src/Pulse.cpp
    ${SOURCE_DIR}/src/RGate.cpp
    ${SOURCE_DIR}/src/SampleHold.cpp
    ${SOURCE_DIR}/src/Shaper.cpp
    ${SOURCE_DIR}/src/ShaperPlus.cpp
    ${SOURCE_DIR}/src/Sine.cpp
    ${SOURCE_DIR}/src/Switch1616.cpp
    ${SOURCE_DIR}/src/Switch18.cpp
    ${SOURCE_DIR}/src/Switch44.cpp
    ${SOURCE_DIR}/src/Switch81.cpp
    ${SOURCE_DIR}/src/Switch88.cpp
    ${SOURCE_DIR}/src/UMix.cpp
    ${SOURCE_DIR}/src/VCA.cpp
    ${SOURCE_DIR}/src/VCAmp.cpp
    ${SOURCE_DIR}/src/VCF.cpp
    ${SOURCE_DIR}/src/VCM.cpp
    ${SOURCE_DIR}/src/VCO.cpp
    ${SOURCE_DIR}/src/VU.cpp
    ${SOURCE_DIR}/src/Velo.cpp
    ${SOURCE_DIR}/src/Vish.cpp
    ${SOURCE_DIR}/src/Walk.cpp
    ${SOURCE_DIR}/src/Walk2.cpp
    ${SOURCE_DIR}/src/XCO.cpp
    ${SOURCE_DIR}/src/XFade.cpp
    # Needs std::condition_variable
    # ${SOURCE_DIR}/src/Analyzer.cpp
    # ${SOURCE_DIR}/src/AnalyzerXL.cpp
    # ${SOURCE_DIR}/src/Ranalyzer.cpp

    ${SOURCE_DIR}/src/Arp.cpp
    ${SOURCE_DIR}/src/Assign.cpp
    ${SOURCE_DIR}/src/Bool.cpp
    ${SOURCE_DIR}/src/CVD.cpp
    ${SOURCE_DIR}/src/Cmp.cpp
    ${SOURCE_DIR}/src/Detune.cpp
    ${SOURCE_DIR}/src/FlipFlop.cpp
    ${SOURCE_DIR}/src/FourMan.cpp
    ${SOURCE_DIR}/src/Inv.cpp
    ${SOURCE_DIR}/src/Lgsw.cpp
    ${SOURCE_DIR}/src/Manual.cpp
    ${SOURCE_DIR}/src/Mono.cpp
    ${SOURCE_DIR}/src/Mult.cpp
    ${SOURCE_DIR}/src/Offset.cpp
    ${SOURCE_DIR}/src/PolyCon16.cpp
    ${SOURCE_DIR}/src/PolyCon8.cpp
    ${SOURCE_DIR}/src/PolyMult.cpp
    ${SOURCE_DIR}/src/PolyOff16.cpp
    ${SOURCE_DIR}/src/PolyOff8.cpp
    ${SOURCE_DIR}/src/Reftone.cpp
    ${SOURCE_DIR}/src/Slew.cpp
    ${SOURCE_DIR}/src/Stack.cpp
    ${SOURCE_DIR}/src/Sums.cpp
    ${SOURCE_DIR}/src/Switch.cpp
    ${SOURCE_DIR}/src/Unison.cpp

    # Helpers:
    ${SOURCE_DIR}/src/Pgmr_shared.cpp
    ${SOURCE_DIR}/src/addressable_sequence.cpp
    ${SOURCE_DIR}/src/dadsrh_core.cpp
    ${SOURCE_DIR}/src/disable_output_limit.cpp
    ${SOURCE_DIR}/src/follower_base.cpp
    ${SOURCE_DIR}/src/lfo_base.cpp
    ${SOURCE_DIR}/src/lpg_common.cpp
    ${SOURCE_DIR}/src/matrix_base.cpp
    ${SOURCE_DIR}/src/menu.cpp
    ${SOURCE_DIR}/src/mixer.cpp
    ${SOURCE_DIR}/src/mixer_expander.cpp
    ${SOURCE_DIR}/src/module.cpp
    ${SOURCE_DIR}/src/output_range.cpp
    ${SOURCE_DIR}/src/param_quantities.cpp
    ${SOURCE_DIR}/src/parametric_eq.cpp
    ${SOURCE_DIR}/src/poly_channels.cpp
    ${SOURCE_DIR}/src/rack_overrides.cpp
    ${SOURCE_DIR}/src/save_latch_to_patch.cpp
    ${SOURCE_DIR}/src/shaper_core.cpp
    ${SOURCE_DIR}/src/skins.cpp
    ${SOURCE_DIR}/src/slew_common.cpp
    ${SOURCE_DIR}/src/trigger_on_load.cpp
    ${SOURCE_DIR}/src/utils.cpp
    ${SOURCE_DIR}/src/vco_base.cpp
    ${SOURCE_DIR}/src/widgets.cpp
    # ${SOURCE_DIR}/src/analyzer_base.cpp #needs std::condition_variable

    ${DSP_SOURCES}
)

# Add includes and compile options for source repo
target_include_directories(BogaudioModules 
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}
    ${SOURCE_DIR}/src
    ${SOURCE_DIR}/src/dsp
    ${SOURCE_DIR}/lib
)

target_compile_options(BogaudioModules PRIVATE 
$<$<COMPILE_LANGUAGE:CXX>:-include src/mutex-stub.hh>
$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
)

create_plugin(
    SOURCE_LIB      BogaudioModules                   # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Bogaudio                          # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json         # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets  # Path to the assets/ dir containing the PNGs
    DESTINATION     ${INSTALL_DIR}                    # Dir where plugin .mmplugin file should be put
)

