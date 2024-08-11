cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(GeodesicsMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Geodesics Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(Geodesics STATIC)

# convenient variable pointing to the VCV Rack repo
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
	# ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(Geodesics 
	PRIVATE 
	# -Wno-double-promotion 
	# $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
)

set_property(TARGET Geodesics PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      Geodesics                                         # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Geodesics                                         # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json                         # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets                  # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/  # Dir where plugin .mmplugin file should be put
)
