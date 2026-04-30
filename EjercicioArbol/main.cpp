#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Estructura básica del Nodo para un árbol general
struct Nodo {
    string nombre;
    vector<Nodo*> hijos; // Lista de punteros para n-hijos

    Nodo(string dato) {
        nombre = dato;
    }
};

// Función para imprimir el árbol con formato visual
void imprimirArbol(Nodo* raiz, int nivel = 0) {
    if (raiz == nullptr) return;

    // Tabulación para representar los niveles
    for (int i = 0; i < nivel; i++) {
        cout << "    ";
    }
    
    // Mostramos el nombre del nodo
    cout << "|-- " << raiz->nombre << endl;

    // Recorremos los hijos recursivamente
    for (Nodo* hijo : raiz->hijos) {
        imprimirArbol(hijo, nivel + 1);
    }
}

int main() {
    // --- NIVEL 0: RAIZ ---
    Nodo* empresa = new Nodo("EMPRESA");

    // --- NIVEL 1 ---
    Nodo* gerenteGral = new Nodo("GERENTE GENERAL");
    empresa->hijos.push_back(gerenteGral);

    // --- NIVEL 2: GERENCIAS ---
    Nodo* gVentas = new Nodo("GERENTE DE VENTAS");
    Nodo* gOperaciones = new Nodo("GERENTE DE OPERACIONES");
    Nodo* gFinanzas = new Nodo("GERENTE DE FINANZAS");

    gerenteGral->hijos.push_back(gVentas);
    gerenteGral->hijos.push_back(gOperaciones);
    gerenteGral->hijos.push_back(gFinanzas);

    // --- NIVEL 3: EMPLEADOS (HOJAS) ---
    // Hijos de Ventas
    gVentas->hijos.push_back(new Nodo("EMP 1"));
    gVentas->hijos.push_back(new Nodo("EMP 2"));

    // Hijos de Operaciones
    gOperaciones->hijos.push_back(new Nodo("EMP 3"));
    gOperaciones->hijos.push_back(new Nodo("EMP 4"));

    // Hijos de Finanzas
    gFinanzas->hijos.push_back(new Nodo("EMP 5"));
    gFinanzas->hijos.push_back(new Nodo("EMP 6"));

    // Visualización
    cout << "ESTRUCTURA DEL ARBOL - EMPRESA" << endl;
    cout << "-------------------------------" << endl;
    imprimirArbol(empresa);

    return 0;
}
