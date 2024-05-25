include(FetchContent)

set(VTK_VERSION 9.3.0)
set(VTK_BUILD_TESTING OFF)
set(VTK_BUILD_EXAMPLES OFF)
set(VTK_USE_CUDA OFF)
set(VTK_WRAP_PYTHON OFF)

FetchContent_Declare(
  VTK
  URL https://gitlab.kitware.com/vtk/vtk/-/archive/v${VTK_VERSION}/vtk-v${VTK_VERSION}.zip
  DOWNLOAD_EXTRACT_TIMESTAMP 1
)
# Ensure the build directory for VTK exists
# FetchContent_GetProperties(VTK)
# if(NOT vtk_POPULATED)
#     FetchContent_Populate(VTK)
#     add_subdirectory(${vtk_SOURCE_DIR} ${vtk_BINARY_DIR})
# endif()

# FetchContent_MakeAvailable(VTK)

# find_package(VTK ${VTK_VERSION} REQUIRED)
# include(mico ${VTK_USE_FILE})

find_package(VTK REQUIRED COMPONENTS
  CommonCore
)


if (NOT VTK_FOUND)
  message(FATAL_ERROR "Unable to find the VTK build folder.")
endif()

# Prevent a "command line is too long" failure in Windows.
set(CMAKE_NINJA_FORCE_RESPONSE_FILE "ON" CACHE BOOL "Force Ninja to use response files.")
target_link_libraries(vedo PRIVATE ${VTK_LIBRARIES})

# vtk_module_autoinit is needed
vtk_module_autoinit(
  TARGETS vedo
  MODULES ${VTK_LIBRARIES}
)
