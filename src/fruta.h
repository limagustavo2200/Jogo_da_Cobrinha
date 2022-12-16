#ifndef _FRUTA_H
#define _FRUTA_H

typedef struct {
    int x;
    int y;
    int tamanho;
} Fruta;

void atualiza_fruta(Fruta *fruta, int largura_janela, int altura_janela);
Fruta* cria_fruta();

#endif