![image](https://user-images.githubusercontent.com/61813081/153123375-0fcfd748-583e-4626-b2e8-19e111ffb8e6.png)

# Battleship

This is the main group project for a C++ software course (software design and project management based) I completed in 2021. For this project, I worked as the software architect, designing the architecture without a framework for the first time (this was also the first large C/C++ project I was part of). In terms of content, I mainly worked on the back-end (ships, board, etc) and ensured quality, while other entities and front-end work like sprites and screens were created by other team members.

While this project overall is pretty simple & straightforward, my team did this mainly to learn more about C++, which we definitely succeeded in. In a few months, I learned a lot of concepts, including properly using pointers, CMAKE, refactoring & software design, and everyone's favorite: fixing plenty of git merge conflicts 🙃

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
