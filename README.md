# TP 2 - Memoria Dinámica

### Ejercicio 35
Hacer un programa que tome los datos de contacto de una persona (Nombre, Apellido, edad, teléfono, mail) y los cargue, en forma directa, en una pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo llamado "contactos.dat", de organización secuencial, los registros ingresados por el usuario si la persona tiene una edad mayor a 21 años.
```c
#include <stdio.h>
#include <stdlib.h>

struct pila {
    struct d{
        char apnom[40], edad, telefono[13], mail[30];
    }dato;
    struct pila * lazo;
};

int menu(void);

int main()
{
    FILE *fp;
    struct pila *aux, *p=NULL;
    int op=1;
    do{
        switch (op=menu()){
            case 1:
                //Apilo
                aux=(struct pila*)malloc(sizeof(struct pila));
                printf("\nApellido y Nombre: ");
                fflush(stdin);
                gets(aux->dato.apnom);
                printf("\nEdad: ");
                scanf("%d", &aux->dato.edad);
                printf("\nTel%cfono: ",130);
                fflush(stdin);
                scanf("%s", &aux->dato.telefono);
                printf("\ne-mail: ");
                fflush(stdin);
                scanf("%s", &aux->dato.mail);
                fflush(stdin);
                aux->lazo=p;
                p=aux;
                break;
            case 2:
                if((fp=fopen("contactos.dat","ab"))==NULL){
                    printf("\nError: No hay espacio para crear el archivo contactos.dat o añadir nuevos registros");
                    return 0;
                }
                if(!p) printf("\nError: No hay elementos en la pila");
                while(p){
                    //Desarmo la Pila
                    int i;
                    aux=p;
                    p=aux->lazo;
                    if((aux->dato.edad)>20){
                        //Escribo en la consola
                        printf("\n-------------------------------------------------");
                        printf("\nNombre:\t\t%s",aux->dato.apnom);
                        printf("\nEdad:\t\t%d a%cos",aux->dato.edad,164);
                        printf("\nE-mail:\t\t%s",aux->dato.mail);
                        printf("\nTel%cfono:\t%s",130,aux->dato.telefono);
                        //Escribo en contactos.dat
                        i=fwrite(&(aux->dato),sizeof(struct d),1,fp);
                        //if(i!=1)printf("\Error: no se pudo cargar el archivo");
                    }
                    free(aux);
                }
                fclose(fp);
                getch();
                break;
        }
    }while(op!=3);

    return 0;
}

int menu(){
    int op;
    system("cls");
    printf("\n 1 - A%cadir nuevo contacto", 164);
    printf("\n 2 - Imprimir y cargar en archivo");
    printf("\n 3 - Salir");
    printf("\n ->\t");
    scanf("%d", &op);
    return op;
}

```
### Ejercicio 36
Hacer un programa que lea al archivo "contactos.dat" creado en el Ejercicio 35 y crear una lista, en memoria dinámica, ordenada alfabéticamente. Una vez creada la lista guardarla en un archivo de organización directa llamado "contactos_ordenados.dat" imprimiendola en pantalla.
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct lista{
    struct d{
        char apnom[40], edad, telefono[13], mail[30];
    }dato;
    struct lista * lazo;
};

int menu(void);

int main()
{
    int op, flag=0;
    FILE *fp;
    struct d bf;
    struct lista *p, *u, *aux, *r;
    p=u=NULL;
    int i;
    do{
        switch (op=menu()){
            case 1:
                if((fp=fopen("contactos.dat","rb"))==NULL){
                printf("\nError: No se encontr%c el archivo contactos.dat",162);
                return 0;
                }
                //para el primer elemento...
                i=fread(&bf,sizeof(struct d),1,fp);

                aux=(struct lista*)malloc(sizeof(struct lista));
                aux->dato=bf;
                p=u=aux;
                u->lazo=NULL;

                while(!feof(fp)){  //Recorro contactos.dat y armo la lista alfabeticamente
                    i=fread(&bf,sizeof(struct d),1,fp);
                    if(i==1) {      //verifico que el dato se lea bien, porque sino me procesaba algo de basura entre el ultimo registro y el final del archivo
                        aux=(struct lista*)malloc(sizeof(struct lista));
                        aux->dato=bf;
                        r=p;

                        if((strcmp(aux->dato.apnom,p->dato.apnom))<0){    //si el dato que entra a la lista va primero en orden alfabetico...
                            aux->lazo=p;
                            p=aux;
                        }
                        else{       //si no va primero.... me fijo si va ultimo
                            if((strcmp(u->dato.apnom,aux->dato.apnom))<0){      //el contacto va ulitmo...
                                u->lazo=aux;
                                u=aux;
                                u->lazo=NULL;
                            }else flag=1;       //NO VA PRIMERO, NI ULTIMO --> VA EN EL MEDIO
                        }
                        while(flag==1){        //indica que va en alguna posicion del medio
                            if((strcmp(aux->dato.apnom,r->lazo->dato.apnom))<0){
                                aux->lazo=r->lazo;
                                r->lazo=aux;
                                flag=0;
                            }else r=r->lazo;
                        }
                        flag=0;
                        }
                    }
                printf("\nLISTA ARMADA");
                fclose(fp);
                getch();

                break;
            case 2:
                //int i;

                if((fp=fopen("contactos_ordenados.dat","ab"))==NULL){ //si no existe lo creo, si existe grabo los contactos a continuacion de los anteriores
                    printf("\nError: No se cre%c el archivo contactos_ordenados.dat",162);
                    return 0;
                }
                if(!p) printf("Error: No hay elementos en la lista");
                while(p){
                    //Desarmo la lista
                    aux=p;
                    p=p->lazo;
                    //Imprimo en consola
                    printf("\n-------------------------------------------------");
                    printf("\nNombre:\t\t%s",aux->dato.apnom);
                    printf("\nEdad:\t\t%d a%cos",aux->dato.edad,164);
                    printf("\nE-mail:\t\t%s",aux->dato.mail);
                    printf("\nTel%cfono:\t%s",130,aux->dato.telefono);
                    //Grabo en contactos_ordenados.dat
                    fwrite(&aux->dato,sizeof(struct lista),1,fp);
                    //if(i!=1)printf("\Error: no se pudo cargar el archivo");
                    free(aux);
                }
                fclose(fp);
                getch();
                break;
        }
    }while(op!=3);
    return 0;
}

