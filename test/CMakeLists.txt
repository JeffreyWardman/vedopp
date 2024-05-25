cmake_minimum_required(VERSION 3.14)

project(vedoTests LANGUAGES CXX)

include(../cmake/project-is-top-level.cmake)
include(../cmake/folders.cmake)

# ---- Dependencies ----

if(PROJECT_IS_TOP_LEVEL)
  find_package(vedo REQUIRED)
  enable_testing()
endif()

# ---- Tests ----

add_executable(vedo_test src/vedo_test.cpp)
target_link_libraries(vedo_test PRIVATE vedo)
# target_link_libraries(vedo_test PRIVATE vedo::vedo)
target_compile_features(vedo_test PRIVATE cxx_std_23)

add_test(NAME vedo_test COMMAND vedo_test)

# ---- End-of-file commands ----

add_folders(Test)
