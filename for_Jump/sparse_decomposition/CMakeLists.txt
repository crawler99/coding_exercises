add_library(sparse_decomposition INTERFACE)

target_include_directories(sparse_decomposition INTERFACE include)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()
