#include "backtracking.h"
//FUNCION PRINCIPAL
bool cuadradoMagico(int N, int solucion[][N], int etapa_f, int etapa_c, unsigned long int *nodos){

    int valores[N*N];//posibles valores a elegir
    int nuevoValor; //valor que es posible candidato a añadirse a la solucion
    int pos = -1, nElementos;//auxiliares para seleccionar nuevoValor
    nElementos = iniciarValores(N,solucion,valores);//inicializa el array valores, y devuelve el numero de elementos que se pueden elegir
    bool exito = false;//variable de returno
    if(etapa_f >= N || etapa_c >= N)
        return exito;

    while(exito == false && ultimoValor(valores, nElementos,pos)){
        (*nodos)++;
        nuevoValor = seleccionarNuevoValor(valores, ++pos);

        if (alcanzable(N,solucion,nuevoValor)){
            solucion[etapa_f][etapa_c] = nuevoValor;
            if(esMagico(N,solucion)){
                imprimirSolucion(N,solucion,nodos);
                exito = true;n
            }else{
                if(etapa_c < N-1)
                    exito = cuadradoMagico(N, solucion, etapa_f,etapa_c + 1,nodos);
                else if(etapa_f < N-1)
                    exito = cuadradoMagico(N, solucion, etapa_f + 1,0,nodos);
            }
            if(exito == false)
                solucion[etapa_f][etapa_c] = 0;
        }else
            break;
                    
                   
    }
    return exito;
}

int iniciarValores(int N, int solucion[][N],int valores[]){
    int i,j,c = 0, disponibles = 0, cont;//auxiliares
    int posiciones[N*N];
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(solucion[i][j] != 0)
                posiciones[c++] = solucion[i][j];
            else
                disponibles++;//si la posicion vale 0, se suma al contador de posiciones disponibles
        }
    }
    c = 0;
    for(i = 1; i <= N*N;i++){
        cont = 0;//reinicia el contador
        for(j = 0; j < (N*N) - disponibles; j++)
            if(i == posiciones[j]){ 
                cont++;
            }
        if(cont == 0)
            valores[c++] = i;
    }

    return disponibles;
}

int seleccionarNuevoValor(int *valores, int pos){
    int aux;

    aux = valores[pos];

    return aux;
}

bool alcanzable(int N, int solucion[][N],int nuevoValor){
    if(nuevoValor <= N*N && nuevoValor != 0){
        int i, j, constante = 0;
        int sumaFila, sumaCol, sumaDiag[2] = {0,0};
        for(j = 0; j < N; j++){
            constante += solucion[0][j];
        }

        //sumar filas y columnas
        for(i = 0; i < N; i++){
            sumaFila = 0;
            sumaCol = 0;
            for(j = 0; j < N; j++){
                if(nuevoValor == solucion[i][j])e
                    return false;
                sumaFila += solucion[i][j];
                sumaCol += solucion[j][i];
            }
            if(sumaFila > constante || sumaCol > constante)
                return false;
        }
        //sumar diagonales
        for(i = 0, j = (N - 1); i < N; i++, j--){
            sumaDiag[0] += solucion[i][i];
            sumaDiag[1] += solucion[i][j];
        }
        //comparar con la constante magica con las diagonales
        if(sumaDiag[0] > constante || sumaDiag[1] > constante)
            return false;


        return true;//si es alcanzable la solucion devuelve true

    }else
        return false;//si el nuevo Valor esta fuera del rango devuelve false


}

bool esMagico(int N, int solucion[][N]){
    int i, j, constante = 0;
    int sumaFila, sumaCol, sumaDiag[2] = {0,0}; 
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(solucion[i][j]== 0) 
                return false;
            if(i == 0)
                constante += solucion[i][j];
        }
    }
  
    for(i = 0; i < N; i++){
        sumaFila = 0;
        sumaCol = 0;
        for(j = 0; j < N; j++){
            sumaFila += solucion[i][j];
            sumaCol += solucion[j][i];
        }
        if(sumaFila != constante || sumaCol != constante)
            return false;
    }

    for(i = 0, j = (N - 1); i < N; i++, j--){
        sumaDiag[0] += solucion[i][i];
        sumaDiag[1] += solucion[i][j];
    }

    if(sumaDiag[0] != constante || sumaDiag[1] != constante)
        return false;
    
    return true;
}

void imprimirSolucion(int N, int solucion[][N], unsigned long int *nodos){
    system("cls");
    int i, j, constante = 0;
    printf(SUCCESS "CUADRADO MAGICO ENCONTRADO:\n"RESET);
    printf(MSSG "NODOS RECORRIDOS:" RESET ERR " %lu\n"RESET,*nodos);
    for(i = 0; i < N; i++){//Recorre las filas
        printf("\n\t");
        for(j = 0; j < N; j++){//recorre las columnas
            printf(TITLE"|"RESET" %2d ",solucion[i][j]);
            if(i == 0) //se calcula la constante magica segun los valores de la fila 1
                constante += solucion[i][j];
        }
        printf(TITLE"|\n"RESET);
    }
    printf(MSSG"\nLA CONSTANTE MAGICA ES: "RESET SUCCESS"%d\n" RESET,constante);
    system("pause");
}

bool ultimoValor (int *valores, int n, int pos){
    if(valores == NULL || pos >= n)
        return false;
    else
        return true;

}

