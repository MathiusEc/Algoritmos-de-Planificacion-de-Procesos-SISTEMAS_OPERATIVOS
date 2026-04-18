# Simulador de Algoritmos de Planificación de CPU

Este proyecto es una simulación en C de varios algoritmos de planificación de procesos del sistema operativo. Permite comparar el rendimiento de cada algoritmo utilizando un conjunto de datos de entrada consistente. El programa es interactivo y se ejecuta en la línea de comandos.

## Descripción General

El simulador implementa cuatro de los algoritmos de planificación más comunes: FIFO, SJF (no apropiativo), Prioridad (no apropiativo) y Round Robin. El objetivo es calcular y comparar métricas clave como el **Tiempo Medio de Espera (TEM)** y el **Tiempo Medio de Retorno (TRM)** para cada uno, demostrando visualmente su ejecución a través de un diagrama de Gantt.

Los datos de los procesos están definidos directamente en el código para asegurar que cada algoritmo se ejecute bajo las mismas condiciones, permitiendo una comparación justa.

## Organización del Repositorio

El proyecto está estructurado de forma modular para separar la lógica de cada componente:

- **`main.c`**: Contiene el punto de entrada del programa. Es responsable de:
    - Inicializar los procesos.
    - Mostrar el menú interactivo al usuario.
    - Invocar el algoritmo de planificación seleccionado.
- **`fifo.c`, `sjf.c`, `prioridad.c`, `round_robin.c`**: Cada archivo contiene la implementación de la lógica de un algoritmo de planificación específico.
- **`utilidades.c`**: Funciones auxiliares compartidas, como `imprimirDiagramaGantt` e `imprimirTablaResultados`.
- **`proceso.h`**: Define la estructura `Process`, el corazón del modelo de datos que representa a cada proceso con sus atributos (ráfaga, llegada, prioridad, etc.).
- **`planificador.h`**: Archivo de cabecera principal que declara los prototipos de todas las funciones de planificación y utilidades, actuando como la interfaz pública de los módulos.
- **`historial.h`**: Define la estructura `PasoEjecucion`, usada para construir el diagrama de Gantt.
- **`Informe_Algoritmos_Planificacion.pdf`**: Documento de análisis que sirve como base teórica y fuente de los datos de prueba.

## Algoritmos Implementados

Todos los algoritmos operan sobre el siguiente conjunto de procesos:

| Proceso | Ráfaga (ut) | Llegada (ut) | Prioridad |
|---------|-------------|--------------|-----------|
| A       | 3           | 2            | 2         |
| B       | 1           | 4            | 3         |
| C       | 3           | 0            | 1         |
| D       | 4           | 1            | 3         |
| E       | 2           | 3            | 4         |

*(ut = unidades de tiempo)*

### 1. FIFO (First-In, First-Out)
También conocido como FCFS (First-Come, First-Served).
- **Funcionamiento**: Los procesos se atienden en el estricto orden en que llegan a la cola de listos.
- **Características**: Es un algoritmo no apropiativo. Una vez que un proceso tiene la CPU, no la libera hasta que termina.
- **Implementación (`fifo.c`)**: El código primero ordena el array de procesos según su `tiempoLlegada` y luego los ejecuta en secuencia.

### 2. SJF (Shortest Job First)
- **Funcionamiento**: De entre los procesos que están en la cola de listos, el planificador selecciona siempre el que tiene la ráfaga de CPU más corta.
- **Características**: Es no apropiativo en esta implementación. Es óptimo para minimizar el tiempo de espera promedio.
- **Implementación (`sjf.c`)**: En cada instante de tiempo, el código busca entre todos los procesos que ya han llegado (`tiempoLlegada <= tiempoActual`) y aún no se han ejecutado, seleccionando el que tenga el `tiempoRafaga` más bajo.

### 3. Planificación por Prioridad
- **Funcionamiento**: Se asigna una prioridad a cada proceso. El planificador selecciona el proceso con la prioridad más alta (en este caso, el valor numérico de prioridad más bajo).
- **Características**: No apropiativo. Puede llevar a inanición si procesos de baja prioridad nunca son seleccionados.
- **Implementación (`prioridad.c`)**: La lógica es similar a SJF, pero el criterio de selección es el campo `prioridad`. En caso de empate, se elige el proceso que llegó primero.

### 4. Round Robin
- **Funcionamiento**: Un algoritmo apropiativo diseñado para sistemas de tiempo compartido. Cada proceso recibe un pequeño intervalo de tiempo de CPU llamado *quantum*. Si el proceso no termina en ese quantum, es interrumpido y movido al final de la cola de listos.
- **Características**: Garantiza que todos los procesos reciban atención de la CPU de forma equitativa.
- **Implementación (`round_robin.c`)**: Se utiliza una cola para gestionar los procesos listos. Un bucle simula el paso del tiempo, encola nuevos procesos a medida que llegan y ejecuta el proceso al frente de la cola durante un *quantum* (fijado en 3 ut). Si el proceso no termina, se vuelve a encolar.

## ¿Cómo Compilar y Ejecutar?

Para poder compilar el proyecto, es necesario tener un compilador de C como **GCC**.

1.  **Abrir una terminal** en el directorio raíz del proyecto.
2.  **Ejecutar el siguiente comando de compilación**:

    ```bash
    gcc -o planificador.exe main.c fifo.c sjf.c prioridad.c round_robin.c utilidades.c -Wall -g
    ```
    - `gcc`: Llama al compilador.
    - `-o planificador.exe`: Especifica el nombre del archivo ejecutable de salida.
    - `main.c fifo.c ...`: Lista todos los archivos de código fuente necesarios.
    - `-Wall -g`: Banderas recomendadas para mostrar todas las advertencias (`-Wall`) e incluir información de depuración (`-g`).

3.  **Ejecutar el programa**:
    ```bash
    ./planificador.exe
    ```

## Ejemplo de Uso

Al ejecutar el programa, se mostrará la tabla de procesos y un menú interactivo.

```
-------------------------------------------------
Procesos de Entrada (Valores Iniciales)
-------------------------------------------------
Proceso         Ráfaga (ut)     Llegada (ut)    Prioridad
A               3               2               2
B               1               4               3
C               3               0               1
D               4               1               3
E               2               3               4
-------------------------------------------------

Seleccione el algoritmo de planificación a ejecutar:
1. FIFO (First-In, First-Out)
2. SJF (Shortest Job First)
3. Prioridad (No Apropiativo)
4. Round Robin (Quantum = 3)
5. Salir
Su elección: 4

--- Ejecutando Round Robin (Quantum=3) ---

--- Diagrama de Gantt para Round Robin (Quantum=3) ---
|  C  |  D  |  A  |  E  |  B  |  D  |
0     3     6     9     11    12    13

--- Tabla de Resultados ---
Proceso         T. Espera (ut)  T. Retorno (ut)
-------------------------------------------------
A               4               7
B               7               8
C               0               3
D               8               12
E               6               8
-------------------------------------------------
Tiempo Medio de Espera (TEM): 5.00 ut
Tiempo Medio de Retorno (TRM): 7.60 ut

Seleccione el algoritmo de planificación a ejecutar:
1. FIFO (First-In, First-Out)
2. SJF (Shortest Job First)
...
```