int menu(){
    int op;
    system("cls");
    printf("\n1 - Ordenar archivo contactos.dat alfabeticamente");
    printf("\n2 - Mostrar lista, y cargar en contactos_ordenados.dat");
    printf("\n3 - Salir");
    printf("\n->\t");
    scanf("%d", &op);
    fflush(stdin);
    return op;
}
```
### Ejercicio 37
Existe un archivo llamado "datos.dat", de tipo binario, cuya organización es secuencial. Los datos están organizados según la siguiente estructura:
```c
struct d{                                                                                            
long clave; //Clave o Id del registro

char d[30]; // Descripcion                                                                                          
unsigned char tipo; //Tipo de datos como entero sin signo                                                                                                                                            
char b; //'A':Alta 'B':Baja                                                                                                                                                                          
}
```
Se Pide: Realizar una funciún que pase como parámetro la clave, entre otros parámetros, y apile dos valores, la Clave y su posición física respecto al archivo (registro 1, 2, etc), si es que el campo tipo tiene el bit 4 con valor 1. En caso de no encontrarlo mostrar por pantalla "Registro no encontrado". La función debe devolver el puntero de pila. Realizar el main con varias llamadas a dicha función y proceder a mostrar las descripciones del archivo, mediante la pila como acceso directo, NO USAR VARIABLES GLOBALES.

```c
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
```
### Ejercicio 38
Hacer una cola con los valores muestreados de un cuarto de ciclo de una señal sinusoidal, en 8 bits, para luego recorrerla y recomponer la señal completa. Las muetras deberán ir de 127 a -127 utilizando el bit más significativo en 1 para los valores negativos y en 0 para los valores positivos. Imprimir en pantalla los valores.

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct cola{
    unsigned char valor;
    struct cola *der;
    struct cola *izq;
};

//struct cola * cuarto_señal();

int main()
{
    char x,i;
    unsigned char valor;
    struct cola *p,*u,*aux;
    p=u=NULL;
    //GENERO EL PRIMER CUARTO DE SEÑAL
    for(x=0;x<91;x+=5){
        aux=(struct cola*)malloc(sizeof(struct cola));
        aux->valor=(char)((double)127.0*sin((double)x*3.14/180));
        if(!p){
            p=u=aux;
            p->izq=NULL;
            p->der=NULL;
        }
        else{
            aux->der=NULL;
            aux->izq=u;
            u->der=aux;
            u=aux;
        }
    }
    ///PRIMER CUARTO, RECORRO LA COLA DE IZQ A DER
    aux=p;
    while(aux){
        printf("%d\n",aux->valor);
        aux=aux->der;
    }
    ///SEGUNDO CUARTO, RECORRO LA COLA DE DER A IZQ
    aux=u;
    while(aux){
        printf("%d\n",aux->valor);
        aux=aux->izq;
    }
    ///TERCER CUARTO, EL BIT 7 LO SETEO EN 1 PARA REPRESENTAR NUMEROS NEGATIVOS, VOY DE IZQ(128) A IZQ (255)
    //Es decir, el 255 (0b11111111) representaria el -127 y el 128 (0b10000001) representaria el -1
    aux=p;
    while(aux){
        printf("%d\n",(aux->valor|0b10000000));
        aux=aux->der;
    }
    ///ULITMO CUARTO DE LA SEÑAL, VOY DE DER(255) A IZQ (128)
    //Ya puedo ir liberando la memoria
    while(u){
        aux=(struct cola*)malloc(sizeof(struct cola));
        aux=u;
        printf("%d\n",(aux->valor|0b10000000));
        u=u->izq;
    }
    system("pause");
    return 0;
}
```
### Ejercicio 39
Hacer un programa que tome los datos de medición de potencia, cargados por el usuario, de un sistema de medición a distancia.
```c
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
```
Donde estado es la multiplicación del valor ASCII de la primer letra de la descripción por la potencia. Los datos cargados se deberán guardar en una lista ordenada, de mayor a menor, del valor de potencia. Una vez finalizada la carga guardar los datos en un archivo de organización directa llamado "potencia.dat" imprimiendo en pantalla los datos.

```c
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

```
### Ejercicio 40
Utilizando el archivo “potencia.dat” creado en el Ejercicio 39, realizar una función que pase como parámetro, entre otros datos, la clave del registro (id).

La función ubicará el registro correspondiente al id pasado como parámetro, y utilizando punteros imprimirá la primera palabra del campo "desc" en forma inversa, además cambiará el estado del bit 3 para luego actualizar el archivo. Además, se agregará a una pila la potencia cuando los bits 0 y 2, del campo estado, estén encendidos, en caso contrario se agregará el registro al archivo “salida.dat” de organización secuencial.

