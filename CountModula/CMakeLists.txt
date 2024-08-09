cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(CountModulaMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Count Modula Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(CountModula STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/VCVRackPlugins)
set(MODULE_DIR ${SOURCE_DIR}/src/modules)

target_sources(CountModula
    PRIVATE
    ${MODULE_DIR}/AnalogueShiftRegister.cpp
    # ${MODULE_DIR}/Arpeggiator.cpp #Needs to rectify PORT_MAX_CHANNELS = 4 but ARP steps is 8
    ${MODULE_DIR}/Attenuator.cpp
    ${MODULE_DIR}/Attenuverter.cpp
    ${MODULE_DIR}/BarGraph.cpp
    ${MODULE_DIR}/BasicSequencer8.cpp
    ${MODULE_DIR}/BinaryComparator.cpp
    ${MODULE_DIR}/BinarySequencer.cpp
    #${MODULE_DIR}/BlankPanel12HP.cpp
    #${MODULE_DIR}/BlankPanel16HP.cpp
    #${MODULE_DIR}/BlankPanel20HP.cpp
    #${MODULE_DIR}/BlankPanel24HP.cpp
    #${MODULE_DIR}/BlankPanel2HP.cpp
    #${MODULE_DIR}/BlankPanel4HP.cpp
    #${MODULE_DIR}/BlankPanel8HP.cpp
    ${MODULE_DIR}/BooleanAND.cpp
    ${MODULE_DIR}/BooleanOR.cpp
    ${MODULE_DIR}/BooleanVCNOT.cpp
    ${MODULE_DIR}/BooleanXOR.cpp
    ${MODULE_DIR}/Breakout.cpp
    ${MODULE_DIR}/BurstGenerator.cpp
    ${MODULE_DIR}/BurstGenerator64.cpp
    ${MODULE_DIR}/BusRoute.cpp
    ${MODULE_DIR}/BusRoute2.cpp
    ${MODULE_DIR}/Carousel.cpp
    ${MODULE_DIR}/Chances.cpp
    ${MODULE_DIR}/ClockDivider.cpp
    ${MODULE_DIR}/ClockedRandomGateExpanderCV.cpp
    ${MODULE_DIR}/ClockedRandomGateExpanderLog.cpp
    ${MODULE_DIR}/ClockedRandomGates.cpp
    ${MODULE_DIR}/Comparator.cpp
    ${MODULE_DIR}/CVSpreader.cpp
    ${MODULE_DIR}/GateSequencer16.cpp
    ${MODULE_DIR}/GateSequencer8.cpp
    ${MODULE_DIR}/Euclid.cpp
    ${MODULE_DIR}/EuclidExpanderCV.cpp
    ${MODULE_DIR}/EventArranger.cpp
    ${MODULE_DIR}/EventTimer.cpp
    ${MODULE_DIR}/EventTimer2.cpp
    ${MODULE_DIR}/Fade.cpp
    ${MODULE_DIR}/FadeExpander.cpp
    ${MODULE_DIR}/G2T.cpp
    ${MODULE_DIR}/GatedComparator.cpp
    ${MODULE_DIR}/GateDelay.cpp
    ${MODULE_DIR}/GateDelayMT.cpp
    ${MODULE_DIR}/GateModifier.cpp
    ${MODULE_DIR}/GateSequencer16.cpp
    ${MODULE_DIR}/GateSequencer8.cpp
    #${MODULE_DIR}/HyperManiac.cpp
    #${MODULE_DIR}/HyperManiacalLFO.cpp
    #${MODULE_DIR}/HyperManiacalLFOExpander.cpp
    # ${MODULE_DIR}/LightStrip.cpp
    ${MODULE_DIR}/Mangler.cpp
    ${MODULE_DIR}/Manifold.cpp
    ${MODULE_DIR}/ManualCV.cpp
    ${MODULE_DIR}/ManualCV2.cpp
    ${MODULE_DIR}/ManualGate.cpp
    ${MODULE_DIR}/MasterReset.cpp
    ${MODULE_DIR}/MatrixCombiner.cpp
    ${MODULE_DIR}/MatrixMixer.cpp
    ${MODULE_DIR}/MinimusMaximus.cpp
    ${MODULE_DIR}/Mixer.cpp
    ${MODULE_DIR}/MorphShaper.cpp
    ${MODULE_DIR}/Mult.cpp
    ${MODULE_DIR}/Multiplexer.cpp
    ${MODULE_DIR}/MultiStepSequencer.cpp
    ${MODULE_DIR}/Mute.cpp
    ${MODULE_DIR}/Mute-iple.cpp
    ${MODULE_DIR}/NibbleTriggerSequencer.cpp
    ${MODULE_DIR}/OctetTriggerSequencer.cpp
    ${MODULE_DIR}/OctetTriggerSequencerCVExpander.cpp
    ${MODULE_DIR}/OctetTriggerSequencerGateExpander.cpp
    ${MODULE_DIR}/OffsetGenerator.cpp
    #${MODULE_DIR}/Oscilloscope.cpp
    #${MODULE_DIR}/Palette.cpp
    ${MODULE_DIR}/PolyChances.cpp
    ${MODULE_DIR}/PolyG2T.cpp
    ${MODULE_DIR}/PolyGateModifier.cpp
    ${MODULE_DIR}/PolyLogic.cpp
    ${MODULE_DIR}/PolyMinMax.cpp
    ${MODULE_DIR}/PolyMute.cpp
    ${MODULE_DIR}/PolyrhythmicGenerator.cpp
    ${MODULE_DIR}/PolyrhythmicGeneratorMkII.cpp
    ${MODULE_DIR}/PolyVCPolarizer.cpp
    ${MODULE_DIR}/PolyVCSwitch.cpp
    #${MODULE_DIR}/RackEarL.cpp
    #${MODULE_DIR}/RackEarR.cpp
    ${MODULE_DIR}/RandomAccessSwitch18.cpp
    ${MODULE_DIR}/RandomAccessSwitch81.cpp
    ${MODULE_DIR}/Rectifier.cpp
    ${MODULE_DIR}/SampleAndHold.cpp
    ${MODULE_DIR}/SampleAndHold2.cpp
    ${MODULE_DIR}/SequenceEncoder.cpp
    ${MODULE_DIR}/Sequencer16.cpp
    ${MODULE_DIR}/Sequencer64.cpp
    ${MODULE_DIR}/Sequencer8.cpp
    ${MODULE_DIR}/SequencerChannel16.cpp
    ${MODULE_DIR}/SequencerChannel8.cpp
    ${MODULE_DIR}/SequencerExpanderCV8.cpp
    ${MODULE_DIR}/SequencerExpanderLog8.cpp
    ${MODULE_DIR}/SequencerExpanderOut8.cpp
    ${MODULE_DIR}/SequencerExpanderRM8.cpp
    ${MODULE_DIR}/SequencerExpanderTrig8.cpp
    ${MODULE_DIR}/SequencerExpanderTSG.cpp
    ${MODULE_DIR}/SequencerGates16.cpp
    ${MODULE_DIR}/SequencerGates8.cpp
    ${MODULE_DIR}/SequencerTriggers16.cpp
    ${MODULE_DIR}/SequencerTriggers8.cpp
    ${MODULE_DIR}/ShepardGenerator.cpp
    ${MODULE_DIR}/ShiftRegister16.cpp
    ${MODULE_DIR}/ShiftRegister32.cpp
    ${MODULE_DIR}/DFlipFlop.cpp
    ${MODULE_DIR}/SRFlipFlop.cpp
    ${MODULE_DIR}/TFlipFlop.cpp
    ${MODULE_DIR}/SlopeDetector.cpp
    ${MODULE_DIR}/Stack.cpp
    ${MODULE_DIR}/StartupDelay.cpp
    ${MODULE_DIR}/StepSequencer8.cpp
    ${MODULE_DIR}/SubHarmonicGenerator.cpp
    ${MODULE_DIR}/Switch16To1.cpp
    ${MODULE_DIR}/Switch1To16.cpp
    ${MODULE_DIR}/Switch1To8.cpp
    ${MODULE_DIR}/Switch2.cpp
    ${MODULE_DIR}/Switch3.cpp
    ${MODULE_DIR}/Switch4.cpp
    ${MODULE_DIR}/Switch8To1.cpp
    ${MODULE_DIR}/TriggerSequencer16.cpp
    ${MODULE_DIR}/TriggerSequencer8.cpp
    ${MODULE_DIR}/VCFrequencyDivider.cpp
    ${MODULE_DIR}/VCFrequencyDividerMkII.cpp
    ${MODULE_DIR}/VCPolarizer.cpp
    ${MODULE_DIR}/VCPulseDivider.cpp
    ${MODULE_DIR}/VoltageControlledSwitch.cpp
    ${MODULE_DIR}/VoltageInverter.cpp
    ${MODULE_DIR}/VoltageScaler.cpp

    ${SOURCE_DIR}/src/components/StdComponentPositions.cpp

    # Note that we build our own plugin.cpp, not the one in CountModula/src/
    # This is because we want to exclude the above modules from the plugin
    CountModula.cpp 
)

target_include_directories(CountModula PRIVATE 
	${SOURCE_DIR}/src 
	# ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(CountModula 
	PRIVATE 
	$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
    -Wno-array-bounds #Fix because Menu returns a nullptr
)

set_property(TARGET CountModula PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      CountModula                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     CountModula                  # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json           # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/CountModula # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
