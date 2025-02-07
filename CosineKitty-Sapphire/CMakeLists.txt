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

project(SapphireMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Sapphire Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(Sapphire STATIC)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/sapphire)

target_sources(Sapphire
    PRIVATE
    ${SOURCE_DIR}/src/elastika_vcv.cpp
    ${SOURCE_DIR}/src/mesh_physics.cpp
    ${SOURCE_DIR}/src/elastika_mesh.cpp

    ${SOURCE_DIR}/src/frolic_vcv.cpp
    ${SOURCE_DIR}/src/galaxy_vcv.cpp
    ${SOURCE_DIR}/src/gravy_vcv.cpp
    ${SOURCE_DIR}/src/glee_vcv.cpp
    ${SOURCE_DIR}/src/hiss_vcv.cpp
    # ${SOURCE_DIR}/src/moots_vcv.cpp
    # ${SOURCE_DIR}/src/nucleus_vcv.cpp
    # ${SOURCE_DIR}/src/pivot_vcv.cpp
    # ${SOURCE_DIR}/src/polynucleus_vcv.cpp
    # ${SOURCE_DIR}/src/pop_vcv.cpp
    # ${SOURCE_DIR}/src/rotini_vcv.cpp
    # ${SOURCE_DIR}/src/sam_vcv.cpp
    # ${SOURCE_DIR}/src/tin_vcv.cpp
    # ${SOURCE_DIR}/src/tout_vcv.cpp
    # ${SOURCE_DIR}/src/tricorder_vcv.cpp
    # ${SOURCE_DIR}/src/tubeunit_vcv.cpp

    ${SOURCE_DIR}/src/sapphire_globals.cpp
    ${SOURCE_DIR}/src/sapphire_panel.cpp

	firmware-stubs.cc
    plugin.cpp 
)

target_include_directories(Sapphire PRIVATE 
	${SOURCE_DIR}/src 
	${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(Sapphire PRIVATE 
#TODO
)

set_property(TARGET Sapphire PROPERTY CXX_STANDARD 20)

create_plugin(
    SOURCE_LIB      Sapphire                            # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     CosineKitty-Sapphire                # This must match the brand "slug" used in VCV Rack
	PLUGIN_JSON     ${SOURCE_DIR}/plugin.json
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins    # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
