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

project(OrangeLineMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "OrangeLine Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(OrangeLine STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/OrangeLine)

target_sources(OrangeLine
    PRIVATE
    ${SOURCE_DIR}/src/Fence.cpp
    ${SOURCE_DIR}/src/Swing.cpp
    ${SOURCE_DIR}/src/Mother.cpp
    ${SOURCE_DIR}/src/Phrase.cpp
    ${SOURCE_DIR}/src/Dejavu.cpp
    ${SOURCE_DIR}/src/Gator.cpp
    ${SOURCE_DIR}/src/Resc.cpp
    ${SOURCE_DIR}/src/Morph.cpp
    ${SOURCE_DIR}/src/Morpheus.cpp

    ${SOURCE_DIR}/src/OrangeLine.cpp

    OrangeLine.cpp 
)

target_include_directories(OrangeLine PRIVATE 
    ${SOURCE_DIR}/src 
)

target_compile_options(OrangeLine 
    PRIVATE 
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-enum-conversion>
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
)

set_property(TARGET OrangeLine PROPERTY CXX_STANDARD 20)

create_plugin(
    SOURCE_LIB      OrangeLine                          # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     OrangeLine                          # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json           # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins   # Dir where you want the plugin .mmplugin file
)
