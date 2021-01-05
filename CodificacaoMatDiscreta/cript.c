#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define proportion 13


int descodificar(int *cod, int tam){
	int i, j;
	char *frase = calloc(tam, sizeof(char));

	//divide pela proporção dada
	for(i=0; i<tam; i++){
		cod[i] = cod[i]/proportion;
	}

	//recebe os valores na forma ordenada
	j=0;
	for(i=0; j<tam; i++){
		frase[i] = cod[j];
		j += 2;
	}

	j=1;
	for(i=i; i<tam; i++){
		frase[i] = cod[j];
		j += 2;
	}

	printf("\nA frase descriptografada é:\n%s\n\n", frase);
	return 0;
}


int selecionar(int opc){
	int *frase;
	int *auxint;
	int i;
	FILE *codific;
	char *aux;

	frase = calloc(160, sizeof(int));
	auxint = calloc(4, sizeof(int));
	aux = calloc(160, sizeof(char));

	codific = fopen("codific.txt", "r");
		rewind(codific);

		//coloca o cursor na posição certa
		for(i=1; i<opc; i++){
			fscanf(codific, "%s", aux);
		}
		
		//passa a frase para um vetor de inteiros
		for(i=0; *auxint!=169; i++){
			fscanf(codific, " %d", auxint);
			frase[i] = (int) *auxint;
			fseek(codific, sizeof(char), SEEK_CUR);
		}

	fclose(codific);

	free(auxint);
	free(aux);

	descodificar(frase, i-1); //i-1 é o tamanho da frase, pois i é incrementado uma vez a mais quando sai do for

	free(frase);
	return 0;
}


int codificar(){
	char opcao;

	//Ler a frase do usuário
	char *frase;

	frase = (char*) calloc(35, sizeof(char));
	printf("Digite a frase a ser criptografada: ");
	scanf(" %[^\n]s", frase);
	//gets(frase);

	int tam;
	tam = strlen(frase);


	//Passa o vetor de char para um vetor de int, já de forma embaralhada
	int i, j=0, *crip;
	crip = (int*) calloc(tam, sizeof(int));
	//primeira metade
	for(i=0; i<tam; i=i+2){
		crip[i] = (int) frase[j];
		j++;
	}
	//segunda metade
	for(i=1; i<tam; i=i+2){
		crip[i] = (int) frase[j];
		j++;
	}

	//Libera a frase original
	free(frase);

	//Multiplica todos os valores pela proporção declarada (um número primo grande, de preferência)
	//isso poderia ser feito no for anterior, mas está aqui para uma melhor visualização do processo de encriptação

	for(i=0; i<tam; i++){
		crip[i] = crip[i] * proportion;
	}

	printf("\n\nA mensagem criptografada é a seguinte:\n");
	//Imprime a mensagem criptografada
	for(i=0; i<tam; i++){
			printf("%d-", crip[i]);
	}

	//para colocar a mensagem codificada customizada no arquivo
	printf("\nDeseja colocar essa mensagem no arquivo (s/n)? ");
	scanf(" %c", &opcao);
	//validação da entrada	
	while(opcao != 's' && opcao != 'S' && opcao != 'n' && opcao != 'N'){
		printf("Digite uma opção válida! ");
		scanf(" %c", &opcao);
	}

	if(opcao == 's' || opcao == 'S'){
		FILE *codific;
		codific = fopen("codific.txt", "a");
			fprintf(codific, "\n");
			for(i=0; i<tam; i++){
				fprintf(codific, "%d-", crip[i]);
			}
			fprintf(codific, "169-");
		fclose(codific);
	}


	return 0;
}