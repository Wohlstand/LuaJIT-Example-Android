cmake_minimum_required(VERSION 3.4.1)
project(HeleZhe_JniBind C CXX)


# Define variables required for work of "library_luajit.cmake" code

include(ExternalProject)

string(TOLOWER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE_LOWER)
if (CMAKE_BUILD_TYPE_LOWER STREQUAL "release")
    add_definitions(-DNDEBUG)
endif()

if(CMAKE_BUILD_TYPE_LOWER STREQUAL "debug" AND NOT ANDROID)
    set(PGE_LIBS_DEBUG_SUFFIX "d")
else()
    set(PGE_LIBS_DEBUG_SUFFIX "")
endif()

if(ANDROID)
    set(DEPENDENCIES_INSTALL_DIR ${CMAKE_BINARY_DIR}/output-deps)
else()
    set(DEPENDENCIES_INSTALL_DIR ${CMAKE_BINARY_DIR}/output)
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output/bin)

foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    message("--> ${OUTPUTCONFIG}")
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}")
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

if(ANDROID)
    set(ANDROID_PLATFORM "android-16")
    set(ANDROID_CMAKE_FLAGS
            "-DANDROID_ABI=${ANDROID_ABI}"
            "-DANDROID_NDK=${ANDROID_NDK}"
            "-DANDROID_STL=c++_static"
            "-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
            "-DANDROID_PLATFORM=${ANDROID_PLATFORM}"
            "-DANDROID_TOOLCHAIN=${ANDROID_TOOLCHAIN}"
            "-DANDROID_NATIVE_API_LEVEL=${ANDROID_NATIVE_API_LEVEL}"
            "-DCMAKE_MAKE_PROGRAM=${CMAKE_MAKE_PROGRAM}"
            "-DANDROID_ARM_NEON=${ANDROID_ARM_NEON}"
            )
endif()

# Include the "library_luajit.cmake" code
include(library_luajit.cmake)

add_library(helezhe-jni SHARED
    src/main/cpp/helezhe-jni.c
)
add_dependencies(helezhe-jni LuaJIT_local)

target_include_directories(helezhe-jni PUBLIC
    src/main/cpp/include
    ${DEPENDENCIES_INSTALL_DIR}/include
)

find_library(
    # Sets the name of the path variable.
    log-lib
    # Specifies the name of the NDK library that
    # you want CMake to locate.
    log
)

target_link_libraries(
    # Specifies the target library.
    helezhe-jni
    # Links the target library to the log library
    # included in the NDK.
    ${log-lib}
    OpenSLES
    # LINK the built LuaJit here
    ${libLuaJit_Lib}
)
