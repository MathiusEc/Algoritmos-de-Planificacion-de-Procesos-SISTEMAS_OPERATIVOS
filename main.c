#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "process.h"
#include "scheduler.h"

// Prototipo para la función de reseteo
void reset_processes(Process *processes, int n);

int main() {
    Process processes[5];
    // Inicialización de los procesos tal como en el PDF
    // Proceso Ráfaga CPU (ut) Tiempo de Llegada Prioridad
    // A 3 2 2
    // B 1 4 3
    // C 3 0 1
    // D 4 1 3
    // E 2 3 4
    processes[0] = (Process){"A", 3, 2, 2, -1, -1, 0, 0, 0};
    processes[1] = (Process){"B", 1, 4, 3, -1, -1, 0, 0, 0};
    processes[2] = (Process){"C", 3, 0, 1, -1, -1, 0, 0, 0};
    processes[3] = (Process){"D", 4, 1, 3, -1, -1, 0, 0, 0};
    processes[4] = (Process){"E", 2, 3, 4, -1, -1, 0, 0, 0};
    int n = sizeof(processes) / sizeof(processes[0]);

    // 1. Imprimir la tabla de procesos inicial
    printf("-------------------------------------------------\n");
    printf("Procesos de entrada (matriz inicial):\n");
    printf("-------------------------------------------------\n");
    printf("Proceso\tRáfaga CPU\tT. Llegada\tPrioridad\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\n", processes[i].name, processes[i].burst_time, processes[i].arrival_time, processes[i].priority);
    }
    printf("-------------------------------------------------\n\n");

    int choice;
    do {
        // 2. Mostrar el menú de opciones
        printf("Seleccione el algoritmo de planificación a ejecutar:\n");
        printf("1. FIFO (First-In, First-Out)\n");
        printf("2. SJF (Shortest Job First)\n");
        printf("3. Prioridad (No Apropiativo)\n");
        printf("4. Round Robin (Quantum = 3)\n");
        printf("5. Salir\n");
        printf("Su elección: ");
        
        scanf("%d", &choice);
        printf("\n");

        // Antes de cada ejecución, reseteamos los valores de los procesos
        reset_processes(processes, n);

        // 3. Ejecutar el algoritmo seleccionado
        switch (choice) {
            case 1:
                printf("--- Ejecutando FCFS/FIFO ---\n");
                schedule_fcfs(processes, n);
                break;
            case 2:
                printf("--- Ejecutando SJF (No Apropiativo) ---\n");
                schedule_sjf(processes, n);
                break;
            case 3:
                printf("--- Ejecutando Prioridad (No Apropiativo) ---\n");
                schedule_priority(processes, n);
                break;
            case 4:
                printf("--- Ejecutando Round Robin (Quantum=3) ---\n");
                schedule_rr(processes, n, 3);
                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                printf("Opción no válida. Por favor, intente de nuevo.\n");
                break;
        }
        printf("\n");

    } while (choice != 5);

    return 0;
}

/**
 * Resetea los valores de ejecución de los procesos para permitir
 * una nueva simulación con los datos originales.
 */
void reset_processes(Process *processes, int n) {
    for (int i = 0; i < n; i++) {
        processes[i].start_time = -1;
        processes[i].finish_time = -1;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].remaining_time = processes[i].burst_time;
    }
}
