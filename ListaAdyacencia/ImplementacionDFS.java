import java.util.Scanner;
import java.util.TreeMap;
import java.util.ArrayList;
import java.util.List;
import java.util.Stack;
import java.util.HashSet;
import java.util.Collections;
import java.util.Map;

// Estructura para representar el Grafo
class GrafoDFS {
    // Lista de adyacencia usando un TreeMap para mantener los nodos ordenados alfabéticamente
    private TreeMap<Character, List<Character>> listaAdyacencia;

    // Constructor que inicializa el grafo exactamente como la imagen
    public GrafoDFS() {
        listaAdyacencia = new TreeMap<>();
        
        listaAdyacencia.put('A', new ArrayList<>(List.of('B', 'C')));
        listaAdyacencia.put('B', new ArrayList<>(List.of('A', 'D', 'E')));
        listaAdyacencia.put('C', new ArrayList<>(List.of('A', 'F')));
        listaAdyacencia.put('D', new ArrayList<>(List.of('B')));
        listaAdyacencia.put('E', new ArrayList<>(List.of('B', 'F')));
        listaAdyacencia.put('F', new ArrayList<>(List.of('C', 'E')));
    }

    // [1] Ver todos los nodos
    public void verTodosLosNodos() {
        System.out.println("\n--- NODOS DEL GRAFO ---");
        for (Character nodo : listaAdyacencia.keySet()) {
            System.out.print("[ " + nodo + " ] ");
        }
        System.out.println();
    }

    // [2] Lista de adyacencia (nodos y vecinos)
    public void mostrarListaAdyacencia() {
        System.out.println("\n--- LISTA DE ADYACENCIA ---");
        for (Map.Entry<Character, List<Character>> entrada : listaAdyacencia.entrySet()) {
            System.out.print(entrada.getKey() + " -> [");
            List<Character> vecinos = entrada.getValue();
            for (int i = 0; i < vecinos.size(); i++) {
                System.out.print(vecinos.get(i));
                if (i < vecinos.size() - 1) {
                    System.out.print(", ");
                }
            }
            System.out.println("]");
        }
    }

    // [3] Recorrido DFS desde A (Usando Stack explícito)
    public void recorridoDFS(char nodoInicio) {
        System.out.println("\n--- RECORRIDO DFS DESDE " + nodoInicio + " ---");

        Stack<Character> pila = new Stack<>();
        HashSet<Character> visitados = new HashSet<>();
        List<Character> ordenVisita = new ArrayList<>();

        // Añadir el nodo inicial a la pila
        pila.push(nodoInicio);

        while (!pila.isEmpty()) {
            char nodoActual = pila.pop();

            // Si el nodo ya fue procesado, lo ignoramos
            if (visitados.contains(nodoActual)) {
                continue;
            }

            // Marcar como visitado
            visitados.add(nodoActual);
            ordenVisita.add(nodoActual);

            // Obtener los vecinos del nodo actual
            // Creamos una copia para no alterar la lista original al ordenar al revés
            List<Character> vecinos = new ArrayList<>(listaAdyacencia.get(nodoActual));

            // Para que el DFS elija el orden alfabético al sacar de la pila (LIFO),
            // debemos meter los vecinos a la pila en orden inverso (de la Z a la A).
            Collections.sort(vecinos, Collections.reverseOrder());

            for (char vecino : vecinos) {
                if (!visitados.contains(vecino)) {
                    pila.push(vecino);
                }
            }
        }

        // Mostrar el resultado final del recorrido
        System.out.print("Orden de visita: ");
        for (int i = 0; i < ordenVisita.size(); i++) {
            System.out.print(ordenVisita.get(i));
            if (i < ordenVisita.size() - 1) {
                System.out.print(" -> ");
            }
        }
        System.out.println();
    }
}

public class ImplementacionDFS {
    public static void main(String[] args) {
        GrafoDFS grafo = new GrafoDFS();
        Scanner teclado = new Scanner(System.in);
        int opcion;

        do {
            System.out.println("\n========== MENU DFS GRAFOS ==========");
            System.out.println("[1] Ver todos los nodos");
            System.out.println("[2] Lista de adyacencia (nodos y vecinos)");
            System.out.println("[3] Recorrido DFS desde A");
            System.out.println("[4] Salir del programa");
            System.out.print("Seleccione una opcion: ");
            
            // Validación simple de entrada entera
            while (!teclado.hasNextInt()) {
                System.out.print("[!] Por favor ingrese un numero valido: ");
                teclado.next();
            }
            opcion = teclado.nextInt();

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
                    System.out.println("\nSaliendo del programa...");
                    break;
                default:
                    System.out.println("\n[!] Opcion invalida. Intente de nuevo.");
            }
        } while (opcion != 4);

        teclado.close();
    }
}