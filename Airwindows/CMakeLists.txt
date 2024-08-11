cmake_minimum_required(VERSION 3.22)
include(../metamodule-plugin-sdk/plugin.cmake)

project(AirwindowsModules 
    VERSION 0.1 
    DESCRIPTION "Airwindows Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(AirwindowsModules STATIC)


target_include_directories(AirwindowsModules PRIVATE 
	. 
    airwin2rack/src
)

target_sources(AirwindowsModules PRIVATE
	airwin_modules.cc
)

target_compile_definitions(AirwindowsModules PRIVATE 
	DISABLE_CONSOLE
)

add_subdirectory(airwin2rack)
target_compile_options(airwin-registry PRIVATE "-Wno-misleading-indentation;-Wno-unused-variable;-Wno-stringop-truncation")

target_link_libraries(AirwindowsModules PUBLIC airwin-registry)
set(EXTRA_LINK_OPTIONS $<TARGET_OBJECTS:airwin-registry>)

create_plugin(
    SOURCE_LIB      AirwindowsModules
    PLUGIN_NAME     Airwindows
    PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/airwin2rack/plugin.json
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins
)

