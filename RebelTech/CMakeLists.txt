cmake_minimum_required(VERSION 3.22)

if(NOT "${METAMODULE_SDK_DIR}" STREQUAL "")
	message("METAMODULE_SDK_DIR set by CMake variable ${METAMODULE_SDK_DIR}")
elseif (DEFINED ENV{METAMODULE_SDK_DIR})
    set(METAMODULE_SDK_DIR "$ENV{METAMODULE_SDK_DIR}")
	message("METAMODULE_SDK_DIR set by environment variable ${METAMODULE_SDK_DIR}")
else()
    set(METAMODULE_SDK_DIR "${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugin-sdk")
	message("METAMODULE_SDK_DIR set to default: ${METAMODULE_SDK_DIR}")
endif()

include(${METAMODULE_SDK_DIR}/plugin.cmake)

project(RebelTechMetaModulePlugin 
    VERSION     0.1 
    DESCRIPTION "RebelTech Plugin for MetaModule" 
    LANGUAGES   C CXX ASM
)

add_library(RebelTech STATIC)

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

set_property(TARGET RebelTech PROPERTY CXX_STANDARD 20)

if("${INSTALL_DIR}" STREQUAL "")
    set(INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins)
endif()

create_plugin(
    SOURCE_LIB      RebelTech                           # This is the cmake target name (defined in add_target)
    PLUGIN_NAME     RebelTech                           # This must match the brand "slug" used in VCV Rack
    PLUGIN_JSON     ${SOURCE_DIR}/plugin.json           # Path to the plugin.json file used by VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets    # Path to the assets/ dir containing the PNGs
    DESTINATION     ${INSTALL_DIR}/                     # Dir where plugin .mmplugin file should be put
)
