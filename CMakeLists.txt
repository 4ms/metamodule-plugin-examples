cmake_minimum_required(VERSION 3.22)

include(${CMAKE_CURRENT_LIST_DIR}/metamodule-plugin-sdk/plugin.cmake)
include(ExternalProject)

project(MetaModulePluginExamples
    VERSION 0.1
    DESCRIPTION  "Examples of building plugins for MetaModule"
    LANGUAGES C CXX ASM
)

set(PLUGINS 
    Valley
    Bogaudio
    Geodesics
    chowdsp
    kocmoc
)

foreach(plugin ${PLUGINS})

    message("Building ${plugin}")

    ExternalProject_Add(
        ${plugin}
        SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/${plugin}
        BUILD_ALWAYS true
        INSTALL_COMMAND ""
    )

endforeach()


