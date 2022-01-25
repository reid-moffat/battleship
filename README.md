# Battleship

Group project for my Fundamentals of Software Development course

Note: This repository works, but is undergoing heavy refactoring, especially the screen .cpp files

### Troubleshooting

**I can't run the project or the tests?** You need to load the correct CMakeLists.txt file. To run
the program itself, load the Cmake in the root directory. To run tests, load the Cmake in the tests/
folder

**Issues with running tests or anything about googletest not being found:** Open tests/ and do
```git clone https://github.com/google/googletest.git```. The googletests repo is not included in
the repo's VCS because it is not necessary (similar to node_modules- it only takes one command and a
few seconds to get it, and greatly reduces the repository size)

**Cannot find file while compiling:** Your compiler working directory needs to be the build/ folder
