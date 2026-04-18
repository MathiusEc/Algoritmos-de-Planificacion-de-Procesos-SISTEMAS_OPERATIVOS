#ifndef PLANIFICADOR_H
#define PLANIFICADOR_H

#include "proceso.h"
#include "historial.h"

// --- Funciones de Planificación ---

/**
 * @brief Ejecuta el algoritmo First-In, First-Out (FIFO).
 */
void planificarFifo(Process procesos[], int n);

/**
 * @brief Ejecuta el algoritmo Shortest Job First (SJF) No Apropiativo.
 */
void planificarSjf(Process procesos[], int n);

/**
 * @brief Ejecuta el algoritmo de Planificación por Prioridad No Apropiativo.
 */
void planificarPrioridad(Process procesos[], int n);

/**
 * @brief Ejecuta el algoritmo Round Robin (RR).
 */
void planificarRr(Process procesos[], int n, int quantum);


// --- Funciones de Utilidad ---

/**
 * @brief Imprime el diagrama de Gantt a partir de un historial de ejecución.
 * @param historial Array con los pasos de la ejecución.
 * @param contadorPasos Número de pasos en el historial.
 * @param nombreAlgoritmo El nombre del algoritmo ejecutado.
 */
void imprimirDiagramaGantt(const PasoEjecucion historial[], int contadorPasos, const char* nombreAlgoritmo);

/**
 * @brief Imprime la tabla final con los resultados de la simulación.
 * @param procesos Array de procesos con sus datos de simulación actualizados.
 * @param n Número de procesos.
 */
void imprimirTablaResultados(const Process procesos[], int n);


#endif //PLANIFICADOR_H
