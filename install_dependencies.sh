#!/bin/bash

GREEN="\e[32m"
RED="\e[31m"
RESET="\e[0m"

echo -e "${GREEN}🔹 Iniciando a instalação das dependências...${RESET}"

echo -e "${GREEN}🔹 Atualizando lista de pacotes...${RESET}"
sudo apt update && sudo apt upgrade -y

echo -e "${GREEN}🔹 Instalando g++, OpenMP e OpenMPI...${RESET}"
sudo apt install -y g++ gcc libomp-dev openmpi-bin openmpi-common libopenmpi-dev

if ! command -v nvcc &> /dev/null
then
    echo -e "${GREEN}🔹 Baixando e instalando CUDA...${RESET}"
    sudo apt install nvidia-cuda-toolkit
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
