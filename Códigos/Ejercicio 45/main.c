/** Ejercicio 45: La lista creada en el ejercicio 44 es procesada por
el depósito. Para dicha tarea se pide hacer un programa que:

-Descuente las cantidades solicitadas del archivo de stock, creado en
el Ejercicio 41.
-Hacer una cola con los repuestos en los que no se encontró stock
suficiente para poder notificar a los clientes la demora de la reparación.*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
   char estado;  //(baja o alta)
}repuestos_t;

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

struct cola{
    long partNumber;
    struct cola *lazo;
};

//de la lista anterior
struct lista44{
    extraccionRepuestos_t datos;
    struct lista44 *lazo;
};

int main()
{

    // de la lista anterior tengo los punteros *pr, *ul, *au, *re;
    struct lista44 *pr, *ul, *au, *re;
    ///continuando los codigos anteriores...
    FILE *fp;
    repuestos_t bf;
    struct cola *p, *u, *aux;
    p=u=NULL;
    char cant=0,flag1=0;

    ///desarmo la lista, y con ese part number doy de baja en el archivo
    if(!(fp=fopen("stock_cosmefulanito.dat","rb+"))){
        printf("\nError: No se pud%c abrir el archivo de stock",162);
        return 0;
    }

    au=pr;
    fread(&bf,sizeof(repuestos_t),1,fp);
    while(!feof(fp) && flag1==0){
        if(au->datos.repuesto.partNumber==bf.partNumber){   //marco como baja 1 repuesto con ese partnumber, y voy contando cuantos estoy dando de baja
            bf.estado='B';
            fseek(fp,-1L*sizeof(repuestos_t),SEEK_CUR);     //retrocedo 1 registro para posicionarme al principio del registro a modificar
            fwrite(&bf,sizeof(repuestos_t),1,fp);
            cant++;
        }
        if(cant==au->datos.cantidad) flag1=1;   //ya desconte los repuestos solicitados

        fread(&bf,sizeof(repuestos_t),1,fp);
    }

    fclose(fp);

    if(flag1 != 1){     //no tengo stock suficiente
        aux=(struct lista44*)malloc(sizeof(struct lista44));
        aux->partNumber=au->datos.repuesto.partNumber;

        free(au);

        if(!p) p=u=aux;
        else{
            u->lazo=aux;
            u=aux;
            u->lazo=NULL;
        }
    }

    ///aca terminaria la funcion

    return 0;
}
