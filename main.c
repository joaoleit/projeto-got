#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char  reinicio = 1;
int end = 0, jogo = 0, conti = 0, contp = 0, contq = 0;
int pos1 = 0, pos2 = 0, vida = 100, vida_cersei = 100, vida_rei = 200, cersei = 0;

int mapa[10][10] = {1,5,0,0,0,0,0,0,0,0,
                    5,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,
                    0,0,0,5,2,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,0,
                    0,0,0,0,0,0,0,0,0,5,
                    0,0,0,0,0,0,0,0,5,3};

void menu(void);
void mapaStatus(void);
void movimentacao(void);
void geracaoMapa(void);
void negociacao(void);
void guerra(void);


int main(void){
  geracaoMapa();
  do
  {
    menu();
    if(end == 1) return 0;
    while(jogo == 1)
    {
      mapaStatus();
      movimentacao();
      if(vida <= 0 && cersei == 0)
      {
        printf("Jon morreu\n");
        jogo = 0;
      }
    }
    if(reinicio == 'o')
    {
      mapa[pos1][pos2] = 0;
      pos1 = 0, pos2 = 0, vida = 100, vida_cersei = 100, vida_rei = 200, cersei = 0;
      for(int i = 0; i < 10; i++)
      {
        for(int j = 0; j < 10; j++)
        {
          if(i == 0 && j == 0) mapa[i][j] = 1;
          else if(i == 3 && j == 4) mapa[i][j] = 2;
          else if(i == 9 && j == 9) mapa[i][j] = 3;
          else mapa[i][j] = 0;
        }
      }
      mapa[0][1] = 5, mapa[1][0] = 5, mapa[3][3] = 5, mapa[9][8] = 5, mapa [8][9] = 5;
      geracaoMapa();
      reinicio = 1;
    }
  }while(end == 0);
}

void menu(void){
  int opcoes = 2;
  while(opcoes == 2)
  {
    printf("\n***MENU***\n1- Jogar\n2- Instrucoes\n3- Sair\nDigite uma opcao: ");
    scanf("%d", &opcoes);
    getchar();
    while(opcoes < 0 || opcoes > 3)
    {
      printf("Opcao Invalida\nDigite uma opcao: ");
      scanf("%d", &opcoes);
      getchar();
    }
    switch(opcoes)
    {
      case 1:
        jogo = 1;
        break;
      case 2:
        printf("\nInstrucoes...\nJon Snow parte de Winterfell em direcao ao reino de Westeros, onde Cersei(C) se encontra.\n");
        printf("O Rei da Noite(N) encontra-se em seu reino ao final de Westeros.\nJon Snow nao pode enfrentar o rei da noite antes de negociar com Cersei.\n");
        printf("Caso Cersei aceite a enfretar o Rei da Noite com Jon Snow, a sua vida aumenta. Caso Cersei nao aceite, Jon tera que guerriar contra ela\n");
        printf("Existem 20 inimigos(tiram 1 de vida), 10 obstaculos e 10 pocoes de vida (restaura 5 de vida) espalhados aleatoriamente pelo cenario.\n");
        printf("Jon Snow e Cersei Possuem 100 de vida. O Rei da Noite possue 200.\nAtaques de Jon e Cersei quando acertados tiram 10 de vida. Ataques do Rei da Noite tiram 5 e curam ele em 5 de vida\n");
        printf("Jon Snow se movimenta pelo w,a,s,d. O 'p' pausa o jogo e volta pro MENU. O 'o' volta para o Menu com o jogo reiniciado.\n");
        printf("(I) Representa o numero de inimigos que restam no mapa. (P) Representa o numero de pocoes.\nPressione ENTER para voltar ao MENU: ");
        getchar();
        break;
      case 3:
        end = 1;
        break;
      default:
        printf("Opcao Invalida\n");
        break;
    }
  }
}

void mapaStatus(void){
  conti = 0;
  contp = 0;
  contq = 0;
  printf("\n");
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      if(mapa[i][j] == 1) printf("J ");
      else if(mapa[i][j] == 2 || mapa[i][j] == -2) printf("C ");
      else if(mapa[i][j] == 3) printf("N ");
      else if(mapa[i][j] == 4) printf("W ");
      else if(mapa[i][j] == 7)
      {
         printf("O ");
         contp++;
      }
      else if(mapa[i][j] == 9)
      {
        printf("O ");
        conti++;
      }
      else printf("O ");
    }
    printf("\n");
  }
  printf("P: %d, I: %d\n", contp, conti);
}

