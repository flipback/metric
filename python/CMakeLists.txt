cmake_minimum_required(VERSION 3.10)
set(CMAKE_VERBOSE_MAKEFILE ON)

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

set(Boost_DEBUG on)
find_package(Boost REQUIRED)

SET(BLA_STATIC ON)
find_package(LAPACK)
find_package(LAPACK)
if(NOT LAPACK_FOUND)
	set(BLA_VENDOR Intel10_64lp_seq)
	message("Generic LAPACK not Found, trying Intel MKL")
	if(NOT BLAS_ROOT)
	     if(WIN32)
		     set(BLAS_ROOT "C:/Program\ Files\ (x86)/IntelSWTools/compilers_and_libraries/windows/mkl/lib/intel64")
	     endif()
	endif()
	find_package(LAPACK QUIET)
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