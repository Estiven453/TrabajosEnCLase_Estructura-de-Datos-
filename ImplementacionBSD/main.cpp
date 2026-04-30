#include <iostream>
using namespace std;

class TreeNode {
public:
    int value;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int v) {
        value = v;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    TreeNode *root;

    BST() {
        root = NULL;
    }

    void insertNode(TreeNode *new_node) {
        if (root == NULL) {
            root = new_node;
            cout << "Valor " << new_node->value << " insertado como raiz." << endl;
        } else {
            TreeNode *temp = root;
            while (temp != NULL) {
                // Caso 1: El valor ya existe
                if (new_node->value == temp->value) {
                    cout << "El valor " << new_node->value << " ya existe. Ingrese otro." << endl;
                    delete new_node; // Liberamos memoria si no se usa
                    return;
                } 
                // Caso 2: Ir a la izquierda
                else if (new_node->value < temp->value) {
                    if (temp->left == NULL) {
                        temp->left = new_node;
                        cout << "Valor " << new_node->value << " insertado a la izquierda de " << temp->value << endl;
                        break;
                    } else {
                        temp = temp->left; // Bajamos un nivel a la izquierda
                    }
                } 
                // Caso 3: Ir a la derecha
                else {
                    if (temp->right == NULL) {
                        temp->right = new_node;
                        cout << "Valor " << new_node->value << " insertado a la derecha de " << temp->value << endl;
                        break;
                    } else {
                        temp = temp->right; // Bajamos un nivel a la derecha
                    }
                }
            }
        }
    }
};

int main() {
    BST miArbol;
    int valorUsuario;
    char continuar;

    cout << "--- SISTEMA DE INSERCION DE NODOS BST ---" << endl;

    do {
        cout << "\nIngrese un numero para insertar en el arbol: ";
        cin >> valorUsuario;

        // Creamos el nodo dinámicamente con el valor ingresado
        TreeNode *nuevo = new TreeNode(valorUsuario);
        
        // Lo insertamos usando tu método
        miArbol.insertNode(nuevo);

        cout << "¿Desea ingresar otro valor? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    cout << "\nProceso terminado. ¡Revisa tu GitHub para ver los cambios!" << endl;

    return 0;
}
