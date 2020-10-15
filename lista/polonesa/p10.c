//
// Lista 8 -- Exercicio 10 -- Notacao Polonesa Inversa
// 

#include <stdio.h>
#include <stdlib.h>

#define SUCESSO                1
#define FALHA                 -1
#define CHAVE_INVALIDA         0

#define MAXIMO_TESTES            10
#define TAMANHO_MAXIMO_PILHA   1000

/*
 * Representação de uma célula da Pilha : [<chave>, <dado>], onde a chave pode 
 * estar no intervalo de 1 ao "máximo inteiro" e o valor ZERO é considerado
 * um valor inválido -- flag
 */
typedef struct { 
     unsigned int chave;
     char         dado;
} Celula;  

/*
 * Representação da Pilha 
 */
typedef struct {
    Celula celulas  [TAMANHO_MAXIMO_PILHA];
    unsigned int    tamanho;
} Pilha; 

/*
 * Criação da Pilha ...
 *     Pode-se criar uma Pilha  inicialmente vazia ou com uma <chave/dado>
 *     já inserida.
 * 
 */
int criarPilhaVazia(Pilha * Pilha ) {
    Pilha ->tamanho = 0;
    return (SUCESSO);
}

int criarPilhaChave(Pilha * Pilha , Celula celula) {
    Pilha ->celulas[0] = celula;
    Pilha ->tamanho    = 1;
    return (SUCESSO);
}

/*
 * Determina, e retorna, o número de células presentes na Pilha.
 */
int tamanhoPilha(Pilha Pilha ) {
    unsigned int i;
    
    if (Pilha.tamanho >= 0) { 
       return(Pilha .tamanho);   
    }
    else {
       return(FALHA);
    }
}

/*
 *  A inserção de uma <chave/dado> pode ocorrer...
 *    - no final da Pilha : após a última célula.
 */

int push (Pilha * Pilha , Celula celula) {
    unsigned int i;
    Celula auxiliar;
    
    if (Pilha->tamanho == TAMANHO_MAXIMO_PILHA) {
        return(FALHA);                 // Overflow da Pilha. 
    }
    else { 
       // 
       // Insere a célula recebida após a última célula atualmente
       // presente na Pilha 
       // 
       Pilha ->celulas[Pilha ->tamanho] = celula;
       Pilha ->tamanho++;
       return(SUCESSO);
    }
}

/*
 *  A remoção de uma <chave/dado> pode ocorrer...
 *    - no início da Pilha : a primeira célula.
 *   
 *  Observação: A remoção devolve a célula removida ou uma célula com chave 
 *              igual a CHAVE_INVALIDA, indicando erro na remoção. 
 */
Celula pop (Pilha * Pilha ) {
    unsigned int i;
    Celula   celulaResultado;
        
    if (Pilha ->tamanho == 0) {        // A Pilha está vazia ?
        celulaResultado.chave = CHAVE_INVALIDA;
        return(celulaResultado);
    }
    else {
       // 
       // Remove a primeira célula da Pilha e atualiza o tamanho desta...
       // 
       celulaResultado = Pilha ->celulas[0];
       for (i = 0; (i < Pilha ->tamanho - 1); i++) {
           Pilha ->celulas[i] = Pilha ->celulas[i+1];
       } 
       Pilha ->tamanho--;
       return(celulaResultado);
    }
}

/*
 * Retorna a célula (primeira) cuja chave é igual à solicitada ou 
 * uma célula com chave igual a CHAVE_INVALIDA, indicando que não encontrou a
 * célula desejada na Pilha. 
 */
Celula consultaChave(Pilha Pilha , Celula celula) {
    unsigned int i;
    
    for (i = 0; (i < Pilha .tamanho); i++) {
        if (Pilha .celulas[i].chave == celula.chave) {
            return(Pilha .celulas[i]);
        }
    }
    celula.chave = CHAVE_INVALIDA;
    return(celula);
}

