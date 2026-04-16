#include "scheduler.h"
#include <stdio.h>
#include <limits.h>

void run_sjf(Process processes[]) {
    int current_time = 0;
    int completed = 0;
    int executed[NUM_PROCESSES] = {0};

    printf("\n--- Gantt Chart para SJF (No Apropiativo) ---\n");

    while (completed < NUM_PROCESSES) {
        int shortest_job_index = -1;
        int shortest_burst = INT_MAX;

        // Encontrar el proceso elegible con el burst time más corto
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!executed[i] && processes[i].arrival_time <= current_time) {
                if (processes[i].burst_time < shortest_burst) {
                    shortest_burst = processes[i].burst_time;
                    shortest_job_index = i;
                }
            }
        }

        if (shortest_job_index == -1) {
            // No hay procesos listos, avanzar el tiempo
            current_time++;
            continue;
        }

        int i = shortest_job_index;
        
        processes[i].start_time = current_time;
        processes[i].finish_time = current_time + processes[i].burst_time;
        
        printf("| P%d (%d) ", processes[i].pid, processes[i].finish_time);

        current_time = processes[i].finish_time;
        executed[i] = 1;
        completed++;
    }
    printf("|\n");
}
