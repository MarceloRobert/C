#include <stdio.h>

void mover (int disco, char origem, char destino, char aux){
	if(disco == 1){
		printf("\nMova disco %d de %c para %c", disco, origem, destino);
		return;
	} else {
		mover(disco-1, origem, aux, destino);
		printf("\nMova disco %d de %c para %c", disco, origem, destino);
		mover(disco-1, aux, destino, origem);
	}
}

int main(void) {
  int disco;
	char origem, destino, aux;

	system("clear");
	printf("Dê a quantidade de discos: ");
	scanf("%d", &disco);

	origem = 'A';
	aux = 'B';
	destino = 'C';

	mover(disco, origem, destino, aux);

	printf("\nFinalizado");
  return 0;
}

/*
FUNCIONAMENTO:

Para uma torre de tamanho n, é de certa forma simples o acontecimento: deseja-se passar toda a torre para o pino 3.

Para que toda a torre esteja no pino 3, é necessário que o disco maior esteja em 3.

Para que o disco maior esteja no pino 3 é necessário mover a torre toda (exceto o último disco, ou seja, de tamanho n-1) para o pino 2, o único local disponível.

Agora, se repetir os passos, queremos mover a torre toda (de tamanho n-1) do pino 1 para o pino 2. Então é necessário que o disco maior esteja em 2, então é necessário mover a torre n-2 para o pino 3.

Esse caso fará com que se repita o processo, sempre alternando o destino entre os pinos 3 e 2.

Para o caso base, n = 1, então simplesmente se move "toda a torre" para o pino de destino.
*/