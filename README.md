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

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct e{
    int id;
    char desc[60];
    unsigned char potencia;
    unsigned int estado;
};

struct pila{
    unsigned char potencia;
    struct pila *lazo;
};

struct pila * funcion(int id, struct pila*p);

int main()
{
    char continuar;
    int id;
    struct pila *p,*aux;
    p=NULL;



    fflush(stdin);

    do{
        printf("\nBuscar registro:  ");
        scanf("%d",&id);
        fflush(stdin);
        p=funcion(id,p);



        printf("\nContinuar buscando registros?\t(0)NO\t(1)SI\t");
        scanf("%d",&continuar);
        fflush(stdin);
    }while(continuar);
    return 0;
}

struct pila * funcion (int id,struct pila* p){
    FILE *fp;
    struct e bf;
    char *s, *i, *z,aux[60];

    if(!(fp=fopen("potencia.dat","rb+"))){
        printf("\nError: No se encontr%c el archivo \"potencia.dat\"", 162);
        return 0;
    }

    fseek(fp,(1L)*sizeof(struct e)*(id-1),0);
    fread(&bf,sizeof(struct e),1,fp);
    if(bf.id==id){
        /// INVIERTO E IMPRIMO
        s=&bf.desc[0];
        i=aux;

        while(*s != ' ')s++;   ///lo posiciono al final de la primer palabra
        z=s;    //un puntero lo apunto a lo que sigue despues de la primer palabra

        s--;        ///lo corro uno a la izq porque sino queda en el espacio

        while(s != &bf.desc[0]){
            *i=*s;
            s--;
            i++;
        }
        *i=*s;      ///primer letra
        i++;
        *i=0;   ///pongo un null al final


        strcpy(bf.desc,strcat(aux,z));        ///guardo la palabra invertida mas lo que seguia despues para despues grabarla
        bf.estado=(bf.estado^8);        /// cambio el estado del bit 3

        ///actualizo el archivo
        fseek(fp,(1L)*sizeof(struct e)*(id-1),0);
        fwrite(&bf,sizeof(struct e),1,fp);
        fclose(fp);
    }
    else{
        printf("\nNo se encontr%c la clave", 162);
        getch();
        return p;
    }

    ///si encontro la clave, chequeo los bits 0 y 2
    if(bf.estado&(1<<2) && bf.estado&1){    ///si ambos estan encendidos
        struct pila *aux;

        aux=(struct pila*)malloc(sizeof(struct pila));
        aux->potencia=bf.potencia;
        aux->lazo=p;
        p=aux;

        printf("\n***Se apilo la potencia***");
        getch();
    }
    else{       ///si no estan encendidos...
        if(!(fp=fopen("salida.dat","ab"))){
            printf("\nError: No se pud%c crear el archivo \"salida.dat\"",162);
            return p;
        }
        fwrite(&bf,sizeof(struct e),1,fp);
        printf("\n***Se agrego el registro a \"salida.dat\"***");
        getch();
        fclose(fp);
    }

    return p;
};

```

### Ejercicio 41
El depósito de la empresa CosmeFulanito necesita cargar su stock de repuestos en forma ordenada. Para dicha tarea se solicitó categorizar a los respuestos bajo la siguiente estructura de datos:
```c
typedef struct{
   long partNumber;
   long serialNumber;
   char descripcion[40];       
   chat ubicacion[100];        
}repuestos_t;
```
Los repuestos no están ordenados, se solicita cargarlos en una lista, la cual ordene por descripción a los repuestos para luego guardarlos en un archivo de stock con organización secuencial.

Imprimir en pantalla la lista con cada inserción.
El archivo se generará cuando el usuario decide no cargar mas productos.

```c
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

```

### Ejercicio 42
El proveedor de repuestos de CosmeFulanito informó que una partida de repuestos salió con falla y debe ser devuelta. Para identificar la partida, el proveedor indicó que la falla fue en el partNumber: 1234 que tiene números de serie con el bit 3 y 5 en 1.

Para estas tareas se solicita:

Hacer una cola con todos los registros fallados
Realizar la baja física a todos los repuestos fallados
Crear un archivo donde se vuelque el contenido de la cola en orden inverso.

```c
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
```

### Ejercicio 43
El servicio técnico de CosmeFulanito recibe órdenes de trabajo diarias. Las mismas son cargadas en un archivo secuencial por el personal de recepción bajo la siguiente estructura de datos:
```c
typedef struct{
   long numeroDeOrden;
   char cliente[40];       
   char descripciondeFalla[200];        
   char modelo[65];
   char fecha[10];
   char hora[10];
}repuestos_t;
```
Se pide:

Hacer una pila con las órdenes de trabajo de forma tal que la más vieja sea la última en cargarse.

```c
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

    fclose(fp);
    ///la pila ya esta armada y ocupa espacio en memoria dinámica, debería usarla para algo
    ///antes de cerrar el programa.

    return 0;
}
```

### Ejercicio 44
El servicio técnico utiliza la pila generada en el ejercicio 43 en su labor diaria. Cada técnico toma una tarea de la pila y genera un orden de extracción de repuestos al depósito. Para optimizar los viajes al depósito se arma una lista con los repuestos que cada orden necesita utilizando la siguiente estructura:
```c
typedef struct{
    repuestos_t repuesto;        
    int cantidad;
}extraccionRepuestos_t;
```
Se pide cargar la lista de repuestos solicitados por los técnicos. Tener en cuenta que varios técnicos pueden necesitar la misma parte, y en esos casos se debe incrementar la cantidad pedida en la lista.

```c
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
```

### Ejercicio 45
La lista creada en el ejercicio 44 es procesada por el depósito. Para dicha tarea se pide hacer un programa que:

Descuente las cantidades solicitadas del archivo de stock, creado en el Ejercicio 41.
Hacer una cola con los repuestos en los que no se encontró stock suficiente para poder notificar a los clientes la demora de la reparación.

```c
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
```