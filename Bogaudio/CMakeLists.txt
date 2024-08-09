cmake_minimum_required(VERSION 3.22)
include(../metamodule-plugin-sdk/plugin.cmake)

project(BogaudioModules 
    VERSION 0.1 
    DESCRIPTION "Bogaudio Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(BogaudioModules STATIC)

# Add sources from the Rack source repo
set(SOURCEDIR ${CMAKE_CURRENT_LIST_DIR}/BogaudioModules)


file(GLOB DSP_SOURCES 
    ${SOURCEDIR}/src/dsp/*cpp 
    ${SOURCEDIR}/src/dsp/filters/*cpp
)

set(ENABLED_MODULE_SOURCES 
    ${SOURCEDIR}/src/Additator.cpp #missing widget (StatefulButton)
    ${SOURCEDIR}/src/FMOp.cpp
    ${SOURCEDIR}/src/Chirp.cpp
    ${SOURCEDIR}/src/LFO.cpp
    ${SOURCEDIR}/src/LLFO.cpp #missing widget (StatefulButton)
    ${SOURCEDIR}/src/FourFO.cpp
    ${SOURCEDIR}/src/EightFO.cpp
    ${SOURCEDIR}/src/LVCF.cpp #missing widget (StatefulButton)
    ${SOURCEDIR}/src/LVCO.cpp #missing widget (StatefulButton)
    ${SOURCEDIR}/src/Pulse.cpp
    ${SOURCEDIR}/src/Sine.cpp
    ${SOURCEDIR}/src/VCF.cpp
    ${SOURCEDIR}/src/VCO.cpp
    ${SOURCEDIR}/src/XCO.cpp
    ${SOURCEDIR}/src/FFB.cpp
    ${SOURCEDIR}/src/EQ.cpp
    ${SOURCEDIR}/src/EQS.cpp
    ${SOURCEDIR}/src/LPG.cpp
    ${SOURCEDIR}/src/LLPG.cpp
    ${SOURCEDIR}/src/MegaGate.cpp #missing widget (StatefulButton)
    ${SOURCEDIR}/src/PEQ.cpp
    ${SOURCEDIR}/src/DADSRH.cpp #missing widget (StatefulButton)
    ${SOURCEDIR}/src/DADSRHPlus.cpp #missing widget (StatefulButton)
    ${SOURCEDIR}/src/Shaper.cpp
    ${SOURCEDIR}/src/ShaperPlus.cpp
    ${SOURCEDIR}/src/AD.cpp
    ${SOURCEDIR}/src/ASR.cpp
    ${SOURCEDIR}/src/ADSR.cpp
    ${SOURCEDIR}/src/Vish.cpp
    ${SOURCEDIR}/src/Follow.cpp
    ${SOURCEDIR}/src/DGate.cpp
    ${SOURCEDIR}/src/RGate.cpp
    ${SOURCEDIR}/src/Edge.cpp

    # Can't load because of the dynamic_cast on the sliders:
    ${SOURCEDIR}/src/PEQ6.cpp
    ${SOURCEDIR}/src/PEQ6XF.cpp
    ${SOURCEDIR}/src/PEQ14.cpp
    ${SOURCEDIR}/src/PEQ14XF.cpp
    ${SOURCEDIR}/src/PEQ14XR.cpp
    ${SOURCEDIR}/src/PEQ14XV.cpp

    ${SOURCEDIR}/src/Noise.cpp
    ${SOURCEDIR}/src/SampleHold.cpp
    ${SOURCEDIR}/src/Walk2.cpp #misssing widget (XY pad) 
    ${SOURCEDIR}/src/Walk.cpp

    # dynamic_cast widget:
    ${SOURCEDIR}/src/Mix8.cpp
    ${SOURCEDIR}/src/Mix4.cpp
    ${SOURCEDIR}/src/Mix2.cpp
    ${SOURCEDIR}/src/Mix1.cpp
    ${SOURCEDIR}/src/Mix8x.cpp
    ${SOURCEDIR}/src/Mix4x.cpp

    ${SOURCEDIR}/src/VCM.cpp
    ${SOURCEDIR}/src/Mute8.cpp #missing widget (SoloMuteButton)
    ${SOURCEDIR}/src/Pan.cpp
    ${SOURCEDIR}/src/XFade.cpp
    ${SOURCEDIR}/src/VCA.cpp
    # dynamic_cast widget:
    ${SOURCEDIR}/src/VCAmp.cpp
    ${SOURCEDIR}/src/Velo.cpp

    ${SOURCEDIR}/src/UMix.cpp
    ${SOURCEDIR}/src/Mumix.cpp

    # dynamic_cast widget:
    ${SOURCEDIR}/src/Matrix81.cpp
    ${SOURCEDIR}/src/Matrix18.cpp
    ${SOURCEDIR}/src/Matrix44.cpp
    ${SOURCEDIR}/src/Matrix44Cvm.cpp
    ${SOURCEDIR}/src/Matrix88.cpp
    ${SOURCEDIR}/src/Matrix88M.cpp
    ${SOURCEDIR}/src/Matrix88Cv.cpp
    ${SOURCEDIR}/src/Switch81.cpp
    ${SOURCEDIR}/src/Switch18.cpp
    ${SOURCEDIR}/src/Switch44.cpp
    ${SOURCEDIR}/src/Switch88.cpp
    ${SOURCEDIR}/src/Switch1616.cpp

    ${SOURCEDIR}/src/AMRM.cpp
    ${SOURCEDIR}/src/Pressor.cpp
    ${SOURCEDIR}/src/Clpr.cpp
    ${SOURCEDIR}/src/Lmtr.cpp
    ${SOURCEDIR}/src/Nsgt.cpp
    ${SOURCEDIR}/src/CmpDist.cpp

    ${SOURCEDIR}/src/OneEight.cpp
    ${SOURCEDIR}/src/EightOne.cpp
    ${SOURCEDIR}/src/AddrSeq.cpp
    ${SOURCEDIR}/src/AddrSeqX.cpp
    ${SOURCEDIR}/src/Pgmr.cpp
    ${SOURCEDIR}/src/PgmrX.cpp

    ${SOURCEDIR}/src/VU.cpp
    
    # Needs std::condition_variable
    # ${SOURCEDIR}/src/Analyzer.cpp
    # ${SOURCEDIR}/src/AnalyzerXL.cpp
    # ${SOURCEDIR}/src/Ranalyzer.cpp

    ${SOURCEDIR}/src/Detune.cpp
    ${SOURCEDIR}/src/Stack.cpp
    ${SOURCEDIR}/src/Reftone.cpp

    ${SOURCEDIR}/src/Mono.cpp
    ${SOURCEDIR}/src/Arp.cpp #misssing widget (StatefulButton)
    ${SOURCEDIR}/src/Assign.cpp
    ${SOURCEDIR}/src/Unison.cpp
    ${SOURCEDIR}/src/PolyCon8.cpp
    ${SOURCEDIR}/src/PolyCon16.cpp
    ${SOURCEDIR}/src/PolyOff8.cpp
    ${SOURCEDIR}/src/PolyOff16.cpp
    ${SOURCEDIR}/src/PolyMult.cpp

    ${SOURCEDIR}/src/Bool.cpp
    ${SOURCEDIR}/src/Cmp.cpp
    ${SOURCEDIR}/src/CVD.cpp
    ${SOURCEDIR}/src/FlipFlop.cpp
    ${SOURCEDIR}/src/Inv.cpp
    ${SOURCEDIR}/src/Manual.cpp
    ${SOURCEDIR}/src/FourMan.cpp
    ${SOURCEDIR}/src/Mult.cpp
    ${SOURCEDIR}/src/Offset.cpp
    ${SOURCEDIR}/src/Slew.cpp
    ${SOURCEDIR}/src/Sums.cpp
    ${SOURCEDIR}/src/Switch.cpp
    ${SOURCEDIR}/src/Lgsw.cpp

)

target_sources(BogaudioModules PUBLIC
    # enabled modules:
    ${SOURCEDIR}/src/metamodule-plugin.cpp

    # Module sources:
    ${ENABLED_MODULE_SOURCES}

    # Helpers:
    ${SOURCEDIR}/src/module.cpp
    ${SOURCEDIR}/src/mixer.cpp
    ${SOURCEDIR}/src/skins.cpp
    ${SOURCEDIR}/src/widgets.cpp
    ${SOURCEDIR}/src/addressable_sequence.cpp
    ${SOURCEDIR}/src/dadsrh_core.cpp
    ${SOURCEDIR}/src/disable_output_limit.cpp
    ${SOURCEDIR}/src/follower_base.cpp
    ${SOURCEDIR}/src/lfo_base.cpp
    ${SOURCEDIR}/src/lpg_common.cpp
    ${SOURCEDIR}/src/matrix_base.cpp
    ${SOURCEDIR}/src/menu.cpp
    ${SOURCEDIR}/src/mixer_expander.cpp
    ${SOURCEDIR}/src/output_range.cpp
    ${SOURCEDIR}/src/param_quantities.cpp
    ${SOURCEDIR}/src/parametric_eq.cpp
    ${SOURCEDIR}/src/poly_channels.cpp
    ${SOURCEDIR}/src/rack_overrides.cpp
    ${SOURCEDIR}/src/save_latch_to_patch.cpp
    ${SOURCEDIR}/src/shaper_core.cpp
    ${SOURCEDIR}/src/slew_common.cpp
    ${SOURCEDIR}/src/trigger_on_load.cpp
    ${SOURCEDIR}/src/utils.cpp
    ${SOURCEDIR}/src/vco_base.cpp
    ${SOURCEDIR}/src/Pgmr_shared.cpp
    ${DSP_SOURCES}

    # ${SOURCEDIR}/src/analyzer_base.cpp #needs std::condition_variable
)

# Add includes and compile options for source repo
target_include_directories(BogaudioModules 
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}
    ${SOURCEDIR}/src
    ${SOURCEDIR}/src/dsp
    ${SOURCEDIR}/lib
)

target_compile_options(BogaudioModules PRIVATE 
$<$<COMPILE_LANGUAGE:CXX>:-include src/mutex-stub.hh>
$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
)

# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      BogaudioModules
    PLUGIN_NAME     Bogaudio                  # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCEDIR}/plugin.json           # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Bogaudio
)

