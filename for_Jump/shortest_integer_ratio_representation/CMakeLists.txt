add_library(shortest_integer_ratio_representation INTERFACE)

target_include_directories(shortest_integer_ratio_representation INTERFACE include)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()
