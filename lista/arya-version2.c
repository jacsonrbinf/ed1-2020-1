#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0

/*Reutilizando do TAD definida pelo prof Luciano http://www.each.usp.br/digiampietri/ed/ */

typedef int bool;
typedef int TIPOCHAVE;

typedef struct
{
    TIPOCHAVE chave;
    // outros campos...
} REGISTRO;

typedef struct tempRegistro
{
    REGISTRO reg;
    struct tempRegistro *prox;
} ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct
{
    PONT inicio;
} LISTA;

/* Inicialização da lista ligada (a lista jah esta criada e eh apontada
pelo endereco em l) */
void inicializarLista(LISTA *l)
{
    l->inicio = NULL;
} /* inicializarLista */

/* Exibição da lista seqüencial */
void exibirLista(LISTA *l)
{
    PONT end = l->inicio;
    printf("Lista: \" ");
    while (end != NULL)
    {
        printf("%d ", end->reg.chave); // soh lembrando TIPOCHAVE = int
        end = end->prox;
    }
    printf("\"\n");
} /* exibirLista */

/* Retornar o tamanho da lista (numero de elementos) */
int tamanho(LISTA *l)
{
    PONT end = l->inicio;
    int tam = 0;
    while (end != NULL)
    {
        tam++;
        end = end->prox;
    }
    return tam;
} /* tamanho */

/* Retornar o tamanho em bytes da lista. Neste caso, isto depende do numero
   de elementos que estao sendo usados.   */
int tamanhoEmBytes(LISTA *l)
{
    return (tamanho(l) * sizeof(ELEMENTO)) + sizeof(LISTA); // sizeof(LISTA) = sizeof(PONT) pois a "LISTA" possui apenas um ponteiro para o 1o elemento
} /* tamanhoEmBytes */

/* Busca sequencial (lista ordenada ou nao) */
PONT buscaSequencial(LISTA *l, TIPOCHAVE ch)
{
    PONT pos = l->inicio;
    while (pos != NULL)
    {
        if (pos->reg.chave == ch)
            return pos;
        pos = pos->prox;
    }
    return NULL;
} /* buscaSequencial */

/* Busca sequencial (lista ordenada) */
PONT buscaSeqOrd(LISTA *l, TIPOCHAVE ch)
{
    PONT pos = l->inicio;
    while (pos != NULL && pos->reg.chave < ch)
        pos = pos->prox;
    if (pos != NULL && pos->reg.chave == ch)
        return pos;
    return NULL;
} /* buscaSequencial */

/* Busca sequencial - funcao de exclusao (retorna no endereço *ant o indice do
   elemento anterior ao elemento que está sendo buscado [ant recebe o elemento
   anterior independente do elemento buscado ser ou não encontrado]) */
PONT buscaSeqExc(LISTA *l, TIPOCHAVE ch, PONT *ant)
{
    *ant = NULL;
    PONT atual = l->inicio;
    while (atual != NULL && atual->reg.chave < ch)
    {
        *ant = atual;
        atual = atual->prox;
    }
    if ((atual != NULL) && (atual->reg.chave == ch))
        return atual;
    return NULL;
}
/* buscaSequencialExc */

/* Exclusão do elemento de chave indicada */
bool excluirElemLista(LISTA *l, TIPOCHAVE ch)
{
    PONT ant, i;
    i = buscaSeqExc(l, ch, &ant);
    if (i == NULL)
        return false;
    if (ant == NULL)
        l->inicio = i->prox;
    else
        ant->prox = i->prox;
    free(i);
    return true;
} /* excluirElemLista */

/* Destruição da lista sequencial
   libera a memoria de todos os elementos da lista*/
void reinicializarLista(LISTA *l)
{
    PONT end = l->inicio;
    while (end != NULL)
    {
        PONT apagar = end;
        end = end->prox;
        free(apagar);
    }
    l->inicio = NULL;
} /* destruirLista */

/* Inserção em lista ordenada sem duplicação */
bool inserirElemListaOrd(LISTA *l, REGISTRO reg)
{
    TIPOCHAVE ch = reg.chave;
    PONT ant, i;
    i = buscaSeqExc(l, ch, &ant);
    if (i != NULL)
        return false;
    i = (PONT)malloc(sizeof(ELEMENTO));
    i->reg = reg;
    if (ant == NULL)
    { // o novo elemento serah o 1o da lista
        i->prox = l->inicio;
        l->inicio = i;
    }
    else
    { // inserção após um elemento já existente
        i->prox = ant->prox;
        ant->prox = i;
    }
    return true;
} /* inserirElemListaOrd */

