if (CMAKE_VERSION VERSION_LESS 3.18)
  set(DEV_MODULE Development)
else()
  set(DEV_MODULE Development.Module)
endif()

execute_process(
    COMMAND which python3
    OUTPUT_VARIABLE Python3_EXECUTABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Execute Python script to get Python include directories
execute_process(
    COMMAND python3 -c "from sysconfig import get_paths; print(get_paths()['include'])"
    OUTPUT_VARIABLE PYTHON_INCLUDE_DIRS
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Include Python headers
include_directories(${PYTHON_INCLUDE_DIRS})
find_package(Python 3.10 COMPONENTS Interpreter ${DEV_MODULE} REQUIRED)
execute_process(
    COMMAND which python3
    OUTPUT_VARIABLE PYTHON_EXECUTABLE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Detect the installed nanobind package and import it into CMake
execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -m nanobind --cmake_dir
    OUTPUT_STRIP_TRAILING_WHITESPACE 
    OUTPUT_VARIABLE NANOBIND_CMAKE_DIR
  )

list(APPEND CMAKE_PREFIX_PATH "${NANOBIND_CMAKE_DIR}")
find_package(nanobind CONFIG REQUIRED)

string(REPLACE "/cmake" "/include" NANOBIND_INCLUDE_DIR ${NANOBIND_CMAKE_DIR})
include_directories(${NANOBIND_INCLUDE_DIR})

# Check if nanobind include directory is found
if(NOT NANOBIND_INCLUDE_DIR)
    message(FATAL_ERROR "Nanobind include directory not found. Please specify the path manually.")
endif()

nanobind_add_module(
  vedopy 
  
  NOMINSIZE 

  # Target the stable ABI for Python 3.12+, which reduces
  # the number of binary wheels that must be built. This
  # does nothing on older Python versions
  STABLE_ABI

  # Build libnanobind statically and merge it into the
  # extension (which itself remains a shared library)
  #
  # If your project builds multiple extensions, you can
  # replace this flag by NB_SHARED to conserve space by
  # reusing a shared libnanobind across libraries
  NB_STATIC

  src/main.cpp
)
