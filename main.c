#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

// Función de utilidad para imprimir los resultados de un algoritmo
void print_results(Process processes[], const char* algorithm_name) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\n--- Resultados para %s ---\n", algorithm_name);
    printf("PID\tLlegada\tBurst\tPrioridad\tInicio\tFinal\tEspera\tTurnaround\n");

    for (int i = 0; i < NUM_PROCESSES; i++) {
        processes[i].turnaround_time = processes[i].finish_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t%d\t%d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].priority,
               processes[i].start_time,
               processes[i].finish_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
        
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nTiempo de espera promedio: %.2f ms\n", (float)total_waiting_time / NUM_PROCESSES);
    printf("Tiempo de turnaround promedio: %.2f ms\n", (float)total_turnaround_time / NUM_PROCESSES);
    printf("----------------------------------------\n");
}

// Función para reiniciar el estado de los procesos antes de cada algoritmo
void reset_processes(Process processes[]) {
    // Datos iniciales basados en la imagen
    Process initial_processes[NUM_PROCESSES] = {
        {1, 0, 20, 2, 20, 0, 0, 0, 0, 0},
        {2, 2, 5,  1, 5,  0, 0, 0, 0, 0},
        {3, 4, 15, 3, 15, 0, 0, 0, 0, 0},
        {4, 6, 10, 2, 10, 0, 0, 0, 0, 0}
    };
    for(int i = 0; i < NUM_PROCESSES; i++) {
        processes[i] = initial_processes[i];
    }
}

int main() {
    Process processes[NUM_PROCESSES];
    const int quantum = 4;

    printf("Iniciando simulación de algoritmos de planificación...\n");

    // Ejecutar FCFS
    reset_processes(processes);
    run_fcfs(processes);
    print_results(processes, "FCFS");

    // Ejecutar SJF
    reset_processes(processes);
    run_sjf(processes);
    print_results(processes, "SJF (No Apropiativo)");

    // Ejecutar Prioridad
    reset_processes(processes);
    run_priority(processes);
    print_results(processes, "Prioridad (No Apropiativo)");

    // Ejecutar Round Robin
    reset_processes(processes);
    run_rr(processes, quantum);
    print_results(processes, "Round Robin (Quantum=4)");

    return 0;
}
