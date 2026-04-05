/**
 * Ejercicio 1 — Permutaciones con Restricciones (Fuerza Bruta)
 * =============================================================
 *
 * Descripcion:
 *   Dado un conjunto de n enteros positivos distintos, genera TODAS las
 *   permutaciones posibles (fuerza bruta) y filtra aquellas que cumplen:
 *       P[i] <= 2 * P[i+1]   para todo i en {0, 1, ..., n-2}
 *
 * Compilacion:
 *   g++ -O2 -std=gnu++17 -o EjercicioFuerzaBruta main.cpp
 *
 * Uso:
 *   ./EjercicioFuerzaBruta
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <filesystem>

using namespace std;
using namespace chrono;

// =============================================
// Verifica si una permutacion cumple la restriccion
// P[i] <= 2 * P[i+1] para todo i en [0, n-2]
// Complejidad: O(n)
// =============================================
bool esValida(const vector<int>& perm) {
    for (int i = 0; i < (int)perm.size() - 1; i++) {
        if (perm[i] > 2 * perm[i + 1]) return false;
    }
    return true;
}

// =============================================
// Imprime una permutacion en formato [ a b c ]
// =============================================
void imprimirPerm(const vector<int>& perm) {
    cout << "[ ";
    for (int x : perm) cout << x << " ";
    cout << "]";
}

// =============================================
// Algoritmo principal de fuerza bruta
// Genera n! permutaciones con next_permutation
// Complejidad temporal: O(n! * n)
// Complejidad espacial: O(n)
// =============================================
void fuerzaBruta(vector<int>& A, bool guardarResultados, const string& archivoSalida) {
    sort(A.begin(), A.end()); // garantiza iniciar desde la permutacion menor

    long long totalGeneradas = 0;
    long long totalValidas   = 0;
    vector<vector<int>> validas;

    auto inicio = high_resolution_clock::now();

    do {
        totalGeneradas++;
        if (esValida(A)) {
            totalValidas++;
            validas.push_back(A);
        }
    } while (next_permutation(A.begin(), A.end()));

    auto fin = high_resolution_clock::now();
    double tiempoMs = duration<double, milli>(fin - inicio).count();

    // Salida por consola
    cout << "\n=== PERMUTACIONES VALIDAS ===\n";
    for (const auto& p : validas) {
        imprimirPerm(p);
        cout << "\n";
    }

    cout << "\n--- Resumen ---\n";
    cout << "Total permutaciones generadas : " << totalGeneradas << "\n";
    cout << "Total permutaciones validas   : " << totalValidas   << "\n";
    cout << "Proporcion validas/total      : "
         << (totalGeneradas > 0 ? (double)totalValidas / totalGeneradas * 100.0 : 0.0)
        << "%\n";
    cout << "Tiempo de ejecucion           : " << tiempoMs << " ms\n";

    // Guardar en archivo de resultados
    if (guardarResultados) {
        ofstream f(archivoSalida);
        if (f.is_open()) {
            f << "Total generadas: " << totalGeneradas << "\n";
            f << "Total validas  : " << totalValidas   << "\n";
            f << "Tiempo (ms)    : " << tiempoMs       << "\n\n";
            f << "Permutaciones validas:\n";
            for (const auto& p : validas) {
                for (int x : p) f << x << " ";
                f << "\n";
            }
            cout << "\nResultados guardados en: " << archivoSalida << "\n";
        }
    }
}

// =============================================
// Experimento de tiempos para distintos n
// =============================================
void experimentoTiempos() {
    cout << "\n+------------------------------------------+\n";
    cout << "|   EXPERIMENTO DE TIEMPOS (n variable)    |\n";
    cout << "+------------------------------------------+\n";
    cout << left
        << setw(6)  << "n"
        << setw(14) << "n!"
        << setw(16) << "Validas"
        << setw(14) << "Tiempo (ms)"
        << "\n";
    cout << string(50, '-') << "\n";

    ofstream fcsv("../results/tiempos_ej1.csv");
    fcsv << "n,n!,validas,tiempo_ms\n";

    for (int n = 1; n <= 11; n++) {
        vector<int> A(n);
        iota(A.begin(), A.end(), 1); // A = {1, 2, ..., n}
        sort(A.begin(), A.end());

        long long totalGeneradas = 0, totalValidas = 0;

        auto inicio = high_resolution_clock::now();
        do {
            totalGeneradas++;
            if (esValida(A)) totalValidas++;
        } while (next_permutation(A.begin(), A.end()));
        auto fin = high_resolution_clock::now();

        double t = duration<double, milli>(fin - inicio).count();

        cout << left
            << setw(6)  << n
            << setw(14) << totalGeneradas
            << setw(16) << totalValidas
            << setw(14) << t
            << "\n";

        fcsv << n << "," << totalGeneradas << "," << totalValidas << "," << t << "\n";

        if (t > 30000) { // mas de 30 segundos → impracticable
            cout << "  [n=" << n << " supera umbral practico. Deteniendo experimento.]\n";
            break;
        }
    }
    cout << "\nTabla de tiempos guardada en: ../results/tiempos_ej1.csv\n";
}

// =============================================
// Menu principal
// =============================================
int main() {

    // Crea la carpeta results/ automaticamente si no existe
    filesystem::create_directories("../results");
    cout << "+--------------------------------------------------------+\n";
    cout << "|  Ejercicio 1 - Permutaciones con Restricciones        |\n";
    cout << "|  Enfoque: Fuerza Bruta con next_permutation           |\n";
    cout << "+--------------------------------------------------------+\n";
    cout << "\n1. Ingresar conjunto propio\n";
    cout << "2. Ejecutar experimento de tiempos (n = 1..11)\n";
    cout << "Opcion: ";

    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        int n;
        cout << "\nIngrese n (tamano del conjunto): ";
        cin >> n;

        if (n <= 0) {
            cout << "Error: n debe ser positivo.\n";
            return 1;
        }

        vector<int> A(n);
        cout << "Ingrese los " << n << " enteros positivos distintos: ";
        for (int i = 0; i < n; i++) cin >> A[i];

        // Verificar que sean distintos
        vector<int> copia = A;
        sort(copia.begin(), copia.end());
        for (int i = 0; i < n - 1; i++) {
            if (copia[i] == copia[i + 1]) {
                cout << "Error: los elementos deben ser distintos.\n";
                return 1;
            }
        }

        string archivo = "../results/resultado_ej1_n" + to_string(n) + ".txt";
        fuerzaBruta(A, true, archivo);
    }
    else if (opcion == 2) {
        experimentoTiempos();
    }
    else {
        cout << "Opcion invalida.\n";
        return 1;
    }

    return 0;
}