void movimentacao(void){
  char controle, aux;
  printf("\nJon tem %d vida\n", vida);
  printf("Mova Jon Snow: ");
  scanf("%s", &controle);
  getchar();
  switch(controle)
  {
    case 'w':
      if(pos1 - 1 == -1)
      {
        printf("Jon nao pode ir para cima\n");
        movimentacao();
      }
      else if(pos1 == 3 && pos2 == 4)
      {
        mapa[pos1 - 1][pos2] = 1;
        mapa[pos1][pos2] = -2;
        pos1--;
      }
      else if(mapa[pos1 - 1][pos2] == 0 || mapa[pos1 - 1][pos2] == 4 || mapa[pos1 - 1][pos2] == 5)
      {
        mapa[pos1 - 1][pos2] = 1;
        mapa[pos1][pos2] = 0;
        pos1--;
      }
      else if(mapa[pos1 - 1][pos2] == 2)
      {
        mapa[pos1 - 1][pos2] = 1;
        mapa[pos1][pos2] = 0;
        pos1--;
        negociacao();
      }
      else if(mapa[pos1 - 1][pos2] == -2)
      {
        printf("Jon ja negociou com Cersei\n");
        movimentacao();
      }
      else if(mapa[pos1 - 1][pos2] == 9)
      {
        printf("Jon encontrou um Inimigo e perdeu 1 de vida\n");
        vida--;
        mapa[pos1 - 1][pos2] = 1;
        mapa[pos1][pos2] = 0;
        pos1--;
      }
      else if(mapa[pos1 - 1][pos2] == 8)
      {
        printf("Jon encontrou um obstaculo\n");
        movimentacao();
      }
      else if(mapa[pos1 - 1][pos2] == 7)
      {
        if(vida > 95 && cersei == 0)
        {
          aux = 100 - vida;
          printf("Jon encontrou uma pocao e recuperou %d de vida\n", aux);
          vida = 100;
        }
        else
        {
        printf("Jon encontrou uma pocao e recuperou 5 de vida\n");
        vida += 5;
        }
        mapa[pos1 - 1][pos2] = 1;
        mapa[pos1][pos2] = 0;
        pos1--;
      }
      break;
    case 's':
      if(pos1 + 1 == 10)
      {
        printf("Jon nao pode ir para baixo\n");
        movimentacao();
      }
      else if(pos1 == 0 && pos2 == 0)
      {
        mapa[pos1 + 1][pos2] = 1;
        mapa[pos1][pos2] = 4;
        pos1++;
      }
      else if(pos1 == 3 && pos2 == 4)
      {
        mapa[pos1 + 1][pos2] = 1;
        mapa[pos1][pos2] = -2;
        pos1++;
      }
      else if(mapa[pos1 + 1][pos2] == 0 || mapa[pos1 + 1][pos2] == 5)
      {
        mapa[pos1 + 1][pos2] = 1;
        mapa[pos1][pos2] = 0;
        pos1++;
      }
      else if(mapa[pos1 + 1][pos2] == 2)
      {
        mapa[pos1 + 1][pos2] = 1;
        mapa[pos1][pos2] = 0;
        pos1++;
        negociacao();
      }
      else if(mapa[pos1 + 1][pos2] == -2)
      {
        printf("Jon ja negociou com Cersei\n");
        movimentacao();
      }
      else if(mapa[pos1 + 1][pos2] == 9)
      {
        printf("Jon encontrou um Inimigo e perdeu 1 de vida\n");
        vida --;
        mapa[pos1 + 1][pos2] = 1;
        mapa[pos1][pos2] = 0;
        pos1++;
      }
      else if(mapa[pos1 + 1][pos2] == 8)
      {
        printf("Jon encontrou um obstaculo\n");
        movimentacao();
      }
      else if(mapa[pos1 + 1][pos2] == 7)
      {
        if(vida > 95 &&  cersei == 0)
        {
          aux = 100 - vida;
          printf("Jon encontrou uma pocao e recuperou %d de vida\n", aux);
          vida = 100;
        }
        else
        {
          printf("Jon encontrou uma pocao e recuperou 5 de vida\n");
          vida += 5;
        }
        mapa[pos1 + 1][pos2] = 1;
        mapa[pos1][pos2] = 0;
        pos1++;
      }
      else if(mapa[pos1 + 1][pos2] == 3)
      {
        if(cersei == 0)
        {
          printf("Voce nao pode enfrentar o rei da noite antes de falar com Cersei\n");
          movimentacao();
        }
        else guerra();
      }
      break;
    case 'a':
      if(pos2 - 1 == -1)
      {
        printf("Jon nao pode ir para a esquerda");
        movimentacao();
      }
      else if(pos1 == 3 && pos2 == 4)
      {
        mapa[pos1][pos2 - 1] = 1;
        mapa[pos1][pos2] = -2;
        pos2--;
      }
      else if(mapa[pos1][pos2 - 1] == 0 || mapa[pos1][pos2 - 1] == 4 || mapa[pos1][pos2 - 1] == 5)
      {
        mapa[pos1][pos2 - 1] = 1;
        mapa[pos1][pos2] = 0;
        pos2--;
      }
      else if(mapa[pos1][pos2 - 1] == 2)
      {
        mapa[pos1][pos2 - 1] = 1;
        mapa[pos1][pos2] = 0;
        pos2--;
        negociacao();
      }
      else if(mapa[pos1][pos2 - 1] == -2)
      {
        printf("Jon ja negociou com Cersei\n");
        movimentacao();
      }
      else if(mapa[pos1][pos2 - 1] == 9)
      {
        printf("Jon encontrou um Inimigo e perdeu 1 de vida\n");
        vida --;
        mapa[pos1][pos2 - 1] = 1;
        mapa[pos1][pos2] = 0;
        pos2--;
      }
      else if(mapa[pos1][pos2 - 1] == 8)
      {
        printf("Jon encontrou um obstaculo\n");
        movimentacao();
      }
      else if(mapa[pos1][pos2 - 1] == 7)
      {
        if(vida > 95 && cersei == 0)
        {
          aux = 100 - vida;
          printf("Jon encontrou uma pocao e recuperou %d de vida\n", aux);
          vida = 100;
        }
        else
        {
          printf("Jon encontrou uma pocao e recuperou 5 de vida\n");
          vida += 5;
        }
        mapa[pos1][pos2 - 1] = 1;
        mapa[pos1][pos2] = 0;
        pos2--;
      }
      break;
    case 'd':
      if(pos2 + 1 == 10)
      {
        printf("Jon nao pode ir para a direita");
        movimentacao();
      }
      else if(pos1 == 0 && pos2 == 0)
      {
        mapa[pos1][pos2 + 1] = 1;
        mapa[pos1][pos2] = 4;
        pos2++;
      }
      else if(pos1 == 3 && pos2 == 4)
      {
        mapa[pos1][pos2 + 1] = 1;
        mapa[pos1][pos2] = -2;
        pos2++;
      }
      else if(mapa[pos1][pos2 + 1] == 0 || mapa[pos1][pos2 + 1] == 5)
      {
        mapa[pos1][pos2 + 1] = 1;
        mapa[pos1][pos2] = 0;
        pos2++;
      }
      else if(mapa[pos1][pos2 + 1] == 2)
      {
        mapa[pos1][pos2 + 1] = 1;
        mapa[pos1][pos2] = 0;
        pos2++;
        negociacao();
      }
      else if(mapa[pos1][pos2 + 1] == -2)
      {
        printf("Jon ja negociou com Cersei\n");
        movimentacao();
      }
      else if(mapa[pos1][pos2 + 1] == 9)
      {
        printf("Jon encontrou um Inimigo e perdeu 1 de vida\n");
        vida --;
        mapa[pos1][pos2 + 1] = 1;
        mapa[pos1][pos2] = 0;
        pos2++;
      }
      else if(mapa[pos1][pos2 + 1] == 8)
      {
        printf("Jon encontrou um obstaculo\n");
        movimentacao();
      }
      else if(mapa[pos1][pos2 + 1] == 7)
      {
        if(vida > 95 && cersei == 0)
        {
          aux = 100 - vida;
          printf("Jon encontrou uma pocao e recuperou %d de vida\n", aux);
          vida = 100;
        }
        else
        {
          printf("Jon encontrou uma pocao e recuperou 5 de vida\n");
          vida += 5;
        }
        mapa[pos1][pos2 + 1] = 1;
        mapa[pos1][pos2] = 0;
        pos2++;
      }
      else if(mapa[pos1][pos2 + 1] == 3)
      {
        if(cersei == 0)
        {
          printf("Voce nao pode enfrentar o rei da noite antes de falar com Cersei\n");
          movimentacao();
        }
        else guerra();
      }
      break;
    case 'p':
      jogo = 0;
      break;
    case 'o':
      jogo = 0;
      reinicio = 'o';
      break;
    default:
      printf("Digite W,A,S,D para mover\n");
      movimentacao();
      break;
  }
    controle =' ';
}

