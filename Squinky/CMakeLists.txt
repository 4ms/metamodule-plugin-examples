cmake_minimum_required(VERSION 3.24)
include(../metamodule-plugin-sdk/plugin.cmake)

project(SquinkyLabs VERSION 0.1 DESCRIPTION "SquinkyLabs for Rack" LANGUAGES C CXX ASM)

# Define SOURCE_DIR first
set(SOURCE_DIR ./squinky)

add_library(SquinkyLabs STATIC)

target_compile_definitions(SquinkyLabs PRIVATE __V1x __PLUGIN)
target_compile_definitions(SquinkyLabs PRIVATE _FILT)


target_sources(SquinkyLabs PRIVATE
    ${SOURCE_DIR}/src/FiltModule.cpp
    ${SOURCE_DIR}/src/Squinky.cpp

    ${SOURCE_DIR}/dsp/utils/AudioMath.cpp
    ${SOURCE_DIR}/dsp/utils/ObjectCache.cpp
    ${SOURCE_DIR}/dsp/utils/AsymWaveshaper.cpp
    ${SOURCE_DIR}/dsp/filters/ButterworthFilterDesigner.cpp
    ${SOURCE_DIR}/dsp/third-party/falco/DspFilter.cpp
)

# Add includes and compile options for source repo
target_include_directories(SquinkyLabs PRIVATE 
    ${SOURCE_DIR}/src
    ${SOURCE_DIR}/composites
    ${SOURCE_DIR}/sqsrc/util
    ${SOURCE_DIR}/dsp/filters
    ${SOURCE_DIR}/dsp/utils
    ${SOURCE_DIR}/util
    ${SOURCE_DIR}/dsp/third-party/falco
    ${SOURCE_DIR}/dsp
    ${SOURCE_DIR}/dsp/third-party/src
)

# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      SquinkyLabs
    PLUGIN_NAME     squinkylabs-plug1
    PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/squinky/plugin.json
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins
)
