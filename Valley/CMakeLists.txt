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

project(ValleyMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Valley Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(Valley STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ValleyRackFree)

target_sources(Valley
    PRIVATE
    # ${SOURCE_DIR}/src/Terrorform/Terrorform.cpp

    ${SOURCE_DIR}/src/Interzone/Interzone.cpp

    ${SOURCE_DIR}/src/Amalgam/Amalgam.cpp
    ${SOURCE_DIR}/src/Amalgam/VecAmalgam.cpp

    ${SOURCE_DIR}/src/Feline/Feline.cpp

    # Requires .bin files built into the binary (possibly, but not yet!)
    # ${SOURCE_DIR}/src/Dexter/Dexter.cpp
    # ${SOURCE_DIR}/src/Dexter/DexterCore.cpp
    # ${SOURCE_DIR}/src/Dexter/DexterRoutingMatrix.cpp
    # ${SOURCE_DIR}/src/Dexter/Chords.cpp


    ${SOURCE_DIR}/src/dsp/filters/OnePoleFilters.cpp
    ${SOURCE_DIR}/src/dsp/filters/VecOnePoleFilters.cpp
    ${SOURCE_DIR}/src/dsp/filters/VecOTAFilter.cpp
    ${SOURCE_DIR}/src/dsp/modulation/VecLoopingADSR.cpp
    ${SOURCE_DIR}/src/dsp/fx/DiodeRingMod.cpp
    ${SOURCE_DIR}/src/dsp/fx/VecDiodeRingMod.cpp
    ${SOURCE_DIR}/src/gui/SteppedSlider.cpp
    ${SOURCE_DIR}/src/gui/DigitalDisplay.cpp
    ${SOURCE_DIR}/src/utilities/Utilities.cpp

    # Note that we build our own plugin.cpp, not the one in Valley/src/
    # This is because we want to exclude the above modules from the plugin
    Valley.cpp 
)

target_include_directories(Valley PRIVATE 
    ${SOURCE_DIR}/src 
)

target_compile_options(Valley PRIVATE 
    -Wno-double-promotion 
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
)

target_compile_definitions(Valley PRIVATE
    DSJ_VEC_DIODE_TABLE_N=64
)

set_property(TARGET Valley PROPERTY CXX_STANDARD 20)

if("${INSTALL_DIR}" STREQUAL "")
    set(INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins)
endif()

create_plugin(
    SOURCE_LIB      Valley                              # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Valley                              # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json           # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${INSTALL_DIR}                      # Dir where plugin .mmplugin file should be put
)
