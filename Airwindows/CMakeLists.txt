cmake_minimum_required(VERSION 3.22)
include(../metamodule-plugin-sdk/plugin.cmake)

project(AirwindowsModules 
    VERSION 0.1 
    DESCRIPTION "Airwindows Plugin for MetaModule" 
    LANGUAGES C CXX ASM
)

add_library(AirwindowsModules STATIC)


target_include_directories(AirwindowsModules PRIVATE 
	. 
    airwin2rack/src
)

target_sources(AirwindowsModules PRIVATE
	airwin_modules.cc
)

target_compile_definitions(AirwindowsModules PRIVATE 
	DISABLE_CONSOLE
)

# add_subdirectory(airwin2rack)
# target_compile_options(airwin-registry PRIVATE "-Wno-misleading-indentation;-Wno-unused-variable;-Wno-stringop-truncation")
# target_link_libraries(AirwindowsModules PUBLIC airwin-registry)
# target_link_libraries(airwin-registry arch_mp15x_a7)

#### from airwin2rack/CMakeLists.txt:
include(airwin2rack/src/autogen_airwin/CMakeLists.txt)
list(TRANSFORM AIRWIN_SOURCES PREPEND "airwin2rack/")

# file(GLOB AWDOC_RESOURCES_GLOB airwin2rack/res/awpdoc/*.txt)
# include(airwin2rack/cmake/CmakeRC.cmake)
# cmrc_add_resource_library(awdoc_resources ${AWDOC_RESOURCES_GLOB})
# target_link_libraries(AirwindowsModules PRIVATE awdoc_resources)

target_sources(AirwindowsModules PRIVATE
	airwin2rack/src/AirwinRegistry.cpp
	airwin2rack/src/airwin_consolidated_base.cpp

	${AIRWIN_SOURCES}
)
target_compile_definitions(AirwindowsModules PRIVATE _USE_MATH_DEFINES)

target_compile_options(AirwindowsModules PRIVATE 
	-Wno-unused-function
	-Wno-unused-value
	-Wno-unused-but-set-variable
	-Wno-multichar
	# Added for MM:
	-Wno-misleading-indentation
	-Wno-unused-variable
	-Wno-stringop-truncation
)



# Call this to link and create the plugin file
create_plugin(
    SOURCE_LIB      AirwindowsModules
    PLUGIN_NAME     Airwin2Rack                  # This must match the brand "slug" used in VCV Rack
    SOURCE_ASSETS   ${CMAKE_CURRENT_LIST_DIR}/assets
    DESTINATION     ${CMAKE_CURRENT_LIST_DIR}/../metamodule-plugins/Airwin2Rack
)

