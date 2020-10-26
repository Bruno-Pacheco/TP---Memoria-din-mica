/**Ejercicio 39: Hacer un programa que tome los datos de medición de potencia,
cargados por el usuario, de un sistema de medición a distancia. Los datos que
cargará el usuario tienen la siguiente estructura:

    char desc[60];
    unsigned char potencia;
    unsigned int estado;

Donde estado es la multiplicación del valor ASCII de la primer letra de la
descripción por la potencia. Los datos cargados se deberán guardar en una lista
ordenada, de mayor a menor, del valor de potencia. Una vez finalizada la carga
guardar los datos en un archivo de organización directa llamado "potencia.dat"
imprimiendo en pantalla los datos.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct d{
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};

struct e{
    int id;
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};

struct lista{
    struct d datos;
    struct lista * lazo;
};

int main()
{
    FILE *fp;
    struct lista *p, *u, *aux, *r;
    struct e bf;
    bf.id=0;
    p=u=NULL;
    char continuar, flag=0;
    fflush(stdin);

    printf("*** Medici%cn de potencia ***\n",162);
    ///Ingreso de datos, ordeno y armo lista
    do{
        aux=(struct lista*)malloc(sizeof(struct lista));
        printf("\nIngrese una descripci%cn:  ",162);
        gets(aux->datos.desc);
        fflush(stdin);
        printf("\nIngrese valor de potencia:    ");
        scanf("%d", &aux->datos.potencia);
        fflush(stdin);
        aux->datos.estado=aux->datos.potencia*aux->datos.desc[0];
        r=p;
        if(p){      //si ya hay al menos 1 elemento en la lista...
            if(aux->datos.potencia>p->datos.potencia){  //Si es el mayor, va primero
                aux->lazo=p;
                p=aux;
                flag=1;     //que no siga buscando
            }

            while(r->lazo && flag == 0){    //si estoy en el ultimo elemento salgo porque ya recorri toda la lista
                if(aux->datos.potencia<r->lazo->datos.potencia)r=r->lazo;   //si es menor que el elemento siguiente, muevo el puntero r
                else{       //si es mayor que el elemnto siguien, lo engancho
                    aux->lazo=r->lazo;
                    r->lazo=aux;
                    flag=1;     //que no siga buscando
                }
            }
            if(r==u && flag==0){    //llegue al utlimo lugar y no encontre la posicion... va ultimo
                u->lazo=aux;
                u=aux;
                u->lazo=NULL;
                flag=1;
            }
            flag=0;
        }
        if(!p){     //Si p apunta a NULL, es el primer elemento
            p=u=aux;
            u->lazo=NULL;
        }
        printf("\nContinuar ingresando datos?\t(0)NO\t(1)SI\t");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);

    /// Carga de datos en "potencia.dat" y muestro en pantalla

    if((fp=fopen("potencia.dat","ab"))==NULL){
        printf("\nError: No se cre%c el archivo potencia.dat",162);
        return 0;
    }
    while(p){
        //Desarmo la lista y libero la memoria
        aux=p;
        p=p->lazo;
        //Imprimo en pantalla
        printf("\n-------------------------------------");
        printf("\nDescripci%cn: %s",162,aux->datos.desc);
        printf("\nPotencia: %d Watts",aux->datos.potencia);
        printf("\nEstado: %d",aux->datos.estado);
        //Cargo en archivo
        bf.id=bf.id++;
        strcpy(bf.desc,aux->datos.desc);
        bf.estado=aux->datos.estado;
        bf.potencia=aux->datos.potencia;
        fwrite(&bf,sizeof(struct e),1,fp);
        free(aux);
    }
    getch();


    return 0;
}
