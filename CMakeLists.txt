cmake_minimum_required(VERSION 3.10)
project(cpp_modules)

# Usa C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Incluye los headers
include_directories(include)

# Añade todos los .cpp de src/
file(GLOB SOURCES src/*.cpp)

# Ejecutable principal
add_executable(cpp_modules_exe ${SOURCES})
