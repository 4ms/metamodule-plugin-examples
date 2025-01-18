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

project(NanoModulesMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "NanoModules Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(NanoModules STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/NANO-Modules_VCV)

target_sources(NanoModules
    PRIVATE
    ${SOURCE_DIR}/src/MAR.cpp
    ${SOURCE_DIR}/src/FONT.cpp
    ${SOURCE_DIR}/src/ALT.cpp
    ${SOURCE_DIR}/src/QUART.cpp
    ${SOURCE_DIR}/src/ONA.cpp
    ${SOURCE_DIR}/src/SERRA.cpp 
    ${SOURCE_DIR}/src/CEQ.cpp    
    ${SOURCE_DIR}/src/STMAR.cpp 
    ${SOURCE_DIR}/src/PerformanceMixer.cpp 
    ${SOURCE_DIR}/src/VCVRANDOM.cpp    
    ${SOURCE_DIR}/src/EXP4.cpp    

    ${SOURCE_DIR}/src/Resources/DaisySP/Source/Filters/svf.cpp
    ${SOURCE_DIR}/src/Resources/DaisySP/Source/Dynamics/compressor.cpp

    # Note that we build our own plugin.cpp, not the one in the source dir.
    # This is because we want to exclude the blank panels
    plugin.cpp 
)

target_include_directories(NanoModules PRIVATE ${SOURCE_DIR}/src .)

target_compile_options(NanoModules PRIVATE -Wno-double-promotion $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion> -Wno-reorder)

set_property(TARGET NanoModules PROPERTY CXX_STANDARD 20)

create_plugin(
    SOURCE_LIB      NanoModules                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     NANOModules                  # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
