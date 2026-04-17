#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

/**
 * @brief Ejecuta el algoritmo First-Come, First-Served (FCFS).
 */
void schedule_fcfs(Process processes[], int n);

/**
 * @brief Ejecuta el algoritmo Shortest Job First (SJF) No Apropiativo.
 */
void schedule_sjf(Process processes[], int n);

/**
 * @brief Ejecuta el algoritmo de Planificación por Prioridad No Apropiativo.
 */
void schedule_priority(Process processes[], int n);

/**
 * @brief Ejecuta el algoritmo Round Robin (RR).
 */
void schedule_rr(Process processes[], int n, int quantum);

#endif //SCHEDULER_H
