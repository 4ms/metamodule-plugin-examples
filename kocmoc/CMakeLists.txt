cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(KocmocMetaModulePlugin
    VERSION     0.1
    DESCRIPTION "Kocmoc Plugin for MetaModule"
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(kocmoc STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/kocmoc-rack-modules/src)

target_sources(kocmoc
	PRIVATE
	${SOURCE_DIR}/DDLY.cpp
	${SOURCE_DIR}/LADR.cpp
	${SOURCE_DIR}/MUL.cpp
	${SOURCE_DIR}/OP.cpp
	${SOURCE_DIR}/PHASR.cpp
	${SOURCE_DIR}/SKF.cpp
	${SOURCE_DIR}/SVF.cpp
	${SOURCE_DIR}/TRG.cpp

	${SOURCE_DIR}/fir.cpp
	${SOURCE_DIR}/iir.cpp
	${SOURCE_DIR}/ladder.cpp
	${SOURCE_DIR}/phasor.cpp
	${SOURCE_DIR}/sallenkey.cpp
	${SOURCE_DIR}/svfilter.cpp

	${SOURCE_DIR}/plugin.cpp
)

target_include_directories(kocmoc PRIVATE
	${SOURCE_DIR}
)

target_compile_options(kocmoc
	PRIVATE
	# No flags needed
)

set_property(TARGET kocmoc PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      kocmoc                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     kocmoc                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Kocmoc # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
