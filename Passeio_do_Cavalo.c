//Bruna Bravin Bueno, Luis Fernando da Silva Serafim

#include <stdio.h>
#include <stdlib.h>

#define MAX1 12
#define MAX2 10

int Tabuleiro[MAX1][MAX1]; 
int cTabuleiro[MAX1][MAX1];

void Inicializa_Tabuleiro(void){      //Atribui valores as casas.
  int i,j;

  for(i=0; i < MAX1; i++)  // Todas as casas ja visitadas.
    for(j=0; j < MAX1; j++){
	Tabuleiro[i][j] = 1;
	cTabuleiro[i][j] = 1;
	}

  for(i=2; i < MAX2; i++) // Atualizando corretamente as casas visitadas.
    for(j=2; j < MAX2; j++){
    	Tabuleiro[i][j] = 0;
    	cTabuleiro[i][j] = 0;
	}
  return;
}

void Imprime_Tabuleiro(void) { //Imprime o tabuleiro já com as visitas.
int i, j;

  	for (i=2 ; i < MAX2; i++){
      for (j=2; j < MAX2; j++) printf("%4d", Tabuleiro[i][j]);
      printf("\n\n");
    }
  
  return;
}


void Leitura_Posicao_Inicial(int *Posi, int *Posj) { //Lê a posição inicial do cavalo.
 
 printf(" Introduza a linha da posição inicial : ");
 scanf("%d",Posi);   //  1 <= Posi <= 4
 printf("\n\n");
 printf(" Introduza a coluna da posição inicial : ");
 scanf("%d",Posj); //  1 <= Posj <= 4

 (*Posi)++;  // Atualizando as posicoes para o tabuleiro real (12x12).
 (*Posj)++;

 return;
}  

int QtdMovimentosPosicao( int Posx, int Posy) { //Verifica a quantidade de possiveis movimentos a partir de uma dada posição.
 int pos=0;

 if(Tabuleiro[Posx-2][Posy+1] == 0) pos++;
 if (Tabuleiro[Posx-1][Posy+2] == 0) pos++;
 if (Tabuleiro[Posx+1][Posy+2] == 0) pos++;
 if (Tabuleiro[Posx+2][Posy+1] == 0) pos++;
 if (Tabuleiro[Posx+2][Posy-1] == 0) pos++;
 if (Tabuleiro[Posx+1][Posy-2] == 0) pos++;
 if (Tabuleiro[Posx-1][Posy-2] == 0) pos++;
 if (Tabuleiro[Posx-2][Posy-1] == 0) pos++;

 return(pos);
}

void Proximo_Movimento(int *pos, int Posx, int Posy) { //Faz o próximo movimento.
  *pos=0;

 if(Tabuleiro[Posx-2][Posy+1] == 0) *pos=1;
 else if (Tabuleiro[Posx-1][Posy+2] == 0) *pos=2;
 else if (Tabuleiro[Posx+1][Posy+2] == 0) *pos=3;
 else if (Tabuleiro[Posx+2][Posy+1] == 0) *pos=4;
 else if (Tabuleiro[Posx+2][Posy-1] == 0) *pos=5;
 else if (Tabuleiro[Posx+1][Posy-2] == 0) *pos=6;
 else if (Tabuleiro[Posx-1][Posy-2] == 0) *pos=7;
 else if (Tabuleiro[Posx-2][Posy-1] == 0) *pos=8;

 return;
}  

void Atualiza_Nova_Posicao(int vis, int *mov, int *pi, int *pj) { //Atualiza a posição onde o cavalo está.
  switch(*mov) {
      case 1: *pi-=2; *pj+=1; break;
      case 2: *pi-=1; *pj+=2; break;
      case 3: *pi+=1; *pj+=2; break;
      case 4: *pi+=2; *pj+=1; break;
      case 5: *pi+=2; *pj-=1; break;
      case 6: *pi+=1; *pj-=2; break;
      case 7: *pi-=1; *pj-=2; break;
      case 8: *pi-=2; *pj-=1;
    }
	Tabuleiro[*pi][*pj]= vis;
  return;
}

void QtdMovimentosTabuleiro(){ // Mapeia a quantidade de movimentos a partir de cada posição e atribui a uma outra matriz.
	int i, j;
	
	for(i=2; i<MAX2; i++)
		for(j=2; j<MAX2; j++){
			cTabuleiro[i][j] = QtdMovimentosPosicao(i, j);
		}
	return;
}

int MovValido(int pi, int pj){ //Verifica se o movimento é valido, ou seja possui a posição conteúdo igual a 0.
	if (Tabuleiro[pi][pj]==0)
	return(1);
	else return(0);
}

void Euristica(int vis, int Posx, int Posy, int *mov){ //Escolhe a casa com menor possibilidade de movimentos segunda a Euristica.
	int menor=8;
	*mov=0;
	while(menor>=2){
		if(cTabuleiro[Posx-2][Posy+1] == menor)
			if(MovValido(Posx-2, Posy+1)) *mov=1;
			
 		if (cTabuleiro[Posx-1][Posy+2] == menor)
		 		if (MovValido(Posx-1, Posy+2)) *mov=2;
		 		
		if (cTabuleiro[Posx+1][Posy+2] == menor)
				if(MovValido(Posx+1, Posy+2)) *mov=3;
				
 		if (cTabuleiro[Posx+2][Posy+1] == menor)
		 		if(MovValido(Posx+2, Posy+1)) *mov=4;
		 		
		if (cTabuleiro[Posx+2][Posy-1] == menor)
				if(MovValido(Posx+2, Posy-1)) *mov=5;
				
 		if (cTabuleiro[Posx+1][Posy-2] == menor)
		 	 	if(MovValido(Posx+1, Posy-2)) *mov=6;
		 	 	
 		if (cTabuleiro[Posx-1][Posy-2] == menor)
		 		if(MovValido(Posx-1, Posy-2)) *mov=7;
		 		
 		if (cTabuleiro[Posx-2][Posy-1] == menor)
		 		if(MovValido(Posx-2, Posy-1)) *mov=8;
	  	menor--;
	}
	
	return;
}


int main(void){
	int pi, pj, i=0;
	int mov=0, vis=2, pos;
	Inicializa_Tabuleiro();
 	QtdMovimentosTabuleiro();
 	Leitura_Posicao_Inicial(&pi,&pj);
 	Tabuleiro[pi][pj]=1;
 	do{
 		Euristica(vis, pi, pj, &mov);
 		Atualiza_Nova_Posicao(vis, &mov, &pi, &pj);
 		vis++;
 	}while(mov);//Enquanto o movimento for válido.
	Imprime_Tabuleiro();
	return(1);
 }
 	
 	
 	

