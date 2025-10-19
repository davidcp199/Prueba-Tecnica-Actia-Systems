FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    git \
    clang-format \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -ms /bin/bash dev
USER dev
WORKDIR /home/dev/app

CMD ["/bin/bash"]
