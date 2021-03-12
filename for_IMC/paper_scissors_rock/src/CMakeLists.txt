file(GLOB_RECURSE SRCS "*.cc")

# Make an automatic library - will be static or dynamic based on user setting.
add_library(paper_scissors_rock ${SRCS})

# We need this directory, and users of our library will need it too.
target_include_directories(paper_scissors_rock PUBLIC ../include)
