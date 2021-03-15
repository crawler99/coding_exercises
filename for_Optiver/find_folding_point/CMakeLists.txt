add_library(find_folding_point INTERFACE)

target_include_directories(find_folding_point INTERFACE include)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()