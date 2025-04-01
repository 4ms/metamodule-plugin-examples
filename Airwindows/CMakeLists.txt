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

# Use our own SDK, not the one installed by the airwind2rack cmake
unset(BUILD_METAMODULE_PLUGIN) 
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

