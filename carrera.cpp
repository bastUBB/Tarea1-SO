/*
Tarea 1 Sistemas Operativos
Integrantes:
- Bastian Rodriguez
- Nicolas Gomez


Costruccion del Programa:

* Sin dibujo:
g++ carrera.cpp -lpthread -o carrera

*Con dibujo:
g++ -DVISUALIZACION carrera.cpp -lpthread -o carrera


Ejecucion:

./carrera <metros_de_la_carrera> <cantidad_de_competidores>

ejemplo:
./carrera 500 6 //Carrera de 500 metros con 6 autos

*/

#include <thread>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <unistd.h>
#include <iomanip>
#include <mutex>
#include <algorithm>
#include <chrono>
#include <string>

using namespace std;

mutex mtx; 
vector<int> posiciones;
int autosTerminados = 0; 
bool carreraTerminada = false;
int aux=0;

#ifdef VISUALIZACION

class Vehiculo {
private:
    int nroauto; // Número del vehículo
    int metros;  // Metros recorridos por el vehículo
    int meta;
    int avanze;

    // Códigos de colores ANSI
    std::string getColor() const {
        switch (nroauto % 6) { // Hasta 7 colores diferentes
            case 0: return "\033[32m"; // Verde
            case 1: return "\033[33m"; // Amarillo
            case 2: return "\033[34m"; // Azul
            case 3: return "\033[35m"; // Magenta
            case 4: return "\033[36m"; // Cian
            case 5: return "\033[37m"; // Blanco
            default: return "\033[0m";  // Sin color
        }
    }

public:
    // Constructor
    Vehiculo(int nro, int llegada) : nroauto(nro), metros(0), meta(llegada) {}

    void avanzar(int avance) {
        metros += avance; // Avanza el vehículo
    }

    int getMetros() const {
        return metros; // Devuelve los metros recorridos
    }

    int getNro() const {
        return nroauto; // Devuelve el número del vehículo
    }

    // Método para dibujar el vehículo en su posición actual
    void dibujar(int posicion) const {
        std::cout << "\033[" << (posicion * 6+1) << ";1H"; // Mueve el cursor a la línea 'posicion'
        std::cout << "\033[K"; // Limpia la línea

        // Calcular cuántos símbolos '=' mostrar (hasta un máximo de 135)
        int avanze = static_cast<int>(static_cast<double>(metros) / meta * 135); // Proporción de avance
        avanze = std::min(avanze, 135); // Limitar a un máximo de 135

        // Aplicar el color correspondiente
        std::cout << getColor(); // Cambia el color

        std::cout << "Auto " << nroauto + 1 << ": \n";
        std::cout << std::string(avanze, '=') << "   __     " << "\n";
        std::cout << std::string(avanze, '=') << ".-'-"<< nroauto + 1<<"`-._ " << "\n";
        std::cout << std::string(avanze, '=') << "'-O---O--'";
        std::cout << "\033[0m"; // Resetea el color a default
    }

};
#endif

