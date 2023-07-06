#include "cabecera.h"

void leerFichero(char *nombre_fichero,canciones total[]){
    int i = 0;
    char linea[500]; // Para guardar la linea de cada fichero
    char *token;     // Para cada token de cada linea
    int auxmin[NUM_CAN], auxseg[NUM_CAN]; //para poder guardar los minutos y segundos en un auxiliar
    //Abrimos el fichero
    FILE *fp = fopen(nombre_fichero,"r");

    // Comprobar que no hay error al abrir
    if(fp == NULL){
        printf(ERR "Error de lectura del archivo"RESET);
    }else{
        // Recorremos cada linea del fichero
        while(fgets(linea,500,fp)!=NULL){

            token = strtok(linea,";");
            strcpy(total[i].nombre, token);

            token = strtok(NULL,";");
            auxmin[i] = atoi(token);

            token = strtok(NULL,";");
            auxseg[i] = atoi(token);

            token = strtok(NULL,";");
            total[i].puntuacion = atoi(token);

            total[i].duracion = (auxmin[i] * 60) + auxseg[i];//auxmin guarda los minutos convertidos en segundo + auxseg que guarda los segundos
            i++;

        }
    }


    fclose(fp);
}


