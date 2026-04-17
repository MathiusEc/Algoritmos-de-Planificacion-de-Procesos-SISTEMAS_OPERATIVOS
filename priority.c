#include "scheduler.h"
#include <stdio.h>
#include <limits.h>

void schedule_priority(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    int executed[100] = {0};

    printf("\n--- Gantt Chart para Prioridad (No Apropiativo) ---\n");

    while (completed < n) {
        int highest_priority_index = -1;
        int highest_priority = INT_MAX;

        // Encontrar el proceso elegible con la prioridad más alta (valor numérico más bajo)
        for (int i = 0; i < n; i++) {
            if (!executed[i] && processes[i].arrival_time <= current_time) {
                if (processes[i].priority < highest_priority) {
                    highest_priority = processes[i].priority;
                    highest_priority_index = i;
                }
            }
        }

        if (highest_priority_index == -1) {
            current_time++;
            continue;
        }

        int i = highest_priority_index;

        if (!processes[i].has_started) {
            processes[i].start_time = current_time;
            processes[i].has_started = 1;
        }
        
        processes[i].finish_time = current_time + processes[i].burst_time;
        
        printf("| %s (%d) ", processes[i].name, processes[i].finish_time);

        current_time = processes[i].finish_time;
        executed[i] = 1;
        completed++;
    }
    printf("|\n");
}
