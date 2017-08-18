cmake_minimum_required(VERSION 2.8)

# GCC settings so we can use the lastest features
# NOTE: The compiler must be set before any project.
set(CMAKE_C_COMPILER "${GCC_ROOT}/bin/gcc" CACHE PATH "Path to C compiler")
set(CMAKE_CXX_COMPILER "${GCC_ROOT}/bin/g++" CACHE PATH "Path to C++ compiler")

# Adding a variable 'test' to let CMake know if we need to build test programs.
# Turn it on with 'cmake -Dvarname=ON'
option(test "Build tests." ON)

# Compilation env settings
function(Add_LD_LIBRARY_PATH PATH)
    string(FIND ENV{LD_LIBRARY_PATH} "${PATH}" _PATH_IDX)
    if (_PATH_IDX EQUAL -1)
        set(ENV{LD_LIBRARY_PATH} "${PATH}:$ENV{LD_LIBRARY_PATH}" PARENT_SCOPE)
    endif()
endfunction()

Add_LD_LIBRARY_PATH("${GCC_ROOT}/lib")
Add_LD_LIBRARY_PATH("${GCC_ROOT}/lib64")

set(CMAKE_CXX_FLAGS "-g -Wall")

add_compile_options(-std=c++14)

set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -pthread")
set(CMAKE_CXX_CREATE_SHARED_LIBRARY "${CMAKE_CXX_CREATE_SHARED_LIBRARY} -pthread")

# Add test dirs
add_subdirectory(1_Two_Sum)
add_subdirectory(2_Add_Two_Numbers)
add_subdirectory(3_Longest_Substring_Without_Repeating_Characters)

#
project(LeetCode)
