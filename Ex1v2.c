/*
	Instituição: UFG
	Cursos: Engenharia de Computação
	Disciplina: Estrutura de Dados 1 - 2020-1
	Professor: André Luiz Moura
	Exercício: Lista de Exercícios sobre TAD
	Finalidade: Conjunto sobre Números Naturais
	Data de criação: 08/09/2020
	Última alteração: 15/09/2020 - 22h43
*/
#include <stdlib.h>	// malloc, free, exit, system
#include <stdio.h>	// printf, scanf
#include <malloc.h>	// malloc, realloc
#include <conio.h>	// getch
#include <ctype.h> 	// toupper
#include <string.h>	// stricmp
#define SUCESSO 1
#define FALHA 0

// TAD Array dinâmico
// Definição de tipo do array unidimensional de inteiros
typedef int* arrayInt;

struct Conjunto {
	int tamanho;	// Quantidade de elementos armazenados
	arrayInt Elementos; // Array para armazenamento dos elementos do conjunto
};

// Protótipo de funções 
int criaConjunto(struct Conjunto *);
int conjuntoVazio(struct Conjunto *);
int insereElementoConjunto(int, struct Conjunto *);
int tamanhoConjunto(struct Conjunto *);
int destroiConjunto(struct Conjunto *);
int excluirElementoConjunto(int, struct Conjunto *);
int tamanhoConjunto(struct Conjunto *);

int maior(int, struct Conjunto *);
int menor(int, struct Conjunto *);
int pertenceConjunto(int, struct Conjunto *);
int conjuntosIdenticos(struct Conjunto *, struct Conjunto *);
int subconjunto(struct Conjunto *, struct Conjunto *);
struct Conjunto* complemento(struct Conjunto *, struct Conjunto *);
struct Conjunto* uniao(struct Conjunto *, struct Conjunto *);
struct Conjunto* interseccao(struct Conjunto *, struct Conjunto *);
struct Conjunto* diferenca(struct Conjunto *, struct Conjunto *);
struct Conjunto* conjuntoPartes(struct Conjunto *);
void mostraConjunto(struct Conjunto *, int);
int copiarConjunto(struct Conjunto *, struct Conjunto *);

int cmp (const void *, const void *);

