cmake_minimum_required(VERSION 3.16)
project(Wordleship_Simple VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Find and install Gtest###
### From the Gtest documentation ###
option (BUILD_GMOCK "Build GoogleMock" OFF)
if(BUILD_GMOCK)
    include(FetchContent)
    FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
endif()
#########################

set (SOURCES 
    src/main.cpp 
    src/Grid.cpp 
    src/WordLoader.cpp 
    src/Game.cpp
    src/AIPlayer.cpp
    src/GameInput.cpp)

add_executable(Wordleship_Simple ${SOURCES})

if (BUILD_GMOCK)
    # Note: this needs to come before the add_subdirectory(test) so that ctest can find the test executable
    enable_testing()
    add_subdirectory(test)
endif()

## Copy word list to build directory
set(copy_source_dir "${CMAKE_SOURCE_DIR}/src")
set(copy_dest_dir "${CMAKE_BINARY_DIR}")
set(copy_file_name "wordlist.csv")

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${copy_source_dir}/${copy_file_name}" "${copy_dest_dir}/${copy_file_name}"
    COMMENT "Copying ${copy_file_name} to build directory"
)