#include <jogo.h>
#include <input.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> 
#include "cobra.h"
#include "fruta.h"

#define MAX_SEGMENTOS 1000
#define TAM_SEGMENTO 10
#define largura_janela 640
#define altura_janela 480

typedef struct {
    int placar;
    char motivo[50];
} game_feedback;

void placarFinal(char *apelido, int placar, char *motivo) {     /* MOSTRANDO APELIDO, MOTIVO DO FIM DE JOGO E PNTUAÇAO*/
    toca_som("assets/fim.wav");
    while (janela_esta_aberta()) {
        desenha_imagem(320, 240, "assets/fundo.png");
        cor(PRETO);
        desenha_linha(0, 120, largura_janela, 120);
        fonte("assets/ubuntu.ttf", 40);
        desenha_texto(20, 85, "%s", motivo);
        fonte("assets/ubuntu.ttf", 20);
            
        fonte("assets/ubuntu.ttf", 30);
        desenha_texto(200, 230, "Apelido: %s", apelido);
        fonte("assets/ubuntu.ttf", 30);
        desenha_texto(300, 270, "Score: %d", placar);
        fonte("assets/ubuntu.ttf", 30);
        desenha_texto(150, 350, "Aperte ENTER para continuar.");
            if (tecla_acabou_de_ser_apertada(ENTER) || tecla_acabou_de_ser_apertada(ESC)) return;
    }

}

                                                    /* MENU DO JOGO */
int menu() {
    while (janela_esta_aberta()) {
        desenha_imagem(320, 240, "assets/fundo.png");
        cor(PRETO);
        desenha_linha(0, 120, largura_janela, 120);
        fonte("assets/ubuntu.ttf", 70);
        desenha_texto(215, 85, " Snake");
        fonte("assets/ubuntu.ttf", 20);

                                                         /*ESCOLHENDO A VELOCIDADE DA COBRINHA*/
        fonte("assets/ubuntu.ttf", 30);
        desenha_texto(170, 230, "Escolha um modo de jogo:");
        fonte("assets/ubuntu.ttf", 30);
        desenha_texto(60, 340, "EASY (F1)");
        desenha_texto(240, 340, "MEDIUM (F2)");
        desenha_texto((largura_janela - 180), 340, "HARD (F3)");
        
        if(tecla_acabou_de_ser_apertada(F1)){
        return 50000000;
        }
        
        if(tecla_acabou_de_ser_apertada(F2)){
        return 30000000;
        }
    
        if(tecla_acabou_de_ser_apertada(F3)){
        return 10000000;
        }

        if (tecla_acabou_de_ser_apertada(ESC)) {
            janela_deve_fechar();
            exit(0);
        }
    }
}

game_feedback game(int dificulty) {                               /* JOGO COMEÇA COM A VELOCIDADE ESCOLHIDA */
    Cobra *cobra = cria_cobra();
    Fruta *fruta = cria_fruta();
    game_feedback retorno;
    retorno.placar = -1;
    retorno.motivo[0] = 0;

    while (janela_esta_aberta()) {                                  
        int segmento_segmento = 0;      
        int cobra_saiu = 0;

        desenha_imagem(320, 240, "assets/fundo.png");
        atualiza_cobra(cobra);
        desenha_cobra(cobra);
        fonte("assets/ubuntu.ttf", 30);
        cor(PRETO);
        desenha_texto(20, 35, "Score: %d", (cobra->tamanho - 1));               /* CONTAGEM DO SCORE */

        if(fruta->x == -1 && fruta->y == -1){                   
            atualiza_fruta(fruta, largura_janela, altura_janela);
        }
        cor(VERMELHO);
        desenha_retangulo(fruta->x, fruta->y, fruta->tamanho, fruta->tamanho);              /* DESENHANDO A FRUTA*/

                                                                                    /* TRATANDO O MOVIMENTO DA COBRA */
        if (tecla_acabou_de_ser_apertada(CIMA) && cobra->direcao != BAIXO) cobra->direcao = CIMA;                                 /* TRATAMENTO PRA COBRA */
        if (tecla_acabou_de_ser_apertada(BAIXO) && cobra->direcao != CIMA) cobra->direcao = BAIXO;
        if (tecla_acabou_de_ser_apertada(ESQUERDA) && cobra->direcao != DIREITA) cobra->direcao = ESQUERDA;
        if (tecla_acabou_de_ser_apertada(DIREITA) && cobra->direcao != ESQUERDA) cobra->direcao = DIREITA;
            
        int i = 0;
        while(i < (dificulty)){                                         /* VELOCIDADE DA COBRA */
            i++;
        }

        for(int j = 4; j < 100; j++){                    /* COBRA BATEU NELA MESMA */     /* FIM DE JOGO */   
            if(cobra->segmentos[0].x == cobra->segmentos[j].x && cobra->segmentos[0].y == cobra->segmentos[j].y){
                retorno.placar = cobra->tamanho - 1;
                strcpy(retorno.motivo, "Colisao com o proprio corpo");
                free(cobra);
                return retorno;      
            }
        }
                                                     /* COBRA PASSOU O LIMITE DA TELA */      /* FIM DE JOGO */ 
        if(cobra->segmentos[0].x > largura_janela || cobra->segmentos[0].y > altura_janela || cobra->segmentos[0].x < 0 || cobra->segmentos[0].y < 0){
            retorno.placar = cobra->tamanho - 1;
            strcpy(retorno.motivo, "Fugiu pelas laterias");
            free(cobra);                                
            return retorno;            
        }

        if(cobra->segmentos[0].x == fruta->x && cobra->segmentos[0].y == fruta->y){
            cobra->tamanho++;
            toca_som("assets/jump.wav");
            if ((cobra->tamanho -1) < MAX_SEGMENTOS) {
                atualiza_fruta(fruta, largura_janela, altura_janela);       /* GERANDO FRUTA QUANDO A COBRA COME */
            } else {
                retorno.placar = cobra->tamanho - 1;
                strcpy(retorno.motivo, "Fim de Jogo, Zerou");               /* ZERANDO O JOGO */
                free(cobra);
                return retorno;
            }
        }


        if (tecla_acabou_de_ser_apertada(ESC)) {
            return retorno;
        }
           
    }
}

int main() {
    char apelido[50];
    printf("Digite seu apelido: ");
    scanf("%s", apelido);

    abre_janela(largura_janela, altura_janela);
    toca_som_em_loop("assets/awesomeness.wav");
    double fator_zoom = 1;

    while (true) {                         // A DIFICULDADE TA RECEBNDO O MENU DO JOGO PARA SER PASSADO
        int dificulty = menu();            // COMO PARAMETRO QUANDO O JOGO COMECA NA FUNCAO GAME
        game_feedback game_response = game(dificulty);
        desenha_texto(215, 85, "%d", game_response.placar);
        if (game_response.placar >= 0) {            // PARA O JOGO E MOSTRA O PLACAR QUANDO O JOGO ACABA
            placarFinal(apelido, game_response.placar, game_response.motivo);

        }
    }
}