cmake_minimum_required(VERSION 2.8)

project(solution)

include_directories(${PROJECT_SOURCE_DIR})

if (${BUILD_TESTS})
  message("Building tests for " ${PROJECT_NAME} " ...")

  include_directories(${GTEST_ROOT}/include)
  include_directories(${GMOCK_ROOT}/include)
  link_directories(${GTEST_ROOT}/lib64)
  link_directories(${GMOCK_ROOT}/lib64)

  file(GLOB TEST_SRCS "test/*.cc")

  set(EXECUTABLE "runUnitTests_${PROJECT_NAME}")

  add_executable(${EXECUTABLE} ${TEST_SRCS})

  # Standard linking to gtest stuff.
  target_link_libraries(${EXECUTABLE} gtest gtest_main)

  # Extra linking for the project.
  # target_link_libraries(${EXECUTABLE} ${PROJECT_NAME})

  # Add tests
  add_test(NAME TestSolution COMMAND ${EXECUTABLE})
endif()

