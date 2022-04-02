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

void ord_sel(int v[], int n){
    int i, j;
    int minj, minx;

    for (i = 0; i < n - 2; ++i) {
        minj = i;
        minx = v[i];
        for (j = i + 1; j <= n ; ++j) {
            if(v[j] < minx){
                minj = j;
                minx = v[j];
            }
        }
        v[minj] = v[i];
        v[i] = minx;
    }
}

void ord_shell(int v[], int n){
    int incremento, i, tmp, j;
    bool seguir;
    incremento = n;
    do{
        incremento /= 2;
        for(i = incremento+1; i < n; i++){
            tmp = v[i];
            j = i;
            seguir = true;
            while(j-incremento >= 0 && seguir){
                if(tmp < v[j-incremento]){
                    v[j]= v[j-incremento];
                    j = j - incremento;
                } else {
                    seguir = false;
                }
            }
            v[j]= tmp;
        }

    }while (incremento != 1);
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

void control(int v[], int n, void ord(int v[], int n), void inic(int v[], int n), char *descripcion){
    inic(v, n);
    listar_vector(v, n);
    printf("\nOrdenado?: %d\n", ordenado(v,n));
    ord(v, n);
    printf("Ordenación por %s\n", descripcion);
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
    printf("%11s%15s%11s%.2f%11s%.2f%11s%.2f\n","n","t(n)","t(n)/n^", sub,
           "t(n)/n^",ajus,"t(n)/n^", sobre);
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

        x = t / pow(n, sub);
        y = t / pow(n, ajus);
        z = t / pow(n, sobre);
        printf("%15.3f%15.8f%15.8f%15.8f\n",t,x,y,z);
    }
}
void tablas_aux(){
    tabla(ord_shell, aleatorio,
          "Ordenación shell con inicializacion aleatoria", 1.1, 1.2, 1.3);
    tabla(ord_shell, ascendente,
          "Ordenación shell con inicializacion ascendente", 0.95, 1.12, 1.2);
    tabla(ord_shell, descendente,
          "Ordenación shell con inicializacion descendente", 1, 1.12, 1.2);
    tabla(ord_sel, aleatorio,
         "Ordenación por selección con inicializacion aleatoria", 1.8, 2, 2.2);
    tabla(ord_sel, ascendente,
         "Ordenación por selección con inicializacion ascendente", 1.8, 2, 2.2);
    tabla(ord_sel, descendente,
          "Ordenación por selección con inicializacion descendente", 1.8, 2, 2.2);
}

int main() {

    inicializar_semilla();
    tablas_aux();

    return 0;
}
