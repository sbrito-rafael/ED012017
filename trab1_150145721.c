#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Universidade de Brasilia
Instituto de Ciencias Exatas
Departamento de Ciencia da Computacao
Estrutura de Dados – 1/2017
Aluno(a): Rafael Silva Brito
Matricula: 15/0145721
Turma: B
Versão do compilador: GCC 6.3
Descricao: Desenvolver o jogo Batalha Naval
*/

typedef struct { //Definição da estrutura dos jogadores
  int tabuleiro[5][5];
  int posicaoEmbarcacao[5][5];
  char nome[20];
  int pontuacao;
}tipoJogador;

void iniciaJogador(tipoJogador *jogador, int *cont){
  int linha, coluna, sub=0, dest=0, port=0;

  printf("Nome jogador %d: ", *cont);
  scanf("%s", jogador->nome);
  jogador->pontuacao = 0;
  for(linha=0 ; linha < 5 ; linha++ ){
    for(coluna=0 ; coluna < 5 ; coluna++ ){
      jogador->tabuleiro[linha][coluna]=-1; //-1 representa água (posiçao oculta) no tabuleiro
      jogador->posicaoEmbarcacao[linha][coluna]=-1; //-1 representa vazio no posicionamento das embarcações
    }
  }

  *cont=*cont+1;

  //Inicio do sorteio de posições do porta aviões
    do{
    linha = rand()%5;
    coluna = rand()%5;
    if(coluna == 1){
      if ((jogador->posicaoEmbarcacao[linha][coluna] == -1) && (jogador->posicaoEmbarcacao[linha][coluna+1] == -1) && (jogador->posicaoEmbarcacao[linha][coluna+2] == -1)){
        jogador->posicaoEmbarcacao[linha][coluna] = 3; //3 será utilizado para representar porta aviões
        jogador->posicaoEmbarcacao[linha][coluna+1] = 3;
        jogador->posicaoEmbarcacao[linha][coluna+2] = 3;
        port++;
      }
    } else if(coluna == 4){
      if ((jogador->posicaoEmbarcacao[linha][coluna] == -1) && (jogador->posicaoEmbarcacao[linha][coluna-1] == -1) && (jogador->posicaoEmbarcacao[linha][coluna-2] == -1)){
        jogador->posicaoEmbarcacao[linha][coluna] = 3; //3 será utilizado para representar porta aviões
        jogador->posicaoEmbarcacao[linha][coluna-1] = 3;
        jogador->posicaoEmbarcacao[linha][coluna-2] = 3;
        port++;
      }
    } else {
      if ((jogador->posicaoEmbarcacao[linha][coluna] == -1) && (jogador->posicaoEmbarcacao[linha][coluna-1] == -1) && (jogador->posicaoEmbarcacao[linha][coluna+1] == -1)){
        jogador->posicaoEmbarcacao[linha][coluna] = 3; //3 será utilizado para representar porta aviões
        jogador->posicaoEmbarcacao[linha][coluna-1] = 3;
        jogador->posicaoEmbarcacao[linha][coluna+1] = 3;
        port++;
      }
    }
  }while(port<1);

  //Inicio do sorteio de posições dos destroyers
    do{
    linha = rand()%5;
    coluna = rand()%5;
    if(coluna != 4){
      if((jogador->posicaoEmbarcacao[linha][coluna] == -1) && (jogador->posicaoEmbarcacao[linha][coluna+1] == -1)){ //confere se a posição está vazia
        jogador->posicaoEmbarcacao[linha][coluna] = 2; //2 será utilizado para representar destroyers
        jogador->posicaoEmbarcacao[linha][coluna+1] = 2;
        dest++;
      }
    } else {
      if((jogador->posicaoEmbarcacao[linha][coluna] == -1) && (jogador->posicaoEmbarcacao[linha][coluna-1] == -1)){ //confere se a posição está vazia
        jogador->posicaoEmbarcacao[linha][coluna] = 2; //2 será utilizado para representar destroyers
        jogador->posicaoEmbarcacao[linha][coluna-1] = 2;
        dest++;
      }
    }
  }while(dest<2);

  //Inicio do sorteio de posições dos submarinos
  srand(time(NULL));
  do{
    linha = rand()%5;
    coluna = rand()%5;
    if(jogador->posicaoEmbarcacao[linha][coluna] == -1){ //confere se a posição está vazia
      jogador->posicaoEmbarcacao[linha][coluna] = 1; //1 será utilizado para representar submarinos
      sub++;
    }
  }while(sub<3);

}

