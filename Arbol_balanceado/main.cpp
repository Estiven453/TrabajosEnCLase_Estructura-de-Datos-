#include<iostream>
#include<vector>

using namespace std;

struct Nodo{
    string nombre;
    vector<Nodo*> hijos;
};

Nodo* crearNodo(string nombre) {
    Nodo* nuevo = new Nodo();
    nuevo->nombre = nombre;
    return nuevo;
}

// Buscar nodo por nombre (recursivo)
Nodo* buscar(Nodo* nodo, string nombre) {
    if (nodo == nullptr) return nullptr;

    if (nodo->nombre == nombre)
        return nodo;

    for (Nodo* hijo : nodo->hijos) {
        Nodo* encontrado = buscar(hijo, nombre);
        if (encontrado != nullptr)
            return encontrado;
    }

    return nullptr;
}

// Mostrar árbol
void mostrar(Nodo* nodo, int nivel = 0) {
    if (nodo == nullptr) return;

    for (int i = 0; i < nivel; i++)
        cout << "  ";

    cout << "- " << nodo->nombre << endl;

    for (Nodo* hijo : nodo->hijos) {
        mostrar(hijo, nivel + 1);
    }
}

int main() {
    Nodo* empresa = crearNodo("Empresa");

    Nodo* gerenteGeneral = crearNodo("Gerente General");
    empresa->hijos.push_back(gerenteGeneral);

    Nodo* ventas = crearNodo("Gerente de Ventas");
    Nodo* operaciones = crearNodo("Gerente de Operaciones");
    Nodo* finanzas = crearNodo("Gerente de Finanzas");

    gerenteGeneral->hijos.push_back(ventas);
    gerenteGeneral->hijos.push_back(operaciones);
    gerenteGeneral->hijos.push_back(finanzas);

    ventas->hijos.push_back(crearNodo("Empleado 1"));
    ventas->hijos.push_back(crearNodo("Empleado 2"));

    operaciones->hijos.push_back(crearNodo("Empleado 3"));
    operaciones->hijos.push_back(crearNodo("Empleado 4"));

    finanzas->hijos.push_back(crearNodo("Empleado 5"));
    finanzas->hijos.push_back(crearNodo("Empleado 6"));

    int opcion;
    string nombrePadre, nombreNuevo;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Mostrar estructura\n";
        cout << "2. Agregar nodo\n";
        cout << "3. Buscar nodo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch(opcion) {
    case 1: {
        mostrar(empresa);
        break;
    }

    case 2: {
        cout << "Ingrese el nombre del nodo padre: ";
        getline(cin, nombrePadre);

        Nodo* padre = buscar(empresa, nombrePadre);

        if (padre == nullptr) {
            cout << "Nodo no encontrado.\n";
        } else {
            cout << "Ingrese el nombre del nuevo nodo: ";
            getline(cin, nombreNuevo);

            padre->hijos.push_back(crearNodo(nombreNuevo));
            cout << "Nodo agregado correctamente.\n";
        }
        break;
    }

    case 3: {
        cout << "Ingrese el nombre a buscar: ";
        getline(cin, nombrePadre);

        if (buscar(empresa, nombrePadre) != nullptr)
            cout << "Nodo encontrado.\n";
        else
            cout << "Nodo no encontrado.\n";

        break;
    }

    case 4: {
        cout << "Saliendo...\n";
        break;
    }

    default: {
        cout << "Opcion invalida.\n";
    }
}
    } while(opcion != 4);

    return 0;
}
