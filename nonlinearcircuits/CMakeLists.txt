cmake_minimum_required(VERSION 3.22)

#########################################################
# Step 1: Include plugin.cmake from the SDK. 
# You must do this before anything else since it defines the TOOLCHAIN
include(${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk/plugin.cmake)

#########################################################
# Step 2: Define your project name, vesion, etc
project(nonlinearcircuitsMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "nonlinearcircuits Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

#########################################################
# Step 3: Create a cmake target for your plugin and add all your sources, compile flags, includes, etc.
add_library(NonlinearCircuits STATIC)

# convenient variable pointing to the VCV Rack repo
set(NONLINEARCIRCUITS_DIR ${CMAKE_CURRENT_LIST_DIR}/nonlinearcircuits)

target_sources(NonlinearCircuits
    PRIVATE
    ${NONLINEARCIRCUITS_DIR}/src/4Seq.cpp
    ${NONLINEARCIRCUITS_DIR}/src/8BitCipher.cpp
    ${NONLINEARCIRCUITS_DIR}/src/BOOLs.cpp
    ${NONLINEARCIRCUITS_DIR}/src/DivideConquer.cpp
    ${NONLINEARCIRCUITS_DIR}/src/DivineCMOS.cpp
    ${NONLINEARCIRCUITS_DIR}/src/DoubleNeuron.cpp
    ${NONLINEARCIRCUITS_DIR}/src/GENiE.cpp
    ${NONLINEARCIRCUITS_DIR}/src/LetsSplosh.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Neuron.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Numberwang.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Router.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Segue.cpp
    ${NONLINEARCIRCUITS_DIR}/src/SlothApathy.cpp
    ${NONLINEARCIRCUITS_DIR}/src/SlothInertia.cpp
    ${NONLINEARCIRCUITS_DIR}/src/SlothTorpor.cpp
    ${NONLINEARCIRCUITS_DIR}/src/SquidAxon.cpp
    ${NONLINEARCIRCUITS_DIR}/src/Statues.cpp
    ${NONLINEARCIRCUITS_DIR}/src/TripleSloth.cpp
    ${NONLINEARCIRCUITS_DIR}/src/NLCShared.cpp
    ${NONLINEARCIRCUITS_DIR}/src/NLC.cpp
)

target_include_directories(NonlinearCircuits PRIVATE ${NONLINEARCIRCUITS_DIR}/src)

set_property(TARGET NonlinearCircuits PROPERTY CXX_STANDARD 20)

target_compile_options(NonlinearCircuits
    PRIVATE
    -Wno-double-promotion
)

#########################################################
# Step 4: call create_plugin()
create_plugin(
    SOURCE_LIB      NonlinearCircuits                  # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     nonlinearcircuits                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/nonlinearcircuits # Path to where you want the plugin dir output: it can be shared between multiple plugins
)
