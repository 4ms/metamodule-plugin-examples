cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(SVModularMetaModulePlugin
    VERSION     0.1
    DESCRIPTION "SVModular Plugin for MetaModule"
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(Drumkit STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/Drumkit/src)

target_sources(Drumkit
	PRIVATE
    ${SOURCE_DIR}/../deps/ADSR.cpp
    ${SOURCE_DIR}/../deps/LFO.cpp
    ${SOURCE_DIR}/../deps/LFO.cpp
    ${SOURCE_DIR}/../deps/SynthDevKit/src/CV.cpp

    ${SOURCE_DIR}/controller/BD9.cpp
    ${SOURCE_DIR}/controller/CR78.cpp
    ${SOURCE_DIR}/controller/ClosedHH.cpp
    ${SOURCE_DIR}/controller/DMX.cpp
    ${SOURCE_DIR}/controller/Gnome.cpp
    ${SOURCE_DIR}/controller/OpenHH.cpp
    ${SOURCE_DIR}/controller/SBD.cpp
    ${SOURCE_DIR}/controller/SampleController.cpp
    ${SOURCE_DIR}/controller/Snare.cpp
    ${SOURCE_DIR}/controller/Tomi.cpp

    ${SOURCE_DIR}/model/SampleManager.cpp

    ${SOURCE_DIR}/view/BD9.cpp
    ${SOURCE_DIR}/view/CR78.cpp
    ${SOURCE_DIR}/view/ClosedHH.cpp
    ${SOURCE_DIR}/view/DMX.cpp
    ${SOURCE_DIR}/view/Gnome.cpp
    ${SOURCE_DIR}/view/OpenHH.cpp
    ${SOURCE_DIR}/view/SBD.cpp
    ${SOURCE_DIR}/view/Snare.cpp
    ${SOURCE_DIR}/view/Tomi.cpp

    ${CMAKE_CURRENT_LIST_DIR}/DrumKit.cpp
)

target_include_directories(Drumkit PRIVATE
	${SOURCE_DIR}
)

target_compile_options(Drumkit
	PRIVATE
	# No flags needed
)

target_compile_definitions(Drumkit PRIVATE FLOATDSP)

set_property(TARGET Drumkit PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      Drumkit # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Drumkit # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${CMAKE_CURRENT_LIST_DIR}/Drumkit/plugin.json # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets                          # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins           # Path to where you want the plugin file output
)
