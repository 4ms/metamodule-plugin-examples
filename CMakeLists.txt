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
    CVfunk
    ChowDSP
    CountModula
    DrumKit
    Fundamental
    Geodesics
    kocmoc
    NANOModules
    OrangeLine
    RebelTech
    Sapphire
    Venom
)

foreach(plugin ${PLUGINS})

    set(project_cmake_root ${plugin})
    if ((plugin STREQUAL "Fundamental") OR (plugin STREQUAL "CountModula") OR (plugin STREQUAL "Sapphire"))
        set(project_cmake_root "${plugin}/metamodule")
    endif()

    message("Building ${plugin} from ${project_cmake_root}")

    ExternalProject_Add(
        ${plugin}
        SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/${project_cmake_root}
        CMAKE_ARGS -DMETAMODULE_SDK_DIR=${CMAKE_CURRENT_LIST_DIR}/metamodule-plugin-sdk -DINSTALL_DIR=${CMAKE_CURRENT_LIST_DIR}/metamodule-plugins
        BUILD_ALWAYS true
        INSTALL_COMMAND ""
    )

endforeach()


