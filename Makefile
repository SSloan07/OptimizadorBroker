
# Compilador y flags

CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Archivos fuente

SRC = main.c \
      Estacion/Estacion.c \
      Estacion/EstacionStatus.c \
      Algoritmos/HashTable/HashTable.c \
      Core/EstructuraOps.c\
      Core/GeneradorDatos.c

# Ejecutable

TARGET = programa

# Regla principal

run: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Limpiar

clean:
	rm -f $(TARGET)

# Recompilar

re: clean all
