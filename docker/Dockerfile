# Imagen base: Ubuntu 22.04 LTS
FROM ubuntu:22.04

# Evita preguntas interactivas durante la instalación
ENV DEBIAN_FRONTEND=noninteractive

# Instala herramientas de desarrollo
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    clang-format \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Crea un usuario no root
RUN useradd -ms /bin/bash dev
USER dev
WORKDIR /home/dev/app

# Montaje del código local se hará con -v al ejecutar el contenedor

# Por defecto abre bash
CMD ["/bin/bash"]
