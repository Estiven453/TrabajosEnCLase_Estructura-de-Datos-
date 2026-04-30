#include <iostream>
#include <string>
#include <queue>
#include <list>
#include <stack>

using namespace std;

struct Solicitud {
    string cedula;
    string nombre;
    string motivo;
};

// Función principal del integrador
void atenderSolicitud(queue<Solicitud>& pendientes, list<Solicitud>& atendidos, stack<Solicitud>& recientes) {
    // Caso de prueba 1: Cola vacía
    if (pendientes.empty()) {
        cout << "\n[ERROR] No hay registros en la cola de pendientes." << endl;
        return;
    }

    Solicitud actual = pendientes.front();
    pendientes.pop();
    
    atendidos.push_back(actual); // Historial
    recientes.push(actual);     // Reciente

    cout << "\n[EXITO] Atendiendo a: " << actual.nombre << endl;
}

void mostrarHistorial(const list<Solicitud>& atendidos) {
    cout << "\n--- HISTORIAL COMPLETO (List) ---" << endl;
    if (atendidos.empty()) cout << "Vacio." << endl;
    for (const auto& s : atendidos) {
        cout << "- " << s.nombre << " (" << s.motivo << ")" << endl;
    }
}

void mostrarUltimoAtendido(stack<Solicitud>& recientes) {
    cout << "\n--- ULTIMO ATENDIDO (Stack - Top) ---" << endl;
    if (recientes.empty()) {
        cout << "No hay registros recientes." << endl;
    } else {
        cout << "Cima del Stack: " << recientes.top().nombre << endl;
    }
}

int main() {
    queue<Solicitud> pendientes;
    list<Solicitud> atendidos;
    stack<Solicitud> recientes;
    int opcion;

    do {
        cout << "\n==== SISTEMA DE ATENCION ====" << endl;
        cout << "1. Agregar Estudiante (Push a Cola)" << endl;
        cout << "2. Atender Siguiente (Pop de Cola)" << endl;
        cout << "3. Ver Historial (List)" << endl;
        cout << "4. Ver mas reciente (Stack Top)" << endl;
        cout << "5. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Solicitud s;
            cout << "Nombre: "; cin.ignore(); getline(cin, s.nombre);
            cout << "Motivo: "; getline(cin, s.motivo);
            pendientes.push(s);
            cout << "Agregado a la cola FIFO." << endl;
        } 
        else if (opcion == 2) {
            atenderSolicitud(pendientes, atendidos, recientes);
        } 
        else if (opcion == 3) {
            mostrarHistorial(atendidos);
        } 
        else if (opcion == 4) {
            mostrarUltimoAtendido(recientes);
        }

    } while (opcion != 5);

    return 0;
}
