#include "cabecera.h"

int main()
{
    system("cls");//limpiar pantalla inicial para que los colores de texto se muestren correctamente al inicio
    char menu;
    int N;

    int i, j;
    for (;;)
    {
        //Imprimir menú
        printf(TITLE "\n**MENU DE OPCIONES**\n\n" RESET);
        printf("1.- CUADRADO MAGICO\n");
        printf("2.- SELECCIONAR CANCIONES\n");

        printf(ERR "0.- SALIR\n" RESET);
        fflush(stdin);
        //Leer opcion seleccionada por teclado
        printf("\nOPCION: ");scanf("%c", &menu);//solicita al usuario una opción del menú

        switch (menu)
        {
            case '1':
                system("cls");
                printf(TITLE "INGRESE EL TAMANO DEL CUADRO (DEBE SER 3 o 4):\n" RESET);//se solicita al usuario el tamaño del cuadrado
                scanf("%d",&N);
                system("cls");
                if(N != 3 && N != 4)
                    printf(ERR "HA INGRESADO UN NUMERO INVALIDO\n" RESET);
                else{
                    printf(MSSG "ESPERE POR FAVOR... BUSCANDO...\n" RESET);
                    int solucion[N][N];//array solucion
                    bool resultado; //auxiliar
                    for(i = 0;i < N; i++)//recorre filas
                        for(j = 0;j < N; j++)//recorre columnas
                            solucion[i][j] = 0;//inicializa las posciones del array a 0
                    unsigned long int nodos = 0;
                    resultado = cuadradoMagico(N, solucion, 0, 0,&nodos);//llama a la funcion
                    system("cls");
                    if(resultado == false)//si no se encontro resultado se le informa al usuario
                        printf(ERR "NO SE ENCONTRO NINGUN CUADRADO MAGICO\n"RESET);
                }
                break;

            case '2':
                system("cls");
                int duracion = 0; //duracion acumulada y tiempo sin grabar
                int puntuacion = 0; //puntuacion acumulada
                unsigned long int nodos = 0;
                canciones disco[NUM_CAN];
                canciones total[NUM_CAN];
                int solucion[NUM_CAN]; // va seleccionando la mejor opcion
                leerFichero("canciones.txt",total);
                cancionesRec(0,solucion,disco,total,&duracion,&puntuacion, &nodos);
                mostrar_sol(disco, duracion, puntuacion, nodos);
                break;
            case '0':
                system("cls");
                return 0;
                break;
            default:
                system("cls");
                printf(ERR"\nOPCION DE MENU NO DISPONIBLE\n"RESET);
                break;

        }
    }

    return 0;
}
