# Nome do compilador
CC = gcc

# Diretórios para organizar o projeto
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/objs
INC_DIR = inc

# Opções de compilação (Flags)
CFLAGS = -Wall -Wextra -g -pthread -I$(INC_DIR)

# Nome do executável final (agora apontando para dentro de build/)
TARGET = $(BUILD_DIR)/cigarrette_smokers

# Lista de arquivos fonte (.c)
SRCS = $(SRC_DIR)/agent.c $(SRC_DIR)/helpers.c $(SRC_DIR)/main.c $(SRC_DIR)/smokers.c

# Lista de arquivos objeto (.o) mapeados para dentro de build/objs/
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# A regra padrão que será executada ao rodar 'make'
all: $(TARGET)

# Regra para criar o executável dentro de build/
$(TARGET): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra de Padrão Estático para compilar arquivos .c em .o dentro de build/objs/
$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados (apaga a pasta build inteira)
clean:
	rm -rf $(BUILD_DIR)

# Declara que 'all' e 'clean' não são arquivos, mas sim comandos
.PHONY: all clean