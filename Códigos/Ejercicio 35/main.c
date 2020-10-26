/** Ejercicio 35: Hacer un programa que tome los datos de contacto de una persona
(Nombre, Apellido, edad, teléfono, mail) y los cargue, en forma directa, en una
pila de memoria dinámica. Imprimir en pantalla y cargar en un archivo llamado
"contactos.dat", de organización secuencial, los registros ingresados por el
usuario si la persona tiene una edad mayor a 21 años.*/

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
