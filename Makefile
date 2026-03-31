
# Compilador

CC = gcc

CFLAGS = -Wall -Wextra -std=c11 \
-I. \
-IAlgoritmos \
-IAlgoritmos/B+Tree \
-IAlgoritmos/HashTable \
-IAlgoritmos/SpatialTree \
-IAlgoritmos/Graph \
-ICore \
-ICore/Benchmark \
-ICore/Benchmark/HashTable \
-ICore/Benchmark/B+Tree \
-ICore/Benchmark/SpatialTree \
-ICore/Benchmark/Graph \
-IEstacion

# Archivos

SRC = \
main.c \
\
Estacion/Estacion.c \
Estacion/EstacionStatus.c \
\
Algoritmos/HashTable/HashTable.c \
\
Algoritmos/B+Tree/B+Tree.c \
Algoritmos/B+Tree/B+TreeNode.c \
\
Algoritmos/SpatialTree/SpatialTree.c \
Algoritmos/SpatialTree/SpatialNode.c \
\
Algoritmos/Graph/Graph.c \
Algoritmos/Graph/GraphNode.c \
\
Core/EstructuraOps.c \
Core/GeneradorDatos.c \
Core/MotorConsultas.c \
\
Core/Benchmark/BenchmarkTotal.c \
Core/Benchmark/HashTable/BenchmarkHash.c \
Core/Benchmark/B+Tree/BenchmarkB+Tree.c \
Core/Benchmark/SpatialTree/BenchmarkSpatialTree.c \
Core/Benchmark/Graph/BenchmarkGraph.c

# Ejecutable

TARGET = programa

# Reglas

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -lm -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

re: clean all