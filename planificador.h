#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include "proceso.h"
#include "historial.h"

// --- Funciones de Planificación ---
void planificarFifo(Process procesos[], int n);
void planificarSjf(Process procesos[], int n);
void planificarPrioridad(Process procesos[], int n);
void planificarRr(Process procesos[], int n, int quantum);


// --- Funciones de Utilidad ---
void imprimirDiagramaGantt(const PasoEjecucion historial[], int contadorPasos, const char* nombreAlgoritmo);
void imprimirTablaResultados(const Process procesos[], int n);

#endif //PLANIFICADOR_H
