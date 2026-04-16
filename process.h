#ifndef PROCESS_H
#define PROCESS_H

// Estructura para representar un proceso
typedef struct {
    int pid;                  // ID del Proceso
    int arrival_time;         // Tiempo de llegada (ms)
    int burst_time;           // Duración o "burst time" (ms)
    int priority;             // Prioridad (1 = Alta, 3 = Baja)
    
    // Campos para cálculos y estadísticas
    int remaining_time;       // Tiempo restante para ejecución (usado en RR y SJF Preemptive)
    int start_time;           // Tiempo en que el proceso comienza su ejecución por primera vez
    int finish_time;          // Tiempo en que el proceso completa su ejecución
    int waiting_time;         // Tiempo total de espera (Turnaround Time - Burst Time)
    int turnaround_time;      // Tiempo total desde la llegada hasta la finalización
    int has_started;          // Bandera para registrar el start_time una sola vez
} Process;

#endif //PROCESS_H
