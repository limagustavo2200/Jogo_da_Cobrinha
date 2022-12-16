#ifndef _COBRA_H
#define _COBRA_H

#define MAX_SEGMENTOS 1000
#define TAM_SEGMENTO 10


typedef struct {
    int x;
    int y;
} Segmento;


typedef struct {
    Segmento segmentos[MAX_SEGMENTOS];
    int direcao;
    int tamanho;
} Cobra;


Cobra *cria_cobra();

void atualiza_cobra(Cobra *cobra);

void desenha_cobra(Cobra *cobra);

#endif