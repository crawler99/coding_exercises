1. There are two projects included in this file package, namely 'shapes' and 'paper_scissors_rock'.
2. For 'shapes':
     - The requirement is pretty straightforward. So there are very little comments and the codes should be self-explanatory.
     - There will be no separate executable generated for 'shapes' during building. Instead, you can run 'make test' to check all the test cases are passed.
3. For 'paper_scissors_rock':
     - There will be an application named 'paper_scissors_rock' generated during building. Run 'make install' to move it to the project directory.
     - Some necessary comments are put into source files.
4. Build steps:
     - ./cmake_release.sh
     - cd build/release
     - make
     - make test
     - make install
