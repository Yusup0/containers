cmake_minimum_required(VERSION 3.5)

project(containers VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -pedantic")

find_package(GTest REQUIRED)
include(GoogleTest)
enable_testing()

add_executable(tests ./test/containers_test.cc)
target_link_libraries(tests GTest::gtest_main)

gtest_discover_tests(tests)

#if(CMAKE_COMPILER_IS_GNUCXX)
LIST(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/gcov_modules")
include(CodeCoverage)
APPEND_COVERAGE_COMPILER_FLAGS()

SETUP_TARGET_FOR_COVERAGE_LCOV(NAME tests_coverage
                              EXECUTABLE tests
                              DEPENDENCIES tests
                              EXCLUDE "${PROJECT_SOURCE_DIR}/test/*"
                              "/usr/*"
                              "/Applications/*"
                          )
#endif()
