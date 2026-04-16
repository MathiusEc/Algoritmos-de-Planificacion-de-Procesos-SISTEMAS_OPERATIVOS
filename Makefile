CC=gcc
CFLAGS=-Iinclude -Wall -g
VPATH=src

# Lista de todos los archivos fuente
SOURCES=$(wildcard src/*.c)

# Genera la lista de archivos objeto a partir de los fuentes
OBJECTS=$(SOURCES:.c=.o)

# Nombre del ejecutable final
TARGET=scheduler_simulation

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Regla para compilar archivos .c a .o
# Los archivos .c se buscarán en el directorio 'src' (gracias a VPATH)
%.o: %.c include/scheduler.h include/process.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
