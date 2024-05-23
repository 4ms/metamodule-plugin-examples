cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(PrismMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Prism Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(Prism STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/Prism)

target_sources(Prism
    PRIVATE
	${SOURCE_DIR}/src/Droplet.cpp
	${SOURCE_DIR}/src/DropletAudio.cpp
	${SOURCE_DIR}/src/DropletFilter.cpp

    plugin.cpp 
)

target_include_directories(Prism PRIVATE 
	${SOURCE_DIR}/src
)

target_compile_options(Prism 
	PRIVATE 
	-Wno-double-promotion 
	$<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
)

set_property(TARGET Prism PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      Prism                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Prism                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Prism # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
