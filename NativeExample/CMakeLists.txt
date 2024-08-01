cmake_minimum_required(VERSION 3.22)
include(../metamodule-plugin-sdk/plugin.cmake)

project(SimpleModules 
    VERSION 0.1 
    DESCRIPTION "Example Native Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(SimpleModules STATIC)
target_include_directories(SimpleModules PRIVATE . )

target_sources(SimpleModules PRIVATE
	simple_gain.cc
	simple_gain_elements.cc
    plugin.cc
)

# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      SimpleModules
    PLUGIN_NAME     SimpleModules
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/SimpleModules
)
