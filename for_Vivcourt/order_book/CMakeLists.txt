add_library(decoder INTERFACE)

target_include_directories(decoder INTERFACE include)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()