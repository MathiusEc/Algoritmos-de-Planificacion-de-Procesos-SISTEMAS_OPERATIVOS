#ifndef PROCESS_H
#define PROCESS_H

// Estructura para representar un proceso
typedef struct {
    char name[10];            // Nombre del Proceso (e.g., "A", "B")
    int burst_time;           // Duración o "burst time" (ut)
    int arrival_time;         // Tiempo de llegada (ut)
    int priority;             // Prioridad (1 = Alta, 4 = Baja)
    
    // Campos para cálculos y estadísticas
    int remaining_time;       // Tiempo restante para ejecución
    int start_time;           // Tiempo en que el proceso comienza
    int finish_time;          // Tiempo en que el proceso termina
    int waiting_time;         // Tiempo de espera
    int turnaround_time;      // Tiempo total de retorno
    int has_started;          // Bandera para el tiempo de inicio
} Process;

#endif //PROCESS_H
