cmake_minimum_required(VERSION 2.8)

project (rapidmp)
enable_testing()

include(CheckIncludeFiles)
include(CheckCXXSourceCompiles)

# build type
set(CMAKE_BUILD_TYPE Release)

# compile option (Debug) 
set(CMAKE_CXX_FLAGS_DEBUG "-g -Wall -Wextra -Wno-array-bounds -Werror -std=c++0x")
set(CMAKE_C_FLAGS_DEBUG "-g -Wall -Wextra -Wno-array-bounds -Werror")

# compile option (Release)
set(CMAKE_CXX_FLAGS_RELEASE "-W -Wall -Wextra -Wno-array-bounds -Werror -std=c++0x -O3")
set(CMAKE_C_FLAGS_RELEASE "-W -Wall -Wextra -Wno-array-bounds -Werror -O3")

#if you don't want the full compiler output, remove the following line
set(CMAKE_VERBOSE_MAKEFILE ON)

set(Boost_USE_MULTITHREADED ON)
find_package(Boost 1.49.0 COMPONENTS unit_test_framework REQUIRED )
if (NOT Boost_FOUND)
  message(SEND_ERROR "Required package Boost is not exist.")
endif (NOT Boost_FOUND)

INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR}/include ${Boost_INCLUDE_DIRS} )
link_directories( ${Boost_LIBRARY_DIRS} )
subdirs( include test )

