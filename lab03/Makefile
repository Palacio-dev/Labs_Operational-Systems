# Nome do compilador
CC = gcc

# Opções de compilação (Flags)
CFLAGS = -Wall -Wextra -g -pthread

# Nome do executável final
TARGET = cigarrette_smokers

# Diretórios para organizar o projeto
SRC_DIR = src
BUILD_DIR = build

# Lista de arquivos fonte (.c)
SRCS = $(SRC_DIR)/agent.c $(SRC_DIR)/helpers.c $(SRC_DIR)/main.c $(SRC_DIR)/smokers.c

# Lista de arquivos objeto (.o) gerados a partir dos arquivos fonte
# A função patsubst substitui o padrão 'src/%.c' por 'build/%.o'
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# A regra padrão que será executada ao rodar 'make'
all: $(TARGET)

# Regra para criar o executável
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Regra para compilar arquivos .c do src/ em .o no build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos compilados (apaga a pasta build inteira e o executável)
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

# Declara que 'all' e 'clean' não são arquivos, mas sim comandos
.PHONY: all clean