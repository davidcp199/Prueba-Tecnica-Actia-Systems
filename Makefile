# ========================================
# Makefile para Docker + CMake + ejecución
# ========================================

DOCKER_IMAGE = cpp_modules_dev
PROJECT_DIR = $(PWD)

.DEFAULT_GOAL := help

# Construir la imagen Docker
build:
	@echo "Construyendo imagen Docker..."
	./run_docker.sh build

# Ejecutar el proyecto dentro de Docker (build + run)
run:
	@echo "Ejecutando proyecto dentro del contenedor..."
	./run_docker.sh run

# Abrir shell interactivo en Docker
shell:
	@echo "🐚 Abriendo shell interactivo en Docker..."
	./run_docker.sh shell

# Ejecutar pruebas dentro del contenedor
test:
	@echo "🧪 Ejecutando tests dentro del contenedor..."
	docker run -it --rm -v "$(PROJECT_DIR)":/home/dev/app $(DOCKER_IMAGE) bash -c "\
		cd build && ctest"

# Subir la imagen a Docker Hub
push:
	@echo "⬆️ Subiendo imagen a Docker Hub..."
	docker push $(DOCKER_IMAGE)

# Mostrar ayuda
help:
	@echo "Uso: make [build|run|shell|test|push]"
	@echo "  build : Construye la imagen Docker"
	@echo "  run   : Compila y ejecuta el proyecto dentro del contenedor"
	@echo "  shell : Abre un shell interactivo dentro del contenedor"
	@echo "  test  : Ejecuta los tests dentro del contenedor"
	@echo "  push  : Sube la imagen a Docker Hub"
