# Compilador

CC = gcc
CFLAGS = -Wall -Wextra -std=c11


# Archivos fuente

SRC = main.c \
      Estacion/Estacion.c \
      Estacion/EstacionStatus.c \
      Algoritmos/HashTable/HashTable.c \
      Algoritmos/B+Tree/B+Tree.c \
      Algoritmos/B+Tree/B+TreeNode.c \
      Core/EstructuraOps.c \
      Core/GeneradorDatos.c \
      Core/MotorConsultas.c


# Ejecutable

TARGET = programa

# Reglas

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

re: clean all