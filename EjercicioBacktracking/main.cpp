/**
 * Ejercicio 2 — Coloracion de Grafos con k Colores (Backtracking)
 * ================================================================
 *
 * Descripcion:
 *   Dado un grafo no dirigido G=(V,E) representado por matriz de adyacencia,
 *   y un numero k de colores, determina si existe una k-coloracion valida
 *   (ningun par de vertices adyacentes comparte color).
 *
 *   Implementa y compara:
 *     - Backtracking con poda temprana
 *     - Fuerza Bruta (k^n combinaciones)
 *
 * Compilacion:
 *   g++ -O2 -std=gnu++17 -o EjercicioBacktracking main.cpp
 *
 * Uso:
 *   ./EjercicioBacktracking
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <filesystem>

using namespace std;
using namespace chrono;

// ==============================================
// Variables globales del grafo
// ==============================================
int n, k;
vector<vector<int>> ady;   // matriz de adyacencia
vector<int> color;         // asignacion actual de colores

long long nodosBT  = 0;    // nodos explorados por backtracking
long long nodosFB  = 0;    // nodos explorados por fuerza bruta

long long totalBT  = 0;    // coloraciones validas halladas por BT
long long totalFB  = 0;    // coloraciones validas halladas por FB

vector<int> primerasBT;    // primera solucion encontrada por BT
bool guardadaBT = false;

// ==========================================================
// Verifica si asignar el color c al vertice v
// es seguro (ningun vecino adyacente tiene ese color)
// Complejidad: O(n)
// ==========================================================
bool esSeguro(int v, int c) {
    for (int u = 0; u < n; u++) {
        if (ady[v][u] && color[u] == c) return false;
    }
    return true;
}

// ==========================================================
// Backtracking recursivo
// Asigna colores vertice a vertice podando
// cuando hay conflicto con vecinos ya coloreados
//
// Complejidad temporal (peor caso): O(k^n * n)
// Complejidad espacial: O(n)  (pila de recursion)
// ==========================================================
void backtracking(int v) {
    nodosBT++;

    if (v == n) {
        // Solucion completa encontrada
        totalBT++;
        if (!guardadaBT) {
            primerasBT = color;
            guardadaBT = true;
        }
        return;
    }

    for (int c = 1; c <= k; c++) {
        if (esSeguro(v, c)) {
            color[v] = c;
            backtracking(v + 1);
            color[v] = 0; // backtrack
        }
    }
}

// ==========================================================
// Verifica si una asignacion completa es valida
// Complejidad: O(n^2)
// ==========================================================
bool asignacionValida(const vector<int>& asign) {
    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) {
            if (ady[u][v] && asign[u] == asign[v]) return false;
        }
    }
    return true;
}

// ===================================================
// Fuerza bruta: prueba las k^n combinaciones
// usando representacion en base k
//
// Complejidad temporal: O(k^n * n^2)
// Complejidad espacial: O(n)
// ===================================================
void fuerzaBruta() {
    long long total = (long long)pow((double)k, n);
    vector<int> asign(n);

    for (long long mask = 0; mask < total; mask++) {
        nodosFB++;
        long long tmp = mask;
        for (int i = 0; i < n; i++) {
            asign[i] = (tmp % k) + 1; // colores 1..k
            tmp /= k;
        }
        if (asignacionValida(asign)) totalFB++;
    }
}

// ===================================================
// Imprime la primera solucion de backtracking
// ===================================================
void imprimirPrimeraSolucion() {
    if (!guardadaBT) {
        cout << "No existe una " << k << "-coloracion valida.\n";
        return;
    }
    cout << "\nPrimera solucion encontrada (Backtracking):\n";
    for (int v = 0; v < n; v++) {
        cout << "  color[" << v << "] = " << primerasBT[v] << "\n";
    }
}

// ===================================================
// Imprime la matriz de adyacencia
// ===================================================
void imprimirGrafo() {
    cout << "\nMatriz de adyacencia:\n  ";
    for (int i = 0; i < n; i++) cout << i << " ";
    cout << "\n";
    for (int i = 0; i < n; i++) {
        cout << i << " ";
        for (int j = 0; j < n; j++) cout << ady[i][j] << " ";
        cout << "\n";
    }
}

// ===================================================
// Carga grafo desde consola
// ===================================================
void leerGrafo() {
    cout << "Ingrese el numero de vertices (n): ";
    cin >> n;
    cout << "Ingrese k (numero de colores disponibles): ";
    cin >> k;

    ady.assign(n, vector<int>(n, 0));
    color.assign(n, 0);

    cout << "Ingrese la matriz de adyacencia (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> ady[i][j];
}

// ===================================================
// Carga uno de los grafos de ejemplo predefinidos
// ===================================================
void cargarEjemplo(int ejemplo) {
    switch (ejemplo) {
        case 1: {
            // Ciclo C4 (grafo del enunciado)
            cout << "[Ejemplo 1] Ciclo C4 (4 vertices, k=3)\n";
            n = 4; k = 3;
            ady = {
                {0,1,0,1},
                {1,0,1,0},
                {0,1,0,1},
                {1,0,1,0}
            };
            break;
        }
        case 2: {
            // Grafo completo K4 (maximiza conflictos)
            cout << "[Ejemplo 2] Grafo completo K4 (4 vertices, k=4)\n";
            n = 4; k = 4;
            ady = {
                {0,1,1,1},
                {1,0,1,1},
                {1,1,0,1},
                {1,1,1,0}
            };
            break;
        }
        case 3: {
            // Grafo bipartito K2,3 (5 vertices, k=2)
            cout << "[Ejemplo 3] Grafo bipartito K2,3 (5 vertices, k=2)\n";
            n = 5; k = 2;
            ady = {
                {0,0,1,1,1},
                {0,0,1,1,1},
                {1,1,0,0,0},
                {1,1,0,0,0},
                {1,1,0,0,0}
            };
            break;
        }
        default:
            cout << "Ejemplo no valido.\n";
            exit(1);
    }
    color.assign(n, 0);
}

// ===============================================
// Guarda resultados en archivo
// ===============================================
void guardarResultados(const string& archivo,
                    double tiempoBT, double tiempoFB) {
    ofstream f(archivo);
    if (!f.is_open()) return;

    f << "=== Ejercicio 2 - Coloracion de Grafos ===\n";
    f << "n=" << n << "  k=" << k << "\n\n";

    f << "--- Backtracking ---\n";
    f << "Coloraciones validas : " << totalBT  << "\n";
    f << "Nodos explorados     : " << nodosBT  << "\n";
    f << "Tiempo (ms)          : " << tiempoBT << "\n\n";

    f << "--- Fuerza Bruta ---\n";
    f << "Coloraciones validas : " << totalFB  << "\n";
    f << "Nodos explorados     : " << nodosFB  << "\n";
    f << "Tiempo (ms)          : " << tiempoFB << "\n\n";

    f << "Primera solucion (BT):\n";
    if (guardadaBT) {
        for (int v = 0; v < n; v++)
            f << "  color[" << v << "] = " << primerasBT[v] << "\n";
    } else {
        f << "  No existe coloracion valida.\n";
    }

    cout << "\nResultados guardados en: " << archivo << "\n";
}

// =================================================
// Menu principal
// =================================================
int main() {
    
    // Crea la carpeta results/ automaticamente si no existe
    filesystem::create_directories("../results");
    cout << "+--------------------------------------------------------+\n";
    cout << "|  Ejercicio 2 - Coloracion de Grafos con k Colores     |\n";
    cout << "|  Backtracking con poda + Fuerza Bruta                 |\n";
    cout << "+--------------------------------------------------------+\n\n";

    cout << "Opciones de entrada:\n";
    cout << "  1. Ingresar grafo manualmente\n";
    cout << "  2. Ejemplo 1 - Ciclo C4   (n=4, k=3)\n";
    cout << "  3. Ejemplo 2 - Completo K4 (n=4, k=4)\n";
    cout << "  4. Ejemplo 3 - Bipartito K2,3 (n=5, k=2)\n";
    cout << "Opcion: ";

    int opcion;
    cin >> opcion;

    if (opcion == 1)       leerGrafo();
    else if (opcion >= 2 && opcion <= 4) cargarEjemplo(opcion - 1);
    else { cout << "Opcion invalida.\n"; return 1; }

    imprimirGrafo();

    // Backtracking
    nodosBT = 0; totalBT = 0; guardadaBT = false;
    color.assign(n, 0);
    auto t0 = high_resolution_clock::now();
    backtracking(0);
    auto t1 = high_resolution_clock::now();
    double tiempoBT = duration<double, milli>(t1 - t0).count();

    // Fuerza Bruta
    nodosFB = 0; totalFB = 0;
    auto t2 = high_resolution_clock::now();
    fuerzaBruta();
    auto t3 = high_resolution_clock::now();
    double tiempoFB = duration<double, milli>(t3 - t2).count();

    // Resultados 
    imprimirPrimeraSolucion();

    cout << "\n=== Comparacion de Enfoques ===\n";
    cout << left
        << setw(28) << "Metodo"
        << setw(18) << "Coloraciones"
        << setw(20) << "Nodos explorados"
        << setw(14) << "Tiempo (ms)"
        << "\n";
    cout << string(80, '-') << "\n";
    cout << left
        << setw(28) << "Backtracking (poda)"
        << setw(18) << totalBT
        << setw(20) << nodosBT
        << setw(14) << tiempoBT
        << "\n";
    cout << left
        << setw(28) << "Fuerza Bruta (k^n)"
        << setw(18) << totalFB
        << setw(20) << nodosFB
        << setw(14) << tiempoFB
        << "\n";

    if (totalBT == totalFB)
        cout << "\n[OK] Ambos enfoques coinciden: " << totalBT << " coloraciones validas.\n";
    else
        cout << "\n[!] DISCREPANCIA: BT=" << totalBT << "  FB=" << totalFB << "\n";

    // Reduccion de nodos por poda
    if (nodosFB > 0) {
        double reduccion = (1.0 - (double)nodosBT / nodosFB) * 100.0;
        cout << "Reduccion de nodos por poda: " << fixed << setprecision(1)
            << reduccion << "%\n";
    }

    string archivo = "../results/resultado_ej2_n" + to_string(n)
                + "_k" + to_string(k) + ".txt";
    guardarResultados(archivo, tiempoBT, tiempoFB);

    return 0;
}