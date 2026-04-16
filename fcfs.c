#include "scheduler.h"
#include <stdio.h>

// Función para ordenar los procesos por tiempo de llegada
static int compare_arrival_time(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    return p1->arrival_time > p2->arrival_time;
}

void run_fcfs(Process processes[]) {
    // En FCFS, los procesos se atienden en el orden en que llegan.
    // Primero, ordenamos por tiempo de llegada para asegurar el orden.
    qsort(processes, NUM_PROCESSES, sizeof(Process), compare_arrival_time);

    int current_time = 0;
    
    printf("\n--- Gantt Chart para FCFS ---\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        // Si el procesador está libre y el proceso aún no ha llegado, adelantamos el tiempo.
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        processes[i].start_time = current_time;
        processes[i].finish_time = current_time + processes[i].burst_time;
        
        printf("| P%d (%d) ", processes[i].pid, processes[i].finish_time);
        
        current_time = processes[i].finish_time;
    }
    printf("|\n");
}
