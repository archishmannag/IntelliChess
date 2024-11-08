# IntelliChess

A Chess engine with a GUI built in C++.

## Features

-   Advanced chess engine
-   Interactive user interface for playing against the engine
-   Ability to analyze and evaluate chess positions
-   Customizable difficulty levels

## Prerequisites

These are the requirements and dependencies of IntelliChess:

-   CMake 3.20 or higher - [Download here](https://cmake.org/download/)
-   Conan - [Download here](https://conan.io/downloads.html)
-   Ninja (optional) - [Download here](https://github.com/ninja-build/ninja/releases)
-   A C++ 17 compatible compiler (GCC, Clang, MSVC, etc.) for building from source

    Ensure these are present in the `PATH` variable so that the scripts can run the executables.

## Installation

To install IntelliChess, follow these steps:<br>

1. Clone the repository:
    ```
    git clone https://github.com/archishmannag/IntelliChess
    cd IntelliChess
    ```
2. Run the script:
    
    On Windows (PowerShell as Administrator):
    ```powershell
    # Ensure the execution policy is set to allow running scripts
    Set-ExecutionPolicy -Scope Process -ExecutionPolicy RemoteSigned
    .\build.ps1
    ```

    On Linux or macOS:
    ```bash
    # Ensure the script is executable
    chmod u+x build.sh
    ./build.sh
    ```

The binary will be in the `bin` directory at the project root.

## Usage

Currently the application is coupled with the GUI, but I plan to add CLI support soon. So running the executable will automatically launch the GUI.

## Roadmap

-   [ ] Add CLI support
-   [ ] Add different game modes (blitz, bullet, etc.)
-   [ ] Add clock
-   [ ] Enhance the GUI
-   [ ] Add support for different themes
-   [ ] Improve the AI and move generation speed

## Contributing

Contributions are welcome! If you'd like to contribute to the project, please do so by forking the repoitory and creating pull requests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