void geracaoMapa(void){
  srand(time(NULL));
  int k=0,l=0,m=0,n=0,o=0,p=0;
  for(int i = 0; i < 20; i++)
  {
    if(i < 10){
      while(mapa[k][l] != 0)
      {
        k = rand() % 10;
        l = rand() % 10;
      }
      mapa[k][l] = 7;
      while(mapa[m][n] != 0)
      {
        m = rand() % 10;
        n = rand() % 10;
      }
      mapa[m][n] = 8;
    }
    while(mapa[o][p] != 0)
    {
      o = rand() % 10;
      p = rand() % 10;
    }
    mapa[o][p] = 9;
  }
}

void negociacao(void){
  srand(time(NULL));
  int tentativa, acerto = 0, n = 1;
  printf("Jon Chegou em Westeros\nA negociacao vai comecar\nPressione ENTER: ");
  getchar();
  while(n < 6)
  {
    if (n > 1)
    {
      printf("\nTentativa %d Pressione ENTER: ", n);
      getchar();
    }
    tentativa = rand() % 101;
    printf("Jon tirou: %d%%\n", tentativa);
    if(tentativa >= 60 && acerto < 2){
      printf("Jon esta convencendo a Cersei\n");
      acerto++;
    }
    else if(tentativa >= 60 && acerto == 2)
    {
      acerto++;
      printf("\nParabens!\nJon convenceu a Cersei!\n");
      break;
    }
    n++;
  }
  if(acerto < 3) guerra();
  else
  {
    vida += 100;
    printf("Jon aumentou sua vida\nVida atual: %d\n", vida);
    printf("Pressione ENTER para continuar: ");
    getchar();
    cersei = 1;
  }
}

