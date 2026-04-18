#include <stdio.h>
#include <string.h>
#include "planificador.h"

void planificarRr(Process procesos[], int n, int quantum) {
    int tiempoActual = 0;
    int completados = 0;
    
    // Cola de procesos listos (almacena índices)
    int colaListos[n * 10]; 
    int cabeza = 0, cola = 0;
    
    // Banderas para controlar qué procesos ya han sido encolados
    int yaEncolado[n];
    for(int i=0; i<n; i++) yaEncolado[i] = 0;

    PasoEjecucion historial[20]; // RR puede tener más pasos
    int contadorPasos = 0;

    // Inicializar tiempo restante
    for(int i=0; i<n; i++) {
        procesos[i].tiempoRestante = procesos[i].tiempoRafaga;
    }

    while(completados < n) {
        // Encolar procesos nuevos que han llegado
        for (int i = 0; i < n; i++) {
            if (!yaEncolado[i] && procesos[i].tiempoLlegada <= tiempoActual) {
                colaListos[cola++] = i;
                yaEncolado[i] = 1;
            }
        }

        if (cabeza == cola) {
            // No hay procesos en la cola, avanzar el tiempo
            tiempoActual++;
            continue;
        }

        int idx = colaListos[cabeza++];
        
        // Si es la primera vez que se ejecuta, registrar su start_time real
        if (procesos[idx].tiempoInicio == -1) {
            procesos[idx].tiempoInicio = tiempoActual;
        }
        
        int tiempoEjecucion = (procesos[idx].tiempoRestante < quantum) ? procesos[idx].tiempoRestante : quantum;
        
        tiempoActual += tiempoEjecucion;
        procesos[idx].tiempoRestante -= tiempoEjecucion;

        // Registrar en el historial para Gantt
        strcpy(historial[contadorPasos].nombreProceso, procesos[idx].nombre);
        historial[contadorPasos].tiempoFin = tiempoActual;
        contadorPasos++;
        
        // Volver a encolar procesos que llegaron durante la ejecución de este
        for (int i = 0; i < n; i++) {
            if (!yaEncolado[i] && procesos[i].tiempoLlegada <= tiempoActual) {
                colaListos[cola++] = i;
                yaEncolado[i] = 1;
            }
        }

        if (procesos[idx].tiempoRestante > 0) {
            // Si no ha terminado, vuelve a la cola
            colaListos[cola++] = idx;
        } else {
            // Si terminó, registrar su tiempo de finalización
            procesos[idx].tiempoFin = tiempoActual;
            completados++;
        }
    }

    // Calcular tiempos finales
    for (int i = 0; i < n; i++) {
        procesos[i].tiempoRetorno = procesos[i].tiempoFin - procesos[i].tiempoLlegada;
        procesos[i].tiempoEspera = procesos[i].tiempoRetorno - procesos[i].tiempoRafaga;
    }
    
    // Imprimir resultados
    char nombreAlgoritmo[50];
    sprintf(nombreAlgoritmo, "Round Robin (Quantum=%d)", quantum);
    imprimirDiagramaGantt(historial, contadorPasos, nombreAlgoritmo);
    imprimirTablaResultados(procesos, n);
}



