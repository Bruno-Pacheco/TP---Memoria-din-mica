/** Ejercicio 41: El depósito de la empresa CosmeFulanito necesita cargar
su stock de repuestos en forma ordenada. Para dicha tarea se solicitó
categorizar a los respuestos bajo la siguiente estructura de datos:

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

Los repuestos no están ordenados, se solicita cargarlos en una lista, la cual
ordene por descripción a los repuestos para luego guardarlos en un archivo de
stock con organización secuencial.
Imprimir en pantalla la lista con cada inserción.
El archivo se generará cuando el usuario decide no cargar mas productos.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

struct lista{
    repuestos_t datos;
    struct lista *lazo;
};


int main()
{
    struct lista *p, *u, *aux, *r;
    p=u=NULL;
    char continuar, flag=0;
    FILE *fp;

    do{
        system("cls");
        ///Levanto los datos del repuesto y los guardo en un espacio en memoria dinamica
        aux=(struct lista*)malloc(sizeof(struct lista));
        printf("\nPartNumber: ");
        scanf("%ld",&aux->datos.partNumber);
        fflush(stdin);
        printf("\nSerialNumber: ");
        scanf("%ld",&aux->datos.serialNumber);
        fflush(stdin);
        printf("\nDescripci%cn: ",162);
        gets(aux->datos.descripcion);
        fflush(stdin);
        printf("\nUbicaci%cn: ",162);
        gets(aux->datos.ubicacion);
        fflush(stdin);

        ///Ordeno la lista
        r=p;
        if(!p){ //si es el primero...
            p=u=aux;
            u->lazo=NULL;
        }
        else{
            if((strcmp(aux->datos.descripcion,p->datos.descripcion))<0){    //va primero alfabeticamente
                aux->lazo=p;
                p=aux;
            }
            else{       //si no va primero.... me fijo si va ultimo
                if((strcmp(u->datos.descripcion,aux->datos.descripcion))<0){      //el contacto va ulitmo...
                    u->lazo=aux;
                    u=aux;
                    u->lazo=NULL;
                }else flag=1;       //NO VA PRIMERO, NI ULTIMO --> VA EN EL MEDIO
            }
            while(flag==1){        //indica que va en alguna posicion del medio
                if((strcmp(aux->datos.descripcion,r->lazo->datos.descripcion))<0){
                    aux->lazo=r->lazo;
                    r->lazo=aux;
                    flag=0;
                }else r=r->lazo;
            }
        }

        ///Muestro la lista parcial
        r=p;
        while(r){
            //Recorro la lista, no la desarmo
            //Imprimo
            printf("\n---------------------------------------");
            printf("\nDescripci%cn: %s",162,r->datos.descripcion);
            printf("\nPartNumber: %ld",r->datos.partNumber);
            printf("\nSerialNumber: %ld",r->datos.serialNumber);
            printf("\nUbicaci%cn: %s",162,r->datos.ubicacion);
            r=r->lazo;
        }

        ///
        printf("\n\nContinuar cargando stock?\t(0)NO\t(1)SI\t");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);

    ///ya terminó de cargar stock, asi que cargo los repuestos en el archivo, y libero la memoria

    if(!(fp=fopen("stock_cosmefulanito.dat","ab"))){
        printf("\nError: No se pud%c crear el archivo",162);
        return 0;
    }

    while(p){
        aux=p;
        p=aux->lazo;

        fwrite(&aux->datos,sizeof(repuestos_t),1,fp);

        free(aux);
    }
    fclose(fp);

    return 0;
}
