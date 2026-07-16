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
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/
)
