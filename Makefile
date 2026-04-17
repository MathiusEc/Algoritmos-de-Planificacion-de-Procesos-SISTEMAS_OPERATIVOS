CC=gcc
CFLAGS=-Wall -g
TARGET=scheduler_simulation

# Lista de todos los archivos fuente
SOURCES=main.c fcfs.c sjf.c priority.c rr.c
# Genera la lista de archivos objeto
OBJECTS=$(SOURCES:.c=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.c scheduler.h process.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS) *.exe
