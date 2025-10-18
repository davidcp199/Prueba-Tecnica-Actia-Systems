# Nombre de la imagen Docker
DOCKER_IMAGE = cpp_modules_dev

# Paths
SRC = src
INCLUDE = include
BUILD = build

# Compilador
CXX = g++
CXXFLAGS = -std=c++17 -I$(INCLUDE)

# Ejecutables
MAIN_EXE = $(BUILD)/cpp_modules_exe
TESTS_EXE = $(BUILD)/tests

# Archivos
MAIN_SRC = $(SRC)/main.cpp $(SRC)/Utils.cpp
TESTS_SRC = tests/main_tests.cpp $(SRC)/Utils.cpp

# Crear carpeta build si no existe
$(BUILD):
	mkdir -p $(BUILD)/tests

# -------------------------
# Compilar main
$(MAIN_EXE): $(MAIN_SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar tests
$(TESTS_EXE): $(TESTS_SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $^ -o $@

# -------------------------
# Ejecutar main
run: $(MAIN_EXE)
	$(MAIN_EXE)

# Ejecutar tests
tests: $(TESTS_EXE)
	$(TESTS_EXE)

# -------------------------
# Docker
docker_build:
	docker build -t $(DOCKER_IMAGE) -f docker/Dockerfile .

docker_run:
	docker run -it --rm -v $(PWD):/home/dev/app $(DOCKER_IMAGE)

.PHONY: run tests docker_build docker_run
