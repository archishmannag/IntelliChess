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

2. Create a directory named `build` and enter it.
3. Run CMake.
4. Run make.

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
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

PowerShell:-

```
Set-EnvironmentVariable -Name "PATH" -Value "path_to_MinGW_bin_folder;$env:PATH" -Scope Machine
```

After the path has been set, the process is straight-forward:-

1. Clone the repository
2. Create a `build` directory
3. Run CMake
4. Run Make

```
git clone https://github.com/archishmannag/IntelliChess.git
cd IntelliChess
md build && cd build
cmake -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" ..
mingw32-make
```

</details>
</details>

The binary will be in the `bin` directory at the project root.

## Usage

Currently the application is coupled with the GUI, but I plan to add CLI support soon. So running the executable will automatically launch the GUI.

## Contributing

Contributions are welcome! If you'd like to contribute to the project, please do so by forking the repoitory and creating pull requests.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more information.
