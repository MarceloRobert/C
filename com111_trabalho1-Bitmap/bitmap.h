#include <stdio.h>

#ifndef _TAD_BITMAP
#define _TAD_BITMAP


// Cria, libera, preenche e imprime a matriz
int* criar_bitmap(int id);
void liberar_bitmap(int* matriz);
void preenche_bitmap(int* matriz);
void imprime_bitmap(int* matriz);

// Consultar os dados
void consultar (int* matriz, int codigo);
void consulta_bitmap(int* matriz, int id);

#endif