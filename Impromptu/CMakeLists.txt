cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(ImpromptuMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "Impromptu Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(Impromptu STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/ImpromptuModular)

target_sources(Impromptu
    PRIVATE
    ${SOURCE_DIR}/src/Sygen.cpp
	${SOURCE_DIR}/src/AdaptiveQuantizer.cpp
	${SOURCE_DIR}/src/BigButtonSeq.cpp
	${SOURCE_DIR}/src/BigButtonSeq2.cpp
	# ${SOURCE_DIR}/src/ChordKey.cpp #needs make_element(OpaqueWidget*,...)
	${SOURCE_DIR}/src/Clocked.cpp
	${SOURCE_DIR}/src/ClockedCommon.cpp
	${SOURCE_DIR}/src/ClockedExpander.cpp
	${SOURCE_DIR}/src/Clkd.cpp
	${SOURCE_DIR}/src/CvPad.cpp
	# ${SOURCE_DIR}/src/Foundry.cpp #needs make_element(OpaqueWidget*,...)
	# ${SOURCE_DIR}/src/FoundryExpander.cpp
	# ${SOURCE_DIR}/src/FourView.cpp


    ${SOURCE_DIR}/src/FundamentalUtil.cpp
    ${SOURCE_DIR}/src/comp/Components.cpp
    ${SOURCE_DIR}/src/comp/PanelTheme.cpp

    # Note we do not support:
    # ...

    # Note that we build our own plugin.cpp, not the one in the source repo
    # This is because we want to exclude the above modules from the plugin
    plugin.cpp 
)

target_include_directories(Impromptu PRIVATE ${SOURCE_DIR}/src .)

# target_compile_options(Befaco PRIVATE -Wno-double-promotion $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>)

set_property(TARGET Impromptu PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      Impromptu                                                 # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     Impromptu                                                 # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets                          # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Impromptu # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
