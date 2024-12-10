cmake_minimum_required(VERSION 3.22)

include(${CMAKE_CURRENT_LIST_DIR}/metamodule-plugin-sdk/plugin.cmake)
include(ExternalProject)

project(MetaModulePluginExamples
    VERSION 0.1
    DESCRIPTION  "Examples of building plugins for MetaModule"
    LANGUAGES C CXX ASM
)

set(PLUGINS 
    Airwindows
    Bogaudio
    CountModula
    Geodesics
    OrangeLine
    RebelTech
    Valley
    chowdsp
    kocmoc
    NANO
    VCV-Fundamental
    Sapphire
    DrumKit
)

foreach(plugin ${PLUGINS})

    message("Building ${plugin}")

    ExternalProject_Add(
        ${plugin}
        SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/${plugin}
        CMAKE_ARGS -DMETAMODULE_SDK_DIR=${CMAKE_CURRENT_LIST_DIR}/metamodule-plugin-sdk -DINSTALL_DIR=${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins
        BUILD_ALWAYS true
        INSTALL_COMMAND ""
    )

endforeach()


