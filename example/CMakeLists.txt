cmake_minimum_required(VERSION 3.24)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")  # -Wpedantic
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(vedoExamples CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

if(PROJECT_IS_TOP_LEVEL)
  find_package(vedo REQUIRED)
  find_package(VTK REQUIRED)
endif()

add_custom_target(run-examples)

function(add_example NAME)
  get_filename_component(TARGET_NAME "${NAME}" NAME_WE)
  get_filename_component(DIR "${NAME}" PATH)
  if (DIR)
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/example/example/${DIR}")
  else()
    set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/example/example")
  endif()

  add_executable("${TARGET_NAME}" "${NAME}.cpp")
  set_target_properties("${TARGET_NAME}" PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
  target_link_libraries("${TARGET_NAME}" PRIVATE vedo ${VTK_LIBRARIES})
  target_compile_features("${TARGET_NAME}" PRIVATE cxx_std_23)
  
  add_custom_target("run_${TARGET_NAME}" COMMAND "${OUTPUT_DIR}/${TARGET_NAME}" VERBATIM)
  add_dependencies("run_${TARGET_NAME}" "${TARGET_NAME}")
  add_dependencies(run-examples "run_${TARGET_NAME}")
endfunction()

add_example(cpp_version)
add_example(load_file)

add_example(mesh/plot_wireframe)

add_example(shapes/convex_hull)

add_folders(Example)
