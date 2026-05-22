import java.util.*; 

  

/** 

* Exposición Integrante 5 - Comparación entre Matriz y Lista de Adyacencia 

* Tema: Representación de Grafos 

*/ 

public class ComparacionGrafos { 

  

    // ========== 1. REPRESENTACIÓN CON MATRIZ DE ADYACENCIA ========== 

    static class GrafoMatriz { 

        private int[][] matriz; 

        private int numVertices; 

        private String[] nombres;  // Para dar nombres a los nodos 

  

        public GrafoMatriz(int vertices, String[] nombres) { 

            this.numVertices = vertices; 

            this.matriz = new int[vertices][vertices]; 

            this.nombres = nombres; 

        } 

  

        // Agregar arista (no dirigida) 

        public void agregarArista(int i, int j) { 

            matriz[i][j] = 1; 

            matriz[j][i] = 1; 

        } 

  

        // Verificar si dos nodos están conectados (O(1)) 

        public boolean estanConectados(int i, int j) { 

            return matriz[i][j] == 1; 

        } 

  

        // Obtener vecinos de un nodo (O(n) porque recorre toda la fila) 

        public List<Integer> obtenerVecinos(int nodo) { 

            List<Integer> vecinos = new ArrayList<>(); 

            for (int i = 0; i < numVertices; i++) { 

                if (matriz[nodo][i] == 1) { 

                    vecinos.add(i); 

                } 

            } 

            return vecinos; 

        } 

  

        // Calcular memoria aproximada en bytes (int = 4 bytes) 

        public int calcularMemoria() { 

            return numVertices * numVertices * 4; 

        } 

  

        // Mostrar matriz visualmente 

        public void mostrar() { 

            System.out.println("\nMATRIZ DE ADYACENCIA ( " + numVertices + "x" + numVertices + " ):"); 

            System.out.print("      "); 

            for (int i = 0; i < numVertices; i++) { 

                System.out.printf("%-6s", nombres[i]); 

            } 

            System.out.println(); 

            for (int i = 0; i < numVertices; i++) { 

                System.out.printf("%-6s", nombres[i]); 

                for (int j = 0; j < numVertices; j++) { 

                    System.out.printf("%-6d", matriz[i][j]); 

                } 

                System.out.println(); 

            } 

        } 

    } 

  

    // ========== 2. REPRESENTACIÓN CON LISTA DE ADYACENCIA ========== 

    static class GrafoLista { 

        private Map<Integer, List<Integer>> lista; 

        private int numVertices; 

        private String[] nombres; 

  

        public GrafoLista(int vertices, String[] nombres) { 

            this.numVertices = vertices; 

            this.lista = new HashMap<>(); 

            this.nombres = nombres; 

            for (int i = 0; i < vertices; i++) { 

                lista.put(i, new ArrayList<>()); 

            } 

        } 

  

        // Agregar arista (no dirigida) 

        public void agregarArista(int i, int j) { 

            lista.get(i).add(j); 

            lista.get(j).add(i); 

        } 

  

        // Verificar si dos nodos están conectados (O(grado)) 

        public boolean estanConectados(int i, int j) { 

            return lista.get(i).contains(j); 

        } 

  

        // Obtener vecinos de un nodo (O(1) para acceder, O(grado) para iterar) 

        public List<Integer> obtenerVecinos(int nodo) { 

            return new ArrayList<>(lista.get(nodo)); 

        } 

  

        // Calcular memoria aproximada (cada entero = 4 bytes + overhead de lista) 

        public int calcularMemoria() { 

            int total = 0; 

            for (int i = 0; i < numVertices; i++) { 

                total += 4;  // referencia en HashMap 

                total += lista.get(i).size() * 4;  // cada vecino 

            } 

            return total; 

        } 

  

        // Mostrar lista visualmente 

        public void mostrar() { 

            System.out.println("\nLISTA DE ADYACENCIA:"); 

            for (int i = 0; i < numVertices; i++) { 

                System.out.print(nombres[i] + " -> "); 

                List<Integer> vecinos = lista.get(i); 

                if (vecinos.isEmpty()) { 

                    System.out.println("[]"); 

                } else { 

                    System.out.print("["); 

                    for (int j = 0; j < vecinos.size(); j++) { 

                        System.out.print(nombres[vecinos.get(j)]); 

                        if (j < vecinos.size() - 1) System.out.print(", "); 

                    } 

                    System.out.println("]"); 

                } 

            } 

        } 

    } 

  

    // ========== 3. MAIN - EJEMPLO PRÁCTICO ========== 

