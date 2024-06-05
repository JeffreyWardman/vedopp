cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")  # -Wpedantic
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(
    vedo
    VERSION 0.0.0
    DESCRIPTION "A C++-based VTK library."
    HOMEPAGE_URL "https://github.com/JeffreyWardman/vedopp"
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)

if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()


# ---- Declare library ----
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/vedo)
add_library(
    vedo
    STATIC
    ${SOURCE_DIR}/core/common_algorithms.cpp
    ${SOURCE_DIR}/core/data_array_helper.cpp
    ${SOURCE_DIR}/core/point_algorithms.cpp
    ${SOURCE_DIR}/file_io/helpers.cpp
    ${SOURCE_DIR}/file_io/reader.cpp
    ${SOURCE_DIR}/plotter/plotter.cpp
    ${SOURCE_DIR}/plotter/show.cpp
    ${SOURCE_DIR}/points/points.cpp

)
target_include_directories(
    vedo ${warning_guard}
    PUBLIC
    "\$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>"
)
target_include_directories(vedo PUBLIC /opt/homebrew/include)

include(cmake/third_party/fmt.cmake)
include(cmake/third_party/vtk.cmake)

# ---- Examples ----

option(BUILD_EXAMPLES "Build examples tree." ON)
if(BUILD_EXAMPLES)
  add_subdirectory(example)
endif()

# ---- Python ----

# option(BUILD_PYTHON "Build python wrapper." true)
# if(BUILD_PYTHON)
#   message("NOT IMPLEMENTED")
# endif()

# ---- Developer mode ----

if(NOT VEDO_DEVELOPER_MODE)
  return()
endif()

include(cmake/dev-mode.cmake)