void guerra(void){
  srand(time(NULL));
  int ataque_jon, ataque_cersei, ataque_rei, cont = 1, vitoria = 0;
  if(cersei == 0)
  {
    printf("\nJon nao convenceu Cersei\nA Guerra vai comecar\n");
    while(vida > 0 && vida_cersei > 0)
    {
      ataque_jon = rand() % 101;
      ataque_cersei = rand() % 101;
      printf("\nPressione Enter para o ataque %d do Jon: ", cont);
      getchar();
      printf("O ataque %d de Jon: %d%%\n", cont, ataque_jon);
      if(ataque_jon >= 50)
      {
        printf("Cersei perdeu 10 de vida\n");
        vida_cersei -= 10;
        if(vida_cersei <= 0)
        {
          vitoria = 1;
          break;
        }
      }
      else
      {
        printf("Jon nao conseguiu dar dano\n");
      }
      printf("\nPressione Enter para o ataque %d da Cersei: ", cont);
      getchar();
      printf("O ataque %d de Cersei: %d%%\n", cont, ataque_cersei);
      if(ataque_cersei >= 50)
      {
        printf("Jon perdeu 10 de vida\n");
        vida -= 10;
        if(vida <= 0)
        {
          vitoria = -1;
          break;
        }
      }
      else
      {
        printf("Cersei nao conseguiu dar dano\n");
      }
      printf("Vida atual do Jon: %d\nVida atual da Cersei: %d\n", vida, vida_cersei);
      cont++;
    }
    if(vitoria == 1)
    {
      printf("Voce derrotou a Cersei e ganhou 100 de vida\nPressione ENTER para continuar: ");
      getchar();
      vida += 100;
    }
    else
    {
      printf("\nVoce foi derrotado por Cersei e voltou para Winterfell\nPressione ENTER para voltar ao MENU: ");
      getchar();
      jogo = 0;
      reinicio = 'o';
    }
    cersei = 1;
  }
  else
  {
    vitoria = 0;
    cont = 1;
    printf("Voce chegou no rei da noite!\nA batalha vai comecar");
    while(vida > 0 && vida_rei > 0)
    {
      ataque_jon = rand() % 101;
      ataque_rei = rand() % 101;
      printf("\nPressione Enter para o ataque %d do Jon: ", cont);
      getchar();
      printf("O ataque 1 de Jon: %d%%\n", ataque_jon);
      if(ataque_jon >= 50)
      {
        printf("O Rei da Noite perdeu 10 de vida\n");
        vida_rei -= 10;
        if(vida_rei <= 0)
        {
          vitoria = 1;
          break;
        }
      }
      else
      {
        printf("Jon nao conseguiu dar dano\n");
      }
      printf("\nPressione Enter para o ataque %d do Rei da Noite: ", cont);
      getchar();
      printf("O ataque %d do Rei da Noite: %d%%\n", cont, ataque_rei);
      if(ataque_rei >= 50)
      {
        printf("O Rei da Noite se curou em 5 e Jon perdeu 5 de vida\n");
        vida -= 5;
        vida_rei += 5;
        if(vida <= 0)
        {
          vitoria = -1;
          break;
        }
      }
      else
      {
        printf("Rei da noite nao conseguiu dar dano\n");
      }
      printf("Vida atual do Jon: %d\nVida atual do Rei da Noite: %d\n", vida, vida_rei);
      cont++;
    }
    if(vitoria == 1)
    {
      printf("\nVoce derrotou o Rei da Noite e Venceu o jogo\nParabens! Pressione ENTER para voltar ao MENU: ");
      getchar();
    }
    else
    {
      printf("\nVoce foi derratado e o Rei da Noite permanece Vivo\nPressione ENTER para voltar ao MENU: ");
      getchar();
    }
    jogo = 0;
    reinicio = 'o';
  }
}