/* retornarPrimeiro - retorna o endereco do primeiro elemento da lista e (caso
   a lista nao esteja vazia) retorna a chave desse elemento na memoria
   apontada pelo ponteiro ch */
PONT retornarPrimeiro(LISTA *l, TIPOCHAVE *ch)
{
    if (l->inicio != NULL)
        *ch = l->inicio->reg.chave;
    return l->inicio;
} /* retornarPrimeiro */

/* retornarUltimo - retorna o endereco do ultimo elemento da lista e (caso
   a lista nao esteja vazia) retorna a chave desse elemento na memoria
   apontada pelo ponteiro ch */
PONT retornarUltimo(LISTA *l, TIPOCHAVE *ch)
{
    PONT ultimo = l->inicio;
    if (l->inicio == NULL)
        return NULL;
    while (ultimo->prox != NULL)
        ultimo = ultimo->prox;
    *ch = ultimo->reg.chave;
    return ultimo;
} /* retornarUltimo */


// Especificações referentes à Lista de Arya

bool inserir_lista_final(LISTA *li, REGISTRO al)
{
    if (li == NULL)
        return false;
    PONT no;
    no = (PONT)malloc(sizeof(ELEMENTO));
    if (no == NULL)
        return false;
    no->reg = al;
    no->prox = NULL;
    if (li->inicio == NULL)
    { //lista vazia: insere início
        li->inicio = no;
    }
    else
    {
        PONT aux;
        aux = li->inicio;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return true;
}

int Insercao(LISTA *li, REGISTRO p, REGISTRO e)
{
    if (li == NULL)
        return false;
    PONT no = li->inicio;
    while (no != NULL && no->reg.chave != e.chave)
    {
        no = no->prox;
    }

    PONT noNovo;
    noNovo = (PONT)malloc(sizeof(ELEMENTO));
    if (noNovo == NULL)
        return false;

    noNovo->reg = p;
    noNovo->prox = no->prox;
    no->prox = noNovo;

    printf("inserido %i", p.chave);
}

int busca_posicao_elemento(LISTA *li, REGISTRO registro)
{
    if (li == NULL)
    {
        return 0;
    }
    else
    {
        PONT no = li->inicio;
        int i = 1;
        while (no != NULL)
        {
            if (no->reg.chave == registro.chave) return i;
            no = no->prox;
            i++;
        }
        return 0;
    }
}

void Contagem(LISTA *li, REGISTRO elema, REGISTRO elemb)
{
    int a, b, distancia;
    a = busca_posicao_elemento(li, elema);
    b = busca_posicao_elemento(li, elemb);

    if (a > b)
    {
        distancia = a - b - 1;
    }
    else
    {
        if (b > a)
        {
            distancia = b - a - 1;
        }
        else
        {
            if (b == a)
            {
                distancia = -1;
            }
        }
    }
    printf("quantidade %i", distancia);
    //return distancia;
}

void MostraLista(LISTA *li)
{
    printf("lista ");
    exibirLista(li);
}

int Remocao(LISTA *li, TIPOCHAVE ch)
{
    bool excluido;

    excluido = excluirElemLista(li, ch);
    if (excluido == true)
        printf("removido %i", ch);
}

int main()
{
    LISTA lista;
    inicializarLista(&lista);

    TIPOCHAVE ch, chp, che;
    REGISTRO dado, p, e;
    char operacao;
    int n, i;

    //printf("Lista de Arya\n\n");
    scanf("%d", &n);
    while ((n < 1) || (n > 1000))
    {
        scanf("%d", &n);
    }
    for (i = 0; i < n; i++)
    {
        scanf("%d", &ch);
        dado.chave = ch;
        inserir_lista_final(&lista, dado);
    }

    // Execucao de operacoes I, R, C, M ou F
    do
    {
        scanf("%c", &operacao);
        if (operacao == 'I')
        {
            scanf("%i%i", &chp, &che);
            p.chave = chp;
            e.chave = che;
            Insercao(&lista, p, e);
        }

        if (operacao == 'C')
        {
            scanf("%i%i", &chp, &che);
            p.chave = chp;
            e.chave = che;
            Contagem(&lista, p, e);
        }

        if (operacao == 'M')
        {
            MostraLista(&lista);
        }

        if (operacao == 'R')
        {
            scanf("%i", &chp);
            p.chave = chp;
            Remocao(&lista, p.chave);
        }
        if (operacao == 'F')
        {
            printf("fim\n");
            break;
        }

    } while (1);

    reinicializarLista(&lista);
    //printf("fim\n");
    return 0;
}
