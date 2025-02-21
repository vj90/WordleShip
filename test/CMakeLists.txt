# Add test executable
add_executable(test1 test.cpp)

# Link the test executable with GoogleTest 
target_link_libraries(test1 PRIVATE GTest::gtest_main)

# Enable GoogleTest integration
include(GoogleTest)
gtest_discover_tests(test1)