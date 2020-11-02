/** Ejercicio 42: El proveedor de repuestos de CosmeFulanito informó que
una partida de repuestos salió con falla y debe ser devuelta. Para
identificar la partida, el proveedor indicó que la falla fue en el partNumber:
1234 que tiene números de serie con el bit 3 y 5 en 1.

Para estas tareas se solicita:

Hacer una cola con todos los registros fallados
Realizar la baja física a todos los repuestos fallados
Crear un archivo donde se vuelque el contenido de la cola en orden inverso.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

struct cola{
    repuestos_t datos;
    struct cola *der, *izq;
};


int main()
{
    FILE *fp, *fpnuevo;
    repuestos_t bf;
    struct cola *aux, *p, *u;
    p=u=NULL;
    char i;

    if(!(fp=fopen("stock_cosmefulanito.dat","rb"))){
        printf("\nError: No se pud%c abrir el archivo \"stock_cosmefulanto.dat\"",162);
        getch();
        return 0;
    }

    if(!(fpnuevo=fopen("nuevo.dat","wb"))){
        printf("\nError: No se pud%c crear archivo nuevo",162);
        getch();
        return 0;
    }

    fread(&bf,sizeof(repuestos_t),1,fp);

    while(!feof(fp)){
        aux=(struct cola*)malloc(sizeof(struct cola));
        aux->datos=bf;

        bf.serialNumber=bf.serialNumber&0b101000;

        getch();
        if(bf.partNumber==1234 && bf.serialNumber==0b101000){    ///registro fallado
            if(!p) p=u=aux;     ///si es el primero
            else{               ///si ya hay elementos, lo ubicamos a la derecha
                u->der=aux;
                aux->izq=u;
                u=aux;
            }
        }
        else   ///si no esta fallado, lo paso a un nuevo archivo, que luego renombraré
            fwrite(&bf,sizeof(repuestos_t),1,fpnuevo);

        fread(&bf,sizeof(repuestos_t),1,fp);




    }
    fclose(fp);
    fclose(fpnuevo);

    if(remove("stock_cosmefulanito.dat")){
        printf("\nError: No se pud%c eliminar registros fallados",162);
        getch();
        return 0;
    }


    if(rename("nuevo.dat","stock_cosmefulanito.dat")){
        printf("\nError: No se pud%c renombrar el archivo",162);
        getch();
        return 0;
    }

    ///Imprimo y cargo en un archivo la cola en orden inverso

    if(!(fp=fopen("historico.dat","ab"))){
        printf("\nError: No se pud%c abrir/crear el archivo \"historico.dat\"",162);
        getch();
        return 0;
    }

    ///Desarmo la cola de atras para adelante y libero memoria

    while(u!=p->izq){
        aux=u;
        u=u->izq;
        bf=aux->datos;
        fwrite(&bf,sizeof(repuestos_t),1,fp);
        //imprimo en consola para ver si se carga bien

        printf("\n----------------------------");
        printf("\nDescripci%cn: %s",162,aux->datos.descripcion);
        printf("\nPartNumber: %ld",aux->datos.partNumber);
        printf("\nSerialNumber: %ld",aux->datos.serialNumber);
        printf("\nUbicaci%cn: %s",162,aux->datos.ubicacion);

        free(aux);
    }

    fclose(fp);
    getch();
    return 0;
}
