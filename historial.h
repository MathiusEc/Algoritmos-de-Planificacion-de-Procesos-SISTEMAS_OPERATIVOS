#ifndef HISTORIAL_H
#define HISTORIAL_H

// Estructura para registrar cada paso de la ejecución para el diagrama de Gantt
typedef struct {
    char nombreProceso[10];
    int tiempoFin;
} PasoEjecucion;

#endif //HISTORIAL_H
