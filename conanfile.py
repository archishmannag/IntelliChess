from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, cmake_layout

class IntelliChess(ConanFile):
    name = "IntelliChess"
    version = "1.1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "CMakeDeps"

    def requirements(self):
        self.requires("gtest/1.15.0")
        self.requires("sfml/2.6.1")

    def configure(self):
        self.options["gtest"].shared = False
        self.options["sfml"].shared = False

    def layout(self):
        cmake_layout(self)
        self.folders.build = "conan/build"
        self.folders.generators = "conan/debug" if self.settings.build_type == "Debug" else "conan/release"

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generator = "Ninja"
        tc.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()

    def test(self):
        cmake = CMake(self)
        cmake.test()