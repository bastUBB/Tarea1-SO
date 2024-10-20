# Tarea 1 - Sistemas Operativos

## Integrantes
- Nicolás Gómez Morgado
- Bastián Rodríguez Campusano

## Descripción

Este programa simula una carrera de autos utilizando hilos en C++. Los autos avanzan por la pista de acuerdo con las instrucciones del usuario, que especifica la distancia de la carrera y la cantidad de competidores.

## Construcción del Programa

Para compilar el programa, se proporcionan las siguientes opciones:

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

### Creación archivo ejecutable Makefile sin visualización gráfica
```bash
make
```

### Ejemplo de ejecución normal
```bash
./carrera <metros_de_la_carrera> <cantidad_de_competidores>
```

### Creación archivos ejecutables con visualización gráfica y sin visualización gráfica
```bash
make all
```

### Ejemplo de ejecución visualización gráfica
Si desea visualizar el modo dibujo, maximize su terminal para evitar sobreescritura de lineas.
```bash
./carrera_con_dibujo <metros_de_la_carrera> <cantidad_de_competidores>
```

### Limpiar archivos generados Makefile
```bash
make clean
```
