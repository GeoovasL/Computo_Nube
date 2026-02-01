#include <iostream>
#include <vector>
#include <omp.h>
#include <ctime>   // Para time()
#include <cstdlib> // Para rand() y srand()

using namespace std;

int main() {
    int n;
    srand(time(NULL)); // Semilla para números aleatorios reales

    cout << "Ingrese el numero de elementos: ";
    cin >> n;

    vector<int> A(n), B(n), C(n);

    // 1. Llenado aleatorio (Secuencial)
    for (int i = 0; i < n; i++) {
        A[i] = rand() % 100; // Números entre 0 y 99
        B[i] = rand() % 100;
    }

    cout << "\n--- Iniciando Suma Paralela ---\n";

    // 2. Suma paralela con rastreo
    // Usamos 'schedule(static)' para que OpenMP reparta el trabajo de forma predecible
#pragma omp parallel for schedule(static)
    for (int i = 0; i < n; i++) {
        int id_hilo = omp_get_thread_num(); // Obtenemos el ID del hilo actual
        C[i] = A[i] + B[i];

        // Imprimimos qué hilo está procesando este índice
        // Nota: El uso de 'critical' evita que los hilos escriban encima de otros en la consola
#pragma omp critical
        {
            cout << "Hilo " << id_hilo << " procesando indice [" << i << "]: "
                << A[i] << " + " << B[i] << " = " << C[i] << endl;
        }
    }

    // 3. Mostrar arreglos finales de forma limpia
    cout << "\n--- Resumen Final ---" << endl;
    cout << "Arreglo A: "; for (int v : A) cout << v << " "; cout << endl;
    cout << "Arreglo B: "; for (int v : B) cout << v << " "; cout << endl;
    cout << "Arreglo C: "; for (int v : C) cout << v << " "; cout << endl;

    return 0;
}