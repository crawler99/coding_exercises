add_library(decoder INTERFACE)

target_include_directories(decoder INTERFACE include)

# The executable codes
add_subdirectory(apps)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()