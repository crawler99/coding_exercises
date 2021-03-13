add_library(divide_integer_sequence INTERFACE)

target_include_directories(divide_integer_sequence INTERFACE include)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()