void exibirTabuleiro(tipoJogador *jogador){
  int linha, coluna;

  printf("   1  2  3  4  5");
  printf("\n");

  for(linha=0 ; linha < 5 ; linha++ ){
    printf("%d",linha+1);
    for(coluna=0 ; coluna < 5 ; coluna++ ){
      if(jogador->tabuleiro[linha][coluna]==-1){ // -1 água
        printf("  ~");
      }else if(jogador->tabuleiro[linha][coluna]==0){ // 0 tiro que não acertou alvo
        printf("  *");
      }else if(jogador->tabuleiro[linha][coluna]==1){ // 1 submarinos
        printf("  S");
      }else if(jogador->tabuleiro[linha][coluna]==2){ // 2 destroyers
        printf("  D");
      } else {
        printf("  P");
      }
    }
    printf("\n");
  }

  }

int tiro(int i, int j, tipoJogador *inimigo) {
  if(inimigo->posicaoEmbarcacao[i-1][j-1] == 1){
    return 1;
  } else if(inimigo->posicaoEmbarcacao[i-1][j-1] == 2){
    return 2;
  } else if(inimigo->posicaoEmbarcacao[i-1][j-1] == 3){
    return 3;
  } else {
    return 0;
  }
}

void modificaTabuleiro(int i, int j, int alvo, tipoJogador *inimigo){
  if(alvo == 0){
    inimigo->tabuleiro[i-1][j-1] = 0;
  }else if(alvo == 1){
    inimigo->tabuleiro[i-1][j-1] = 1;
  }else if(alvo == 2){
    inimigo->tabuleiro[i-1][j-1] = 2;
  }else{
    inimigo->tabuleiro[i-1][j-1] = 3;
  }
}

int main() {
  tipoJogador jogadorA, jogadorB;
  int cont=1, i, j, alvo;

  iniciaJogador(&jogadorA, &cont);
  iniciaJogador(&jogadorB, &cont);

  do {
    //Inicio do turno do jogadorA
    printf("\n--- Vez de: %s ---\n", jogadorA.nome);
    printf("Atirar! (linha coluna): ");
    scanf("%d%d", &i, &j);
    while((i < 1) || (i > 5) || (j < 1) || (j > 5)){
      printf("\nCoordenadas inválidas! Tente novamente.\n");
      printf("Atirar! (linha coluna): ");
      scanf("%d%d", &i, &j);
    }
    alvo = tiro(i, j, &jogadorB);
    if (alvo != 0) {
      jogadorA.pontuacao++;
    }
    printf("\n");
    modificaTabuleiro(i, j, alvo, &jogadorB);
    exibirTabuleiro(&jogadorB);
    if(alvo == 1){
      printf("\nVocê acertou um submarino!\n");
    } else if(alvo == 2){
      printf("\nVocê acertou parte de um destroyer!\n");
    }else if(alvo == 3){
      printf("\nVocê acertou parte de um Porta aviões!\n");
    } else {
      printf("\nVocê errou o tiro!\n");
    }
    alvo = 0;
    //Final do turno do jogadorA

    //Inicio do turno do jogadorB
    printf("\n--- Vez de: %s ---\n", jogadorB.nome);
    printf("Atirar! (linha coluna): ");
    scanf("%d%d", &i, &j);
    while((i < 1) || (i > 5) || (j < 1) || (j > 5)){
      printf("\nCoordenadas inválidas! Tente novamente.\n");
      printf("Atirar! (linha coluna): ");
      scanf("%d%d", &i, &j);
    }
    alvo = tiro(i, j, &jogadorA);
    if (alvo != 0) {
      jogadorB.pontuacao++;
    }
    printf("\n");
    modificaTabuleiro(i, j, alvo, &jogadorA);
    exibirTabuleiro(&jogadorA);
    if(alvo == 1){
      printf("\nVocê acertou um submarino!\n");
    } else if(alvo == 2){
      printf("\nVocê acertou parte de um destroyer!\n");
    }else if(alvo == 3){
      printf("\nVocê acertou parte de um Porta aviões!\n");
    } else {
      printf("\nVocê errou o tiro!\n");
    }
    alvo = 0;
    //Final do turno do jogadorB
  } while((jogadorA.pontuacao != 10) && (jogadorB.pontuacao != 10));

  if (jogadorA.pontuacao > jogadorB.pontuacao) {
    printf("\n--- VENCEDOR ---\n%s destruiu todas as embarcacoes!!\n", jogadorA.nome);
  } else {
    printf("\n--- VENCEDOR ---\n%s destruiu todas as embarcacoes!!\n", jogadorB.nome);
  }

  printf("\n--- FIM DE JOGO! ---\n");
  return 0;
}