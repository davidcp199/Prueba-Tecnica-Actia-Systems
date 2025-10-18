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
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SRC = $(SRC_DIR)/main.cpp $(SRC_FILES)
# Excluir main.cpp para tests
MODULE_FILES = $(filter-out $(SRC_DIR)/main.cpp,$(SRC_FILES))
TESTS_SRC = $(TESTS_DIR)/main_tests.cpp

# -------------------------
# Crear carpeta build
$(BUILD):
	mkdir -p $(BUILD)

# -------------------------
# Compilar main
$(MAIN_EXE): $(MAIN_SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(MAIN_SRC) -o $(MAIN_EXE)

# -------------------------
# Compilar tests
$(TESTS_EXE): $(MODULE_FILES) $(TESTS_SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(MODULE_FILES) $(TESTS_SRC) -o $(TESTS_EXE)

# -------------------------
# Ejecutar main
run: $(MAIN_EXE)
	./$(MAIN_EXE)

# -------------------------
# Ejecutar tests
tests: $(TESTS_EXE)
	./$(TESTS_EXE)

# -------------------------
.PHONY: run tests

clean:
	rm -rf $(BUILD)