// La hebra inicia su ejecución en esta función
void avance(int meta, int nroauto) {
    
    const std::string COLOR_ROJO_FUERTE = "\033[1;31m"; // Rojo brillante
    const std::string RESET_COLOR = "\033[0m"; // Restablecer color
    
    #ifdef VISUALIZACION
    Vehiculo autoActual(nroauto, meta); // Crear vehículo
    #endif 

    int metros = 0; // Inicializa los metros recorridos por el auto
    int reductorVelocidad = rand() % 10;
    /*if (reductorVelocidad == 1) {
      sleep(0.5);
    }
    */

    while (true) {
        int avance = rand() % 10; // Genera una distancia aleatoria entre 0 y 9
        // Sección crítica protegida por mutex 
        {
            mtx.lock(); // Bloquea el mutex
            
            #ifdef VISUALIZACION
            autoActual.avanzar(avance); // Avanza el vehículo
            #else
            metros += avance; // Avanza el auto
            cout << "Auto " << nroauto + 1 << " avanza: " << avance << " metros, lleva " << metros << " metros en total.\n";
            #endif
            
            #ifdef VISUALIZACION
            metros += avance;
            // Mover el cursor a la línea del auto actual
            std::cout << "\033[" << (nroauto*6+4) << ";2H"; // Mueve el cursor a la línea específica del auto
            // Imprimir el estado del auto
            std::cout << "\nAuto " << nroauto +1 << " avanza: " << avance << " metros, lleva " << metros << " metros en total.\n";
            std::cout << "\033[K"; // Limpia toda la línea actual
            #endif

            // Si el auto ha llegado a la meta y aún no ha terminado
            if (metros >= meta && !carreraTerminada) {
                posiciones[autosTerminados] = nroauto + 1; // Guarda el auto en la posición correspondiente
                autosTerminados++; // Aumenta el contador de autos terminados
                std::cout << COLOR_ROJO_FUERTE << "Autos " << nroauto + 1 << " ha finalizado la carrera en " << autosTerminados << "° lugar\n" << RESET_COLOR;

                // Si todos los autos han terminado, termina la carrera
                if (autosTerminados == posiciones.size()) {
                    carreraTerminada = true; // Marca que la carrera ha terminado
                }
                mtx.unlock(); // Desbloquea el mutex antes de salir
                break; // Sale del bucle
            }
             #ifdef VISUALIZACION
             autoActual.dibujar(nroauto);
             #endif
            mtx.unlock(); // Desbloquea el mutex
        }
        int tiempoEspera;
        #ifdef VISUALIZACION
        tiempoEspera = rand() % 300 + 100; // Tiempo de espera entre 100 ms y 400 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(tiempoEspera)); // Pausa para permitir que otros autos se muestren
        #endif
        tiempoEspera = rand() % 50 + 150; // Tiempo de espera entre 50 ms y 200 ms
        std::this_thread::sleep_for(std::chrono::milliseconds(tiempoEspera)); // Pausa para permitir que otros autos se muestren
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cout << "uso: ./carrera <metros> <cantidad de autos>\n";
        return -1;
    }

    if (atoi(argv[1]) <= 0) {
        cout << "numero debe ser > 0\n";
        return -1;
    }

    if (atoi(argv[2]) <= 1) {
        cout << "numero debe ser >= 2\n";
        return -1;
    }

    int meta = atoi(argv[1]);
    int cantAutos = atoi(argv[2]);
    posiciones.resize(cantAutos, -1); // Inicializa el vector de posiciones

    thread threads[cantAutos]; // Crear hilos para cada auto

    std::cout << "\033[2J"; // Limpia la línea
    // Crear y lanzar las hebras
    for (int i = 0; i < cantAutos; i++) {
        threads[i] = thread(avance, meta, i);
    }

    // Esperar a que todas las hebras terminen
    for (int i = 0; i < cantAutos; i++) {
        threads[i].join();
    }

    #ifdef VISUALIZACION
    std::cout << "\033[" << cantAutos*6+1<< ";1H"; 
    #endif
    
    cout << "\nTabla de posiciones:\n";
    cout << left << setw(15) << "Posición" << setw(15) << "Auto" << endl;
    cout << string(20, '-') << endl; // Línea de separación

    for (int i = 0; i < cantAutos; i++) {
    cout << left << setw(15) << (to_string(i + 1) + "°")
         << left << setw(15) << posiciones[i]
         << endl;
    }

    // Mostrar el podio
    cout << "\nPodio:\n";
    cout << string(20, '-') << endl; // Línea de separación

    // Formato del podio con emojis de medalla
    cout << "🥇Auto " << (autosTerminados > 0 ? to_string(posiciones[0]) : " ") << "🥇" << endl; // Primer lugar
    cout << "🥈Auto " << (autosTerminados > 1 ? to_string(posiciones[1]) : " ") << "🥈" << endl; // Segundo lugar
    cout << "🥉Auto " << (autosTerminados > 2 ? to_string(posiciones[2]) : " ") << "🥉" << endl; // Tercer lugar

    cout << "\n" << "🏁🏁¡¡Terminó la carrera!!🏁🏁\n";
    return 0;
}