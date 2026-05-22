#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <iomanip>
#include <sstream>

// ========== 1. REPRESENTACIÓN CON MATRIZ DE ADYACENCIA ========== 
class GrafoMatriz {
private:
    std::vector<std::vector<int>> matriz;
    int numVertices;
    std::vector<std::string> nombres; // Para dar nombres a los nodos 

public:
    GrafoMatriz(int vertices, const std::vector<std::string>& nombres) {
        this->numVertices = vertices;
        this->nombres = nombres;
        // Inicializa una matriz de V x V llena de ceros
        this->matriz = std::vector<std::vector<int>>(vertices, std::vector<int>(vertices, 0));
    }

    // Agregar arista (no dirigida) 
    void agregarArista(int i, int j) {
        matriz[i][j] = 1;
        matriz[j][i] = 1;
    }

    // Verificar si dos nodos están conectados (O(1)) 
    bool estanConectados(int i, int j) {
        return matriz[i][j] == 1;
    }

    // Obtener vecinos de un nodo (O(n) porque recorre toda la fila) 
    std::vector<int> obtenerVecinos(int nodo) {
        std::vector<int> vecinos;
        for (int i = 0; i < numVertices; i++) {
            if (matriz[nodo][i] == 1) {
                vecinos.push_back(i);
            }
        }
        return vecinos;
    }

    // Calcular memoria aproximada en bytes (int = 4 bytes) 
    int calcularMemoria() {
        return numVertices * numVertices * 4;
    }

    // Mostrar matriz visualmente 
    void mostrar() {
        std::cout << "\nMATRIZ DE ADYACENCIA ( " << numVertices << "x" << numVertices << " ):\n";
        std::cout << "      ";
        for (int i = 0; i < numVertices; i++) {
            std::cout << std::left << std::setw(6) << nombres[i];
        }
        std::cout << "\n";
        for (int i = 0; i < numVertices; i++) {
            std::cout << std::left << std::setw(6) << nombres[i];
            for (int j = 0; j < numVertices; j++) {
                std::cout << std::left << std::setw(6) << matriz[i][j];
            }
            std::cout << "\n";
        }
    }
};

// ========== 2. REPRESENTACIÓN CON LISTA DE ADYACENCIA ========== 
class GrafoLista {
private:
    std::unordered_map<int, std::vector<int>> lista;
    int numVertices;
    std::vector<std::string> nombres;

public:
    GrafoLista(int vertices, const std::vector<std::string>& nombres) {
        this->numVertices = vertices;
        this->nombres = nombres;
        for (int i = 0; i < vertices; i++) {
            lista[i] = std::vector<int>();
        }
    }

    // Agregar arista (no dirigida) 
    void agregarArista(int i, int j) {
        lista[i].push_back(j);
        lista[j].push_back(i);
    }

    // Verificar si dos nodos están conectados (O(grado)) 
    bool estanConectados(int i, int j) {
        const auto& vecinos = lista[i];
        // Busca si 'j' existe dentro del vector de vecinos de 'i'
        return std::find(vecinos.begin(), vecinos.end(), j) != vecinos.end();
    }

    // Obtener vecinos de un nodo (O(1) para acceder, O(grado) para iterar) 
    std::vector<int> obtenerVecinos(int nodo) {
        return lista[nodo];
    }

    // Calcular memoria aproximada (cada entero = 4 bytes + overhead de lista) 
    int calcularMemoria() {
        int total = 0;
        for (int i = 0; i < numVertices; i++) {
            total += 4;  // referencia/llave en el map
            total += lista[i].size() * 4;  // cada vecino 
        }
        return total;
    }

    // Mostrar lista visualmente 
    void mostrar() {
        std::cout << "\nLISTA DE ADYACENCIA:\n";
        for (int i = 0; i < numVertices; i++) {
            std::cout << nombres[i] << " -> ";
            const std::vector<int>& vecinos = lista[i];
            if (vecinos.empty()) {
                std::cout << "[]\n";
            } else {
                std::cout << "[";
                for (size_t j = 0; j < vecinos.size(); j++) {
                    std::cout << nombres[vecinos[j]];
                    if (j < vecinos.size() - 1) std::cout << ", ";
                }
                std::cout << "]\n";
            }
        }
    }
};

