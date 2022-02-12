![image](https://user-images.githubusercontent.com/61813081/153123375-0fcfd748-583e-4626-b2e8-19e111ffb8e6.png)

# Battleship

This was the first large project that I manually designed without a framework and first large C/C++ project I was part of, done as a group project for my Fundamentals of Software Development course (C++ and project-managment focused). For this project, I worked as the Software Architect, designing the repository and file structure as well as ensuring quality (front-end work like sprites were created by other team members)

There are some fundamental design flaws that should have been rectified during planning (such as the non-responsiveness of screen sizes), but for a team with essentially no initial software design or C++ experience, it didn't turn out too bad. Although this project is not very practically useful, it was mainly done to learn important skills such as the software design process, repository structure, refactoring, fixing (many) git issues 🙃, C++ (especially pointers) and CMAKE

## Repository info

### To run the most recent compiled .exe, simply clone the repo (```git clone https://github.com/reid-moffat/battleship.git```) and run ```bin/battleship.exe``` (note: do not move the .exe file from this path or it will not work)

If you'd like to compile it yourself, make changes or play around with the tests:
* *(If needed)* Clone googletest into the ```include/``` folder with ```git clone https://github.com/google/googletest.git```
* **Reload CMakeLists.txt**
  * For non-windows OSs, you'll probably need to make another CMAKE to compile on your computer
* Run eiher ```battleship``` or ```battleship-tests```

*If you find a bug, feel free to create an issue*
