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

int sumaSubMax1(const int v[], int n){
    int estaSuma, sumaMax=0;
    for(int i=0;i<=n;i++){
        estaSuma=0;
        for(int j=i;j<n;j++){
            estaSuma += v[j];
            if(estaSuma > sumaMax){
                sumaMax=estaSuma;
            }
        }
    }
    return sumaMax;
}

int sumaSubMax2(const int v[], int n){

    int estaSuma = 0, sumaMax = 0;

    for(int j=0; j<n; j++){
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

void listar_vector(int v[], int n){
    printf("[");
    for(int i=0; i<n; i++){

        printf("%3d", v[i]);
    }
    printf("]");
}


void informeResultados1(int n, double t,bool control){
    double t1, t2, t3;
    t1 = t / pow(n, 1.8);
    t2 = t / pow(n, 2);
    t3 = t / pow(n, 2.2);
    if(control==false) {
        printf("\t\t%d\t\t%1.4f\t%f\t%f\t%f\n", n, t, t1, t2, t3);
    }
    else{
        printf("(*)\t\t%d\t\t%1.4f\t%f\t%f\t%f\n", n, t, t1, t2, t3);
    }

}

void informeResultados2(int n, double t,bool control){
    double t1, t2, t3;
    t1 = t / pow(n, 0.8);
    t2 = t / n;
    t3 = t / pow(n, 1.2);
    if(control==false) {
        printf("\t\t%d\t\t%1.4f\t\t%f\t%f\t%f\n", n, t, t1, t2, t3);
    }
    else{
        printf("(*)\t\t%d\t\t%1.4f\t\t%f\t%f\t%f\n", n, t, t1, t2, t3);
    }

}

void tiempoEjecucion1(){

    double ta, tb, t, t1, t2;
    bool control = false;

    puts("\nSumaSubMax 1");
    puts("\t\tn\t\tt(n)\t\tt(n)/n^1.8\tt(n)/n^2\tt(n)/n^2.2");

    for (int i = 500; i <= 32000; i = 2 * i) {

        int v[i];
        aleatorio(v, i);
        ta = microsegundos();
        sumaSubMax1(v, i);
        tb = microsegundos();
        t = tb - ta;

        if(t < 500){
            int k;
            control=true;
            ta = microsegundos();
            for (k = 0; k < 1000; k++) {
                aleatorio(v, i);
                sumaSubMax1(v, i);
            }
            tb = microsegundos();
            t1 = tb - ta;
            ta = microsegundos();
            for (k = 0; k < 1000; k++) {
                aleatorio(v, i);
            }
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1 - t2) / k;
        }
        informeResultados1(i, t,control);
    }

}

void tiempoEjecucion2(){

    double ta, tb, t, t1, t2;
    bool control=false;


    puts("\nSumaSubMax 2");
    puts("\t\tn\t\tt(n)\t\tt(n)/n^0.8\tt(n)/n^1\tt(n)/n^1.2");

    for (int i = 500; i <= 32000; i = 2 * i) {

        int v[i];
        aleatorio(v, i);
        ta = microsegundos();
        sumaSubMax2(v, i);
        tb = microsegundos();
        t = tb - ta;

        if(t < 500){
            control=true;
            int k;
            control=true;
            ta = microsegundos();
            for (k = 0; k < 1000; ++k) {
                aleatorio(v, i);
                sumaSubMax2(v, i);
            }
            tb = microsegundos();
            t1 = tb - ta;
            ta = microsegundos();
            for (k = 0; k < 1000; ++k) {
                aleatorio(v,i);
            }
            tb = microsegundos();
            t2 = tb - ta;
            t = (t1 - t2) / k;
        }
        informeResultados2(i,t,control);
    }
}

void test1(){

    int v[5], a, b;
    printf("Test 1\n");
    printf("%22s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (int i = 0; i < 6; ++i) {

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
        printf("%15d%15d\n", a, b);
    }


}

void test2(){

    int i, a, b;
    int v[9];
    printf("\nTest 2\n");
    printf("%33s%15s%15s\n", "", "sumaSubMax1", "sumaSubMax2");
    for (i=0; i<10; i++) {
        aleatorio(v, 9);
        listar_vector(v, 9);
        a = sumaSubMax1(v, 9);
        b = sumaSubMax2(v, 9);
        printf("%15d%15d\n", a, b);
    }

}


int main() {
    inicializar_semilla();
    test1();
    test2();
    tiempoEjecucion1();
    tiempoEjecucion1();
    tiempoEjecucion1();
    tiempoEjecucion1();
    tiempoEjecucion2();
    tiempoEjecucion2();
    tiempoEjecucion2();
    tiempoEjecucion2();
    return 0;
}