int main() 
{
	struct Conjunto C1, C2;
	int elemento; 
	int i;
	char ch;
	char conjuntoDestino[3];
	
	C1.Elementos = NULL;
	C1.tamanho = 0;
	C2.Elementos = NULL;
	C2.tamanho = 0;
	
	do {
		printf("Conjuntos de Numeros Naturais\n\n");
		printf("A. Criar conjunto vazio\n");
		printf("B. Verificar se conjunto eh vazio\n");
		printf("C. Incluir elemento no conjunto\n");
		printf("D. Excluir elemento do conjunto\n");
		printf("E. Calcular cardinalidade do conjunto\n");
		printf("F. Quantificar elementos maiores que x\n");
		printf("G. Quantificar elementos menores que x\n");
		printf("H. Verificar se elemento pertence ao conjunto\n");
		printf("I. Verificar se dois conjunto sao identicos\n");
		printf("J. Verificar se o conj. C1 eh subconjunto do conj. C2\n");
		printf("K. Gerar complemento do conj. C1 em relacao ao conj. C2\n");
		printf("L. Gerar uniao do conjunto C1 com o conjunto C2\n");
		printf("M. Gerar interseccao do conjunto C1 com o conjunto C2\n");
		printf("N. Gerar diferenca entre o conjunto C1 e o conjunto C2\n");
		printf("O. Gerar conjunto das partes no conjunto C\n");
		printf("P. Mostrar os elementos presentes no conjunto C\n");
		printf("Q. Copiar o conjunto C1 para o conjunto C2\n");
		printf("R. Destruir o conjunto\n");
		printf("S. Sair\n");
		ch = getch();

		switch(toupper(ch)) {
			case 'A':
				if (criaConjunto(&C1))
					printf("Conjunto C1 criado com sucesso!\n");
				else
					printf("Conjunto C1 nao criado!\n");
						
				if (criaConjunto(&C2))
					printf("Conjunto C2 criado com sucesso!\n");
				else
					printf("Conjunto C2 nao criado!\n");
				printf("\n");
				break;

			case 'B':
				if (conjuntoVazio(&C1))
					printf("Conjunto C1 vazio!\n");
				else
					printf("Conjunto C1 nao vazio!\n");
					
				if (conjuntoVazio(&C2))
					printf("Conjunto C2 vazio!\n");
				else
					printf("Conjunto C2 nao vazio!\n");									
				break;

			case 'C':
				printf("Conjunto de destino [C1, C2]: ");
				scanf("%[^\n]", conjuntoDestino);
				printf("Elemento a ser inserido: ");
				scanf("%d%*c", &elemento);
				if (stricmp(conjuntoDestino, "C1") == 0) {
					if (insereElementoConjunto(elemento, &C1)) {
						printf("Elemento %d inserido com sucesso em C1!\n", elemento);
					}
					else {
						printf("Elemento %d nao inserido!\n");
					}
				}				
				else if (stricmp(conjuntoDestino, "C2") == 0) {
					if (insereElementoConjunto(elemento, &C2)) {
						printf("Elemento %d inserido com sucesso em C2!\n", elemento);
					}
					else {
						printf("Elemento %d nao inserido!\n");
					}					
				}
				else {
					printf("Nome de conjunto invalido!\n");
				}
				break;

			case 'D':
				printf("Conjunto de destino [C1, C2]: ");
				scanf("%[^\n]", conjuntoDestino);
				printf("Elemento a ser excluido: ");
				scanf("%d%*c", &elemento);
				
				if (stricmp(conjuntoDestino, "C1") == 0) {
					if (conjuntoVazio(&C1)) {
						printf("Conjunto C1 vazio!\n");
					}
					else {
						if (excluirElementoConjunto(elemento, &C1)) {
							printf("Elemento %d excluido com sucesso em C1!\n", elemento);
						}
						else {
							printf("Elemento %d nao excluido!\n", elemento);
						}
					}
				}				
				else if (stricmp(conjuntoDestino, "C2") == 0) {
					if (conjuntoVazio(&C2)) {
						printf("Conjunto C2 vazio!\n");
					}
					else {
						if (excluirElementoConjunto(elemento, &C2)) {
							printf("Elemento %d excluido com sucesso em C2!\n", elemento);
						}
						else {
							printf("Elemento %d nao excluido!\n", elemento);
						}					
					}
				}
				else {
					printf("Nome de conjunto invalido!\n");
				}				
				break;

			case 'E':
				printf("Conjunto de destino [C1, C2]: ");
				scanf("%[^\n]", conjuntoDestino);
				if (stricmp(conjuntoDestino, "C1") == 0)
					printf("Cardinalidade do conjunto C1: %d\n\n", tamanhoConjunto(&C1));
				else if (stricmp(conjuntoDestino, "C2") == 0)
					printf("Cardinalidade do conjunto C2: %d\n\n", tamanhoConjunto(&C2));
				else
					printf("Nome de conjunto invalido!\n");
				break;

			case 'F':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'G':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'H':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'I':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'J':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'K':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'L':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'M':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'N':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'O':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'P':
				int ordem;
				printf("Conjunto de destino [C1, C2]: ");
				scanf("%[^\n]", conjuntoDestino);
				printf("Ordem (1. Crescente, 2. Decrescente): ");
				scanf("%i%*c", &ordem);
				if (stricmp(conjuntoDestino, "C1") == 0) {
					if (conjuntoVazio(&C1)) {
						printf("Conjunto C1 vazio!\n");
					}
					else {
						mostraConjunto(&C1, ordem);
					}
				}				
				else if (stricmp(conjuntoDestino, "C2") == 0) {
					if (conjuntoVazio(&C2)) {
						printf("Conjunto C2 vazio!\n");
					}
					else {
						mostraConjunto(&C2, ordem);
					}
				}
				else {
					printf("Nome de conjunto invalido!\n");
				}				
				break;

			case 'Q':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'R':
				printf("\nPrograma finalizado com sucesso!");
				break;

			case 'S':
				printf("\nPrograma finalizado com sucesso!");
				exit(0);
				break;

			default:
				printf("\nEntrada errada!");
		}
		printf("\n");
	} while (toupper(ch) != 'S');

		
	if (destroiConjunto(&C1))
		printf("Conjunto C destruido com sucesso!");
	else
		printf("Falha na destruicao do conjunto C");
		
	system("pause > nul");
	
	return 0;
}


