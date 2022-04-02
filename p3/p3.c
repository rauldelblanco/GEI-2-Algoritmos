/*Nombres:
 * Brais Gonzalez Piñeiro brais.gonzalezp
 * Armando Martínez Noya  a.mnoya
 * Raul Fernández del Blanco r.delblanco
 * Grupo 2.4
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <sys/time.h>
#include <math.h>

#define UMBRAL 100
#define INTERCAMBIAR(x,y) { int aux = x; x = y; y = aux; }

void inicializar_semilla() {
    srand(time(NULL));
    /* se establece la semilla de una nueva serie de enteros pseudo-aleatorios */
}

double microsegundos() {
/* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void aleatorio(int v [], int n) {
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
    /* se generan números pseudoaleatorio entre -n y +n */
}

void ord_ins(int v[], int n){
    int i, x, j;
    for (i = 1; i < n; i++){
        x = v[i];
        j = i - 1;
        while (j >= 0 && v[j] >= x){
            v[j+1] = v[j];
            j = j - 1;
        }
        v[j+1] = x;
    }

}


void mediana3(int v[], int i, int j){

    int k = (i + j) / 2;
    if(v[k] > v[j]){
        INTERCAMBIAR(v[k], v[j]);
    }
    if(v[k] > v[i]){
        INTERCAMBIAR(v[k], v[i]);
    }
    if(v[i] > v[j]){
        INTERCAMBIAR(v[i], v[j]);
    }

}

void ordenarAux(int v[], int izq, int der){
    int i, j;
    int pivote;
    if((izq+UMBRAL) <= der){
        mediana3(v, izq, der);
        pivote = v[izq];

        i = izq;
        j = der;
        do {
            do{
                i = i + 1;
            }while(v[i] < pivote);
            do{
                j = j - 1;
            }while(v[j] > pivote);
            INTERCAMBIAR(v[i], v[j])
        } while (j > i);
        INTERCAMBIAR(v[i],v[j])
        INTERCAMBIAR(v[izq],v[j])
        ordenarAux(v, izq, j-1);
        ordenarAux(v, j+1, der);
    }
}

void ordenacionRapida(int v[], int n){
    ordenarAux(v, 0, n-1);
    if(UMBRAL > 1){
        ord_ins(v,n);
    }
}

void ascendente(int v[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        v[i] = i;
}

void descendente(int v[], int n)
{
    int i;
    for (i = n - 1; i >= 0; i--)
        v[i] = n - i;
}

bool ordenado(const int v[], int n){
    int i;
    for (i = 0; i < n -1; i++){
        if(v[i] > v[i+1])
            return false;
    }
    return true;
}

void listar_vector(int v[], int n){

    int i;
    printf("[");
    for(i=0; i<n; i++){
        printf(" %d ", v[i]);
    }
    printf("]");
}

void control(int v[], int n, void ord(int v[], int n),
             void inic(int v[], int n), char *descripcion){
    inic(v, n);
    listar_vector(v, n);
    printf("\nOrdenado?: %d\n", ordenado(v,n));
    ord(v, n);
    printf("Ordenacion por %s\n", descripcion);
    listar_vector(v, n);
    printf("\nOrdenado?: %d\n", ordenado(v,n));
}

void test(void tipo(int v[], int n), char *descripcion){
    int n = 17, j = 10;
    int v[n];

    printf("ALeatorio:\n");
    control(v, n, tipo, aleatorio, descripcion);

    printf("Ascendente: \n");
    control(v, j, tipo, ascendente, descripcion);

    printf("Descendente:\n");
    control(v, j, tipo, descendente, descripcion);
}

void tabla(void (*ord)(int v[], int n), void (*inicializacion)(int v[], int n)
        , char* descripcion, float sub, float ajus, float sobre){
    int v[32000];
    int n, i, k = 1000;
    double t1, t2, t3, t, x, y, z;
    printf("\n%s\n", descripcion);
    printf("%11s%15s%15s%15s%15s\n","n","t(n)","t(n)/f(n)",
           "t(n)/g(n)","t(n)/h(n)");
    t = 0;
    for(n = 500;n <= 32000 && t<1000000;n*=2){
        inicializacion(v, n);
        t1 = microsegundos();
        ord(v, n);
        t2 = microsegundos();
        t = t2-t1;
        if (t < 500) {
            printf("%s%8d", "(*)", n);
            t1 = microsegundos();
            for (i = 0; i < k; i++) {
                inicializacion(v, n);
                ord(v, n);
            }
            t2 = microsegundos();
            for (i = 0; i < k; i++){
                inicializacion(v, n);
            }
            t3 = microsegundos();
            t = ((t2-t1)-(t3-t2))/k;
        }else printf("%11d", n);
        if(ord==ord_ins){
            x = t / pow(n, sub);
            y = t / pow(n, ajus);
            z = t / pow(n, sobre);
            printf("%15.3f%15.8f%15.8f%15.8f\n",t,x,y,z);
        } else {
            x = t / ((pow(n, sub))* log(n));
            y = t / ((pow(n, ajus))* log(n));
            z = t / ((pow(n, sobre))* log(n));
            printf("%15.3f%15.8f%15.8f%15.8f\n",t,x,y,z);
        }
    }
}

void tablas_aux(){
    tabla(ord_ins, aleatorio,
          "Ordenacion por insercion con inicializacion aleatoria", 1.8, 2, 2.2);
    tabla(ord_ins, ascendente,
          "Ordenacion por insercion con inicializacion ascendente", 0.8, 1, 1.2);
    tabla(ord_ins, descendente,
          "Ordenacion por insercion con inicializacion descendente", 1.8, 2, 2.2);
    switch (UMBRAL) {
        case 1:
            tabla(ordenacionRapida, aleatorio,
                  "Ordenacion Rapida con inicializacion aleatoria", 0.9, 0.98, 1.1);
            tabla(ordenacionRapida, ascendente,
                  "Ordenacion Rapida con inicializacion ascendente", 0.8, 0.96, 1.1);
            tabla(ordenacionRapida, descendente,
                  "Ordenacion Rapida con inicializacion descendente", 0.8, 0.96, 1.1);
            break;
        case 10:
            tabla(ordenacionRapida, aleatorio,
                  "Ordenacion Rapida con inicializacion aleatoria", 0.9, 0.98, 1.1);
            tabla(ordenacionRapida, ascendente,
                  "Ordenacion Rapida con inicializacion ascendente", 0.9, 0.99, 1.15);
            tabla(ordenacionRapida, descendente,
                  "Ordenacion Rapida con inicializacion descendente", 0.9, 0.99, 1.15);
            break;
        case 100:
            tabla(ordenacionRapida, aleatorio,
                  "Ordenacion Rapida con inicializacion aleatoria", 0.9, 0.99, 1.1);
            tabla(ordenacionRapida, ascendente,
                  "Ordenacion Rapida con inicializacion ascendente", 1, 1.06, 1.15);
            tabla(ordenacionRapida, descendente,
                  "Ordenacion Rapida con inicializacion descendente", 0.9, 1.06, 1.15);
            break;
    }
}

int main() {
    inicializar_semilla();
    test(ord_ins, "Insercion");
    test(ordenacionRapida, "Ordenacion rapida");
    tablas_aux();
    return 0;
}