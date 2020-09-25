/* ED1 - EC
   LISTA DE ARYA - CÓDIGO PARCIAL

   Prof. André L. Moura e Prof. Jacson
*/
//Arquivo ListaDinEncad.h
#include <stdio.h>
#include <stdlib.h>

struct registro
{
    int id;
    // Outros campos/membros
};

//Definição do tipo lista
struct elemento
{
    struct registro dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

typedef struct elemento *Lista;

Lista *cria_lista();
void libera_lista(Lista *li);
int insere_lista_final(Lista *li, struct registro al);
int insere_lista_inicio(Lista *li, struct registro al);
int insere_lista_ordenada(Lista *li, struct registro al);
int remove_lista(Lista *li, int mat);
int remove_lista_inicio(Lista *li);
int remove_lista_final(Lista *li);
int tamanho_lista(Lista *li);
int lista_vazia(Lista *li);
int lista_cheia(Lista *li);
void imprime_lista(Lista *li);
int consulta_lista_elem(Lista *li, int elem, struct registro *al);
int consulta_lista_pos(Lista *li, int pos, struct registro *al);
int busca_posicao_elemento(Lista *li, struct registro al);

// Especificações referentes à Lista de Arya
void MostraLista(Lista *li);
int InsercaoInimigosIniciais(Lista *li, struct registro al);
int Insercao(Lista *li, struct registro p, struct registro e);
int consulta_lista_mat(Lista *li, int mat, struct registro *al);
void Contagem(Lista *li, struct registro elema, struct registro elemb);
int Remocao(Lista *li, int elem);

int main()
{
    struct registro al;
    Lista *li = cria_lista();
    char operacao;
    int param1, param2;
    int nInimigosIniciais, inimigo;
    struct registro p, e;
    int i;

    printf("Lista de Arya\n\n");
    scanf("%i", &nInimigosIniciais);

    for (i = 1; i <= nInimigosIniciais; i++)
    {
        scanf("%i%*c", &inimigo);
        al.id = inimigo;

        InsercaoInimigosIniciais(li, al);
    }

    // Execução de operações I, R, C, M ou F
    do
    {
        scanf("%c", &operacao);
        if (operacao == 'I')
        {
            scanf("%i%i", &p, &e);
            Insercao(li, p, e);
        }

        if (operacao == 'C')
        {
            scanf("%i%i", &p, &e);
            Contagem(li, p, e);
        }

        if (operacao == 'M')
        {
            MostraLista(li);
        }

        if (operacao == 'R')
        {
            scanf("%i", &p);
            Remocao(li, p.id);
        }
        if (operacao == 'F')
        {
            printf("fim");
            break;
        }

    } while (1);

    libera_lista(li);
    system("pause > nul");
    return 0;
}

Lista *cria_lista()
{
    Lista *li = (Lista *)malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista *li)
{
    if (li != NULL)
    {
        Elem *no;
        while ((*li) != NULL)
        {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista *li, int pos, struct registro *al)
{
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos)
    {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else
    {
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_elem(Lista *li, int elem, struct registro *al)
{
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.id != elem)
    {
        no = no->prox;
    }
    if (no == NULL)
        return 0;
    else
    {
        *al = no->dados;
        return 1;
    }
}

int busca_posicao_elemento(Lista *li, struct registro al)
{
    if (li == NULL)
    {
        return 0;
    }
    else
    {
        Elem *no = *li;
        int i = 1;
        while (no != NULL)
        {
            if (no->dados.id == al.id) return i;
            no = no->prox;
            i++;
        }
        return 0;
    }
}

int insere_lista_final(Lista *li, struct registro al)
{
    if (li == NULL)
        return 0;
    Elem *no;
    no = (Elem *)malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if ((*li) == NULL)
    { //lista vazia: insere início
        *li = no;
    }
    else
    {
        Elem *aux;
        aux = *li;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return 1;
}

int insere_lista_inicio(Lista *li, struct registro al)
{
    if (li == NULL)
        return 0;
    Elem *no;
    no = (Elem *)malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_lista_ordenada(Lista *li, struct registro al)
{
    if (li == NULL)
        return 0;
    Elem *no = (Elem *)malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL)
    { //lista vazia: insere início
        no->prox = NULL;
        *li = no;
        return 1;
    }
    else
    {
        Elem *ant, *atual = *li;
        while (atual != NULL && atual->dados.id < al.id)
        {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li)
        { //insere início
            no->prox = (*li);
            *li = no;
        }
        else
        {
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_lista(Lista *li, int elem)
{
    if (li == NULL)
        return 0;
    if ((*li) == NULL) //lista vazia
        return 0;
    Elem *ant, *no = *li;
    while (no != NULL && no->dados.id != elem)
    {
        ant = no;
        no = no->prox;
    }
    if (no == NULL) //não encontrado
        return 0;

    if (no == *li) //remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int remove_lista_inicio(Lista *li)
{
    if (li == NULL)
        return 0;
    if ((*li) == NULL) //lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_lista_final(Lista *li)
{
    if (li == NULL)
        return 0;
    if ((*li) == NULL) //lista vazia
        return 0;

    Elem *ant, *no = *li;
    while (no->prox != NULL)
    {
        ant = no;
        no = no->prox;
    }

    if (no == (*li)) //remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return 1;
}

int tamanho_lista(Lista *li)
{
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem *no = *li;
    while (no != NULL)
    {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista *li)
{
    return 0;
}

int lista_vazia(Lista *li)
{
    if (li == NULL)
        return 1;
    if (*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista *li)
{
    if (li == NULL)
        return;
    Elem *no = *li;
    while (no != NULL)
    {
        printf("%d ", no->dados.id);
        no = no->prox;
    }
}

// Implementações referentes à Lista de Arya
void MostraLista(Lista *li)
{
    printf("lista ");
    imprime_lista(li);
}

int InsercaoInimigosIniciais(Lista *li, struct registro al)
{
    insere_lista_final(li, al);
}

int Insercao(Lista *li, struct registro p, struct registro e)
{
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.id != e.id)
    {
        no = no->prox;
    }

    Elem *noNovo;
    noNovo = (Elem *)malloc(sizeof(Elem));
    if (noNovo == NULL)
        return 0;

    noNovo->dados = p;
    noNovo->prox = no->prox;
    no->prox = noNovo;

    printf("inserido %i", p.id);
}


void Contagem(Lista *li, struct registro elema, struct registro elemb)
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

int Remocao(Lista *li, int elem)
{
    printf("removido %i", elem);
    remove_lista(li, elem);
}
