import java.util.*;

public class ComparacionesGrafos {
    static class GrafoMatriz {
        private int[][] matriz;
        private int numVertices;
        private String[] nombres;

        public GrafoMatriz(int vertices, String[] nombre){
            this.numVertices = vertices;
            this.nombres = nombre;
            this.matriz = new int[vertices][vertices];

        }
        //Agregar artista no dirigida
        public void agregarArista(int i, int j){
            matriz[i][j] = 1;
            matriz[j][i] = 1;
        }

        public boolean estanConectados(int i, int j){
            return matriz[i][j] == 1;
        }

        public List<Integer> obtenerVecinos (int nodo){
            List<Integer> vecinos = new ArrayList<>();
            for (int j = 0; j < numVertices; j++){
                if (matriz[nodo][j] == 1){
                    vecinos.add(j);
                }
            }
            return vecinos;
            }
        
            public int calcularMemoria() {
                return numVertices * numVertices * 4;
            }

            //Mostrar matriz visualmente
            public void mostrar(){
                System.out.println("\nMatriz");
            }
        
        }
    }