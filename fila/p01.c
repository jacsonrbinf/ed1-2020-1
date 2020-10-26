#include <stdio.h>
#include <stdlib.h>

//Número máximo de pacientes no dia
#define N 25

//Struct de dados
typedef struct {
    int chegadaHr, chegadaMin, critico;
} dados;

int main(int argc, char** argv) {
    /*
     * n - número de pacientes
     * j - variável auxliar
     * hr - hora de possíveis atendimentos
     * min - minutos de possíveis atendimentos
     * i - início da fila
     * f - fim da fila
     * v[N] - vetor com as entradas
     * fila[N] - fila
     */
    int n, j, hr, min, cont, i, f;
    dados v[N], fila[N];

    //Lê o número de pacientes
    scanf("%d", &n);

    //Lê os horários de chegada dos pacientes
    for (i = 0; i < n; i++)
        scanf("%d%d%d", &v[i].chegadaHr, &v[i].chegadaMin, &v[i].critico);
    
    //Inicializa variáveis
    j = 0;
    hr = 7;
    min = 0;
    i = 0;
    f = 0;
    cont = 0;
    
    //Até terminar o expediente
    while(hr < 19){

        //Insere quem chegou até o horário atual de atendimento na fila
        while((hr*60+min) >= (v[j].chegadaHr*60 + v[j].chegadaMin) && j < n){
            fila[f].chegadaHr = v[j].chegadaHr;
            fila[f].chegadaMin = v[j].chegadaMin;
            fila[f].critico = v[j].critico;
            f++;
            j++;
        }
        
        //Se fila não for vazia
        if(f != 0){
            //Se o atendimento ocorrer depois do estado crítico
            if((hr*60+min) > (fila[i].chegadaHr*60 + fila[i].chegadaMin + fila[i].critico))
                cont++;
            
            i++;//"Remove" da fila
        } else if (j >= n)//Se a fila for vazia e já tiver percorrido todos os dados
            break;
        
        //Se removeu todos os dados da fila zera inicio e fim
        if(i == f){
            f = 0;
            i = 0;
        }
        
        //Incrementa o horário
        hr = hr + (min+30)/60;
        min = (min+30)%60;
    }

    //Imprime a saída
    printf("%d", cont);
    return (EXIT_SUCCESS);
}
