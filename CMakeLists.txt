
# Project Properties
CMAKE_MINIMUM_REQUIRED (VERSION 2.6)
PROJECT (QuantSystem)
SET (APPLICATION_NAME "Quant System")
SET (quantsystem_VERSION_MAJOR 0)
SET (quantsystem_VERSION_MINOR 1)
SET (quantsystem_VERSION_PATCH 0)
SET (quantsystem_VERSION_DECORATOR "")

enable_testing()

option(quantsystem_build_tests "Build all of quantsystem' own tests." ON)
option(quantsystem_build_samples "Build quantsystem sample programs." ON)

# Debugging Options
SET (CMAKE_VERBOSE_MAKEFILE 1) # Use 1 for debugging, 0 for release

# Project Output Paths
SET (MAINFOLDER ${PROJECT_SOURCE_DIR})
SET (EXECUTABLE_OUTPUT_PATH "${MAINFOLDER}/bin")
SET (LIBRARY_OUTPUT_PATH "${MAINFOLDER}/lib")
set (QUANTSYSTEM_INSTALL_LIB_DIR ${LIBRARY_OUTPUT_PATH})
set (QUANTSYSTEM_INSTALL_INCLUDE_DIR ${MAINFOLDER}/include/quantsystem)
set (QUANTSYSTEM_INSTALL_DIR ${MAINFOLDER}/bin/main)

# Options
option(quansystem_build_tests "Build all the own tests." ON)
option(quantsystem_build_sammples "Build smaple programs." ON)

if (MSVC)
  option(gtest_force_shared_crt "Force Gmock to use standard compiler flags" ON)
  ADD_DEFINITIONS(-DCOMPILER_MSVC -DNOMINMAX -DWIN32_LEAN_AND_MEAN /Zm1000 /J
                  -D_WIN32_WINNT=0x0600
                  -D_UNICODE -DUNICODE
                  -DGFLAGS_DLL_DECL= -DGFLAGS_DLL_DEFINE_FLAG=
                  -D_VARIADIC_MAX=10 -DGLOG_NO_ABBREVIATED_SEVERITIES)
                set(GLOG_LIBRARY libglog)
                set(CURL_LIBRARY libcurl_imp)
else()
  set(GLOG_LIBRARY glog)
  set(CURL_LIBRARY curl)
endif()

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  # using regular Clang or AppleClang
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall
-Wconversion -Wshadow -Wno-sign-conversion")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  # using GCC
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall
  #-Wconversion -Wshadow -Wextra")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
endif()

# Project Search Paths
SET (CMAKE_MODULE_PATH "${MAINFOLDER}/_cmake_scripts")
include_directories("${MAINFOLDER}/src")

# Library
link_directories("${LIBRARY_OUTPUT_PATH}")

# Add thirdparty packages
include(gmock)
include(introspect)

# Configure Files
configure_file(
  "${PROJECT_SOURCE_DIR}/src/quantsystem/config.h.in"
  "${PROJECT_SOURCE_DIR}/src/quantsystem/config.h")

#
# Add Build Targets
#
ADD_SUBDIRECTORY(src)

if (quansystem_build_samples)
  add_subdirectory(src/samples)
endif()

#
# Add Documentation Targets
#
#INCLUDE (DocumentationTargets)


