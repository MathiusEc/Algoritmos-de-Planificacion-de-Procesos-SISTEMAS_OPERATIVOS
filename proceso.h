#ifndef PROCESO_H
#define PROCESO_H

// Estructura para representar un proceso
typedef struct {
    char* nombre;               // Nombre del Proceso (e.g., "A", "B")
    int tiempoRafaga;           // Duración o "burst time" (ut)
    int tiempoLlegada;          // Tiempo de llegada (ut)
    int prioridad;              // Prioridad (1 = Alta, 4 = Baja)
    
    // Campos para cálculos y estadísticas de la simulación
    int tiempoRestante;         // Para RR, tiempo que aún falta por ejecutar
    int tiempoInicio;           // Momento en que el proceso se ejecuta por primera vez
    int tiempoFin;              // Momento en que el proceso termina completamente
    int tiempoEspera;           // Tiempo total esperando en la cola de listos
    int tiempoRetorno;          // Tiempo total desde la llegada hasta la finalización
} Process;

#endif //PROCESO_H
