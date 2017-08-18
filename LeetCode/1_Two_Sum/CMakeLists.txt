cmake_minimum_required(VERSION 2.8)

project(1_Two_Sum)

include_directories(${PROJECT_SOURCE_DIR})

if (test)
  enable_testing()

  include_directories(${GTEST_ROOT}/include)
  include_directories(${GMOCK_ROOT}/include)
  link_directories(${GTEST_ROOT}/lib)
  link_directories(${GMOCK_ROOT}/lib)

  file(GLOB TEST_SRCS "test/*.cxx")

  add_executable(runUnitTests ${TEST_SRCS})

  # Standard linking to gtest stuff.
  target_link_libraries(runUnitTests gtest gtest_main)

  # Extra linking for the project.
  # target_link_libraries(runUnitTests ${PROJECT_NAME})

  # Add tests
  add_test(NAME testAll COMMAND runUnitTests)
endif()
