#include <stdio.h>
#include <stdlib.h>
#include "proceso.h"
#include "planificador.h"

// --- Prototipos de Funciones Locales ---
void reiniciarProcesos(Process procesos[], int n);
void limpiarBufferEntrada();
int obtenerOpcionMenu();

int main() {
    // --- Encabezado ---
    printf("SISTEMAS OPERATIVOS\n");
    printf("ITIZ 2100 / 5473 / 2026-20 \n\n");
    printf("PROGRAMACION ALGORITMOS DE PLANIFICACION DE PROCESOS \n\n");
    printf("NOMBRE DE LA PRACTICA:\tPROGRAMACION ALGORITMOS DE PLANIFICACION DE PROCESOS \n");
    printf("LABORATORIO:\tUPE -315\n");
    printf("PROFESOR:\tJUAN CARLOS FIGUEROA DURAN\n");
    printf("FECHA:\t19-04-2026\n\n");
    printf("Autor (Castillo Mathias) \n");
    printf("Estudiantes del curso [ITIZ 2100] – [SISTEMAS OPERATIVOS], Universidad de Las Americas, Quito-Ecuador \n\n\n");

    Process procesos[5];
    // Datos de los procesos extraídos del informe
    procesos[0] = (Process){"A", 3, 2, 2};
    procesos[1] = (Process){"B", 1, 4, 3};
    procesos[2] = (Process){"C", 3, 0, 1};
    procesos[3] = (Process){"D", 4, 1, 3};
    procesos[4] = (Process){"E", 2, 3, 4};
    int n = sizeof(procesos) / sizeof(procesos[0]);

    // 1. Imprimir la tabla de procesos inicial
    printf("-------------------------------------------------\n");
    printf("Procesos de Entrada (Valores Iniciales)\n");
    printf("-------------------------------------------------\n");
    printf("Proceso\t\tRáfaga (ut)\tLlegada (ut)\tPrioridad\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t\t%d\t\t%d\t\t%d\n", procesos[i].nombre, procesos[i].tiempoRafaga, procesos[i].tiempoLlegada, procesos[i].prioridad);
    }
    printf("-------------------------------------------------\n\n");

    int opcion;
    do {
        // 2. Mostrar menú y obtener opción validada
        opcion = obtenerOpcionMenu();
        printf("\n");

        // Antes de cada ejecución, reiniciamos los valores de los procesos
        reiniciarProcesos(procesos, n);

        // 3. Ejecutar el algoritmo seleccionado
        switch (opcion) {
            case 1:
                printf("--- Ejecutando FIFO (First-In, First-Out) ---\n");
                planificarFifo(procesos, n);
                break;
            case 2:
                printf("--- Ejecutando SJF (Shortest Job First) ---\n");
                planificarSjf(procesos, n);
                break;
            case 3:
                printf("--- Ejecutando Prioridad (No Apropiativo) ---\n");
                planificarPrioridad(procesos, n);
                break;
            case 4:
                printf("--- Ejecutando Round Robin (Quantum=3) ---\n");
                planificarRr(procesos, n, 3);
                break;
            case 5:
                printf("Saliendo del programa.\n");
                break;
            default:
                // Esta validación ahora está en obtenerOpcionMenu
                break;
        }
        printf("\n");

    } while (opcion != 5);

    return 0;
}

/**
 * @brief Reinicia los valores de simulación de los procesos.
 */
void reiniciarProcesos(Process procesos[], int n) {
    for (int i = 0; i < n; i++) {
        procesos[i].tiempoInicio = -1;
        procesos[i].tiempoFin = -1;
        procesos[i].tiempoEspera = 0;
        procesos[i].tiempoRetorno = 0;
        procesos[i].tiempoRestante = procesos[i].tiempoRafaga;
    }
}

/**
 * @brief Limpia el buffer de entrada (stdin) para evitar bucles infinitos
 * en caso de entrada no válida.
 */
void limpiarBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * @brief Muestra el menú, solicita una opción al usuario y la valida.
 * @return La opción elegida por el usuario (1-5).
 */
int obtenerOpcionMenu() {
    int opcion;
    int resultadoScan;

    printf("Seleccione el algoritmo de planificación a ejecutar:\n");
    printf("1. FIFO (First-In, First-Out)\n");
    printf("2. SJF (Shortest Job First)\n");
    printf("3. Prioridad (No Apropiativo)\n");
    printf("4. Round Robin (Quantum = 3)\n");
    printf("5. Salir\n");
    
    while (1) {
        printf("Su elección: ");
        resultadoScan = scanf("%d", &opcion);

        if (resultadoScan == 1 && opcion >= 1 && opcion <= 5) {
            limpiarBufferEntrada(); // Limpiar por si el usuario escribió algo después del número
            return opcion;
        } else {
            printf("\nError: Ingrese un número válido entre 1 y 5.\n");
            limpiarBufferEntrada(); // Esencial para limpiar la entrada incorrecta (ej. letras)
        }
    }
}

