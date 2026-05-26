#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

// Estructura para representar el Grafo
class GrafoDFS {
private:
    // Lista de adyacencia usando un map para mantener los nodos ordenados alfabéticamente
    map<char, vector<char>> listaAdyacencia;

public:
    // Constructor que inicializa el grafo exactamente como la imagen
    GrafoDFS() {
        listaAdyacencia['A'] = {'B', 'C'};
        listaAdyacencia['B'] = {'A', 'D', 'E'};
        listaAdyacencia['C'] = {'A', 'F'};
        listaAdyacencia['D'] = {'B'};
        listaAdyacencia['E'] = {'B', 'F'};
        listaAdyacencia['F'] = {'C', 'E'};
    }

    // [1] Ver todos los nodos
    void verTodosLosNodos() {
        cout << "\n--- NODOS DEL GRAFO ---" << endl;
        for (auto const& [nodo, vecinos] : listaAdyacencia) {
            cout << "[ " << nodo << " ] ";
        }
        cout << endl;
    }

    // [2] Lista de adyacencia (nodos y vecinos)
    void mostrarListaAdyacencia() {
        cout << "\n--- LISTA DE ADYACENCIA ---" << endl;
        for (auto const& [nodo, vecinos] : listaAdyacencia) {
            cout << nodo << " -> [";
            for (size_t i = 0; i < vecinos.size(); i++) {
                cout << vecinos[i];
                if (i < vecinos.size() - 1) cout << ", ";
            }
            cout << "]" << endl;
        }
    }

    // [3] Recorrido DFS desde A (Usando Stack explícito)
    void recorridoDFS(char nodoInicio) {
        cout << "\n--- RECORRIDO DFS DESDE " << nodoInicio << " ---" << endl;

        stack<char> pila;
        set<char> visitados;
        vector<char> ordenVisita;

        // Añadir el nodo inicial a la pila
        pila.push(nodoInicio);

        while (!pila.empty()) {
            char nodoActual = pila.top();
            pila.pop();

            // Si el nodo ya fue procesado, lo ignoramos
            if (visitados.find(nodoActual) != visitados.end()) {
                continue;
            }

            // Marcar como visitado
            visitados.insert(nodoActual);
            ordenVisita.push_back(nodoActual);

            // Obtener los vecinos del nodo actual
            vector<char> vecinos = listaAdyacencia[nodoActual];

            // Para que el DFS elija el orden alfabético al sacar de la pila (LIFO),
            // debemos meter los vecinos a la pila en orden inverso (de la Z a la A).
            sort(vecinos.rbegin(), vecinos.rend());

            for (char vecino : vecinos) {
                if (visitados.find(vecino) == visitados.end()) {
                    pila.push(vecino);
                }
            }
        }

        // Mostrar el resultado final del recorrido
        cout << "Orden de visita: ";
        for (size_t i = 0; i < ordenVisita.size(); i++) {
            cout << ordenVisita[i];
            if (i < ordenVisita.size() - 1) cout << " -> ";
        }
        cout << endl;
    }
};

int main() {
    GrafoDFS grafo;
    int opcion;

    do {
        cout << "\n========== MENU DFS GRAFOS ==========" << endl;
        cout << "[1] Ver todos los nodos" << endl;
        cout << "[2] Lista de adyacencia (nodos y vecinos)" << endl;
        cout << "[3] Recorrido DFS desde A" << endl;
        cout << "[4] Salir del programa" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                grafo.verTodosLosNodos();
                break;
            case 2:
                grafo.mostrarListaAdyacencia();
                break;
            case 3:
                grafo.recorridoDFS('A');
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