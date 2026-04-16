#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

// Define el número de procesos a manejar
#define NUM_PROCESSES 4

/**
 * @brief Ejecuta el algoritmo First-Come, First-Served (FCFS).
 * @param processes Un arreglo de procesos a planificar.
 */
void run_fcfs(Process processes[]);

/**
 * @brief Ejecuta el algoritmo Shortest Job First (SJF) No Apropiativo.
 * @param processes Un arreglo de procesos a planificar.
 */
void run_sjf(Process processes[]);

/**
 * @brief Ejecuta el algoritmo de Planificación por Prioridad No Apropiativo.
 * @param processes Un arreglo de procesos a planificar.
 */
void run_priority(Process processes[]);

/**
 * @brief Ejecuta el algoritmo Round Robin (RR).
 * @param processes Un arreglo de procesos a planificar.
 * @param quantum El valor del quantum en ms.
 */
void run_rr(Process processes[], int quantum);

#endif //SCHEDULER_H
