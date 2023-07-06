
#ifndef BACKTRACKING_H
    #define BRACKTRACKING_H
    #include <stdbool.h>
    #include "cabecera.h"
    bool cuadradoMagico(int N, int solucion[][N], int etapa_l, int etapa_c,unsigned long int *nodos);
    void imprimirSolucion(int N,int solucion[][N],unsigned long int *nodos);
    bool esMagico(int N, int solucion[][N]);
    bool alcanzable(int N, int solucion[][N],int nuevoValor);
    int iniciarValores(int N, int solucion[][N],int valores[]);
    int seleccionarNuevoValor(int *valores, int pos);
    bool ultimoValor (int *valores, int n, int pos);


    void cancionesRec(int etapa,int solucion[],canciones disco[],canciones total[],int *duracion,int *puntuacion, unsigned long int *numero_nodos);
    int valido(int solucion[], int etapa, canciones disco[]);
    void actualizarSolucion(int solucion[], canciones disco[], canciones total[],int *duracion_final, int *puntuacion_final);
    void mostrar_sol(canciones *disco, int duracion, int puntuacion, unsigned long int numero_nodos);
#endif
