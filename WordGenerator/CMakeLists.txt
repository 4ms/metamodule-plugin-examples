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

project(WordGeneratorMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "WordGenerator Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(WordGenerator STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/word-generator)

target_sources(WordGenerator
    PRIVATE
    ${SOURCE_DIR}/src/WordGenerator.cpp
    ${SOURCE_DIR}/src/plugin.cpp
)

target_include_directories(WordGenerator PRIVATE 
    ${SOURCE_DIR}/src 
    .
)

target_compile_options(WordGenerator PRIVATE -Wno-double-promotion $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion> -Wno-reorder)

set_property(TARGET WordGenerator PROPERTY CXX_STANDARD 20)

if("${INSTALL_DIR}" STREQUAL "")
    set(INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins)
endif()

create_plugin(
    SOURCE_LIB      WordGenerator # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     WordGenerator                       # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets  # Path to the assets/ dir containing the PNGs
    DESTINATION     ${INSTALL_DIR}                    # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
