find_package(Catch2 REQUIRED)
if (NOT Catch2_FOUND)
    include(FetchContent)
    FetchContent_Declare(
    catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.6.0 # or the latest tag
    )
    FetchContent_MakeAvailable(catch2)
endif()
include(Catch)
