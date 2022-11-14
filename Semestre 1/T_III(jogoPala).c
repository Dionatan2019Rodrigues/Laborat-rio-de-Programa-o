/** Dionatan Rodrigues **/
#include "tela.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef struct{
  float x;
  float y;
  float vx;
  float vy;
  char palaum[24];
  bool espera;
  bool caindo;
  bool selecionada;
  bool sumiu;
  bool morta;
} palavra_t;

typedef struct{
  palavra_t pal_moveis[50];
  int min_x;
  int min_y;
  int max_x;
  int max_y;
  int lim_lancamento;
  int score;
  int vida;
  bool fim;
  int nivel;
  int selecao;
} game_t;

int placar[5]={0,0,0,0,0};

void inicializa_jogo(game_t *g);
void desenha_tela(game_t *g);
void move_palavras(game_t *g);
void verifica_entradas(game_t *g);

int main()
{  
    game_t g; 
    bool flag=true;
    inicializa_jogo(&g);

    tela_inicio(500,500,"game");
    while(flag){ //TELA INICIO DO JOGO
        tela_texto(250, 200, 40, branco, "JOGO DE PALAVRAS");
        tela_texto(250, 300, 20, branco, "Divirta-se, hoje é dia de RECORD");
        tela_texto(250, 340, 20, branco, "Pressione qualquer tecla para jogar");
        tela_retangulo(30, 30, 470, 470, 5, azul, transparente);
        tela_atualiza();
        if (tela_tecla() !='\0') {
            flag = false;
        }
    }
    FILE *arq;
    arq = fopen("score", "r");
    if (arq != NULL) {//INICIALIZA O SCORE
      for (int p=0; p<5; p++) {
        fscanf(arq, "%d", &placar[p]);
      }
    } 
   
    while (!g.fim) {//TELA JOGO
        
        desenha_tela(&g);
        move_palavras(&g);
        verifica_entradas(&g);

    } 
    char txt[4]; sprintf(txt, "%d", placar[0]); 
    char txt1[4]; sprintf(txt1, "%d", placar[1]); 
    char txt2[4]; sprintf(txt2, "%d", placar[2]); 
    char txt3[4]; sprintf(txt3, "%d", placar[3]);
    char txt4[5]; sprintf(txt4, "%d", placar[4]);
    flag=true;
    while(flag){ //TELA FIM DO JOGO
        tela_texto(250, 200, 40, branco, "GAME OVER");
        tela_retangulo(30, 30, 470, 470, 5, azul, transparente);
        tela_texto(250, 230, 20, branco, "Pressione qualquer tecla para sair");
        // desenha um círculo na posição do mouse
        tela_circulo(tela_rato_x(), tela_rato_y(), 7, 1.5, branco, vermelho);
        tela_texto(220, 270, 20, branco, "(1º)");
        tela_texto(260, 270, 20, branco, txt);
        tela_texto(220, 290, 20, branco, "(2º)");
        tela_texto(260, 290, 20, branco, txt1);
        tela_texto(220, 310, 20, branco, "(3º)");
        tela_texto(260, 310, 20, branco, txt2);
        tela_texto(220, 330, 20, branco, "(4º)");
        tela_texto(260, 330, 20, branco, txt3);
        tela_texto(220, 350, 20, branco, "(5º)");
        tela_texto(260, 350, 20, branco, txt4);
        if (tela_tecla() !='\0') {
            flag = false;
        } 
        tela_atualiza();
    }
    tela_fim();
    return 0;
}
//AUXILIARES
int aleat_entre(int m, int M){
  return rand()%(M-m+1)+m;
}
//INICIALIZA O JOGO
void inicializa_jogo(game_t *g){

  // inicializa os limites de movimento
  g->min_x = 50;
  g->max_x = 450;
  g->min_y = 50;
  g->max_y = 400;
  g->lim_lancamento = 120;
  g->vida = 6;
  g->nivel = 1;
  g->score = 0;
  g->selecao=-1;

  FILE *arq;
  arq = fopen("palaum", "r");
  for (int i=0; i<49; i++) {
    palavra_t *p = &(g->pal_moveis[i]);
    p->x =  aleat_entre(70,430);
    p->y = aleat_entre(60,100);
    p->vx = aleat_entre(-40,40);
    p->vy = aleat_entre(-40,40);
    p->espera = true;
    p->selecionada = false;
    p->caindo = false;
    p->sumiu = false;
    p->morta = false;
    fscanf(arq, "%s", p->palaum);

  }
  fclose(arq);

  // o programa ainda nao termimou
  g->fim = false;
}
//DESENHA
void desenha_palavra(palavra_t p){
    if ((p.y < 400)&&(p.caindo==true)) tela_texto(p.x, p.y, 15, branco, p.palaum);
    if ((p.y < 400)&&(p.selecionada==true)) tela_texto(p.x, p.y, 15, amarelo, p.palaum);
}
void desenha_tela(game_t *g){
  // desenha o contorno da área de movimentação
  tela_retangulo(g->min_x, g->min_y, g->max_x, g->lim_lancamento, 3, azul, preto);
  tela_retangulo(g->min_x, g->lim_lancamento, g->max_x, g->max_y, 3, azul, preto);//regiao resto
  tela_retangulo(g->min_x, g->max_y, g->max_x, 450, 3, azul, preto); //REGIAo JOGADOR
  //AVISOS
  tela_texto_dir(10, 470, 15, branco, "PAUSE NA TECLA |ESPAÇO|");
  //Vida
  for(int i=0; i<g->vida;i++){
    tela_circulo(480-i*25, 25, 10, 1.5, branco, azul);
  } 
  //score
  char txt[10];
  sprintf(txt, "%d", g->score);
  tela_texto_dir(20, 20, 15, branco, txt);

  // desenha as palavras moveis
  for (int i=0; i<49; i++) {
    if((g->pal_moveis[i].caindo!=false)||((g->pal_moveis[i].selecionada!=false))){
      desenha_palavra(g->pal_moveis[i]);
    }
    
  }
  tela_atualiza();
}
//MOVIMENTO
void move_palavra(game_t *g, int i){

  //CADENCIA DE QUEDA DAS PALAVRAS
  switch(g->nivel){
      case 1:
        if(aleat_entre(0,10000)<5){
          g->pal_moveis[i].caindo=true;
          g->pal_moveis[i].espera=false;
        }
      case 2:
        if(aleat_entre(0,10000)<50){
          g->pal_moveis[i].caindo=true;
          g->pal_moveis[i].espera=false;
        }
      case 3:
        if(aleat_entre(0,10000)<100){
          g->pal_moveis[i].caindo=true;
          g->pal_moveis[i].espera=false;
        }
  }
  
  // faz um ponteiro apontar para a palavra a mover
  palavra_t *p = &(g->pal_moveis[i]);
  p->x += p->vx * SEGUNDOS_POR_QUADRO;
  p->y += p->vy * SEGUNDOS_POR_QUADRO;
  if (p->x < g->min_x && p->vx < 0) p->vx *= -1;
  if (p->x > g->max_x && p->vx > 0) p->vx *= -1;
  if (p->y < g->min_y && p->vy < 0) p->vy *= -1;  
  
  //PALAVRA MORTA
  if((g->pal_moveis[i].y>g->max_y)&&(g->pal_moveis[i].sumiu!=true)){
      g->pal_moveis[i].morta=true;
      g->pal_moveis[i].caindo=false;
      g->pal_moveis[i].selecionada=false;
      g->vida -= 1;
  }

  
}
void move_palavras(game_t *g){
  for (int i=0; i<aleat_entre(2,4); i++) {  
    move_palavra(g, aleat_entre(0,15));
  }
}
//ENTRADA DE DADOS
void verifica_entradas(game_t *g){
  char tecla = tela_tecla();
  for(int i=0; i<49;i++){
    if((g->pal_moveis[i].caindo==true)&&(tecla==g->pal_moveis[i].palaum[0])&&(g->selecao==-1)){ 
      g->pal_moveis[i].caindo=false;
      g->pal_moveis[i].selecionada=true;   
      g->selecao=i;
    }
    for(int i=0;i<49;i++){
      if((g->pal_moveis[i].selecionada)&&(tecla==g->pal_moveis[i].palaum[0])){
        for (int j=0; j<24 ; j++) {
          g->pal_moveis[i].palaum[j] = g->pal_moveis[i].palaum[j+1];
          g->score += 1;
        }
        if(g->pal_moveis[i].palaum[0]=='\0'){
          g->pal_moveis[i].selecionada=false;
          g->pal_moveis[i].sumiu=true;
          g->selecao=-1;
        }
      }
    }    
  }
  //PAUSE
  if(tecla==' '){
      bool flag =  true;
      while(flag){
        if(tecla==' '){
            flag=false;
        }
      }
  }
  //acaba o jogo caso vida chega a zero e atualiza o record de score
  if(g->vida<=0){
    FILE *arq;
    bool fg=true;
    arq = fopen("score", "w"); 
    for (int p=0; p<5; p++) {
      if((g->score > placar[p])&&(fg)){
        placar[p] = g->score;
        fg=false;
      }
      fprintf(arq, "%d\n", placar[p]);
    }
    fclose(arq);
    g->fim=true;
  }
}
