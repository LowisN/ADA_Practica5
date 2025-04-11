#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Prototipos de funciones
int** crear_matriz(int n);
void liberar_matriz(int** matriz, int n);
void llenar_aleatorio(int** matriz, int n);
void multiplicar_tradicional(int** A, int** B, int** C, int n);
void divide_y_venceras(int** A, int** B, int** C, int n);
void strassen(int** A, int** B, int** C, int n);
void imprimir_matriz(int** matriz, int n);

// Crear matriz
int** crear_matriz(int n) {
    int** matriz = (int**)malloc(n * sizeof(int*));// Reservar memoria para filas
    for (int i = 0; i < n; i++) {
        matriz[i] = (int*)malloc(n * sizeof(int));// Reservar memoria para columnas
    }
    return matriz;
}

// Liberar matriz
void liberar_matriz(int** matriz, int n) {//como se uso malloc, se usa free
    for (int i = 0; i < n; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

// Llenar matriz con valores aleatorios
void llenar_aleatorio(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matriz[i][j] = rand() % 10;
        }
    }
}

// Multiplicacion tradicional de matrices
void multiplicar_tradicional(int** A, int** B, int** C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = 0;
            for (int k = 0; k < n; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

// Funciones auxiliares para Divide y Venceras
void crear_submatrices_dyv(int*** A11, int*** A12, int*** A21, int*** A22,
                          int*** B11, int*** B12, int*** B21, int*** B22,
                          int*** C11, int*** C12, int*** C21, int*** C22,
                          int nuevo_tam) {
    *A11 = crear_matriz(nuevo_tam);
    *A12 = crear_matriz(nuevo_tam);
    *A21 = crear_matriz(nuevo_tam);
    *A22 = crear_matriz(nuevo_tam);
    *B11 = crear_matriz(nuevo_tam);
    *B12 = crear_matriz(nuevo_tam);
    *B21 = crear_matriz(nuevo_tam);
    *B22 = crear_matriz(nuevo_tam);
    *C11 = crear_matriz(nuevo_tam);
    *C12 = crear_matriz(nuevo_tam);
    *C21 = crear_matriz(nuevo_tam);
    *C22 = crear_matriz(nuevo_tam);
}

void liberar_submatrices_dyv(int** A11, int** A12, int** A21, int** A22,
                            int** B11, int** B12, int** B21, int** B22,
                            int** C11, int** C12, int** C21, int** C22,
                            int nuevo_tam) {
    liberar_matriz(A11, nuevo_tam);
    liberar_matriz(A12, nuevo_tam);
    liberar_matriz(A21, nuevo_tam);
    liberar_matriz(A22, nuevo_tam);
    liberar_matriz(B11, nuevo_tam);
    liberar_matriz(B12, nuevo_tam);
    liberar_matriz(B21, nuevo_tam);
    liberar_matriz(B22, nuevo_tam);
    liberar_matriz(C11, nuevo_tam);
    liberar_matriz(C12, nuevo_tam);
    liberar_matriz(C21, nuevo_tam);
    liberar_matriz(C22, nuevo_tam);
}

// Funciones auxiliares para Strassen
void crear_submatrices_strassen(int*** A11, int*** A12, int*** A21, int*** A22,
                               int*** B11, int*** B12, int*** B21, int*** B22,
                               int*** P1, int*** P2, int*** P3, int*** P4,
                               int*** P5, int*** P6, int*** P7,
                               int nuevo_tam) {
    *A11 = crear_matriz(nuevo_tam);
    *A12 = crear_matriz(nuevo_tam);
    *A21 = crear_matriz(nuevo_tam);
    *A22 = crear_matriz(nuevo_tam);
    *B11 = crear_matriz(nuevo_tam);
    *B12 = crear_matriz(nuevo_tam);
    *B21 = crear_matriz(nuevo_tam);
    *B22 = crear_matriz(nuevo_tam);
    *P1 = crear_matriz(nuevo_tam);
    *P2 = crear_matriz(nuevo_tam);
    *P3 = crear_matriz(nuevo_tam);
    *P4 = crear_matriz(nuevo_tam);
    *P5 = crear_matriz(nuevo_tam);
    *P6 = crear_matriz(nuevo_tam);
    *P7 = crear_matriz(nuevo_tam);
}

void liberar_submatrices_strassen(int** A11, int** A12, int** A21, int** A22,
                                 int** B11, int** B12, int** B21, int** B22,
                                 int** P1, int** P2, int** P3, int** P4,
                                 int** P5, int** P6, int** P7,
                                 int nuevo_tam) {
    liberar_matriz(A11, nuevo_tam);
    liberar_matriz(A12, nuevo_tam);
    liberar_matriz(A21, nuevo_tam);
    liberar_matriz(A22, nuevo_tam);
    liberar_matriz(B11, nuevo_tam);
    liberar_matriz(B12, nuevo_tam);
    liberar_matriz(B21, nuevo_tam);
    liberar_matriz(B22, nuevo_tam);
    liberar_matriz(P1, nuevo_tam);
    liberar_matriz(P2, nuevo_tam);
    liberar_matriz(P3, nuevo_tam);
    liberar_matriz(P4, nuevo_tam);
    liberar_matriz(P5, nuevo_tam);
    liberar_matriz(P6, nuevo_tam);
    liberar_matriz(P7, nuevo_tam);
}

// Multiplicacion por division y conquista
void divide_y_venceras(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int nuevo_tam = n/2;
    int **A11, **A12, **A21, **A22, **B11, **B12, **B21, **B22;
    int **C11, **C12, **C21, **C22;
    int **T1, **T2;  // Matrices temporales para almacenar resultados parciales

    crear_submatrices_dyv(&A11, &A12, &A21, &A22,
                         &B11, &B12, &B21, &B22,
                         &C11, &C12, &C21, &C22,
                         nuevo_tam);
    
    T1 = crear_matriz(nuevo_tam);
    T2 = crear_matriz(nuevo_tam);

    // Dividir matrices
    for (int i = 0; i < nuevo_tam; i++) {
        for (int j = 0; j < nuevo_tam; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + nuevo_tam];
            A21[i][j] = A[i + nuevo_tam][j];
            A22[i][j] = A[i + nuevo_tam][j + nuevo_tam];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + nuevo_tam];
            B21[i][j] = B[i + nuevo_tam][j];
            B22[i][j] = B[i + nuevo_tam][j + nuevo_tam];
        }
    }

    // C11 = A11*B11 + A12*B21
    divide_y_venceras(A11, B11, T1, nuevo_tam);
    divide_y_venceras(A12, B21, T2, nuevo_tam);
    for(int i = 0; i < nuevo_tam; i++)
        for(int j = 0; j < nuevo_tam; j++)
            C11[i][j] = T1[i][j] + T2[i][j];

    // C12 = A11*B12 + A12*B22
    divide_y_venceras(A11, B12, T1, nuevo_tam);
    divide_y_venceras(A12, B22, T2, nuevo_tam);
    for(int i = 0; i < nuevo_tam; i++)
        for(int j = 0; j < nuevo_tam; j++)
            C12[i][j] = T1[i][j] + T2[i][j];

    // C21 = A21*B11 + A22*B21
    divide_y_venceras(A21, B11, T1, nuevo_tam);
    divide_y_venceras(A22, B21, T2, nuevo_tam);
    for(int i = 0; i < nuevo_tam; i++)
        for(int j = 0; j < nuevo_tam; j++)
            C21[i][j] = T1[i][j] + T2[i][j];

    // C22 = A21*B12 + A22*B22
    divide_y_venceras(A21, B12, T1, nuevo_tam);
    divide_y_venceras(A22, B22, T2, nuevo_tam);
    for(int i = 0; i < nuevo_tam; i++)
        for(int j = 0; j < nuevo_tam; j++)
            C22[i][j] = T1[i][j] + T2[i][j];

    // Combinar resultados
    for (int i = 0; i < nuevo_tam; i++) {
        for (int j = 0; j < nuevo_tam; j++) {
            C[i][j] = C11[i][j];
            C[i][j + nuevo_tam] = C12[i][j];
            C[i + nuevo_tam][j] = C21[i][j];
            C[i + nuevo_tam][j + nuevo_tam] = C22[i][j];
        }
    }

    liberar_matriz(T1, nuevo_tam);
    liberar_matriz(T2, nuevo_tam);
    liberar_submatrices_dyv(A11, A12, A21, A22,
                           B11, B12, B21, B22,
                           C11, C12, C21, C22,
                           nuevo_tam);
}

