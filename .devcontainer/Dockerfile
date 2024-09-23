FROM ubuntu

ARG USERNAME=student

# Create user
RUN useradd $USERNAME \
    && apt-get update \
    && apt-get install -y sudo \
    && echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME \
    && chmod 0440 /etc/sudoers.d/$USERNAME


# Install necessary packages (env dev 42)
RUN apt-get update && \
    apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        llvm \
        libunwind-dev \
        gdb \
        valgrind \
        python3 \
        python3-pip \
        python3-venv \
        git \
        zsh \
        fish && \
    apt-get clean

# Installation Oh-my-ZSH
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended

# Switch to user $USERNAME
USER $USERNAME

WORKDIR /home/${USERNAME}

# Install env python && norminette && c_formatter_42
RUN  python3 -m venv $HOME/.venv && \
    . $HOME/.venv/bin/activate && \
    python3 -m pip install --upgrade pip setuptools && \
    python3 -m pip install norminette && \
    echo "export PATH=\$PATH:$HOME/.venv/bin" >> $HOME/.profile && \
    deactivate

# Start with Fish Shell
CMD [ "fish" ]
