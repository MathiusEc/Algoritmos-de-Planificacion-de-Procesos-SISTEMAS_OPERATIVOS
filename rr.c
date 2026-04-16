#include "scheduler.h"
#include <stdio.h>

void run_rr(Process processes[], int quantum) {
    int current_time = 0;
    int completed = 0;
    
    // Cola para los procesos listos (IDs de proceso)
    int ready_queue[NUM_PROCESSES * 10]; // Asumimos un tamaño grande para la cola
    int head = 0, tail = 0;

    // Copia de los remaining_time para no modificar el burst_time original
    for(int i=0; i<NUM_PROCESSES; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    printf("\n--- Gantt Chart para Round Robin (Quantum=%d) ---\n", quantum);

    int last_arrival_check = -1;

    while(completed < NUM_PROCESSES) {
        // 1. Añadir procesos que han llegado a la cola de listos
        if (current_time != last_arrival_check) {
            for (int i = 0; i < NUM_PROCESSES; i++) {
                if (processes[i].arrival_time == current_time) {
                    ready_queue[tail++] = i;
                }
            }
            last_arrival_check = current_time;
        }

        if (head == tail) {
            // Cola vacía, avanzar tiempo
            current_time++;
            continue;
        }

        // 2. Sacar un proceso de la cola
        int process_index = ready_queue[head++];

        if (!processes[process_index].has_started) {
            processes[process_index].start_time = current_time;
            processes[process_index].has_started = 1;
        }
        
        int time_slice = (processes[process_index].remaining_time < quantum) ? processes[process_index].remaining_time : quantum;
        
        printf("| P%d ", processes[process_index].pid);
        
        current_time += time_slice;
        processes[process_index].remaining_time -= time_slice;
        
        printf("(%d) ", current_time);

        // 3. Volver a encolar procesos que han llegado durante la ejecución
        for (int i = 0; i < NUM_PROCESSES; i++) {
             if (processes[i].arrival_time > last_arrival_check && processes[i].arrival_time <= current_time) {
                int in_queue = 0;
                for(int j=head; j<tail; j++) {
                    if(ready_queue[j] == i) {
                        in_queue = 1;
                        break;
                    }
                }
                if(!in_queue) ready_queue[tail++] = i;
            }
        }
        last_arrival_check = current_time;


        // 4. Si el proceso no ha terminado, volver a encolarlo al final
        if (processes[process_index].remaining_time > 0) {
            ready_queue[tail++] = process_index;
        } else {
            // Proceso completado
            processes[process_index].finish_time = current_time;
            completed++;
        }
    }
    printf("|\n");
}
