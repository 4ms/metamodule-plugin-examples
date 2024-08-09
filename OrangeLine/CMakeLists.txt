cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(OrangeLineMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "OrangeLine Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(OrangeLine STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/OrangeLine)

target_sources(OrangeLine
    PRIVATE
    ${SOURCE_DIR}/src/Fence.cpp
    ${SOURCE_DIR}/src/Swing.cpp
    ${SOURCE_DIR}/src/Mother.cpp
    ${SOURCE_DIR}/src/Phrase.cpp
    ${SOURCE_DIR}/src/Dejavu.cpp
    ${SOURCE_DIR}/src/Gator.cpp
    ${SOURCE_DIR}/src/Resc.cpp
    ${SOURCE_DIR}/src/Morph.cpp
    ${SOURCE_DIR}/src/Morpheus.cpp

    ${SOURCE_DIR}/src/OrangeLine.cpp

    OrangeLine.cpp 
)

target_include_directories(OrangeLine PRIVATE 
	${SOURCE_DIR}/src 
	# ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(OrangeLine 
	PRIVATE 
	# -Wno-double-promotion 
	# $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
)

set_property(TARGET OrangeLine PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      OrangeLine                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     OrangeLine                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/OrangeLine # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
