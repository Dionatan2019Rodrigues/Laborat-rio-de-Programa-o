/**Dionatan Rodrigues**/
#include "tela.h"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int le_jogada(int i,int j,char mat[3][3]);
void atribuiMAT(int i, int j, int jogador,char mat[3][3]);
int detecta_fim(char mat[3][3]);
int realizapartida(int jogador);
int posicao_y(float y);
int posicao_x(float x);
bool novamente_sim(float x, float y);
bool novamente_nao(float x, float y);
void desenhaTAB(char mat[3][3],int jogador);

int main(){
    FILE *arq;
    int i,jogador,validacao=3,novamente=1,notini=0,ult=1;
    //INICIALIZANDO PLACAR 
    int placar[4] = {0,0,0,0};
    bool flag = true;
    arq = fopen("placar", "r");
      if (arq != NULL) {
       for (int p=0; p<4; p++) {
          fscanf(arq, "%d", &placar[p]);
       }
      }
    tela_inicio(500,500,"jogo");
    while(flag){
        tela_texto(250, 200, 40, branco, "JOGO DA VELHA");
        tela_texto(250, 300, 20, branco, "Uau que bom vê-los por aqui divirtam-se");
        tela_texto(250, 340, 20, branco, "Pressione qualquer tecla para jogar");
        // desenha um quadrado no contorno da janela
        tela_retangulo(30, 30, 470, 470, 5, amarelo, transparente);
        tela_atualiza();
        if (tela_tecla() !='\0') {
            flag = false;
        }
    }  
    while(novamente!=0){
        //JOGADOR ALEATORIO
        if(notini==0){
            srand(time(0));
            jogador = 1+(rand()%2);
            notini++;
        }
        //ULTIMO VENCEDOR
        if(validacao==1){
            jogador = 1;
            ult=2;
        }else if(validacao==2){
            jogador = 2;
            ult=1;
        }
        //O ULTIMO QUE NAO COMEÇOU
        if(validacao==0){
            jogador=ult;
        }
        validacao = realizapartida(jogador);
        for(i=0;i<4;i++){
            if(validacao==i){
                placar[i]++;
            }    
        }
        char txt[4];
        sprintf(txt, "%d", placar[0]); 
        char txt1[4];
        sprintf(txt1, "%d", placar[1]); 
        char txt2[4];
        sprintf(txt2, "%d", placar[2]); 
        char txt3[4];
        sprintf(txt3, "%d", placar[3]);  
        flag=true;
        while(flag){
            tela_texto(250, 200, 40, branco, "FIM DE JOGO");
            tela_texto(250, 250, 20, branco, "Deseja jogar novamente ?");
            tela_texto(170, 340, 20, branco, "Empates      ");
            tela_texto(250, 340, 20, branco, txt);
            tela_texto(170, 360, 20, branco, "1ºJogador    ");
            tela_texto(250, 360, 20, branco, txt1);
            tela_texto(170, 380, 20, branco, "2ºJogador    ");
            tela_texto(250, 380, 20, branco, txt2);
            tela_texto(175, 400, 20, branco,  "Desistências ");
            tela_texto(250, 400, 20, branco, txt3);
            //desenha um quadrado no contorno da janela
            tela_retangulo(30, 30, 470, 470, 5, amarelo, transparente);
            //DESENHA BOTAO SIM
            tela_retangulo(170, 290,250,320,2,branco,transparente); 
            tela_texto_esq(230, 295, 20, branco, "SIM");
            //DESENHA BOTAO NÃO
            tela_retangulo(280, 290,360,320,2,branco,transparente); 
            tela_texto_esq(340, 295, 20, branco, "NÃO");
            //DESENHA CIRCULO NA POSICAO DO MOUSE
            tela_circulo(tela_rato_x(), tela_rato_y(), 10, 2, vermelho, vermelho);
            if (tela_rato_apertado()) {
                if(novamente_sim(tela_rato_x(),tela_rato_y())){
                    novamente = 1;
                    flag = false;  
                }
                if (novamente_nao(tela_rato_x(),tela_rato_y())){
                    novamente = 0;
                    flag = false;
                }
            }   
            tela_atualiza(); 
        }        
        arq = fopen("placar", "w");
        for (int p=0; p<4; p++) {
            fprintf(arq, "%d\n", placar[p]);
        }
        fclose(arq);
    }
    tela_fim();
    return 0;
}
int realizapartida(int jogador){
    int repete=4,valido=1,x,y;
    bool flag = true;
    //INICIALIZANDO MATRIZ COM ' '
    char mat[3][3] = {{' ',' ',' '}, {' ',' ',' '}, {' ',' ',' '}};
    while((repete!=0)&&(repete!=1)&&(repete!=2)&&(repete!=3)){
    
        if(flag){
            desenhaTAB(mat,jogador);
            flag = false;
        }        
        //LAÇO VALIDACAO DE JOGADA
        while((valido!=0)&&(valido!=3)){
            desenhaTAB(mat,jogador);
            //DESENHA CIRCULO NA POSICAO DO MOUSE
            tela_circulo(tela_rato_x(), tela_rato_y(), 10, 2, vermelho, vermelho);
            if(tela_rato_apertado()){
                y = posicao_y(tela_rato_y());
                x = posicao_x(tela_rato_x());
               valido = le_jogada(posicao_y(tela_rato_y()),posicao_x(tela_rato_x()),mat);               
            }    
            
        }
        if(valido==3){
            repete=valido;
        }else{  
           valido = 1;
           atribuiMAT(y,x,jogador,mat);
           desenhaTAB(mat,jogador);
           repete = detecta_fim(mat);
           if(jogador==1){
              jogador=2;
           }else{jogador=1;} 
        }
        
    }
    return repete;
}
void atribuiMAT(int i, int j, int jogador, char mat[3][3]){
    if(jogador==1){
        mat[i][j]='X';
    }
    if(jogador==2){
        mat[i][j]='O';
    }
}
void desenhaTAB(char mat[3][3],int jogador){
    //DESENHA POSICOES JA OCUPADAS DO TABULEIRO
        for(int l=0;l<3;l++){
            for(int c=0;c<3;c++){
                if(mat[l][c]=='X'){
                    tela_linha((c*100)+110,  (l*100)+110, (c*100)+190, (l*100)+190, 2, branco);
                    tela_linha((c*100)+190, (l*100)+110, (c*100)+110,  (l*100)+190, 2, branco);
                }
                if(mat[l][c]=='O'){
                    tela_circulo((c*100)+150, (l*100)+150, 30, 4, branco, transparente);
                }
            }
        }
        //DESENHA QUEM VAI JOGAR 
        char txt[2];
        sprintf(txt, "%d", jogador);
        tela_texto(250, 50, 20, branco, "Jogue jogador nº ");
        tela_texto(350, 50, 20, branco, txt);
        //DESENHA LINHAS DO TABULEIRO
        tela_linha(200, 100, 200, 400, 2, branco);
        tela_linha(300, 100, 300, 400, 2, branco);
        tela_linha(100, 200, 400, 200, 2, branco);
        tela_linha(100, 300, 400, 300, 2, branco);
        //DESENHA CIRCULO NA POSICAO DO MOUSE
        tela_circulo(tela_rato_x(), tela_rato_y(), 10, 2, vermelho, vermelho);
        //DESENHA BOTAO DE DESISTENCIA
        tela_retangulo(370, 440,470,470,2,branco,transparente); 
        tela_texto_esq(465, 445, 20, branco, "DESISTIR");
        //ATUALIZA O QUE FOI DESENHADO
        tela_atualiza();
}
int le_jogada(int i,int j,char mat[3][3]){
    //JOGADA DE DESISTENCIA
    if(i==3 && j==3){
        return 3;
    }
    //JOGADA FORA DO TABULEIRO
    if(i>3 || j>3){
        return 1;
    }
    //JOGADA EM POSICAO JA OCUPADA
    if(mat[i][j]!=' '){
        return 1;
    }
    //JOGADA VALIDA
    if(mat[i][j]==' '){
        return 0;
    }

    return 7;
}
int detecta_fim(char mat[3][3]){
    int i,j,cont=0;
    
    for(i=0;i<3;i++){
        //VITORIA EM LINHAS
        if((mat[i][0]==mat[i][1])&&(mat[i][0]==mat[i][2])){
            if(mat[i][0]=='X'){
                return 1;
            }
            if(mat[i][0]=='O'){
                return 2;
            }
        }
        //VITORIA EM COLUNAS
        if((mat[0][i]==mat[1][i])&&(mat[0][i]==mat[2][i])){
            if(mat[0][i]=='X'){
                return 1;
            }
            if(mat[0][i]=='O'){
                return 2;
            }
        }
    }
    //VITORIA DIAGONAL PRINCIPAL
    if((mat[0][0]==mat[1][1])&&(mat[0][0]==mat[2][2])){
        if(mat[0][0]=='X'){
            return 1;
        }
        if(mat[0][0]=='O'){
            return 2;
        }
    }
    //VITORIA DIAGONAL SECUNDARIA
    if((mat[0][2]==mat[1][1])&&(mat[0][2]==mat[2][0])){
        if(mat[0][2]=='X'){
            return 1;
        }
        if(mat[0][2]=='O'){
            return 2;
        }
    }
    //SITUAÇÃO DE EMPATE
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(mat[i][j]!=' '){
                cont++;
            }
        }
    }
    if(cont==9){
       return 0; 
    }
    //JOGO CONTINUA
    return 4;
}
int posicao_y(float y){
    if((y>100)&&(y<200)){
        return 0;
    }else if((y>200)&&(y<300)){
        return 1;
    }else if((y>300)&&(y<400)){
        return 2;
    }else if((y>440)&&(y<470)){
        return 3;
    }else{return 4;}
}
int posicao_x(float x){
    if((x>100)&&(x<200)){
        return 0;
    }else if((x>200)&&(x<300)){
        return 1;
    }else if((x>300)&&(x<400)){
        return 2;
    }else if((x>370)&&(x<470)){
        return 3;
    }else {return 4;}
}
bool novamente_sim(float x, float y){
    //BOTAO JOGAR NOVAMENTE
    if((x>170)&&(x<250)&&(y>290)&&(y<320)){
        return true;
    }
    return false; 
}
bool novamente_nao(float x, float y){
    //NAO JOGAR NOVAMENTE
    if((x>280)&&(x<360)&&(y>290)&&(y<320)){
        return true;
    }
    return false;
}
