cmake_minimum_required(VERSION 3.10)
if (POLICY CMP0025)
  cmake_policy(SET CMP0025 NEW)
endif ()
if (POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

set(CMAKE_VERBOSE_MAKEFILE ON)

if(CMAKE_SYSTEM_NAME MATCHES Windows)
    if(CMAKE_SYSTEM_PROCESSOR MATCHES ".*64$")
        message("Build architecture: x64")
        set(CMAKE_GENERATOR_PLATFORM x64)
    else()
        message("Build architecture: x86")
        set(CMAKE_GENERATOR_PLATFORM Win32)
    endif()
endif()

#set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(PYBIND11_CPP_STANDARD -std=c++1z)

project(metric_py DESCRIPTION "metric python binding")

SET(SOURCE_PATH ${CMAKE_SOURCE_DIR}/src)
if(NOT DEFINED ENV{METRIC_SOURCE_PATH})
    SET(METRIC_SOURCE_PATH ${CMAKE_SOURCE_DIR}/..)
else ()
    SET(METRIC_SOURCE_PATH $ENV{METRIC_SOURCE_PATH})
endif()

find_package(Python3 COMPONENTS Interpreter Development)

# set(Boost_DEBUG on)
find_package(Boost REQUIRED)

SET(BLA_STATIC ON)
find_package(LAPACK)
if(NOT LAPACK_FOUND)
    if(WIN32)
        message("Generic LAPACK not Found, trying Intel MKL")
        set(BLAS_ROOT "C:/Program\ Files\ (x86)/IntelSWTools/compilers_and_libraries/windows/mkl/lib/intel64")
        find_package(LAPACK)
        if(NOT LAPACK_FOUND)
	        SET(BLAS_ROOT "C:/opt/lib/")
	    endif()
	    find_package(LAPACK REQUIRED)
    endif()
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
else ()
find_package(PkgConfig REQUIRED)
endif ()

set(COMMON_LIBRARIES
    #${Boost_LIBRARIES}
    ${LAPACK_LIBRARIES}
)

SET(HEADER_INCLUDE_PATH
    ${Boost_INCLUDE_DIR}
    ${SOURCE_PATH}
    ${METRIC_SOURCE_PATH}
)

include_directories(${HEADER_INCLUDE_PATH})

add_subdirectory(pybind11)
add_subdirectory(src)