#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "planificador.h"

// Compara dos procesos para ordenarlos por tiempo de llegada.
static int compararTiempoLlegada(const void* a, const void* b) {
    Process* p1 = (Process*)a;
    Process* p2 = (Process*)b;
    if (p1->tiempoLlegada < p2->tiempoLlegada) return -1;
    if (p1->tiempoLlegada > p2->tiempoLlegada) return 1;
    return 0;
}

void planificarFifo(Process procesos[], int n) {
    // Array para el historial de ejecución para el diagrama de Gantt
    PasoEjecucion historial[10];
    int contadorPasos = 0;

    // Ordenar los procesos por tiempo de llegada
    qsort(procesos, n, sizeof(Process), compararTiempoLlegada);

    int tiempoActual = 0;
    
    for (int i = 0; i < n; i++) {
        if (tiempoActual < procesos[i].tiempoLlegada) {
            tiempoActual = procesos[i].tiempoLlegada;
        }

        procesos[i].tiempoInicio = tiempoActual;
        procesos[i].tiempoFin = tiempoActual + procesos[i].tiempoRafaga;
        
        // Registrar en el historial para Gantt
        strcpy(historial[contadorPasos].nombreProceso, procesos[i].nombre);
        historial[contadorPasos].tiempoFin = procesos[i].tiempoFin;
        contadorPasos++;
        
        tiempoActual = procesos[i].tiempoFin;
    }

    // Calcular tiempos finales para cada proceso
    for (int i = 0; i < n; i++) {
        procesos[i].tiempoEspera = procesos[i].tiempoInicio - procesos[i].tiempoLlegada;
        procesos[i].tiempoRetorno = procesos[i].tiempoFin - procesos[i].tiempoLlegada;
    }

    // Imprimir los resultados utilizando las funciones de utilidad
    imprimirDiagramaGantt(historial, contadorPasos, "FIFO");
    imprimirTablaResultados(procesos, n);
}

