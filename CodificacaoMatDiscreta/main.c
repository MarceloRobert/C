#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cript.h"

//Tarefa de matemática discreta sobre codificação de mensagens usando uma função e a conseguinte decodificação da mensagem usando a função inversa à codificação

int main(void) {
	int opcao, escolha, tamarq;
	char test;
	FILE *codific;
	char *aux;

	system("clear");
	do{
		printf("\nEscolha uma opção:");
		printf("\n1 - Ver mensagens a serem decodificadas");
		printf("\n2 - Decodificar mensagem escolhida");
		printf("\n3 - Codificar mensagem customizada");
		printf("\n4 - Sair");
		printf("\n\nEscolha: ");
		scanf("%d", &opcao);

		switch(opcao){
			case 1: //ver mensagens
				system("clear");
				aux = calloc(160,sizeof(char));
				test = 'a';

				codific = fopen("codific.txt", "r");
					rewind(codific);
					fseek(codific, sizeof(char), SEEK_CUR);
					while(test != EOF){
						fseek(codific, -sizeof(char), SEEK_CUR);
						fscanf(codific, " %[^\n]s", aux);
						printf("\n%s\n", aux);
						test = fgetc(codific);
					}
				fclose(codific);
				
				free(aux);

				break;

			case 2: //decodificar mensagem escolhida
				system("clear");
				tamarq = 0;

				//olha no arquivo quantas mensagens tem
				aux = calloc(200,sizeof(char));
				test = 'a';
				codific = fopen("codific.txt", "r");
					rewind(codific);
					fseek(codific, sizeof(char), SEEK_CUR);
					while(test != EOF){
						fseek(codific, -sizeof(char), SEEK_CUR);
						fscanf(codific, " %[^\n]s", aux);
						test = fgetc(codific);
						tamarq++;
					}
				fclose(codific);				
				free(aux);
				

				//recebe a escolha do usuário, com validação
				printf("Selecione a mensagem a ser descriptografada: ");
				scanf("%d", &escolha);
				while(escolha <= 0 || escolha > tamarq){
					printf("\nDigite um número válido! ");
					scanf("%d", &escolha);
				}

				//decodifica a mensagem escolhida
				selecionar(escolha);
				break;

			case 3: //codificar sua própria mensagem
				system("clear");
				codificar();
				break;

			case 4: //sair
				system("clear");
				printf("Programa encerrado.");
				break;

			default:
				system("clear");
				printf("Digite uma opção válida!\n");
				break;
		}
	} while(opcao != 4);

	return 0;
}