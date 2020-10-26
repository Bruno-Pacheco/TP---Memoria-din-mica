/**Ejercicio 38: Hacer una cola con los valores muestreados de
un cuarto de ciclo de una señal sinusoidal, en 8 bits, para luego
recorrerla y recomponer la señal completa. Las muetras deberán ir
de 127 a -127 utilizando el bit más significativo en 1 para los
valores negativos y en 0 para los valores positivos. Imprimir en
pantalla los valores.*/

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


