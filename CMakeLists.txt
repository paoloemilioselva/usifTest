cmake_minimum_required(VERSION 3.23)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TARGET "usifTest")
add_definitions(-DNOMINMAX)
add_definitions(-DTBB_USE_DEBUG)

project( 
    ${TARGET}
    LANGUAGES CXX C
)

# check target config
if(NOT TARGET_CONFIG)
    set( TARGET_CONFIG "usd-23.11")
endif()

string(REPLACE "-" ";" _t_config ${TARGET_CONFIG})
list(LENGTH _t_config _t_config_length)
if(_t_config_length LESS 2)
    MESSAGE(FATAL_ERROR "Wrong TARGET_CONFIG value " ${TARGET_CONFIG} )
endif()

list(GET _t_config 0 _target_name )

set( USD_LIBS "" )
if( _target_name MATCHES "houdini" )
    # not implemented yet
elseif( _target_name MATCHES "usd" )
    list(GET _t_config 1 USD_VERSION )
    set(USD_ROOT "C:\\dev\\usd-${USD_VERSION}" )
else()
    MESSAGE(FATAL_ERROR "Invalid target " ${_target_name})
endif()
include(cmake/FindUsd.cmake)

include(cmake/FindTBB.cmake)

add_library( ${TARGET} SHARED
    usifTest.cpp
    usifTest.h
    usifTestPlugin.h
    usifTestPlugin.cpp
)

target_compile_options( 
    ${TARGET}
    PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /O2 /wd4273 /Zi /experimental:external /external:W0>
    $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:RelWithDebInfo>>:/Ob0 /Od> 
)

target_link_options( 
    ${TARGET}
    PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/ignore:4217 /ignore:4049> 
)

target_link_directories( 
    ${TARGET}
    PRIVATE 
    ${USD_LIBRARY_DIR}
)

target_link_libraries(
    ${TARGET}
    PUBLIC
    ${USD_LIBS}
)

set(_installation_folder "")
if( _target_name MATCHES "houdini" )
    # not implemented yet
elseif( _target_name MATCHES "usd" )
    set(_installation_folder bin)
    install(TARGETS ${TARGET} RUNTIME DESTINATION ${_installation_folder}/usd-extra/plugin/usd)
    install(FILES ${CMAKE_SOURCE_DIR}/usd-extra/plugInfo.json DESTINATION ${_installation_folder}/usd-extra/plugin/usd/${TARGET}/resources )
endif()