/*Nombres:
 * Brais Gonzalez Piñeiro brais.gonzalezp
 * Armando Martínez Noya  a.mnoya
 * Raul Fernández del Blanco r.delblanco
 * Grupo 2.4
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/time.h>
#include<math.h>
#include <limits.h>
#define TAM_MAX 1600
#define N 7
#define K 1000 //si empieza 5 demasiadas repeticiones

typedef int ** matriz;

typedef struct{
    int x, y, peso;
}arista;

typedef arista tipo_elemento;

typedef struct{
    int cabeza, final, tamano;
    tipo_elemento vector[TAM_MAX];
} cola;

double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla(){
    srand(time(NULL));
}

void crear_cola(cola *c){
    c->cabeza = 0;
    c->final = -1;
    c->tamano = 0;
}

int cola_vacia(cola c){
    return (c.tamano == 0);
}

void incrementar(int *x){
    if (++(*x) == TAM_MAX)
        *x = 0;
}

void insertar(tipo_elemento a, cola *c){
    if (c->tamano == TAM_MAX){
        printf("error: colca llena: %d\n",c->tamano);
        exit(EXIT_FAILURE);
    }
    c->tamano++;
    incrementar(&(c->final));
    c->vector[c->final] = a;

}

tipo_elemento quitar_primero(cola *c){
    tipo_elemento x;
    if (cola_vacia(*c)){
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    c->tamano--;
    x = c->vector[c->cabeza];
    incrementar(&(c->cabeza));
    return x;
}

tipo_elemento primero(cola c){
    if (cola_vacia(c)){
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    return (c.vector[c.cabeza]);
}

void mostrar_cola(cola c){
    int i;

    if (cola_vacia(c)){
        printf("error: cola vacia\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < c.tamano; i++)
        printf("(%d,%d) ",c.vector[c.cabeza+i].x,
               c.vector[c.cabeza+i].y);
    printf("\n");
}

void prim(matriz m, int nodos, cola *aristas){//prim2
    int min, i, j, k=0, x=0;
    arista a;
    int *masProximo = (int *) malloc(nodos*sizeof(int));
    int *distanciaMinima = (int *) malloc(nodos*sizeof(int));

    crear_cola(aristas);
    distanciaMinima[0] = -1;
    for(i = 1; i < nodos; i++) {
        masProximo[i] = 0;
        distanciaMinima[i] = m[i][0];
    }
    while (x < nodos-1){
        min = INT_MAX;
        for (j = 1; j < nodos; j++){
            if ((distanciaMinima[j] >= 0) &&
                (distanciaMinima[j] < min)){
                min = distanciaMinima[j];
                k = j;
            }
        }
        a.x = masProximo[k];
        a.y = k;
        a.peso = min;
        insertar(a,aristas);
        distanciaMinima[k] = -1;
        for (j = 1; j < nodos; j++){
            if (m[j][k] < distanciaMinima[j]){
                distanciaMinima[j] = m[j][k];
                masProximo[j] = k;
            }
        }
        x++;
    }
    free(masProximo);
    free(distanciaMinima);
}

matriz crear_matriz(int n){
    int i;
    matriz aux;

    if ((aux = malloc(n*sizeof(int *))) == NULL)
        return NULL;
    for (i=0; i<n; i++)
        if ((aux[i] = malloc(n*sizeof(int))) == NULL)
            return NULL;
    return aux;
}

/* Crea un grafo completo no dirigido con valores aleatorios entre 1 y n */
void inicializar_matriz(matriz m, int n){
    int i, j;

    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
            m[i][j] = rand() % n + 1;

    for (i=0; i<n; i++)
        for (j=0; j<=i; j++)
            if (i==j)
                m[i][j] = 0;
            else
                m[i][j] = m[j][i];
}

void liberar_matriz(matriz m, int n){
    int i;

    for (i=0; i<n; i++)
        free(m[i]);
    free(m);
}

