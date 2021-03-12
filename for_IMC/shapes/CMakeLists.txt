add_library(shapes INTERFACE)

target_include_directories(shapes INTERFACE include)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()