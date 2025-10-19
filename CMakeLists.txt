cmake_minimum_required(VERSION 3.10)
project(cpp_modules)

# Usa C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Headers
include_directories(include)

# .cpp
file(GLOB SOURCES src/*.cpp)

# Ejecutable
add_executable(cpp_modules_exe ${SOURCES})
