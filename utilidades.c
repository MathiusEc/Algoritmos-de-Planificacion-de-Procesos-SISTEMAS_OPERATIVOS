#include <stdio.h>
#include <string.h>
#include "planificador.h"

#define MAX_LINEA 80 // Longitud máxima para las líneas del diagrama

void imprimirDiagramaGantt(const PasoEjecucion historial[], int contadorPasos, const char* nombreAlgoritmo) {
    char lineaSuperior[MAX_LINEA] = "|";
    char lineaInferior[MAX_LINEA] = "0";
    char buffer[20];

    printf("\n--- Diagrama de Gantt para %s ---\n", nombreAlgoritmo);

    for (int i = 0; i < contadorPasos; i++) {
        // Dibuja la parte del proceso
        int longitudProceso = strlen(historial[i].nombreProceso) + 4; // " Px "
        int relleno = (longitudProceso > 5) ? 0 : 5 - longitudProceso;
        
        for(int j=0; j < relleno / 2; j++) strcat(lineaSuperior, " ");
        strcat(lineaSuperior, " ");
        strcat(lineaSuperior, historial[i].nombreProceso);
        strcat(lineaSuperior, " ");
        for(int j=0; j < relleno - (relleno / 2); j++) strcat(lineaSuperior, " ");
        strcat(lineaSuperior, "|");

        // Dibuja la parte del tiempo
        sprintf(buffer, "%d", historial[i].tiempoFin);
        int longitudTiempo = strlen(buffer);
        
        for (int j = 0; j < 5 - longitudTiempo; j++) {
            strcat(lineaInferior, " ");
        }
        strcat(lineaInferior, buffer);
    }

    printf("%s\n", lineaSuperior);
    printf("%s\n\n", lineaInferior);
}

void imprimirTablaResultados(const Process procesos[], int n) {
    float totalTiempoEspera = 0;
    float totalTiempoRetorno = 0;

    printf("--- Tabla de Resultados ---\n");
    printf("Proceso\t\tT. Espera (ut)\tT. Retorno (ut)\n");
    printf("-------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%d\n", procesos[i].nombre, procesos[i].tiempoEspera, procesos[i].tiempoRetorno);
        totalTiempoEspera += procesos[i].tiempoEspera;
        totalTiempoRetorno += procesos[i].tiempoRetorno;
    }

    printf("-------------------------------------------------\n");
    printf("Tiempo Medio de Espera (TEM): %.2f ut\n", totalTiempoEspera / n);
    printf("Tiempo Medio de Retorno (TRM): %.2f ut\n", totalTiempoRetorno / n);
}
