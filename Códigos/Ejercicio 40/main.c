/**Ejercicio 40: Utilizando el archivo “potencia.dat” creado
 en el Ejercicio 39, realizar una función que pase como parámetro,
 entre otros datos, la clave del registro (id).
La función ubicará el registro correspondiente al id pasado como
parámetro, y utilizando punteros imprimirá la primera palabra del
campo "desc" en forma inversa, además cambiará el estado del bit 3
para luego actualizar el archivo. Además, se agregará a una pila la
potencia cuando los bits 0 y 2, del campo estado, estén encendidos,
en caso contrario se agregará el registro al archivo “salida.dat” de
organización secuencial.*/

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
