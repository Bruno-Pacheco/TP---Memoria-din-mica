/**Ejercicio 37: Existe un archivo llamado "datos.dat", de tipo binario, cuya organización
es secuencial. Los datos están organizados según la siguiente estructura:

struct d{
long clave; //Clave o Id del registro
char d[30]; // Descripcion
unsigned char tipo; //Tipo de datos como entero sin signo
char b; //'A':Alta 'B':Baja
}

Se Pide: Realizar una función que pase como parámetro la clave, entre otros parámetros, y
apile dos valores, la Clave y su posición física respecto al archivo (registro 1, 2, etc),
si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo mostrar por
pantalla "Registro no encontrado". La función debe devolver el puntero de pila. Realizar el
main con varias llamadas a dicha función y proceder a mostrar las descripciones del archivo,
mediante la pila como acceso directo, NO USAR VARIABLES GLOBALES.*/

#include <stdio.h>
#include <stdlib.h>

struct d{
    long clave; //Clave o Id del registro
    char d[30]; // Descripcion
    unsigned char tipo; //Tipo de datos como entero sin signo
    char b; //'A':Alta 'B':Baja
};

struct registro{        //datos que voy a apilar
    long clave, nregistro;
};

struct pila{
    struct registro dato;
    struct pila * lazo;
};

struct pila * apilar_b4en1(long, struct pila *);

int menu(void);

int main()
{
    /**pido la clave
    y llamo a la funcion*/
    struct pila *aux, *p=NULL;
    long clave;
    int op;

    do{
        switch(op=menu()){
            case 1:
                printf("\nIngrese clave del registro:  ");
                scanf("%ld",&clave);
                p=apilar_b4en1(clave,p);  //llamo a la función, le paso que clave buscar, y la posicion del puntero pila, me retorna la nueva posicion de p si apila
                break;
            case 2:
                if(!p) printf("\nNo hay registros apilados");
                while(p){
                    //Desapilo y libero memoria
                    aux=p;
                    p=p->lazo;
                    printf("\n>>Registro nro %ld. Clave: %ld", aux->dato.nregistro,aux->dato.clave);
                    free(aux);
                }
                getch();
                break;
        }
    }while(op!=3);

return 0;
}


int menu(){
    system("cls");
    int op;
    printf("(1) Apilar registro\n");        //apilo el valor de la clave, y la posicion del registro en el archivo si el bit 4 de tipo es 1
    printf("(2) Mostrar registros apilados\n"); //imprimo lo que se apilo y libero la memoria dinamica
    printf("(3) Salir\n");
    printf("->\t");
    scanf("%d",&op);
    return (op);
}

//FUNCIÓN QUE RECIBE UNA CLAVE Y EL PUNTERO PILA.
struct pila * apilar_b4en1(long clave, struct pila *p)
{
    FILE *fp;
    struct d bf;
    struct pila *aux;
    long nregistro=1;

    if(!(fp=fopen("datos.dat","rb"))){  //abro el archivo para su lectura
        printf("Error: No se encontr%c el archivo \"datos.dat\"\n",162);
        system ("exit");
    }

    fread(&bf,sizeof(struct d),1,fp);
    while(!feof(fp)){
        if(bf.clave==clave){
            if(bf.b=='A'){
                if((bf.tipo&0b00010000)){    //si el bit 4 de tipo está en 1...
                    //APILO
                    aux=(struct pila*)malloc(sizeof(struct pila));
                    aux->dato.clave=bf.clave;
                    aux->dato.nregistro=nregistro;
                    aux->lazo=p;
                    p=aux;
                    return p;       //devuelvo la dirección de la pila en memoria dinamica
                }
            }else {
                printf("\nEsta clave se encuentra dada de baja\n");
                return p;
            }
        }
        fread(&bf,sizeof(struct d),1,fp);
        nregistro ++;
    }
    printf("\nRegistro no encontrado");
    getch();
    return p;
};
