![image](https://user-images.githubusercontent.com/61813081/153123375-0fcfd748-583e-4626-b2e8-19e111ffb8e6.png)

# Battleship

This is the main group project for a C++ software course (software design and project management based) I completed in 2021. For this project, I worked as the software architect, designing the architecture without a framework for the first time (this was also the first large C/C++ project I was part of). In terms of content, I mainly worked on the back-end (ships, board, etc) and ensured quality, while other entities and front-end work like sprites, screens were created by other team members

There are some fundamental design flaws that could have been rectified during planning (such as the non-responsiveness of the screen size), but this was a project made by a team without much C++ experience in a limited amount of time, so we primarily focused on correctness. Although this project isn't that practically useful, it was made to learn important skills such as the software design process, repository structure, refactoring, fixing (many) git issues 🙃, C++ (especially pointers) and CMAKE

## Running the game

### To run the most recent compiled .exe, simply clone the repo (```git clone https://github.com/reid-moffat/battleship.git```) and run ```bin/battleship.exe``` (do not move the .exe file!)

If you'd like to compile it yourself, make some changes or just play around with it:
* If you're running tests, you need to clone googletest into the ```include/``` folder with ```git clone https://github.com/google/googletest.git```
* **Reload CMakeLists.txt** when making changes before compiling
  * This was made on windows; for non-windows OSs, you'll need to make your own script to compile
* Run ```battleship``` for the game or ```battleship-tests``` for the test suite

*If you find a bug, feel free to create an issue*

## File structure

*SFML: [download](https://www.sfml-dev.org/download.php) | [git repo](https://github.com/SFML/SFML)*

    .
    ├── .github                 # Contains the issue template
    ├── .idea                   # JetBrains (CLion) settings
    ├── .vscode                 # Visual Studio Code settings
    ├── bin
    |   └── battleship.exe      # Compiled binary with the most recent code
    ├── include
    |   └── SFML                # A copy of the SFML library (see above for download)
    ├── res
    |   └── images              # Pixel graphic images for the game's UI
    ├── src
    |   ├── controllers         # Overarching classes that manage and define the screens and game state
    |   ├── entity              # Game entities
    |   ├── enums               # Enumerations for types of screens, ships and grid squares
    |   ├── helpers             # Stateless helper classes and funtions
    |   ├── screens             # Each possible game screen
    |   └── main.cpp            # Entry point for the program
    ├── test                    # Tests using googletest (incomplete)
    ├── .clang-format           # Formatting settings
    ├── .gitignore
    ├── CMakeLists.txt          # Build script
    ├── LICENSE
    └── README.md
