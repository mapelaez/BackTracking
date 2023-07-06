#include "backtracking.h"
//FUNCION PRINCIPAL
bool cuadradoMagico(int N, int solucion[][N], int etapa_f, int etapa_c, unsigned long int *nodos){

    int valores[N*N];//posibles valores a elegir
    int nuevoValor; //valor que es posible candidato a añadirse a la solucion
    int pos = -1, nElementos;//auxiliares para seleccionar nuevoValor
    nElementos = iniciarValores(N,solucion,valores);//inicializa el array valores, y devuelve el numero de elementos que se pueden elegir
    bool exito = false;//variable de returno
    if(etapa_f >= N || etapa_c >= N)//si ya alcanzó el maximo de filas y columnas devuelve false
        return exito;

    while(exito == false && ultimoValor(valores, nElementos,pos)){//mientras no haya solucion ni se llegue al ultimo valor se ejecuta
        (*nodos)++;
        nuevoValor = seleccionarNuevoValor(valores, ++pos);//selecciona un nuevo valor a traves de la funcion

        if (alcanzable(N,solucion,nuevoValor)){//si cumple los requisitos con el nuevo Valor esta es una posible solucion
            solucion[etapa_f][etapa_c] = nuevoValor;//guarda el nuevo valor en la posicion actual
            if(esMagico(N,solucion)){//comprueba si es solucion
                imprimirSolucion(N,solucion,nodos);//si hay solucion, la imprime
                exito = true;//devuelve true porque se ha encontrado la solucion
            }else{//sino aplica recursividad
                if(etapa_c < N-1)//si aun no se recorren todas las columnas de la fila
                    exito = cuadradoMagico(N, solucion, etapa_f,etapa_c + 1,nodos);//solo se recorre la siguiente fila
                else if(etapa_f < N-1)//si ya se han recorrido todas las columnas
                    exito = cuadradoMagico(N, solucion, etapa_f + 1,0,nodos);//se avanza a la siguiente fila desde la columna 1
            }
            if(exito == false)// si no se encontro la solucion
                solucion[etapa_f][etapa_c] = 0;//la posicion se vuelve a dejar a 0
        }else
            break;//Si encuentra un nodo que no es alcanzable es decir que su suma es mayor que la constante magica
                    //ya no continua buscando en el resto de valores disponibles que quedan ya que se sabe que son mayores
                    //por lo que el resto de valores disponibles serán también inalcanzables
    }
    return exito;//devuelve true o false segun los procesos ejecutados
}

int iniciarValores(int N, int solucion[][N],int valores[]){
    int i,j,c = 0, disponibles = 0, cont;//auxiliares
    int posiciones[N*N];//Auxiliar para guardar los valores que se encuentran en el array solucion
    for(i = 0; i < N; i++){//recorre filas
        for(j = 0; j < N; j++){//recorre columnas
            if(solucion[i][j] != 0)//si la posicion es diferente de 0
                posiciones[c++] = solucion[i][j];//almacena el valor en el array auxiliar
            else
                disponibles++;//si la posicion vale 0, se suma al contador de posiciones disponibles
        }
    }
    c = 0;
    for(i = 1; i <= N*N;i++){//Recorre el total de elementos que se pueden agregar al cuadrado magico
        cont = 0;//reinicia el contador
        for(j = 0; j < (N*N) - disponibles; j++)//recorre para saber que valores ya estan dentro de la solucion
            if(i == posiciones[j]){ //si un valor ya esta dentro de la solucion se suma al contador
                cont++;
            }
        if(cont == 0)//si el contador es 0, ese valor no se encuentra dentro de la solucion actual y aun se puede escoger
            valores[c++] = i;//guarda el posible valor
    }

    return disponibles;//Retorna disponibles que es el numero de valores disponibles para elegir
}

int seleccionarNuevoValor(int *valores, int pos){
    int aux;//variable auxiliar para retornar

    aux = valores[pos];//se selecciona un nuevo valor dentro de los posibles elementos a escoger la posicion va aumentando en la funcion principal

    return aux;//Retorna el nuevo valor a utilizar
}

