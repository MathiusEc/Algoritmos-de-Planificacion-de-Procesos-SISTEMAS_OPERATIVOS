#include "scheduler.h"
#include <stdio.h>

void schedule_rr(Process processes[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;
    
    // Cola para los procesos listos (IDs de proceso)
    int ready_queue[1000]; // Suficientemente grande para el ejercicio
    int head = 0, tail = 0;

    // Inicializamos remaining_time
    for(int i=0; i<n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].has_started = 0;
    }
    
    printf("\n--- Gantt Chart para Round Robin (Quantum=%d) ---\n", quantum);

    int last_arrival_check = -1;

    while(completed < n) {
        // Encolar los procesos que llegan
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].arrival_time > last_arrival_check) {
                ready_queue[tail++] = i;
            }
        }
        last_arrival_check = current_time;

        if (head == tail) {
            current_time++;
            continue;
        }

        int idx = ready_queue[head++];

        if (!processes[idx].has_started) {
            processes[idx].start_time = current_time;
            processes[idx].has_started = 1;
        }
        
        int time_slice = (processes[idx].remaining_time < quantum) ? processes[idx].remaining_time : quantum;
        
        printf("| %s ", processes[idx].name);
        
        // Ejecución simulada durante el time_slice
        for(int t=0; t<time_slice; t++) {
            current_time++;
            // Revisar si llegan nuevos procesos durante este tiempo
            for (int i = 0; i < n; i++) {
                if (processes[i].arrival_time == current_time) {
                    ready_queue[tail++] = i;
                    last_arrival_check = current_time;
                }
            }
        }
        
        processes[idx].remaining_time -= time_slice;
        printf("(%d) ", current_time);

        if (processes[idx].remaining_time > 0) {
            ready_queue[tail++] = idx;
        } else {
            processes[idx].finish_time = current_time;
            completed++;
        }
    }
    printf("|\n");
}
