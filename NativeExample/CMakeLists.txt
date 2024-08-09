cmake_minimum_required(VERSION 3.22)
include(../metamodule-plugin-sdk/plugin.cmake)

project(NativeExample 
    VERSION 0.1 
    DESCRIPTION "Example Native Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(NativeExample STATIC)
target_include_directories(NativeExample PRIVATE . )

target_sources(NativeExample PRIVATE
	simple_gain.cc
	simple_gain_elements.cc
    plugin.cc
)

# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      NativeExample
    PLUGIN_NAME     NativeExample
    PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/plugin.json           # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/NativeExample
)