int criaConjunto(struct Conjunto *C)
{
	if (C->Elementos == NULL) {
		printf("Ainda nao fui criado\n");
		C->Elementos = (arrayInt) malloc(1 * sizeof(int));
		C->tamanho = 0;
	}
	else {
		printf("Conjunto jah havia sido criado!\n");
	}
	return (C->Elementos != NULL);
}

int conjuntoVazio(struct Conjunto *C)
{	
	return (C->tamanho == 0);
}


int insereElementoConjunto(int x, struct Conjunto *C)
{
	int insercaoOcorrida = FALHA;
	
	C->Elementos[C->tamanho] = x;
	
	C->Elementos = (arrayInt) realloc(C->Elementos, (C->tamanho)+1 * sizeof(int));
    if (C->Elementos == NULL) {
        printf("Nao ha memoria suficiente!");
    }
    else {
        C->tamanho++;
        
        insercaoOcorrida = SUCESSO;
    }	
    return insercaoOcorrida;
}

// Apresenta bug?!
int excluirElementoConjunto(int x, struct Conjunto *C)
{
	int exclusaoOcorrida = FALHA;
	int elementoEncontrado = FALHA;
	int i, j, pos;
	for (i=0; i<C->tamanho; i++) {
		if (C->Elementos[i] == x) {
			elementoEncontrado = SUCESSO;
			pos = i;
			break;
		}
	}
	
	if (elementoEncontrado) {
		for (i=pos; i<C->tamanho-1; i++) {
			C->Elementos[i] = C->Elementos[i+1];	
		}		
		C->Elementos = (arrayInt) realloc(C->Elementos, (C->tamanho)-1 * sizeof(int));
		C->tamanho--;
		exclusaoOcorrida = SUCESSO;
	}
    return exclusaoOcorrida;
}


int tamanhoConjunto(struct Conjunto *C)
{
	return C->tamanho; 
}


int destroiConjunto(struct Conjunto *C)
{
	free(C->Elementos);
	C->Elementos = NULL;
	C->tamanho = 0;
	return (C->Elementos == NULL);
}


// Apresenta bug após exclusao do valor 3 da sequência 1, 3, 5 ou 1, 3, 5, 7
void mostraConjunto(struct Conjunto *C, int ordem)
{
	int i;
	
	/* Ordena os elementos do array */
	qsort(C->Elementos, C->tamanho, sizeof (int), cmp);
	
	printf("Elementos do conjunto ");
	if (ordem == 1)	{ // Crescente
		printf("em ordem crescente: ");
		for (i=0; i<C->tamanho; i++) {
			printf("%i ", C->Elementos[i]);
		}
	}
	else {
		printf("em ordem decrescente: ");
		for (i=C->tamanho-1; i>=0; i--) {
			printf("%i ", C->Elementos[i]);
		}
	}
	printf("\n\n");	
}
	
/* Define as regras de comparacao utilizadas em 'qsort' */
int cmp (const void *x, const void *y)
{
	return (*(int *)x - *(int *)y);
}
