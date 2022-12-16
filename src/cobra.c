#include <jogo.h>
#include <input.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cobra.h"



Cobra *cria_cobra(){
    Cobra *cobra = (Cobra*)malloc(sizeof(Cobra));
    cobra->segmentos[0].x = 320;
    cobra->segmentos[0].y = 240;
    cobra->direcao = DIREITA;
    cobra->tamanho = 1;
    return cobra;
}



void atualiza_cobra(Cobra *cobra){
    Segmento nova_cabeca;
    int tamanho_cobra = cobra->tamanho;
    nova_cabeca.x = cobra->segmentos[0].x;
    nova_cabeca.y = cobra->segmentos[0].y;

    
    if(cobra->direcao == CIMA){
        nova_cabeca.y -= TAM_SEGMENTO;
    }

    if(cobra->direcao == BAIXO){
        nova_cabeca.y += TAM_SEGMENTO;   
    }

    if(cobra->direcao == DIREITA){
        nova_cabeca.x += TAM_SEGMENTO;      
    }
    
    if(cobra->direcao == ESQUERDA){
        nova_cabeca.x -= TAM_SEGMENTO;  
    }


    for(int i=tamanho_cobra-1; i>=0; i--){
        cobra->segmentos[i+1] = cobra->segmentos[i];
    }
    cobra->segmentos[0] = nova_cabeca;
}

void desenha_cobra(Cobra *cobra){
    for(int i=0; i < cobra->tamanho; i++){
        int x = cobra->segmentos[i].x;
        int y = cobra->segmentos[i].y;
        cor(MARROM_ESCURO);
        desenha_retangulo(x, y, TAM_SEGMENTO, TAM_SEGMENTO);
    }
}