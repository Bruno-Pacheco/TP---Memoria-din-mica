/** Ejercicio 43: El servicio t�cnico de CosmeFulanito recibe
�rdenes de trabajo diarias. Las mismas son cargadas en un archivo
secuencial por el personal de recepci�n bajo la siguiente
estructura de datos:

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

Se pide:
Hacer una pila con las �rdenes de trabajo de forma tal que la
m�s vieja sea la �ltima en cargarse.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
   long numeroDeOrden;
   char cliente[40];
   char descripciondeFalla[200];
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;

struct pila{
    repuestos_t datos;
    struct pila *lazo;
};

int main()
{
    char flag=0, continuar;
    FILE *fp;
    repuestos_t bf;
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
        fwrite(&bf,sizeof(repuestos_t),1,fp);


        aux=(struct pila*)malloc(sizeof(repuestos_t));
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
                if(aux->datos.fecha > r->lazo->datos.fecha) r=r->lazo;      ///muevo r una posici�n
                else{
                    r->lazo=aux;
                    aux->lazo=r->lazo->lazo;
                    flag=1;     ///aviso que ya lo ubiqu�
                }
            }
            flag=0;
        }

        printf("\nIngresar otra orden?\t(0)NO\t(1)SI\t");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);

    fclose(fp);
    ///la pila ya esta armada y ocupa espacio en memoria din�mica, deber�a usarla para algo
    ///antes de cerrar el programa.

    return 0;
}
