# The library codes
add_subdirectory(src)

# The executable codes
add_subdirectory(apps)

if (${BUILD_TESTING})
    add_subdirectory(tests)
endif()
