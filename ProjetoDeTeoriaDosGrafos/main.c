//
//  main.c
//  ProjetoDeTeoriaDosGrafos
//
//  Created by Rodrigo Soldi Lopes on 25/05/16.
//  Copyright © 2016 Rodrigo Soldi Lopes. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void removeColumn(int, int, int, int **);
void allocAll(int, int, int **, int **, int *);
void prim(int *, int, int, int **, int **);
int count(int *, int);

//int *franjas;
//int **matrixU;
//int **matrixFinal;
//int countRows = 8;
int countTeste = 0;
//int countColumns = 8;

int main(int argc, char **argv){
    
    int i;
    int j;
    int countRows       = 8;
    int countColumns    = 8;
    int countVertices;
    int countArestas;
    int *franjas;
    int ** matrixU;
    int **matrixFinal;
    
    // ======= ALOCAÇÃO ========
    
    int *tamanhoLinha = malloc(countRows * countColumns * sizeof(int));
    
    // Tamanho MatrixU
    matrixU = malloc(countRows * sizeof(int *));
    
    int x;
    for (x = 0; x < countRows; x++)
        matrixU[x] = tamanhoLinha + x * countColumns;
    
    int v, w;
    for(v = 0; v < countRows; v++)
        for(w = 0; w < countColumns; w++)
            matrixU[v][w] = -1;
    
    int *tamanhoLinha2 = malloc(countRows * countColumns * sizeof(int));
    
    matrixFinal = malloc(countRows * sizeof(int *));
    
    for (x = 0; x < countRows; x++)
        matrixFinal[x] = tamanhoLinha2 + x * countColumns;
    
    for(v = 0; v < countRows; v++)
        for(w = 0; w < countColumns; w++)
            matrixFinal[v][w] = -1;
    
    
    franjas = malloc(countRows * sizeof(int));
    
    // =========================
    
    printf("Digite o numero de vertices e arestas (exemplo: 1 2)   :   ");
    scanf("%d %d",&countVertices, &countArestas);
    printf("\n");
    
    
    countRows = countColumns = countVertices;
    
    //Preenchendo a matriz com -1
    for(i = 0; i < countRows; i++)
        for(j = 0; j < countColumns; j++)
            matrixU[i][j] = -1;
    
    for(i = 0; i < countArestas; i++){
        
        int v1;
        int v2;
        int custo;
        
        printf("Digite o vertice 1 o vertice 2 e o custo (exemplo: 1 2 10)   :   ");
        scanf("%d %d %d",&v1, &v2, &custo);
        
        int vertice1 = v1 - 1;
        int vertice2 = v2 - 1;
        
        matrixU[vertice1][vertice2] = custo;
        matrixU[vertice2][vertice1] = custo;
    }
    
    //"Apagando" todas as franjas
    for(i = 0; i < countRows; i++)
        franjas[i] = -1;
    
    //Escolhendo o vertice zero como primeira franja
    franjas[0] = 0;
    
    //Removendo a coluna zero
    removeColumn(0, 0, countRows, matrixU);
    
    for(i = 0; i < countRows - 1; i++)
        prim(franjas, countColumns, countRows, matrixU, matrixFinal);
    
    printf("\n====== RESULTADO FINAL ======\n\n");
    
    printf("Teste %d\n", ++countTeste);
    
    for(i = 0; i < countRows; i++)
        for(j = 0; j < countColumns; j++)
            if (matrixFinal[i][j] != -1)
                printf("%d %d\n", i+1, j+1);
    
    printf("\n=============================\n\n");
    
    main(argc, argv);
    
    return 0;
}

void removeColumn(int remover, int conservar, int countRows, int **matrix){
    int i = 0;
    
    for(i = 0; i < countRows; i++)
        if(i != conservar)
            matrix[i][remover] = -1;
}

void prim(int *franjas, int countColumns, int countRows, int **matrix, int **matrixFinal){
    int i = 0, j = 0;
    int menor = INT_MAX;
    int countFranjas = count(franjas, countRows);
    int currentLine = 0;
    int column = 0;
    int line = 0;
    
    for(i = 0;i < countFranjas; i++){
        currentLine = franjas[i];
        
        for(j = 0; j < countColumns; j++){
            
            if(matrix[currentLine][j] != -1 && matrix[currentLine][j] < menor){
                menor = matrix[currentLine][j];
                column = j;
                line = currentLine;
            }
        }
    }
    
    matrix[line][column] = -1;
    matrix[column][line] = -1;
    
    matrixFinal[line][column] = menor;
    franjas[countFranjas] = column;
    
    removeColumn(column, line, countRows, matrix);
}

int count(int *array, int count){
    int i = 0, countArray = 0;
    
    for(i = 0; i < count; i++)
        if(array[i] != -1)
            countArray++;
    
    return countArray;
}