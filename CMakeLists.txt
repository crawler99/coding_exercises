# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.1...3.11)

# Start project.
# Listing the version is nice here since it sets lots of useful variables.
project(coding_exercises VERSION "1.0" DESCRIPTION "Exercises" LANGUAGES CXX)

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
    message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). "
                        "Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# If you set any CMAKE_ variables, that can go here.
# (But usually don't do this, except maybe for C++ standard)

# Notice: The following settings are OK for the final target,
# but for libraries we should use target_compile_features and
# set_target_properties as replacements of following settings.

# Notice: Don't set manual flags yourself. You'll then become
# responsible for mainting correct flags for every release of
# every compiler, error messages for unsupported compilers won't
# be useful, and some IDEs might not pick up the manual flags.

# Requires C++17 (set CXX_STANDARD property on all targets)
set(CMAKE_CXX_STANDARD 17 CACHE STRING "The C++ standard to use")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# Optional: it ensures -std=c++11 vs. something like -std=g++11
set(CMAKE_CXX_EXTENSIONS OFF)

# Much of the time, CMake will include this -fPIC flag for SHARED or MODULE libraries.
# If explicity needed, we can set it globally or on particular targets.
#set(CMAKE_POSITION_INDEPENDENT_CODE ON)
#set_target_properties(<target> PROPERTIES POSITION_INDEPENDENT_CODE ON)

# Set -flto globally.
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION ON)

# CMake normally does a "non-release, non debug" empty build type.
# We prefer to set the default build type to Release.
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
        STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui.
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
        "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Set path to find helper modules (Find*.cmake)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Find packages
find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

# Usually do not init/update submodules automatically,
# as you may do development on the submodules as well.

# Enable testing and set a BUILD_TESTING option (default on) so users can turn testing on and off.
# The reason do compare project names is that if someone else includes this package
# and they use BUILD_TESTING, they probably do not want your tests to build.
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
    if(BUILD_TESTING)
        add_subdirectory("extern/googletest" EXCLUDE_FROM_ALL)
        # Use the GoogleTest module to help use the Google Test infrastructure.
        include(GoogleTest)
    endif()
endif()

# A helper macro to utilize GoogleTest module to add tests.
macro(package_add_test LIBNAME)
    # Create an exectuable in which the tests will be stored.
    set(EXECUTABLE "test_${LIBNAME}")
    add_executable(${EXECUTABLE} ${ARGN})
    # Link the Google test infrastructure, mocking library, and a default main fuction to the test executable.
    # Remove g_test_main if writing an own main function.
    target_link_libraries(${EXECUTABLE} ${LIBNAME} gtest gmock gtest_main)
    gtest_discover_tests(
        ${EXECUTABLE}
        # Set working directory to project root so that we can find test data via paths relative to the project root.
        # If not set, the working directory will be the one where the executed test binary locates.
        WORKING_DIRECTORY ${PROJECT_BINARY_DIR}
    )
endmacro()

# A helper macro to list all sub-dirs
function(SUBDIRLIST result curdir)
  file(GLOB children RELATIVE ${curdir} ${curdir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${curdir}/${child})
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist} PARENT_SCOPE)
endfunction()

# Add library dirs
add_subdirectory(for_IMC)
add_subdirectory(for_SIG)
add_subdirectory(for_Optiver)
add_subdirectory(for_Vivcourt)
add_subdirectory(for_Jump)
