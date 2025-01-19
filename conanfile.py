from conan import ConanFile
from conan.tools.cmake import CMake

class ExpressCpp(ConanFile):
    name = "expresscpp"
    version = "1.0.0"
    license = "MIT"
    url = "https://gitlab.com/expresscpp/expresscpp"
    description = "same as expressjs for nodejs but for C++"
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Use the CMakeDeps and CMakeToolchain generators
    generators = ["CMakeDeps", "CMakeToolchain"]

    exports_sources = "CMakeLists.txt", "src/*", "include/*", "conanfile.py", "package.json"

    def requirements(self):
        self.requires("boost/1.73.0")
        self.requires("fmt/7.1.3")
        self.requires("nlohmann_json/3.10.4")

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.hpp", src=".")
        self.copy("*expresscpp.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["expresscpp"]
