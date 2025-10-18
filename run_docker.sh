#!/bin/bash
# run_docker.sh [comando]

DOCKER_IMAGE=cpp_modules_dev
PROJECT_DIR=$(pwd)

COMMAND=$1

case $COMMAND in
  build)
    echo "Building Docker image..."
    docker build -t $DOCKER_IMAGE -f docker/Dockerfile .
    ;;
  run)
    echo "Running project inside Docker..."
    docker run -it --rm -v "$PROJECT_DIR":/home/dev/app $DOCKER_IMAGE bash -c "\
      mkdir -p build && cd build && cmake .. && make -j\$(nproc) && ./cpp_modules_exe"
    ;;
  shell)
    echo "Opening interactive shell..."
    docker run -it --rm -v "$PROJECT_DIR":/home/dev/app $DOCKER_IMAGE bash
    ;;
  *)
    echo "Usage: $0 {build|run|shell}"
    ;;
esac
