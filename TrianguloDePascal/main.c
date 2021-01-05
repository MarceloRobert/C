#include <stdio.h>

//código simples para gerar o triângulo de Pascal das duas formas possíveis

int Pas(int h, int ind){
	int elemento;

	if(ind == 0){
		elemento = 1;
	} else {
		if(ind == h){
			elemento = 1;
		} else {
			elemento = Pas(h-1, ind) + Pas(h-1, ind-1);
		}
	}

	return elemento;
}

int fatorial(int num){
	int elemento;

	if(num == 1 || num == 0)
		elemento = 1;
	else
	  elemento = (num) * (fatorial(num-1));
	
	return elemento;
}

int main(void) {
  int n;
	int i, h, elemento;
	printf("Quantas linhas do triângulo de Pascal devem ser geradas? ");
	scanf("%d", &n);


	printf("primeiro método - recursividade\n");
	for(h=0; h<n; h++){
		for(i=0; i<=h; i++){
			elemento = Pas(h, i);
			printf("%d ", elemento);
		}
		printf("\n");
	}


	printf("\n\n");


	printf("segundo método - combinação da altura sobre o índice\n");
	for(h=0; h<n; h++){
		for(i=0; i<=h; i++){
			elemento = fatorial(h)/(fatorial(i) * fatorial(h-i));
			printf("%d ", elemento);
		}
		printf("\n");
	}


	printf("\n\n");
	

  return 0;
}