// Helper para mostrar nombres de vecinos 
std::string vecinosComoString(const std::vector<int>& vecinos, const std::vector<std::string>& nombres) {
    if (vecinos.empty()) return "[]";
    std::stringstream ss;
    ss << "[";
    for (size_t i = 0; i < vecinos.size(); i++) {
        ss << nombres[vecinos[i]];
        if (i < vecinos.size() - 1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

// ========== 3. MAIN - EJEMPLO PRÁCTICO ========== 
int main() {
    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "        COMPARACION PRACTICA: MATRIZ vs LISTA DE ADYACENCIA\n";
    std::cout << "----------------------------------------------------------------------\n";

    // Grafo ejemplo: 6 nodos (ciudades), 5 aristas (disperso) 
    std::vector<std::string> nombres = {"A", "B", "C", "D", "E", "F"};
    int numVertices = 6;

    // Crear ambas representaciones 
    GrafoMatriz matriz(numVertices, nombres);
    GrafoLista lista(numVertices, nombres);

    // Aristas del grafo (disperso: 5 aristas) 
    std::vector<std::vector<int>> aristas = { 
        {0, 1},  // A-B 
        {0, 2},  // A-C 
        {1, 3},  // B-D 
        {2, 4},  // C-E 
        {3, 5}   // D-F 
    };

    for (const auto& a : aristas) {
        matriz.agregarArista(a[0], a[1]);
        lista.agregarArista(a[0], a[1]);
    }

    // ===== MOSTRAR AMBAS REPRESENTACIONES ===== 
    matriz.mostrar();
    lista.mostrar();

    // ===== COMPARACIÓN DE MEMORIA ===== 
    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "COMPARACION DE MEMORIA:\n";
    std::cout << "   Matriz: " << matriz.calcularMemoria() << " bytes\n";
    std::cout << "   Lista:  " << lista.calcularMemoria() << " bytes\n";
    std::cout << "   Nota: En este caso (grafo disperso), la lista usa " 
              << (matriz.calcularMemoria() - lista.calcularMemoria()) << " bytes menos.\n";

    // ===== OPERACIÓN: VER CONEXIÓN DIRECTA ===== 
    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "OPERACION 1: ¿A y B estan conectados?\n";
    std::cout << "   Matriz: consulta O(1) -> " << (matriz.estanConectados(0, 1) ? "true" : "false") << "\n";
    std::cout << "   Lista:  consulta O(grado) -> " << (lista.estanConectados(0, 1) ? "true" : "false") << "\n";

    // ===== OPERACIÓN: VER VECINOS ===== 
    std::cout << "\n----------------------------------------------------------------------\n";
    int nodoConsultado = 0;
    std::cout << "OPERACION 2: Obtener vecinos de " << nombres[nodoConsultado] << "\n";
    std::cout << "   Matriz: recorre toda la fila (O(n)) -> " << vecinosComoString(matriz.obtenerVecinos(nodoConsultado), nombres) << "\n";
    std::cout << "   Lista:  accede directamente a su lista (O(grado)) -> " << vecinosComoString(lista.obtenerVecinos(nodoConsultado), nombres) << "\n";

    // ===== GRÁFICO DEL GRAFO EN CONSOLA ===== 
    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "REPRESENTACION VISUAL DEL GRAFO:\n";
    std::cout << "        A\n";
    std::cout << "       / \\\n";
    std::cout << "      B   C\n";
    std::cout << "      |   |\n";
    std::cout << "      D   E\n";
    std::cout << "      |\n";
    std::cout << "      F\n";
    std::cout << "\n   Aristas: A-B, A-C, B-D, C-E, D-F\n";

    // ===== CONCLUSIÓN ===== 
    std::cout << "\n----------------------------------------------------------------------\n";
    std::cout << "CONCLUSION PARA ESTE GRAFO DISPERSO:\n";
    std::cout << "    La LISTA de adyacencia es mejor porque:\n";
    std::cout << "      - Usa menos memoria (" << matriz.calcularMemoria() << " vs " << lista.calcularMemoria() << " bytes)\n";
    std::cout << "      - Obtener vecinos es mas rapido (acceso directo)\n";
    std::cout << "    La MATRIZ desperdicia espacio en celdas con 0\n";
    std::cout << "\n    Nota: Si el grafo fuera DENSO (muchas aristas), la matriz seria mejor\n";
    std::cout << "----------------------------------------------------------------------\n\n";

    return 0;
}