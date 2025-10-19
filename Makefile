# Paths
SRC_DIR = src
INCLUDE = include
BUILD = build
TESTS_DIR = tests

# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -I$(INCLUDE) -Wall -Wextra -pthread

# Executables
MAIN_EXE = $(BUILD)/cpp_modules_exe
TESTS_EXE = $(BUILD)/tests

# Sources
SRC_FILES = $(SRC_DIR)/Module1.cpp $(SRC_DIR)/Module2.cpp $(SRC_DIR)/Module3.cpp
MAIN_SRC = $(SRC_DIR)/main.cpp $(SRC_FILES)
TESTS_SRC = $(TESTS_DIR)/main_tests.cpp

# Docker image
DOCKER_IMAGE = cpp_modules_dev
PROJECT_DIR = $(shell pwd)

# -------------------------------
# Local build
# -------------------------------

# Build folder
$(BUILD):
	mkdir -p $(BUILD)

# Compile main
$(MAIN_EXE): $(MAIN_SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(MAIN_SRC) -o $(MAIN_EXE)

# Compile tests
$(TESTS_EXE): $(SRC_FILES) $(TESTS_SRC) | $(BUILD)
	$(CXX) $(CXXFLAGS) $(SRC_FILES) $(TESTS_SRC) -o $(TESTS_EXE)

# Run main locally
run: $(MAIN_EXE)
	$(MAIN_EXE)

# Run tests locally
tests: $(TESTS_EXE)
	$(TESTS_EXE)

# Clean build
clean:
	rm -rf $(BUILD)

# -------------------------------
# Docker targets
# -------------------------------

# Variables
DOCKER_IMAGE=cpp_modules_dev

# -------------------------------
# Build docker image
# -------------------------------
docker_build:
	docker build -t $(DOCKER_IMAGE) -f docker/Dockerfile .

# -------------------------------
# Run main executable inside docker
# -------------------------------
docker_run: docker_build
	docker run -it --rm -v "$(PWD)":/home/dev/app $(DOCKER_IMAGE) bash -c "\
		mkdir -p build && cd build && cmake .. && make -j\`nproc\` && ./cpp_modules_exe"

# -------------------------------
# Run tests executable inside docker
# -------------------------------
docker_run_tests: docker_build
	docker run -it --rm -v "$(PWD)":/home/dev/app $(DOCKER_IMAGE) bash -c "\
		mkdir -p build && cd build && cmake .. && make -j\`nproc\` && ./tests"
