#include <iostream>
#include <queue>

using namespace std;

// 1. Definición del Nodo
struct Node {
    int value;
    Node *left, *right;

    Node(int item) {
        value = item;
        left = right = nullptr;
    }
};

// 2. Función BFS (Recorrido por niveles) usando std::queue
void printBFS(Node* root) {
    if (root == nullptr) return;

    // Creamos la cola de punteros a Nodos
    queue<Node*> q;

    // Agregamos la raíz a la cola
    q.push(root);

    cout << "Recorrido BFS: ";

    while (!q.empty()) {
        // Extraemos el frente de la cola
        Node* currentNode = q.front();
        cout << currentNode->value << " ";
        q.pop();

        // Si tiene hijo izquierdo, lo encolamos
        if (currentNode->left != nullptr) {
            q.push(currentNode->left);
        }

        // Si tiene hijo derecho, lo encolamos
        if (currentNode->right != nullptr) {
            q.push(currentNode->right);
        }
    }
    cout << endl;
}

int main() {
    /* Construcción del árbol de la imagen image_e46b03.png:
                 50
               /    \
              30     70
             /  \   /  \
            20  40 60  80
    */
    Node* root = new Node(50);
    root->left = new Node(30);
    root->right = new Node(70);
    
    root->left->left = new Node(20);
    root->left->right = new Node(40);
    
    root->right->left = new Node(60);
    root->right->right = new Node(80);

    // Ejecución del ejercicio
    printBFS(root);

    return 0;
}