// Metodo de Strassen
void strassen(int** A, int** B, int** C, int n) {
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int nuevo_tam = n/2;
    int **A11, **A12, **A21, **A22, **B11, **B12, **B21, **B22;
    int **P1, **P2, **P3, **P4, **P5, **P6, **P7;

    crear_submatrices_strassen(&A11, &A12, &A21, &A22,
                              &B11, &B12, &B21, &B22,
                              &P1, &P2, &P3, &P4, &P5, &P6, &P7,
                              nuevo_tam);

    // Dividir matrices de entrada
    for (int i = 0; i < nuevo_tam; i++) {
        for (int j = 0; j < nuevo_tam; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + nuevo_tam];
            A21[i][j] = A[i + nuevo_tam][j];
            A22[i][j] = A[i + nuevo_tam][j + nuevo_tam];
            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + nuevo_tam];
            B21[i][j] = B[i + nuevo_tam][j];
            B22[i][j] = B[i + nuevo_tam][j + nuevo_tam];
        }
    }

    // Calcular P1 a P7
    strassen(A11, B12, P1, nuevo_tam);
    strassen(A12, B22, P2, nuevo_tam);
    strassen(A21, B11, P3, nuevo_tam);
    strassen(A22, B21, P4, nuevo_tam);
    strassen(A11, B11, P5, nuevo_tam);
    strassen(A12, B21, P6, nuevo_tam);
    strassen(A21, B12, P7, nuevo_tam);

    // Calcular C11, C12, C21, C22
    for (int i = 0; i < nuevo_tam; i++) {
        for (int j = 0; j < nuevo_tam; j++) {
            C[i][j] = P5[i][j] + P4[i][j] - P2[i][j] + P6[i][j];
            C[i][j + nuevo_tam] = P1[i][j] + P2[i][j];
            C[i + nuevo_tam][j] = P3[i][j] + P4[i][j];
            C[i + nuevo_tam][j + nuevo_tam] = P5[i][j] + P1[i][j] - P3[i][j] - P7[i][j];
        }
    }

    liberar_submatrices_strassen(A11, A12, A21, A22,
                                B11, B12, B21, B22,
                                P1, P2, P3, P4, P5, P6, P7,
                                nuevo_tam);
}

