cmake_minimum_required(VERSION 3.16)
project(Wordleship_Simple VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Find and install Gtest###
### From the Gtest documentation ###
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
#########################

add_executable(Wordleship_Simple src/main.cpp src/Grid.cpp)

# Note: this needs to come before the add_subdirectory(test) so that ctest can find the test executable
enable_testing()
add_subdirectory(test)