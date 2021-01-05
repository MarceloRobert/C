#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

//--------------------------------------------------------------------------//
// Função para criar a matriz
int* criar_bitmap(int id){
	int i, j;

	//Matriz de numero de linhas = id e numero de colunas = 5 (numero de campos bitmap)
	//printf("\nLinhas: %d\nColunas: %d\n\n", id, 7);
  int *matriz = (int*) malloc(id * 5 * sizeof(int) );

  if (matriz != NULL) {
    //printf("\nMatriz criada com sucesso!\n\n");
    //printf("\nPonteiro memoria: %p\n\n", bitsliced);
    return matriz;
  } else {//(bitsliced == NULL)
    printf("\nMemória Insuficiente!\n\n");
	  return NULL ;
  }
}

//--------------------------------------------------------------------------//
// Função para liberar a memória da matriz
void liberar_bitmap(int* matriz){
	free(matriz);
  matriz = NULL;
}

//--------------------------------------------------------------------------//
// Função para preencher a matriz
void preenche_bitmap(int* matriz){
  int i, cont;
	char nome[30], sexo, nacion, comprou, auxc;
	int idade, id;

	FILE *dados;
  
  auxc = 'a';
  cont = 0;
  dados = fopen("dados.txt", "r");
		//pega quantos dados estão no arquivo
    while(auxc != EOF){
      auxc = fgetc(dados);
      if(auxc == '\n')
        cont++;
    }
    rewind(dados);
    for(i=0; i<cont; i++){
      fscanf(dados, " %s %c %d %c %c %d", nome, &sexo, &idade, &nacion, &comprou, &id);

      // Preenche o campo de sexo da linha, Feminino = 1, Masculino = 0
      if(sexo == 'F')
          matriz[i*5] = 1;
      else
          matriz[i*5] = 0;
      //--------------------------------------------------------------//

      /*
			. Preenche o campo de idade <18 da linha, idade esta subdividida em 3 faixas, logo usam-se 2 arrays de indices bitmap para salvar as categorias
      . Caso idade for < 18, campo do primeiro array é 1 e campo do segundo array é 0
      . Caso idade estiver entre 18 e 60 anos, ambos os campos são 0
      . Caso idade for > 60, campo do primeiro array é 0 e campo do segundo array é 1
			*/

      //Campo no primeiro array
      if(idade < 18)
          matriz[i*5 + 1] = 1;
      else
          matriz[i*5 + 1] = 0;
      //---------------------//

      //Campo no segundo array
      if(idade > 60)
          matriz[i*5 + 2] = 1;
      else
          matriz[i*5 + 2] = 0;
      //---------------------//




      // Preenche o campo de nacionalidade da linha, Nativo = 1, Estrangeiro = 0
      if(nacion == 'N')
          matriz[i*5 + 3] = 1;
      else
          matriz[i*5 + 3] = 0;
      //------------------------------------------------------------------------//


      // Preenche o campo que indica se o aluno comprou pacote de intercambio, caso tenha comprado, 1, caso nao tenha comprado, 0
      if(comprou == 'S')
          matriz[i*5 + 4] = 1;
      else
          matriz[i*5 + 4] = 0;
      //------------------------------------------------------------------------//

    }
  fclose(dados);

}


//--------------------------------------------------------------------------//
// Função para imprimir a matriz
void imprime_bitmap(int* matriz){
	int i;

	FILE *dados;  
  char auxc = 'a';
  int cont = 0;
  dados = fopen("dados.txt", "r");
		//pega quantos dados estão no arquivo
    while(auxc != EOF){
      auxc = fgetc(dados);
      if(auxc == '\n')
        cont++;
    }
	fclose(dados);

  printf("\n  Sexo | <18 | >60 |  Nacion |  Pacote\n\n");
  for (i=0; i<cont; i++){
    printf("   %d   |  %d  |  %d  |    %d    |    %d\n", matriz[(i*5)], matriz[(i*5)+1], matriz[(i*5)+2], matriz[(i*5)+3], matriz[(i*5)+4]);
  }
}

