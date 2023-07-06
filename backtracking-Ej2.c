#include "backtracking.h"
void cancionesRec(int etapa,int solucion[],canciones disco[],canciones total[],int *duracion,int *puntuacion, unsigned long int *numero_nodos){
    int i = 0;
    if (etapa > NUM_CAN - 1) return;
    do{
        solucion[etapa] = i;
        (*numero_nodos)++;
        if(valido(solucion,etapa,total) == 1){ // si es válido entra en el if
            if(etapa == NUM_CAN - 1){
                actualizarSolucion(solucion,disco,total,duracion,puntuacion);
            }
            else
                cancionesRec(etapa+1,solucion,disco,total,duracion,puntuacion,numero_nodos);
           }
        i++;
    } while(solucion[etapa] != 1);
    solucion[etapa] = -1;
}

int valido(int solucion[], int etapa, canciones total[]){
      int i, num = 0; //num = numero de canciones en el disco
      int duracion_total = 0, tiempo_sin = 0; //tiempo_sin = tiempo sin grabar
      for(i = 0;i <= etapa;i++){
        if(solucion[i]==1){ // si ha sido cogido
              num++;
              duracion_total += total[i].duracion;
        }
      }


      if((num == 12) && (duracion_total < 2400)){  // si hay 12 canciones y la duracion es menor que 40 minutos
        tiempo_sin = 2400 - duracion_total; // se calcula el tiempo que se esta sin grabar
        if((tiempo_sin > 120)){ // si supera los 2 minutos
            return 0;
        }
      }
      if((duracion_total > 2400) || (num > 12) ){ // si la duracion supera los 40 minutos y el numero de canciones
         return 0;
      }
      else
         return 1;
}

void actualizarSolucion(int solucion[], canciones disco[], canciones total[],int *duracion_final, int *puntuacion_final){
    int duracion = 0, num = 0;
    int puntuacion = 0, i;
    for(i =0;i< NUM_CAN;i++){
        if(solucion[i]==1){ // si ha sido cogida
            num++;
            duracion += total[i].duracion;
            puntuacion += total[i].puntuacion;
        }
    }
    if((puntuacion > *puntuacion_final) && (num == 12)){ // si esta puntuación es mejor que la anterior y si son justo 12 canciones
        int i;
        for(i = 0; i < NUM_CAN; i++){
            disco[i].activo = 0; // lo igualo a 0 para que no se tome en cuenta los anteriores
        }
        for(i = 0; i < NUM_CAN; i++){
            if((solucion[i] == 1)){ // si ha sido cogida
                strcpy(disco[i].nombre,total[i].nombre);
                disco[i].duracion = total[i].duracion;
                disco[i].puntuacion = total[i].puntuacion;
                disco[i].activo = 1; // Lo igualo a 1 para que al imprimirlo se sepa que ha sido el seleccionado
                }
            }
        *duracion_final = duracion;
        *puntuacion_final = puntuacion;
    }
}

void mostrar_sol(canciones *disco, int duracion, int puntuacion, unsigned long int numero_nodos){
    int i, j=0;
    printf(SUCCESS"LISTADO DE CANCIONES DEL CD\n"RESET);
    for(i = 0; i < NUM_CAN; i++){
        if(disco[i].activo == 1){ //si es activo
            printf(TITLE"\nCANCION %d"RESET,++j);
            printf(MSSG "\nNombre: "RESET SUCCESS"%s"RESET,disco[i].nombre);
            printf(MSSG "\nDuracion: "RESET SUCCESS"%d:%.2d min"RESET, disco[i].duracion/60,disco[i].duracion%60 );
            printf(MSSG "\nPuntuacion: "RESET SUCCESS"%d\n"RESET,disco[i].puntuacion);
        }
    }
    printf(MSSG "\n\nDuracion Total: "RESET SUCCESS"%d:%.2d min"RESET, duracion/60,duracion%60 );
    printf(MSSG "\nPuntuacion: "RESET SUCCESS"%d"RESET,puntuacion);
    printf(MSSG "\nNODOS RECORRIDOS: "RESET ERR"%lu\n"RESET, numero_nodos);
    system("pause");
    system("cls");
}

