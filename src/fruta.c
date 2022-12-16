#include <stdio.h>
#include <stdlib.h>
#include "fruta.h"
#include "cobra.h"

void atualiza_fruta(Fruta *fruta, int largura_janela, int altura_janela) {                              /* GERANDO A POSICAO DA FRUTA RANDOMICAMENTE PRA X E Y */                         
    int x_fruta = rand() % (largura_janela - fruta->tamanho);
    fruta->x = x_fruta - (x_fruta % fruta->tamanho);
    int y_fruta = rand() % (altura_janela - fruta->tamanho);
    fruta->y = y_fruta - (y_fruta % fruta->tamanho);
}

Fruta* cria_fruta() {
    Fruta *new = (Fruta*)malloc(sizeof(Fruta));
    new->tamanho = TAM_SEGMENTO;
    new->x = -1;
    new->y = -1;
    return new;
}