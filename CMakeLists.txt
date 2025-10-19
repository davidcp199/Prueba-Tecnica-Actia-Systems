cmake_minimum_required(VERSION 3.10)
project(CppModulesProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluye la carpeta con los headers
include_directories(include)

# -------------------------------
# Ejecutable principal
# -------------------------------
add_executable(cpp_modules_exe
    src/main.cpp
    src/Module1.cpp
    src/Module2.cpp
    src/Module3.cpp
)

# -------------------------------
# Ejecutable de tests
# -------------------------------
add_executable(tests
    tests/main_tests.cpp
    src/Module1.cpp
    src/Module2.cpp
    src/Module3.cpp
)
