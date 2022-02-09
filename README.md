![image](https://user-images.githubusercontent.com/61813081/153123375-0fcfd748-583e-4626-b2e8-19e111ffb8e6.png)

# Battleship

This was my first major project that I manually designed without a framework and first major C/C++ project, done in a team for my Fundamentals of Software Development course. For this project, I worked as the Software Architect, designing the repository and file structure as well as ensuring quality.

There are some fundamental design flaws that should have been rectified during planning (such as the non-responsiveness of screens), but for a team with essential no initial software design or C++ experience, I am happy with the result.

Although the project is not very practically useful, the skills I've learned such as the software design process, repository structure, refactoring, how to fix (many) git issues 🙃, C++ (especially pointers) and CMAKE are immensely important

## Repository info

### To run the most recent .exe I have made, simply clone the repo (```git clone https://github.com/reid-moffat/battleship.git```) and run ```bin/battleship.exe``` (note: do not move the .exe file from this path)

If you'd like to compile it yourself, make changes or play around with the tests:
* *(If needed)* Clone googletest into the ```include/``` folder with ```git clone https://github.com/google/googletest.git```
* **Reload CMakeLists.txt**
  * For non-windows OSs, you'll need to make a cmake file to compile
* Run eiher ```battleship``` or ```battleship-tests```

*If you find a bug, feel free to create an issue*