    public static void main(String[] args) { 

        System.out.println("\n----------------------------------------------------------------------"); 

        System.out.println("        COMPARACION PRACTICA: MATRIZ vs LISTA DE ADYACENCIA"); 

        System.out.println("----------------------------------------------------------------------"); 

  

        // Grafo ejemplo: 6 nodos (ciudades), 5 aristas (disperso) 

        String[] nombres = {"A", "B", "C", "D", "E", "F"}; 

        int numVertices = 6; 

  

        // Crear ambas representaciones 

        GrafoMatriz matriz = new GrafoMatriz(numVertices, nombres); 

        GrafoLista lista = new GrafoLista(numVertices, nombres); 

  

        // Aristas del grafo (disperso: 5 aristas) 

        int[][] aristas = { 

            {0, 1},  // A-B 

            {0, 2},  // A-C 

            {1, 3},  // B-D 

            {2, 4},  // C-E 

            {3, 5}   // D-F 

        }; 

  

        for (int[] a : aristas) { 

            matriz.agregarArista(a[0], a[1]); 

            lista.agregarArista(a[0], a[1]); 

        } 

  

        // ===== MOSTRAR AMBAS REPRESENTACIONES ===== 

        matriz.mostrar(); 

        lista.mostrar(); 

  

        // ===== COMPARACIÓN DE MEMORIA ===== 

        System.out.println("\n----------------------------------------------------------------------"); 

        System.out.println("COMPARACION DE MEMORIA:"); 

        System.out.println("   Matriz: " + matriz.calcularMemoria() + " bytes"); 

        System.out.println("   Lista:  " + lista.calcularMemoria() + " bytes"); 

        System.out.println("   Nota: En este caso (grafo disperso), la lista usa "  

                         + (matriz.calcularMemoria() - lista.calcularMemoria()) + " bytes menos."); 

  

        // ===== OPERACIÓN: VER CONEXIÓN DIRECTA ===== 

        System.out.println("\n----------------------------------------------------------------------"); 

        System.out.println("OPERACION 1: ¿A y B estan conectados?"); 

        System.out.println("   Matriz: consulta O(1) -> " + matriz.estanConectados(0, 1)); 

        System.out.println("   Lista:  consulta O(grado) -> " + lista.estanConectados(0, 1)); 

  

        // ===== OPERACIÓN: VER VECINOS ===== 

        System.out.println("\n----------------------------------------------------------------------"); 

        int nodoConsultado = 0; 

        System.out.println("OPERACION 2: Obtener vecinos de " + nombres[nodoConsultado]); 

        System.out.println("   Matriz: recorre toda la fila (O(n)) -> " + vecinosComoString(matriz.obtenerVecinos(nodoConsultado), nombres)); 

        System.out.println("   Lista:  accede directamente a su lista (O(grado)) -> " + vecinosComoString(lista.obtenerVecinos(nodoConsultado), nombres)); 

  

        // ===== GRÁFICO DEL GRAFO EN CONSOLA ===== 

        System.out.println("\n----------------------------------------------------------------------"); 

        System.out.println("REPRESENTACION VISUAL DEL GRAFO:"); 

        System.out.println("        A"); 

        System.out.println("       / \\"); 

        System.out.println("      B   C"); 

        System.out.println("      |   |"); 

        System.out.println("      D   E"); 

        System.out.println("      |"); 

        System.out.println("      F"); 

        System.out.println("\n   Aristas: A-B, A-C, B-D, C-E, D-F"); 

  

        // ===== CONCLUSIÓN ===== 

        System.out.println("\n----------------------------------------------------------------------"); 

        System.out.println("CONCLUSION PARA ESTE GRAFO DISPERSO:"); 

        System.out.println("    La LISTA de adyacencia es mejor porque:"); 

        System.out.println("      - Usa menos memoria (" + matriz.calcularMemoria() + " vs " + lista.calcularMemoria() + " bytes)"); 

        System.out.println("      - Obtener vecinos es mas rapido (acceso directo)"); 

        System.out.println("    La MATRIZ desperdicia espacio en celdas con 0"); 

        System.out.println("\n    Nota: Si el grafo fuera DENSO (muchas aristas), la matriz seria mejor"); 

        System.out.println("----------------------------------------------------------------------\n"); 

    } 

  

    // Helper para mostrar nombres de vecinos 

    private static String vecinosComoString(List<Integer> vecinos, String[] nombres) { 

        if (vecinos.isEmpty()) return "[]"; 

        StringBuilder sb = new StringBuilder("["); 

        for (int i = 0; i < vecinos.size(); i++) { 

            sb.append(nombres[vecinos.get(i)]); 

            if (i < vecinos.size() - 1) sb.append(", "); 

        } 

        sb.append("]"); 

        return sb.toString(); 

    } 

} 