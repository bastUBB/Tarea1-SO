# Tarea 1 - Sistemas Operativos

## Integrantes
- Bastian Rodriguez
- Nicolas Gomez

## Descripción

Este programa simula una carrera de autos utilizando hilos en C++. Los autos avanzan por la pista de acuerdo con las instrucciones del usuario, que especifica la distancia de la carrera y la cantidad de competidores.

## Construcción del Programa

Para compilar el programa, se proporcionan las opciones con y sin visualización gráfica de la carrera.

### Compilación sin visualización
Este comando compila el programa sin incluir gráficos de la carrera:
```bash
g++ carrera.cpp -lpthread -o carrera
```

### Compilación con visualización
Este comando compila el programa con una representación gráfica de la carrera:
```bash
g++ -DVISUALIZACION carrera.cpp -lpthread -o carrera
```

### Ejemplo de ejecución
```bash
./carrera <metros_de_la_carrera> <cantidad_de_competidores>
```
