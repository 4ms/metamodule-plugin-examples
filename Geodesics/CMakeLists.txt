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

project(GeodesicsMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Geodesics Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(Geodesics STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/Geodesics)

target_sources(Geodesics
    PRIVATE
    ${SOURCE_DIR}/src/BlackHoles.cpp
    ${SOURCE_DIR}/src/Branes.cpp
    ${SOURCE_DIR}/src/DarkEnergy.cpp
    ${SOURCE_DIR}/src/Energy.cpp
    ${SOURCE_DIR}/src/EnergyOsc.cpp
    ${SOURCE_DIR}/src/Entropia.cpp
    ${SOURCE_DIR}/src/Fate.cpp
    ${SOURCE_DIR}/src/GeoWidgets.cpp
    ${SOURCE_DIR}/src/Ions.cpp
    ${SOURCE_DIR}/src/Pulsars.cpp
    ${SOURCE_DIR}/src/Torus.cpp

    # Note that we build our own plugin.cpp, not the one in Geodesics/src/
    # This is because we want to exclude the above modules from the plugin
    Geodesics.cpp 
)

target_include_directories(Geodesics PRIVATE 
    ${SOURCE_DIR}/src 
)

set_property(TARGET Geodesics PROPERTY CXX_STANDARD 20)

if("${INSTALL_DIR}" STREQUAL "")
    set(INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins)
endif()

create_plugin(
    SOURCE_LIB      Geodesics                           # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Geodesics                           # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json           # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${INSTALL_DIR}                      # Dir where plugin .mmplugin file should be put
)