// Imprimir matriz
void imprimir_matriz(int** matriz, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n;
    clock_t inicio, fin;
    double tiempo_cpu;

    printf("Ingrese el tamano de la matriz (debe ser potencia de 2): ");
    scanf("%d", &n);

    if (n & (n - 1)) {
        printf("Error: El tamano de la matriz debe ser potencia de 2\n");
        return 1;
    }

    int** A = crear_matriz(n);
    int** B = crear_matriz(n);
    int** C = crear_matriz(n);

    llenar_aleatorio(A, n);
    llenar_aleatorio(B, n);

    inicio = clock();
    multiplicar_tradicional(A, B, C, n);
    fin = clock();
    tiempo_cpu = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
    printf("\nTiempo metodo tradicional: %f segundos\n", tiempo_cpu);

    inicio = clock();
    divide_y_venceras(A, B, C, n);
    fin = clock();
    tiempo_cpu = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo divide y venceras: %f segundos\n", tiempo_cpu);

    inicio = clock();
    strassen(A, B, C, n);
    fin = clock();
    tiempo_cpu = ((double) (fin - inicio)) / CLOCKS_PER_SEC;
    printf("Tiempo metodo de Strassen: %f segundos\n", tiempo_cpu);

    liberar_matriz(A, n);
    liberar_matriz(B, n);
    liberar_matriz(C, n);

    return 0;
}