/*
 * Retorna a célula cuja posição é igual à solicitada ou 
 * uma célula com chave igual a CHAVE_INVALIDA, indicando que não existe a
 * célula desejada na Pilha . 
 * 
 * A primeira célula está na posição UM.
 */
Celula consultaPosicao(Pilha Pilha , unsigned int intPosicao) {
    
    Celula celulaResultado;
    
    if ((intPosicao > 0) && (intPosicao <= Pilha .tamanho)) { 
        celulaResultado = Pilha .celulas[intPosicao - 1];
    }
    else {
        celulaResultado.chave = CHAVE_INVALIDA;
    }
    return(celulaResultado);
}

/*
 * Concatena duas Pilhas, desde que a Pilha  final não ultrapasse 
 * o tamanho máximo permitido. Neste caso, retorna uma Pilha  linear
 * "falsa", cujo tamanho é igual a FALHA, indicando que ocorreu um 
 * erro durante a concatenação.
 */

Pilha concatPilhas(Pilha *Pilha1, Pilha *Pilha2) {
    unsigned int i;
    int          intResultado;
    Celula       celula;
    Pilha         PilhaResultado;
    
    i = criarPilhaVazia(&PilhaResultado);
    if ((Pilha1->tamanho + Pilha2->tamanho) > TAMANHO_MAXIMO_PILHA) {
        PilhaResultado.tamanho = FALHA;
        return (PilhaResultado); 
    }
    else {
        for (i = 0; (i < Pilha1->tamanho); i++) {
            celula       = consultaPosicao(*Pilha1,(unsigned int) (i+1));
            intResultado = push(&PilhaResultado, celula);
            if (intResultado == CHAVE_INVALIDA) {
                PilhaResultado.tamanho = FALHA;
                return (PilhaResultado);
            }
        }
        for (i = 0; (i < Pilha2->tamanho); i++) {
            celula       = consultaPosicao(*Pilha2,(unsigned int) (i+1));
            intResultado = push(&PilhaResultado, celula);
            if (intResultado == CHAVE_INVALIDA) {
                PilhaResultado.tamanho = FALHA;
                return (PilhaResultado);
            }
        }
    }
}

/*
 * Apresenta, no dispositivo de saída (monitor de vídeo), o valor
 * da <chave> e do <dado> de uma célula recebida como entrada.
 */
void mostrarCelula(Celula celula) {
    printf("Chave......: %u\n", celula.chave);
    printf("Dado.......: %u\n", celula.dado);
}

/*
 * Mostra as células da Pilha , a partir de sua 'cabeça' até sua 'cauda'.
 */
void mostrarPilha(Pilha Pilha) {
    unsigned int i;
    
    if (Pilha.tamanho == 0) { 
       printf("Atenção: A Pilha  está vazia.\n");   
    }
    else {
       printf("A <pilha> possui %u elementos.\n\n", Pilha.tamanho); 
       for (i = 0; (i < Pilha.tamanho); i++) {
           printf("Elemento nº: %u\n", (i+1)); 
           mostrarCelula(Pilha.celulas[i]);
       }
    }
}
/*
 * Programa principal: utiliza as funções de Pilha
 * 
 */
int main(int argc, char** argv) {
    int    i, t;
    int    intResultado;
    char   ch;
    Pilha  Pilha;
    Celula celula;
    //
    // Cria, inicialmente, uma Pilha vazia...
    //
    intResultado =  criarPilhaVazia(&Pilha);
    if (intResultado == FALHA) {
        return(EXIT_FAILURE);
    }
    mostrarPilha(Pilha);
    
    do { 
       scanf("%u",&t);
    } while ((t < 1) || (t > MAXIMO_TESTES));
    for (i = 0; (i < t); i++) {
        do { 
           ch = getchar();
           switch (ch) {
                case '(':
                case ')':
                case '+':
                case '-':
                case '*':
                case '/':
                case '^':
                default : printf("\n%c",ch);
           }
        } while (ch != 13); 
    }
        
    return (EXIT_SUCCESS);
}

