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

project(RackFundamentalMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Fundamental Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(Fundamental STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/Fundamental/src)

target_sources(Fundamental
    PRIVATE

	${SOURCE_DIR}/8vert.cpp
	${SOURCE_DIR}/ADSR.cpp
	${SOURCE_DIR}/CVMix.cpp
	${SOURCE_DIR}/Compare.cpp
	${SOURCE_DIR}/Fade.cpp
	${SOURCE_DIR}/Gates.cpp
	${SOURCE_DIR}/LFO.cpp
	${SOURCE_DIR}/Logic.cpp
	${SOURCE_DIR}/MidSide.cpp
	${SOURCE_DIR}/Mixer.cpp
	${SOURCE_DIR}/Mult.cpp
	${SOURCE_DIR}/Mutes.cpp
	${SOURCE_DIR}/Noise.cpp
	${SOURCE_DIR}/Octave.cpp 
	${SOURCE_DIR}/Process.cpp
	${SOURCE_DIR}/Pulses.cpp
	${SOURCE_DIR}/Push.cpp
	${SOURCE_DIR}/Quantizer.cpp
	${SOURCE_DIR}/Random.cpp
	${SOURCE_DIR}/RandomValues.cpp
	${SOURCE_DIR}/Rescale.cpp
	${SOURCE_DIR}/SEQ3.cpp
	${SOURCE_DIR}/SHASR.cpp
	${SOURCE_DIR}/SequentialSwitch.cpp
	${SOURCE_DIR}/Unity.cpp
	${SOURCE_DIR}/VCA-1.cpp
	${SOURCE_DIR}/VCA.cpp
	${SOURCE_DIR}/VCF.cpp
	${SOURCE_DIR}/VCMixer.cpp
	${SOURCE_DIR}/VCO.cpp
	${SOURCE_DIR}/Scope.cpp 

	quant.cc

    # Not relevent without polyphony:
	# ${SOURCE_DIR}/Merge.cpp
	# ${SOURCE_DIR}/Split.cpp # not relevent without polyphony
	# ${SOURCE_DIR}/Sum.cpp # not relevent without polyphony
	# ${SOURCE_DIR}/Viz.cpp #not relevent without polyphony

	# Uses filesystem:
	${SOURCE_DIR}/WTLFO.cpp
	${SOURCE_DIR}/WTVCO.cpp
	${SOURCE_DIR}/dr_wav.c

    # src_new src_delete src_process
	${SOURCE_DIR}/Delay.cpp

	plugin.cpp
)

target_include_directories(Fundamental PRIVATE 
    ${SOURCE_DIR}/
    .
)

target_compile_options(Fundamental PRIVATE 
    -fexceptions
	$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
)

target_compile_definitions(Fundamental PRIVATE 
	METAMODULE
)

set_source_files_properties(
	${SOURCE_DIR}/WTLFO.cpp
	${SOURCE_DIR}/WTVCO.cpp
	COMPILE_FLAGS -Wno-deprecated #silence warnings about deprecated capture of this with [=]
)


set_property(TARGET Fundamental PROPERTY CXX_STANDARD 20)


create_plugin(
    SOURCE_LIB      Fundamental                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Fundamental                  # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/Fundamental/plugin.json
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
