#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "planificador.h"

void planificarPrioridad(Process procesos[], int n) {
    int tiempoActual = 0;
    int completados = 0;
    int ejecutado[n];
    for(int i=0; i<n; i++) ejecutado[i] = 0;

    PasoEjecucion historial[10];
    int contadorPasos = 0;

    while (completados < n) {
        int idxProcesoSeleccionado = -1;
        int prioridadMasAlta = INT_MAX;

        // Encontrar el proceso elegible con la prioridad más alta (valor numérico más bajo)
        for (int i = 0; i < n; i++) {
            if (!ejecutado[i] && procesos[i].tiempoLlegada <= tiempoActual) {
                if (procesos[i].prioridad < prioridadMasAlta) {
                    prioridadMasAlta = procesos[i].prioridad;
                    idxProcesoSeleccionado = i;
                }
                // Desempate: si las prioridades son iguales, el que llegó primero
                else if (procesos[i].prioridad == prioridadMasAlta) {
                    if (procesos[i].tiempoLlegada < procesos[idxProcesoSeleccionado].tiempoLlegada) {
                        idxProcesoSeleccionado = i;
                    }
                }
            }
        }

        if (idxProcesoSeleccionado == -1) {
            tiempoActual++;
            continue;
        }

        int i = idxProcesoSeleccionado;

        procesos[i].tiempoInicio = tiempoActual;
        procesos[i].tiempoFin = tiempoActual + procesos[i].tiempoRafaga;
        
        // Registrar en el historial para Gantt
        strcpy(historial[contadorPasos].nombreProceso, procesos[i].nombre);
        historial[contadorPasos].tiempoFin = procesos[i].tiempoFin;
        contadorPasos++;

        tiempoActual = procesos[i].tiempoFin;
        ejecutado[i] = 1;
        completados++;
    }

    // Calcular tiempos finales
    for (int i = 0; i < n; i++) {
        procesos[i].tiempoEspera = procesos[i].tiempoInicio - procesos[i].tiempoLlegada;
        procesos[i].tiempoRetorno = procesos[i].tiempoFin - procesos[i].tiempoLlegada;
    }
    
    // Imprimir resultados
    imprimirDiagramaGantt(historial, contadorPasos, "Prioridad (No Apropiativo)");
    imprimirTablaResultados(procesos, n);
}

