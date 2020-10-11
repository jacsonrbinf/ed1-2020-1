    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    // defino minha struct que tera minha fila.
    typedef struct lista{
        char dado;
        struct lista *next;
    }Lista;
     
    // Função que aloca e cria um no.
     
    Lista *cria_no(char x){
        Lista *no = (Lista*) malloc(sizeof(Lista));
        no->dado = x;
        no->next = NULL;
        return no;
    }
     
    //  insere o nó no inicio da lista.
    Lista *insere_inicio(Lista *L, char x){
        Lista *tmp = cria_no(x);
        tmp->next = L; 
        return tmp;
    } 
     
    // Verifico se a lista esta vazia.
    int vazia(Lista *P){
        if(P == NULL) return 1;
        return 0;
    } 
     
    // Funão que remove elemento do inicio da lista
     
    Lista *remover(Lista *p){
        Lista *tmp = p->next;
        free(p);
        return tmp;
    }
     
    // Função recursiva que desaloca a fila.
     
    void limpa(Lista *L){
        if(L == NULL){
            return;
        }
        limpa(L->next);
        free(L);
        L = NULL;
    }
     
    int main(){
        // Variaveis que vou utilizar
        int i;
        Lista *pilha = NULL;
        char s[1010];
	printf("Forneca uma expressao:\n");
        scanf("%s", s);
        // Percorro toda a string
        for(i = 0;i < strlen(s);i++){
            // Se for '(, só preciso inserir
            if(s[i] == '(') pilha = insere_inicio(pilha, '(');
            // Se for ')' preciso checar se a pilha esta vazia, se estiver, esta errado.
            else if(!vazia(pilha) && s[i] == ')') pilha = remover(pilha);
            else if(vazia(pilha) && s[i] == ')'){
                // Insiro um placeholder, para dizer que esta incorreta.
                pilha = insere_inicio(pilha, '-');
                break;
            }
        }
        // Se a pilha não estiver vazia, esta incorreto.
        if(!vazia(pilha)) printf("incorreta\n");
        else printf("correta\n");
        limpa(pilha);
    }