bool alcanzable(int N, int solucion[][N],int nuevoValor){
    if(nuevoValor <= N*N && nuevoValor != 0){//comprueba que el nuevo Valor este dentro del rango permitido
        int i, j, constante = 0;
        int sumaFila, sumaCol, sumaDiag[2] = {0,0};//auxiliares para sumar filas y columnas
        for(j = 0; j < N; j++){
            constante += solucion[0][j];//calcula la constante magica segun los valores de la primera fila
        }

        //sumar filas y columnas
        for(i = 0; i < N; i++){
            sumaFila = 0;//se inicia a 0 el contador para cada fila
            sumaCol = 0;//se inicia a 0 el contador para cada columna
            for(j = 0; j < N; j++){
                if(nuevoValor == solucion[i][j])//si el nuevo Valor ya se encuentra dentro de la solucion devuelve false
                    return false;
                sumaFila += solucion[i][j];//suma por filas
                sumaCol += solucion[j][i];//suma por columnas
            }
            if(sumaFila > constante || sumaCol > constante)//si una de las filas o columnas es mayor que la constante duevuelve false
                return false;
        }
        //sumar diagonales
        for(i = 0, j = (N - 1); i < N; i++, j--){
            sumaDiag[0] += solucion[i][i];//suma los valores de la diagonal principal
            sumaDiag[1] += solucion[i][j];//suma los valores de la diagonal secundaria
        }
        //comparar con la constante magica con las diagonales
        if(sumaDiag[0] > constante || sumaDiag[1] > constante)//si una de la diagonales es mayor de la constante se suma al contador
            return false;


        return true;//si es alcanzable la solucion devuelve true

    }else
        return false;//si el nuevo Valor esta fuera del rango devuelve false


}

bool esMagico(int N, int solucion[][N]){
    int i, j, constante = 0;
    int sumaFila, sumaCol, sumaDiag[2] = {0,0}; //arrays auxiliares para guardar la suma de columnas, filas y diagonales
    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            if(solucion[i][j]== 0) //busca si alguna posicion aun tiene un 0
                return false;//si encuentra un 0 no es una solucion
            if(i == 0)//si la fila es 0 se suma a la que seria la constante en base a la fila 1
                constante += solucion[i][j];//calcula la constante magica con los valores de la primera fila para luego comparar con el resto
        }
    }
    //sumar filas y columnas
    for(i = 0; i < N; i++){
        sumaFila = 0;//se inicia a 0 el contador para cada fila
        sumaCol = 0;//se inicia a 0 el contador para cada columna
        for(j = 0; j < N; j++){
            sumaFila += solucion[i][j];//suma por filas
            sumaCol += solucion[j][i];//suma por columnas
        }
        if(sumaFila != constante || sumaCol != constante)//si una de las filas o las columnas no tiene el valor de la constante magica no es solucion
            return false;
    }
    //sumar diagonales
    for(i = 0, j = (N - 1); i < N; i++, j--){
        sumaDiag[0] += solucion[i][i];//suma los valores de la diagonal principal
        sumaDiag[1] += solucion[i][j];//suma los valores de la diagonal secundaria
    }
    //comparar con la constante magica con las diagonales
    if(sumaDiag[0] != constante || sumaDiag[1] != constante)//si una de la diagonales es diferente de la constante se suma al contador
        return false;
    //si pasa todos los filtros anteriores, se ha encontrado una solucion al problema
    return true;
}

void imprimirSolucion(int N, int solucion[][N], unsigned long int *nodos){
    system("cls");
    int i, j, constante = 0;
    printf(SUCCESS "CUADRADO MAGICO ENCONTRADO:\n"RESET);
    printf(MSSG "NODOS RECORRIDOS:" RESET ERR " %lu\n"RESET,*nodos);//numero de nodos recorridos hasta llegar a la primera solucion encontrada
    for(i = 0; i < N; i++){//Recorre las filas
        printf("\n\t");//Imprime un salto de linea y un tab para el comienzo de cada linea
        for(j = 0; j < N; j++){//recorre las columnas
            printf(TITLE"|"RESET" %2d ",solucion[i][j]);//imprime el elemento en la posicion (i,j)
            if(i == 0) //se calcula la constante magica segun los valores de la fila 1
                constante += solucion[i][j];//se suman los valores para la constante
        }
        printf(TITLE"|\n"RESET);
    }
    printf(MSSG"\nLA CONSTANTE MAGICA ES: "RESET SUCCESS"%d\n" RESET,constante);//imprime la constante magica
    system("pause");
}

bool ultimoValor (int *valores, int n, int pos){
    if(valores == NULL || pos >= n)//si valores es NULL quiere decir que ya no hay mas valores que añadir y si la poscicion es mayor
                                    //o igual al numero de elementos que se pueden seleccionar retorna false
        return false;
    else
        return true;

}

