/** Ejercicio 44: El servicio técnico utiliza la pila generada en el
ejercicio 43 en su labor diaria. Cada técnico toma una tarea de la pila
y genera un orden de extracción de repuestos al depósito. Para optimizar
los viajes al depósito se arma una lista con los repuestos que cada orden
necesita utilizando la siguiente estructura:

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

Se pide cargar la lista de repuestos solicitados por los técnicos. Tener en
cuenta que varios técnicos pueden necesitar la misma parte, y en esos casos
se debe incrementar la cantidad pedida en la lista.*/

#include <stdio.h>
#include <stdlib.h>


typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}orden_t;

typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];
   char ubicacion[100];
}repuestos_t;

typedef struct{
    repuestos_t repuesto;
    int cantidad;
}extraccionRepuestos_t;

struct pila{
    orden_t datos;
    struct pila *lazo;
};

struct lista{
    extraccionRepuestos_t datos;
    struct lista *lazo;
};

///copio el ejercicio anterior para tener la pila
int main()
{
    char flag=0, continuar;
    FILE *fp;
    orden_t bf;
    struct pila *p,*aux, *r;
    p=NULL;

    if(!(fp=fopen("ordenes.dat","ab"))){
        printf("\nError: No se puede abrir o crear archivo");
        return 0;
    }

    do{
        printf("\nNumero de orden: ");
        scanf("%ld",&bf.numeroDeOrden);
        fflush(stdin);
        printf("\nCliente: ");
        gets(bf.cliente);
        fflush(stdin);
        printf("\nDescripci%cn de falla: ",162);
        gets(bf.descripciondeFalla);
        fflush(stdin);
        printf("\nModelo: ");
        gets(bf.modelo);
        fflush(stdin);
        printf("\nFecha: ");
        gets(bf.fecha);
        fflush(stdin);
        printf("\nHora: ");
        gets(bf.hora);
        fflush(stdin);

        ///cargo la orden en el archivo
        fwrite(&bf,sizeof(orden_t),1,fp);


        aux=(struct pila*)malloc(sizeof(orden_t));
        aux->datos=bf;
        ///ordeno por antiguedad
        r=p;
        if(!p) p=aux;     //si es el primero
        else{
            if(aux->datos.fecha < p->datos.fecha){    ///la orden que entra es la mas antigua
                aux->lazo=p;
                p=aux;
                flag=1;
            }
            while(r->lazo && flag==0){
                if(aux->datos.fecha > r->lazo->datos.fecha) r=r->lazo;      ///muevo r una posición
                else{
                    r->lazo=aux;
                    aux->lazo=r->lazo->lazo;
                    flag=1;     ///aviso que ya lo ubiqué
                }
            }
            flag=0;
        }

        printf("\nIngresar otra orden?\t(0)NO\t(1)SI\t");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);


    ///EJERCICIO 44
    extraccionRepuestos_t bfr;
    struct lista *pr, *ul, *au, *re;
    pr=ul=NULL;
    flag=0;
    //cada técnico saca la tarea mas antigua de la pila
    do{
        printf("\nPresione una tecla para tomar la tarea mas antigua");
        getch();
        aux=p;
        p=p->lazo;
        printf("\nNum Orden: %d",aux->datos.numeroDeOrden);
        printf("\nCliente: %s",aux->datos.cliente);
        printf("\nDescripcion de falla; %s",aux->datos.descripciondeFalla);
        printf("\nModelo: %s",aux->datos.modelo);
        printf("\nFecha: %s",aux->datos.fecha);
        printf("\nHora: %s",aux->datos.hora);

        free(aux);      //libero la memoria de la pila creada en el ejercicio 43

        au=(struct lista*)malloc(sizeof(struct lista));


        printf("\n\nPartNumber del repuesto solicitado: ");
        scanf("%d",&au->datos.repuesto.partNumber);
        printf("\nCuantos repuestos necesita?\t");
        scanf("%d",&au->datos.cantidad);

        ///armo lista de extraccion de repuestos
        if(!pr) pr=au; //si va primero
        //recorro la lista para ver si nadie pidio el mismo repuesto
        re=pr;
        if(pr->datos.repuesto.partNumber==au->datos.repuesto.partNumber){
                pr->datos.cantidad= pr->datos.cantidad + au->datos.cantidad;
                flag=1;
        }
        while(re->lazo && flag==0){

            if(re->lazo->datos.repuesto.partNumber==au->datos.repuesto.partNumber){
                re->lazo->datos.cantidad=re->datos.cantidad+au->datos.cantidad;
                flag=1;
            }else r=r->lazo;
        }
        if(flag=0){
            ul->lazo=au;
            ul=au;
            ul->lazo=NULL;
        }

        printf("\nTomar otra tarea?\t(0)NO\t(1)SI\t");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);


    fclose(fp);
    ///la pila ya esta armada y ocupa espacio en memoria dinámica, debería usarla para algo
    ///antes de cerrar el programa.

    return 0;
}
