cmake_minimum_required(VERSION 2.8)

project(paper_scissors_rock)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRCS "src/*.cc" "app/*.cc")
add_executable(${PROJECT_NAME} ${SRCS})

if (${BUILD_TESTS})
  message("Building tests for " ${PROJECT_NAME} " ...")

  include_directories(${GTEST_ROOT}/include)
  include_directories(${GMOCK_ROOT}/include)
  link_directories(${GTEST_ROOT}/lib)
  link_directories(${GMOCK_ROOT}/lib)

  file(GLOB TEST_SRCS "test/*.cc")

  set(EXECUTABLE "runUnitTests_${PROJECT_NAME}")

  add_executable(${EXECUTABLE} ${TEST_SRCS})

  # Standard linking to gtest stuff.
  target_link_libraries(${EXECUTABLE} gtest gtest_main)

  # Extra linking for the project.
  # target_link_libraries(${EXECUTABLE} ${PROJECT_NAME})

  # Add tests
  add_test(NAME TestPaperScissorsRock COMMAND ${EXECUTABLE})
endif()