//--------------------------------------------------------------------------//
// Função para consultar os dados
void consultar (int* matriz, int codigo){
	int i;
	//as variáveis são apenas "resposta 1" e "resposta 2" para não ficar muitas variáveis atoa
	int res1 = 0, res2 = 0;

	//conta quantos clientes estão registrados
	FILE *dados;  
  char auxc = 'a';
  int cont = 0;
  dados = fopen("dados.txt", "r");
    while(auxc != EOF){
      auxc = fgetc(dados);
      if(auxc == '\n')
        cont++;
    }
	fclose(dados);

	//verifica se a matriz é nula
	if(matriz == NULL){
		printf("A matriz não foi criada!\n\n");
		return;
	}

	//switch para os comandos
	switch(codigo){
		case 1: //quantos clientes homens e quantas clientes mulheres

			for(i=0; i<cont; i++){

				if (matriz[(i*5)] == 1)
					res1++; //mulher
				else
					res2++; //homem
			}

			printf("\nExistem %d mulheres e %d homens.\n\n", res1, res2);
			break;
		case 2: //quantos clientes (estrangeiros ou nativos) compraram o pacote

			for(i=0; i<cont; i++){
				if(matriz[i*5 + 4] == 1){ //se comprou o pacote
					if(matriz[i*5 + 3] == 1)
						res1++; //nativo
					else
						res2++; //estrangeiro
				}

			}
			printf("\nDos que compraram pacote de intercâmbio,\n%d são nativos e %d são estrangeiros\n\n", res1, res2);
			break;

		case 3: //quantos clientes tem direito a promocao 1 (clientes menores de 18 anos ou maiores de 60)

			for(i=0; i<cont; i++){
				if (matriz[i*5+1] == 1 || matriz[i*5+2] == 1)
						res1++; //tem direito a promocao 1
					else
						res2++; //nao tem direito a promocao 1
				
			}
			printf("\nDireito à promoção 1:\n");

      printf("\n%d clientes tem direito\n", res1);
      printf("%d clientes não tem direito\n\n", res2);

			break;

		case 4: //quantos clientes tem direito a promocao especial (clientes estrangeiros, maiores de idade, que nao tenham comprado pacote de intecambio)

			for(i=0; i<cont; i++){
				if (matriz[i*5+1] == 0 && matriz[i*5+3] == 0 && matriz[i*5+4] == 0)
						res1++; //tem direito a promocao especial
					else
						res2++; //nao tem direito a promocao especial

			}
			printf("\nDireito à promoção especial:\n\n");

      printf("\n%d clientes tem direito\n", res1);
      printf("%d clientes não tem direito\n\n", res2);
			break;

		default:
			break;
	}
}


void consulta_bitmap(int* matriz, int id) {
	int *vetor = (int*) malloc(sizeof(int) * 5);
	char sexo, nacionalidade, pacote, menos18, mais60;
	int cont = 0;
  
  if(matriz == NULL){
		printf("O Bitmap não foi criado!\n\n");
		return;
	}

	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
	printf("             Busca de Dados\n");
	printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-\n\n");

	//Recebe os dados de busca e armazena em um vetor
	do {
		printf("Sexo [M/F]: ");
		scanf(" %c", &sexo);
	} while (sexo != 'M' && sexo != 'F' && sexo != 'm' && sexo != 'f');

	if (sexo == 'F' || sexo == 'f') {
		vetor[0] = 1;
	} else {
		vetor[0] = 0;
	}

	do {
		printf("Menos de 18 anos? (S/N) ");
    scanf(" %c", &menos18);
  } while (menos18 != 'S' && menos18 != 'N' && menos18 != 's' && menos18 != 'n');
  if (menos18 != 'S' && menos18 != 's' ) {
    do {
      printf("Mais de 60 anos? (S/N) ");
      scanf(" %c", &mais60);
    } while (mais60 != 'S' && mais60 != 'N' && mais60 != 's' && mais60 != 'n');
  }

	if (menos18 == 'S' || menos18 == 's') {
		vetor[1] = 1;
		vetor[2] = 0;
	} else if (mais60 == 'S' || mais60 == 's') {
		vetor[1] = 0;
		vetor[2] = 1;
	} else {
		vetor[1] = 0;
		vetor[2] = 0;
	}

	do {
		printf("Nacionalidade (Estrangeiro/Nativo)");
    printf("Informe [E/N]: ");
		scanf(" %c", &nacionalidade);
	} while (nacionalidade != 'E' && nacionalidade != 'N' && nacionalidade != 'e' && nacionalidade != 'n');
	if (nacionalidade == 'N' || nacionalidade == 'n') {
		vetor[3] = 1;
	} else {
		vetor[3] = 0;
	}

	do {
		printf("Pacote [S/N]: ");
		scanf(" %c", &pacote);
	} while (pacote != 'S' && pacote != 'N' && pacote != 's' && pacote != 'n');
	if (pacote == 'S' || pacote == 's') {
		vetor[4] = 1;
	} else {
		vetor[4] = 0;
	}

  //Procura dados iguais aos informados
  for (int i = 0; i < id; i++) {
    if (vetor[0] == matriz[(i*5)] && vetor[1] == matriz[(i*5)+1] && vetor[2] == matriz[(i*5)+2] && vetor[3] == matriz[(i*5)+3] && vetor[4] == matriz[(i*5)+4]) {
      cont++;
    }
  }

	if(cont == 0)
	  printf("\nNão foram encontrados registros relacionados aos dados informados\n\n");
	else
		if(cont == 1)
			printf("\nFoi encontrado %d registro relacionado aos dados informados\n\n", cont);
		else
		 printf("\nForam encontrados %d registros relacionados aos dados informados\n\n", cont);
	
	free(vetor);
} 