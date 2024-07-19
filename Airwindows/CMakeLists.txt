cmake_minimum_required(VERSION 3.22)
include(../metamodule-plugin-sdk/plugin.cmake)

project(AirwindowsModules 
    VERSION 0.1 
    DESCRIPTION "Airwindows Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)


set(METAMODULE ON)
add_subdirectory(airwin2rack)
target_compile_options(airwin-registry PRIVATE "-Wno-misleading-indentation;-Wno-unused-variable")

add_library(AirwindowsModules STATIC)

target_link_libraries(AirwindowsModules PRIVATE airwin-registry)


# Add includes and compile options for source repo
target_include_directories(AirwindowsModules 
    PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/../airwin2rack/src
)

target_sources(AirwindowsModules PRIVATE
    plugin.cc
)

target_compile_options(AirwindowsModules PRIVATE 
)

# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      AirwindowsModules
    PLUGIN_NAME     Airwin2Rack                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Airwin2Rack
)

