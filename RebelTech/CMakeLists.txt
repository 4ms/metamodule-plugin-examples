cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(RebelTechMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "RebelTech Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(RebelTech STATIC)

# convenient variable pointing to the VCV Rack repo
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/rebel-tech-vcv)

target_sources(RebelTech
    PRIVATE
    ${SOURCE_DIR}/src/CLK.cpp
    ${SOURCE_DIR}/src/Klasmata.cpp
    ${SOURCE_DIR}/src/Logoi.cpp
    ${SOURCE_DIR}/src/Phoreo.cpp
    ${SOURCE_DIR}/src/Stoicheia.cpp
    ${SOURCE_DIR}/src/Tonic.cpp

    ${SOURCE_DIR}/src/plugin.cpp
)

target_include_directories(RebelTech PRIVATE 
	${SOURCE_DIR}/src 
	# ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(RebelTech 
	PRIVATE 
	# -Wno-double-promotion 
	# $<$<COMPILE_LANGUAGE:CXX>:-Wno-deprecated-enum-float-conversion>
)

set_property(TARGET RebelTech PROPERTY CXX_STANDARD 20)


#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      RebelTech                                         # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     RebelTech                                         # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json                         # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets                  # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/  # Dir where plugin .mmplugin file should be put
)
