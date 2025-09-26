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

project(VostokInstrumentsMetaModulePlugin 
    VERSION 0.1 
    DESCRIPTION "Vostok Instruments for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(VostokInstruments STATIC)

# Add sources from the Rack source repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/VCV)




message([STATUS] "SOURCE_DIR : ${SOURCE_DIR}")


target_compile_options(VostokInstruments PRIVATE 
    -Wdouble-promotion 
    $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
    -Wno-alloc-size-larger-than
    -fsingle-precision-constant
    -ffast-math
    -funsafe-math-optimizations
    -Ofast
)


target_sources(VostokInstruments PRIVATE
    # ${SOURCE_DIR}/src/plugin.cpp                    # Note: this file contains init(rack::Plugin*)
    ${SOURCE_DIR}/src/Asset.cpp
    ${SOURCE_DIR}/src/Atlas.cpp
    ${SOURCE_DIR}/src/Ceres.cpp
    ${SOURCE_DIR}/src/Fuji.cpp
    ${SOURCE_DIR}/src/Hive.cpp
    ${SOURCE_DIR}/src/Path.cpp
    ${SOURCE_DIR}/src/Sena.cpp
    ${SOURCE_DIR}/src/Trace.cpp
    # Add any additional module source files here
    ${SOURCE_DIR}/src/plugin.cpp
)

# Add includes and compile options for source repo
target_include_directories(VostokInstruments PRIVATE 
	${SOURCE_DIR}/src 
	${SOURCE_DIR}/src/ripples
)

set_property(TARGET VostokInstruments PROPERTY CXX_STANDARD 23)


# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      VostokInstruments                                     # The cmake target name (defined in add_target)
    PLUGIN_NAME     VostokInstruments                                     # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json                         # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets                  # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins   # Path to where you want the plugin file output
)