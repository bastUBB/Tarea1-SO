# Tarea 1 - Sistemas Operativos
<div style="float: right;">
  <img src="https://upload.wikimedia.org/wikipedia/commons/3/35/Tux.svg" alt="Logo" width="50">
</div>

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
Este comando compila el programa con una representación gráfica de la carrera (considerar un tamaño de la terminal optimo para la visualización):
```bash
g++ -DVISUALIZACION carrera.cpp -lpthread -o carrera
```

### Ejemplo de ejecución
```bash
./carrera <metros_de_la_carrera> <cantidad_de_competidores>
```

### Compilación archivo Makefile sin visualización gráfica
```bash
make
```

### Compilación archivo Makefile con visualización gráfica
```bash
make visual
```

### Limpiar archivos generados Makefile
```bash
make clean
```
