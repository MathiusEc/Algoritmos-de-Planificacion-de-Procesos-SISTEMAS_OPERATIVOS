#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>

// Función para ordenar los procesos por tiempo de llegada
static int compare_arrival_time(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    if (p1->arrival_time < p2->arrival_time) return -1;
    if (p1->arrival_time > p2->arrival_time) return 1;
    return 0;
}

void schedule_fcfs(Process processes[], int n) {
    // Ordenamos por tiempo de llegada
    qsort(processes, n, sizeof(Process), compare_arrival_time);

    int current_time = 0;
    
    printf("\n--- Gantt Chart para FCFS ---\n");
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }

        processes[i].start_time = current_time;
        processes[i].finish_time = current_time + processes[i].burst_time;
        
        printf("| %s (%d) ", processes[i].name, processes[i].finish_time);
        
        current_time = processes[i].finish_time;
    }
    printf("|\n");
}
