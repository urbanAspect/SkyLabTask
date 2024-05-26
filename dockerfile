FROM ubuntu:20.04

# Set non-interactive mode
ENV DEBIAN_FRONTEND=noninteractive

# Install dependencies
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    git \
    gcc-multilib \
    g++-multilib \
    gdb \
    make \
    sudo \
    tzdata \
    && rm -rf /var/lib/apt/lists/*

# Set timezone to avoid interactive prompt
RUN ln -fs /usr/share/zoneinfo/Etc/UTC /etc/localtime && dpkg-reconfigure --frontend noninteractive tzdata

# Create a user
RUN useradd -ms /bin/bash devuser && echo "devuser:devuser" | chpasswd && adduser devuser sudo

USER devuser
WORKDIR /home/devuser

# Clone FreeRTOS repository with submodules
RUN git clone --recurse-submodules https://github.com/FreeRTOS/FreeRTOS.git

WORKDIR /home/devuser/FreeRTOS/FreeRTOS/Demo/Posix_GCC

# Build the FreeRTOS POSIX simulator
RUN cmake . && make

CMD ["bash"]
