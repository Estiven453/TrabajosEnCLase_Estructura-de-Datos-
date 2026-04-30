#include <iostream>
#include <stack>
#include <string>
#include <sstream> 
#include <cctype>
#include <cstdlib>  // <--- ESTA ES LA QUE TE FALTA
using namespace std;

struct Nodo {
    string valor; // Cambiado de char a string
    Nodo *izq, *der;

    Nodo(string v) : valor(v), izq(NULL), der(NULL) {}
};

bool esOperador(string s) {
    return (s == "+" || s == "-" || s == "*" || s == "/");
}

// CONSTRUCCIÓN DEL ÁRBOL PARA NÚMEROS MULTIDÍGITO
Nodo* construirArbol(string expr) {
    stack<Nodo*> pila;
    stringstream ss(expr);
    string token;

    // ss >> token extrae palabras separadas por espacios
    while (ss >> token) {
        if (isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            pila.push(new Nodo(token));
        } 
        else if (esOperador(token)) {
            if (pila.size() < 2) return NULL;

            Nodo* nuevo = new Nodo(token);
            nuevo->der = pila.top(); pila.pop();
            nuevo->izq = pila.top(); pila.pop();
            pila.push(nuevo);
        }
    }
    return (pila.empty()) ? NULL : pila.top();
}

// EVALUACIÓN CON DOUBLE (Para mayor precisión)
double evaluar(Nodo* raiz) {
    if (!raiz) return 0;

    if (!esOperador(raiz->valor)) {
        return atof(raiz->valor.c_str()); // Convierte string a numero
    }

    double izq = evaluar(raiz->izq);
    double der = evaluar(raiz->der);

    if (raiz->valor == "+") return izq + der;
    if (raiz->valor == "-") return izq - der;
    if (raiz->valor == "*") return izq * der;
    if (raiz->valor == "/") return (der != 0) ? izq / der : 0;

    return 0;
}

void mostrarInorden(Nodo* raiz) {
    if (raiz) {
        if (esOperador(raiz->valor)) cout << "(";
        mostrarInorden(raiz->izq);
        cout << " " << raiz->valor << " ";
        mostrarInorden(raiz->der);
        if (esOperador(raiz->valor)) cout << ")";
    }
}

int main() {
    Nodo* raiz = NULL;
    string expresion;
    int opcion;

    do {
        cout << "\n--- EVALUADOR PROFESIONAL (Multidigito) ---\n";
        cout << "1. Ingresar expresion POSTFIJA (Separar con espacios: 10 5 + 2 *)\n";
        cout << "2. Ver expresion (Inorden)\n";
        cout << "3. Evaluar resultado\n";
        cout << "4. Salir\n";
        cout << "Seleccione: ";
        cin >> opcion;
        cin.ignore(); // Limpiar el buffer

        switch (opcion) {
            case 1:
                cout << "Ejemplo: 100 20 - 2 / (esto es (100-20)/2)\n";
                cout << "Ingrese: ";
                getline(cin, expresion); // Leer toda la linea con espacios
                raiz = construirArbol(expresion);
                if (raiz) cout << ">> Arbol construido.\n";
                else cout << ">> Error: Revisa los espacios y operadores.\n";
                break;
            case 2:
                if (raiz) { mostrarInorden(raiz); cout << endl; }
                break;
            case 3:
                if (raiz) cout << "Resultado: " << evaluar(raiz) << endl;
                break;
        }
    } while (opcion != 4);

    return 0;
}
