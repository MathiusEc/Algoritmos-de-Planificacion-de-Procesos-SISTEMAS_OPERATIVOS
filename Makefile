CC=gcc
CFLAGS=-Wall -g
TARGET=planificador.exe

# Lista de todos los archivos fuente (ahora en español)
SOURCES=main.c fifo.c sjf.c prioridad.c round_robin.c utilidades.c
# Genera la lista de archivos objeto
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

# Dependencias actualizadas a los nuevos nombres de headers
%.o: %.c planificador.h proceso.h historial.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) *.exe
