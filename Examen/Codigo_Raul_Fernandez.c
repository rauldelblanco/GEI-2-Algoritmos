/*Nombre:
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

int max(int num1, int num2) {
    int result;

    if (num1 > num2) {
        result = num1;
    } else {
        result = num2;
    }

    return result;
}

int sumaSubMax1(const int v[], int n){
    int estaSuma, sumaMax=0, i, j;
    for(i=0;i<=n;i++){
        estaSuma=0;
        for(j=i;j<n;j++){
            estaSuma += v[j];
            if(estaSuma > sumaMax){
                sumaMax=estaSuma;
            }
        }
    }
    return sumaMax;
}

int sumaSubMax2(const int v[], int n){

    int estaSuma = 0, sumaMax = 0, j;

    for(j=0; j<n; j++){
        estaSuma += v[j];
        if(estaSuma>sumaMax){
            sumaMax=estaSuma;
        }
        else if(estaSuma<0) {
            estaSuma=0;
        }
    }
    return sumaMax;
}

int SumaSubMaxAux(const int v[], int n, int izq, int der){

    int centro, sumBordeIzq, sumAux, x, sumBordeDer, sumIzq, sumDer;

    if(izq == der){
        if(v[izq] > 0){
            return v[izq];
        } else {
            return 0;
        }
    } else {

        centro = (izq + der) / 2;
        sumBordeIzq = 0;
        sumAux = 0;

        for (x = centro-1; x >= izq ; --x) {
            sumAux += v[x];
            if(sumAux > sumBordeIzq){
                sumBordeIzq = sumAux;
            }
        }

        sumBordeDer = 0;
        sumAux = 0;

        for (x = centro; x <= der; x++) {
            sumAux += v[x];
            if(sumAux > sumBordeDer){
                sumBordeDer = sumAux;
            }
        }

        sumIzq = SumaSubMaxAux(v, n, izq, centro);
        sumDer = SumaSubMaxAux(v, n, centro + 1, der);

        return max(max(sumIzq, sumDer), (sumBordeIzq+sumBordeDer));
    }

}

int sumaSubMax3(const int v[], int n){
    return SumaSubMaxAux(v, n, 0, n-1);
}

void listar_vector(int v[], int n){
    int i;
    printf("[");
    for(i=0; i<n; i++){

        printf("%3d", v[i]);
    }
    printf("]");
}

void test1(){

    int v[5], a, b, c, i;
    printf("Test 1\n");
    printf("%22s%15s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2", "SumaSubMax3");
    for (i = 0; i < 6; ++i) {

        switch (i) {
            case 0:
                v[0] = -9, v[1] = 2, v[2] = -5, v[3] = -4; v[4] = 6;
                break;
            case 1:
                v[0] = 4, v[1] = 0, v[2] = 9, v[3] = 2; v[4] = 5;
                break;
            case 2:
                v[0] = -2, v[1] = -1, v[2] = -9, v[3] = -7; v[4] = -1;
                break;
            case 3:
                v[0] = 9, v[1] = -2, v[2] = 1, v[3] = -7; v[4] = -8;
                break;
            case 4:
                v[0] = 15, v[1] = -2, v[2] = -5, v[3] = -4; v[4] = 16;
                break;
            case 5:
                v[0] = 7, v[1] = -5, v[2] = 6, v[3] = 7; v[4] = -7;
                break;
            default:
                break;
        }
        listar_vector(v, 5);
        a = sumaSubMax1(v, 5);
        b = sumaSubMax2(v, 5);
        c = sumaSubMax3(v, 5);
        printf("%20d%15d%15d\n", a, b, c);
    }


}

void test2(){

    int i, a, b, c;
    int v[9];
    printf("\nTest 2\n");
    printf("%33s%15s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2", "SumaSubMax3");
    for (i=0; i<10; i++) {
        aleatorio(v, 9);
        listar_vector(v, 9);
        a = sumaSubMax1(v, 9);
        b = sumaSubMax2(v, 9);
        c = sumaSubMax3(v, 9);
        printf("%19d%15d%15d\n", a, b, c);
    }

}


void tabla(int (*ord)(const int v[], int n),
        char* descripcion, float sub, float ajus, float sobre){
    int v[32000];
    int n, i, k = 1000;
    double t1, t2, t3, t, x, y, z;
    printf("\n%s\n", descripcion);
    printf("%11s%15s%11s%.2f%11s%.2f%11s%.2f\n","n","t(n)","t(n)/n^", sub,
           "t(n)/n^",ajus,"t(n)/n^", sobre);
    t = 0;
    for(n = 500;n <= 32000 && t<1000000;n*=2){
        aleatorio(v, n);
        t1 = microsegundos();
        ord(v, n);
        t2 = microsegundos();
        t = t2-t1;

        if (t < 500) {
            printf("%s%8d", "(*)", n);
            t1 = microsegundos();
            for (i = 0; i < k; i++) {
                aleatorio(v, n);
                ord(v, n);
            }
            t2 = microsegundos();
            for (i = 0; i < k; i++){
                aleatorio(v, n);
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
    tabla(sumaSubMax1,
          "sumaSubMax1", 1.8, 2, 2.2);
    tabla(sumaSubMax1,
          "sumaSubMax1", 1.8, 2, 2.2);
    tabla(sumaSubMax1,
          "sumaSubMax1", 1.8, 2, 2.2);
    tabla(sumaSubMax2,
          "sumaSubMax2", 0.8, 1, 1.2);
    tabla(sumaSubMax2,
          "sumaSubMax2", 0.8, 1, 1.2);
    tabla(sumaSubMax2,
          "sumaSubMax2", 0.8, 1, 1.2);
    tabla(sumaSubMax3,
          "sumaSubMax3", 0.8, 1.05, 1.2);
    tabla(sumaSubMax3,
          "sumaSubMax3", 0.8, 1.05, 1.2);
    tabla(sumaSubMax3,
          "sumaSubMax3", 0.8, 1.05, 1.2);            
}

int main() {
    inicializar_semilla();
    test1();
    test2();
    tablas_aux();
    return 0;
}
