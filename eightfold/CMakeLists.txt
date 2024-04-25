cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(eightfoldMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "eightfold Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(eightfold STATIC)

target_sources(eightfold
    PRIVATE
    eightfold/src/SDOrcasHeartV2.cpp
    plugin.cpp
)

target_include_directories(eightfold PRIVATE ${CMAKE_CURRENT_LIST_DIR}/eightfold/src)

target_compile_options(eightfold PRIVATE -Wno-double-promotion)

set_property(TARGET eightfold PROPERTY CXX_STANDARD 20)

#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      eightfold                           # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     eightfold                           # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/eightfold # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
