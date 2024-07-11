cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(BaconMusicModules 
    VERSION     0.1 
    DESCRIPTION "Bacon Music Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(BaconMusic STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/BaconPlugs)

target_sources(BaconMusic
    PRIVATE
    ${SOURCE_DIR}/src/Glissinator.cpp
    ${SOURCE_DIR}/src/Components.cpp
    ${SOURCE_DIR}/src/Style.cpp

    # Note that we build our own plugin.cpp, not the one in BaconMusic/src/
    # This is because we want to exclude the above modules from the plugin
    BaconMusic.cpp 
)

target_include_directories(BaconMusic PRIVATE 
	${SOURCE_DIR}/src 
    .
    ${SOURCE_DIR}/libs
)

target_compile_options(BaconMusic 
	PRIVATE 
	# -Wno-double-promotion 
	# $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
)

set_property(TARGET BaconMusic PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      BaconMusic                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     BaconMusic                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/BaconMusic # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
