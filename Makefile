# -------------------------
# Paths
SRC_DIR = src
INCLUDE = include
BUILD = build
TESTS_DIR = tests

# -------------------------
# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++17 -I$(INCLUDE) -Wall -Wextra -pthread

# -------------------------
# Ejecutables
MAIN_EXE = $(BUILD)/cpp_modules_exe
TESTS_EXE = $(BUILD)/tests

# -------------------------
# Archivos fuente
SRC_FILES = $(SRC_DIR)/Utils.cpp $(SRC_DIR)/Module1.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp $(SRC_FILES)
TESTS_SRC = $(TESTS_DIR)/main_tests.cpp

# -------------------------
# Crear carpeta build si no existe
$(BUILD):
	mkdir -p $(BUILD)

# -------------------------
# Compilar main
$(MAIN_EXE): $(MAIN_SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(MAIN_SRC) -o $(MAIN_EXE)

# -------------------------
# Compilar tests
$(TESTS_EXE): $(SRC_FILES) $(TESTS_SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(TESTS_SRC) -o $(TESTS_EXE)

# -------------------------
# Ejecutar main
run: $(MAIN_EXE)
	$(MAIN_EXE)

# -------------------------
# Ejecutar tests
tests: $(TESTS_EXE)
	$(TESTS_EXE)

# -------------------------
# Docker
DOCKER_IMAGE = cpp_modules_dev

docker_build:
	docker build -t $(DOCKER_IMAGE) -f docker/Dockerfile .

docker_run:
	docker run -it --rm -v $(PWD):/home/dev/app $(DOCKER_IMAGE)

# -------------------------
.PHONY: run tests docker_build docker_run
