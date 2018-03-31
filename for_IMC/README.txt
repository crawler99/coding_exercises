1. There are two projects included in this package, namely 'shapes' and 'paper_scissors_rock'.
2. gtest is used for unit testing. It is required to properly build this package.
3. For 'shapes':
     - The requirement is pretty straightforward. So there are very little comments and the codes should be self-explanatory.
     - There will be no separate executable generated for 'shapes' during building. Instead, you can run 'make test' to verify all the test cases are passed.
4. For 'paper_scissors_rock':
     - There will be an application named 'paper_scissors_rock' generated during building. Run 'make install' to move it to the project directory and run it.
     - Some necessary comments are put into the source files.
5. Build steps:
     - ./cmake_release.sh
     - cd build/release
     - make
     - make test
     - make install
