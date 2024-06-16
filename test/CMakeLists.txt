cmake_minimum_required(VERSION 3.24)

project(vedoTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(vedo REQUIRED)
  find_package(VTK REQUIRED)
  enable_testing()
endif()

include("../cmake/third_party/catch2.cmake")

# ---- Tests ----

# Define the function to get filename without path
function(get_filename_without_path filepath result)
    get_filename_component(filename ${filepath} NAME)
    set(${result} ${filename} PARENT_SCOPE)
endfunction()

# Define the function to find and add Catch2 tests
function(add_catch2_tests base_directory)
    # Find all subdirectories in the specified base directory
    file(GLOB subdirectories RELATIVE ${base_directory} ${base_directory}/*)

    foreach(subdirectory ${subdirectories})
        if(IS_DIRECTORY ${base_directory}/${subdirectory})
            # Process each subdirectory separately
            file(GLOB test_files "${base_directory}/${subdirectory}/*.cpp")

            foreach(test_file ${test_files})
                # Get the filename without path for the test executable name
                get_filename_component(test_name ${test_file} NAME_WE)

                # Create a test executable for each test file
                add_executable(${subdirectory}_${test_name} ${test_file})

                # Set the output directory to match the source directory structure
                set_target_properties(${subdirectory}_${test_name} PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/test/${subdirectory}")

                # Link Vedo and Catch2 to the test executable
                target_link_libraries(${subdirectory}_${test_name} PRIVATE vedo Catch2::Catch2WithMain ${VTK_LIBRARIES})

                # Define compile features
                target_compile_features(${subdirectory}_${test_name} PRIVATE cxx_std_23)

                # Add the test to CTest
                add_test(NAME ${subdirectory}_${test_name} COMMAND ${subdirectory}_${test_name})
            endforeach()
        else()
            # Handle files directly in the base directory
            if("${subdirectory}" MATCHES ".*\\.cpp$")
                get_filename_component(test_name ${subdirectory} NAME_WE)
                add_executable(${test_name} ${base_directory}/${subdirectory})

                # Set the output directory to match the source directory structure
                set_target_properties(${test_name} PROPERTIES
                    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/test/test")

                target_link_libraries(${test_name} PRIVATE vedo Catch2::Catch2WithMain ${VTK_LIBRARIES})

                # Define compile features
                target_compile_features(${test_name} PRIVATE cxx_std_23)

                add_test(NAME ${test_name} COMMAND ${test_name})
            endif()
        endif()
    endforeach()
endfunction()

# Example usage: Add all tests from the test/src/test directory
add_catch2_tests(${CMAKE_SOURCE_DIR}/test/src/test)

# ---- End-of-file commands ----

add_folders(Test)
