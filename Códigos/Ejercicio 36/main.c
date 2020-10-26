/**Ejercicio 36: Hacer un programa que lea al archivo "contactos.dat"
creado en el Ejercicio 35 y crear una lista, en memoria dinámica,
ordenada alfabéticamente. Una vez creada la lista guardarla en un
archivo de organización directa llamado "contactos_ordenados.dat"
imprimiendola en pantalla.*/

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
