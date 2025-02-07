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

project(KocmocMetaModulePlugin
    VERSION     0.1
    DESCRIPTION "Kocmoc Plugin for MetaModule"
    LANGUAGES   C CXX ASM
)

add_library(kocmoc STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/kocmoc-rack-modules/src)

target_sources(kocmoc
	PRIVATE
	${SOURCE_DIR}/DDLY.cpp
	${SOURCE_DIR}/LADR.cpp
	${SOURCE_DIR}/uLADR.cpp
	${SOURCE_DIR}/MUL.cpp
	${SOURCE_DIR}/OP.cpp
	${SOURCE_DIR}/PHASR.cpp
	${SOURCE_DIR}/SKF.cpp
	${SOURCE_DIR}/SVF.cpp
	${SOURCE_DIR}/uSVF.cpp
	${SOURCE_DIR}/TRG.cpp

	${SOURCE_DIR}/fir.cpp
	${SOURCE_DIR}/iir.cpp
	${SOURCE_DIR}/iir32.cpp
	${SOURCE_DIR}/ladder.cpp
	${SOURCE_DIR}/phasor.cpp
	${SOURCE_DIR}/sallenkey.cpp
	${SOURCE_DIR}/svfilter.cpp

	${SOURCE_DIR}/plugin.cpp
)

target_include_directories(kocmoc PRIVATE
	${SOURCE_DIR}
)

target_compile_definitions(kocmoc PRIVATE FLOATDSP)

set_property(TARGET kocmoc PROPERTY CXX_STANDARD 20)

if("${INSTALL_DIR}" STREQUAL "")
    set(INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins)
endif()

create_plugin(
    SOURCE_LIB      kocmoc                                                    # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     kocmoc                                                    # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/kocmoc-rack-modules/plugin.json # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets                          # Path to the assets/ dir containing the PNGs
    DESTINATION     ${INSTALL_DIR}                                            # Path to where you want the plugin file output
)