void copiaMatriz(matriz m, int g[N][N], int tam){
    int i,j;

    for (i = 0; i < tam; i++)
        for (j = 0; j < tam; j++)
            m[i][j] = g[i][j];
}

void muestraMatriz(matriz m, int tam){
    int i,j;

    for (i = 0; i < tam; i++){
        printf("\n");
        for (j = 0; j < tam; j++)
            printf(" %2d ",m[i][j]);
    }
    printf("\n");
}

int sumPesos(cola c){
    int i, p = 0;

    if (cola_vacia(c)){
        p = 0;
    }else{
        for (i = 0; i < c.tamano; i++)
            p = p + c.vector[c.cabeza+i].peso;
    }
    return p;
}

void usarPrim(matriz m, int tam){
    cola c;

    crear_cola(&c);
    prim(m,tam,&c);
    printf("\tAristas:\t");
    mostrar_cola(c);
    printf("\tPeso:\t\t%d\n",sumPesos(c));

}

void test(){
    int grafo1[N][N] = {
            {0,1,8,4,7}, {1,0,2,6,5}, {8,2,0,9,5}, {4,6,9,0,3}, {7,5,5,3,0}
    };
    int grafo2[N][N] = {
            {0,1,4,7}, {1,0,2,8}, {4,2,0,3}, {7,8,3,0}
    };
    int grafo3[N][N] = {
            {0,7,99,5,99,99,99}, {7,0,8,9,7,99,99}, {99,8,0,99,5,99,99},
            {5,9,99,0,15,6,99}, {99,7,5,15,0,8,9}, {99,99,99,6,8,0,11},
            {99,99,99,99,9,11,0}
    };
    matriz m1 = crear_matriz(5);
    matriz m2 = crear_matriz(4);
    matriz m3 = crear_matriz(7);

    copiaMatriz(m1,grafo1,5);
    copiaMatriz(m2,grafo2,4);
    copiaMatriz(m3,grafo3,7);

    printf("Grafo1\n");
    muestraMatriz(m1,5);
    usarPrim(m1,5);

    printf("Grafo2\n");
    muestraMatriz(m2,4);
    usarPrim(m2,4);

    printf("Grafo3\n");
    muestraMatriz(m3,7);
    usarPrim(m3,7);

    liberar_matriz(m1,5);
    liberar_matriz(m2,4);
    liberar_matriz(m3,7);
}

void tiempos(){
    double t, t1, t2, ta, tb, x, y, z, y1;
    int n, i; char ct; cola c; matriz m;

    printf("\t********************PRIM********************\n");
    printf("%5s%17s%15s%15s%15s%16s\n",
           "n","t(n)","t(n)/f(n)","t(n)/g(n)","t(n)/h(n)","t(n)/g(n)**");
    for (n = 10; n <= 640; n *=2){
        ct = ' ';
        m = crear_matriz(n);
        inicializar_matriz(m,n);
        crear_cola(&c);
        t1 = microsegundos();
        prim(m,n,&c);
        t2 = microsegundos();
        t = (t2 - t1);
        if (t < 500){
            ct = '*';
            t1 = microsegundos();
            for (i = 0 ; i < K; i++){
                crear_cola(&c);
                prim(m,n,&c);
            }
            t2 = microsegundos();
            ta = (t2 - t1); //tiempo crear_cola+prim
            t1 = microsegundos();
            for (i = 0; i < K; i++)
                crear_cola(&c);
            t2 = microsegundos();
            tb = (t2 - t1); // tiempo crear_cola
            t = (ta - tb)/K;
        }
        x = t / pow(n,1.5);
        y = t / pow(n,2); //teorica
        y1 = t / pow(n,2.08); //ajustar bien
        z = t / pow(n,2.8);
        printf("%5d%c%15.3f%15.4f%15.5f%15.7f%15.5f\n"
                ,n,ct,t,x,y,z,y1);
        liberar_matriz(m,n);
    }
}

/*****************************************************************************/
int main(){

    inicializar_semilla();
    test();
    printf("\n");
    tiempos();
    tiempos();

    return 0;
}
