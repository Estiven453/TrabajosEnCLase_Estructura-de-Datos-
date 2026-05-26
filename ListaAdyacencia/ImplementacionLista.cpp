#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Constante para el número de estaciones
const int NUM_ESTACIONES = 5;

// Arreglo para mapear los índices con los nombres reales de las estaciones
const string nombresEstaciones[NUM_ESTACIONES] = {
    "El Labrador",
    "Jipijapa",
    "La Pradera",
    "El Ejido",
    "La Magdalena"
};

// Función para inicializar y cargar la red de metro
void cargarRedMetro(vector<vector<int>>& listaAdyacencia, bool& cargado) {
    // Limpiar el grafo por si ya tenía datos
    for (int i = 0; i < NUM_ESTACIONES; i++) {
        listaAdyacencia[i].clear();
    }

    // Definición de las aristas del enunciado: 0-1, 0-2, 1-3, 2-3, 3-4
    int aristas[][2] = {
        {0, 1},
        {0, 2},
        {1, 3},
        {2, 3},
        {3, 4}
    };
    int totalAristas = 5;

    // Insertar las aristas en la lista de adyacencia (Grafo No Dirigido)
    for (int i = 0; i < totalAristas; i++) {
        int u = aristas[i][0];
        int v = aristas[i][1];
        
        listaAdyacencia[u].push_back(v);
        listaAdyacencia[v].push_back(u); // Conexión bidireccional
    }

    cout << "\n[+] Red de metro cargada con exito." << endl;
    cargado = true;
}

// Función para mostrar las estaciones y sus vecinos
void mostrarEstacionesYVecinos(const vector<vector<int>>& listaAdyacencia, bool cargado) {
    if (!cargado) {
        cout << "\n[!] Primero debes cargar la red de metro (Opcion 1)." << endl;
        return;
    }

    cout << "\n--- ESTACIONES Y SUS VECINOS ---" << endl;
    for (int i = 0; i < NUM_ESTACIONES; i++) {
        cout << "Estacion [" << i << "] " << nombresEstaciones[i] << " -> Vecinos: ";
        if (listaAdyacencia[i].empty()) {
            cout << "Ninguno";
        } else {
            for (size_t j = 0; j < listaAdyacencia[i].size(); j++) {
                int vecinoIdx = listaAdyacencia[i][j];
                cout << nombresEstaciones[vecinoIdx] << " (" << vecinoIdx << ")";
                if (j < listaAdyacencia[i].size() - 1) cout << ", ";
            }
        }
        cout << endl;
    }
}

// Función para calcular el total de valores guardados en la lista de adyacencia
void calcularTotalValores(const vector<vector<int>>& listaAdyacencia, bool cargado) {
    if (!cargado) {
        cout << "\n[!] Primero debes cargar la red de metro (Opcion 1)." << endl;
        return;
    }

    int totalValores = 0;
    for (int i = 0; i < NUM_ESTACIONES; i++) {
        totalValores += listaAdyacencia[i].size();
    }

    cout << "\n--- TOTAL DE VALORES GUARDADOS ---" << endl;
    cout << "Cada conexion almacena el ID del nodo vecino." << endl;
    cout << "El numero total de valores guardados en la lista de adyacencia es: " << totalValores << endl;
    cout << "(Equivale a 2 veces el numero de aristas: 2 * 5 = 10)" << endl;
}

int main() {
    // Estructura principal: un vector de vectores
    vector<vector<int>> listaAdyacencia(NUM_ESTACIONES);
    bool redCargada = false;
    int opcion;

    do {
        cout << "\n========== MENU REPASO GRAFOS ==========" << endl;
        cout << "1. Inicializar y Cargar la Red de Metro" << endl;
        cout << "2. Mostrar Estaciones y sus Vecinos" << endl;
        cout << "3. Calcular Total de Valores Guardados" << endl;
        cout << "4. Salir del Programa" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cargarRedMetro(listaAdyacencia, redCargada);
                break;
            case 2:
                mostrarEstacionesYVecinos(listaAdyacencia, redCargada);
                break;
            case 3:
                calcularTotalValores(listaAdyacencia, redCargada);
                break;
            case 4:
                cout << "\nSaliendo del programa..." << endl;
                break;
            default:
                cout << "\n[!] Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 4);

    return 0;
}