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
MinGW builds are provided in the Releases, so the binaries can be simply downloaded. You may build it yourself though.

As MinGW builds require the MinGW 13.1.0 version, this PowerShell command is necessary whether you build it locally or download the binaries.

<br>
PowerShell command (Run in elevated prompt (as administrator)):-

```
[System.Environment]::SetEnvironmentVariable("PATH","path_to_MinGW_bin_folder;;$env:PATH","Machine")
```
<br>
The following steps are required if you plan to build locally. If you have installed the binaries, you may simply run the executable directly.

<br>

<details><summary>Steps</summary>

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
</details>

The binary will be in the `bin` directory at the project root. <br>
Windows users ensure to keep the provided DLLs in the same directory as the executable.

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
