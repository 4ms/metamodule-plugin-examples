cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(SapphireMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Sapphire Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(Sapphire STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/sapphire)

target_sources(Sapphire
    PRIVATE
    # ${SOURCE_DIR}/src/elastika_vcv.cpp
    # ${SOURCE_DIR}/src/mesh_physics.cpp
    # ${SOURCE_DIR}/src/mesh_hex.cpp

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

target_compile_definitions(Sapphire PRIVATE 
	METAMODULE
)

set_property(TARGET Sapphire PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      Sapphire                            # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     CosineKitty-Sapphire                # This must match the brand "slug" used in VCV Rack
	PLUGIN_JSON     ${SOURCE_DIR}/plugin.json
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins    # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
