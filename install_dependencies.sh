#!/bin/bash

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

echo -e "${GREEN}🔹 Iniciando a instalação das dependências...${RESET}"

echo -e "${GREEN}🔹 Atualizando lista de pacotes...${RESET}"
sudo apt update && sudo apt upgrade -y

echo -e "${GREEN}🔹 Instalando g++, OpenMP e OpenMPI...${RESET}"
sudo apt install -y g++ gcc libomp-dev openmpi-bin openmpi-common libopenmpi-dev cmake

if ! command -v nvcc &> /dev/null
then
    echo -e "${GREEN}🔹 Baixando e instalando CUDA...${RESET}"
    wget https://developer.download.nvidia.com/compute/cuda/repos/wsl-ubuntu/x86_64/cuda-wsl-ubuntu.pin
    sudo mv cuda-wsl-ubuntu.pin /etc/apt/preferences.d/cuda-repository-pin-600
    wget https://developer.download.nvidia.com/compute/cuda/12.6.0/local_installers/cuda-repo-wsl-ubuntu-12-6-local_12.6.0-1_amd64.deb
    sudo dpkg -i cuda-repo-wsl-ubuntu-12-6-local_12.6.0-1_amd64.deb
    sudo cp /var/cuda-repo-wsl-ubuntu-12-6-local/cuda-*-keyring.gpg /usr/share/keyrings/
    sudo apt-get update
    sudo apt-get -y install cuda-toolkit-12-6
    echo -e "${GREEN} CUDA instalado com sucesso!${RESET}"
else
    echo -e "${GREEN} CUDA já está instalado!${RESET}"
fi

# Verificar instalações
echo -e "${GREEN} Verificando instalações...${RESET}"
echo -e "${GREEN}  g++ versão:${RESET} $(g++ --version | head -n 1)"
echo -e "${GREEN}  OpenMPI versão:${RESET} $(mpicc --version | head -n 1)"
echo -e "${GREEN}  CUDA versão:${RESET} $(nvcc --version | grep "release")"

echo -e "${GREEN} Todas as dependências foram instaladas com sucesso!${RESET}"
