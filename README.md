# IntelliChess

A Chess engine with a GUI built in C++.

## Features

-   Advanced chess engine
-   Interactive user interface for playing against the engine
-   Ability to analyze and evaluate chess positions
-   Customizable difficulty levels

## Prerequisites

These are the requirements and dependencies of IntelliChess:

-   CMake
-   Windows MinGW requires MinGW 13.1.0 version specifically - [Download here](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.1.0-16.0.5-11.0.0-msvcrt-r5/winlibs-x86_64-posix-seh-gcc-13.1.0-mingw-w64msvcrt-11.0.0-r5.7z)

## Installation

To install IntelliChess, follow these steps:

<details>
<summary>Linux</summary>

Installation on Linux is easy and straight-forward.

1. Clone the repository and enter it.

```
git clone https://github.com/archishmannag/IntelliChess.git
cd IntelliChess
```

2. Turn off the tests (they are enabled by default).

> Open CMakeLists.txt in project root and set the `BUILD_TESTING` variable to OFF

3. Create a directory named `build` and enter it.

```
mkdir build && cd build
```

4. Run CMake.

```
cmake -DCMAKE_BUILD_TYPE=Release ..
```

5. Run make.

```
make
```

</details>
<details>
<summary>Windows</summary>
Windows users can use either MSVC or MinGW for building the application
<details>
<summary>MSVC</summary>
Visual Studio can run CMake projects without a solution(sln) file. Clone the repository from within Visual Studio, and set the build type from configuration, then build it.
</details>
<details>
<summary>MinGW</summary>
For MinGW build to work, first install the required version and add its /bin directory to the PATH variable.

<br>
PowerShell command:-

```
Set-EnvironmentVariable -Name "PATH" -Value "path_to_MinGW_bin_folder;$env:PATH" -Scope Machine
```

After the path has been set, the process is straight-forward:-

1. Clone the repository

```
git clone https://github.com/archishmannag/IntelliChess.git
cd IntelliChess
```

2. Turn off the tests (they are enabled by default).

> Open CMakeLists.txt in project root and set the `BUILD_TESTING` variable to OFF

3. Create a `build` directory

```
md build && cd build
```

4. Run CMake

```
cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ..
```

5. Run Make

```
mingw32-make
```

</details>
</details>

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
