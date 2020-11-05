#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <unistd.h> //só funcionam no linux
//#include <sys/wait.h>

char *read_line (void);
char *verifica_espaco (char* linha);
int verifica_virgulas(char* linha);


int main(){
    char *linha;
    char *comando;
    char **comandos = malloc(sizeof(char*) * 30);
    char **comandos2 = malloc(sizeof(char*) * 30);
    int i=0;
    int qtd_virgula;


    if (!comandos) {
        fprintf(stderr, "lsh: erro de alocacao\n");
        return 0;
    }

    if (!comandos2) {
        fprintf(stderr, "lsh: erro de alocacao\n");
        return 0;
    }


    while(1 == 1) { //while para depois de uma execução por causa do return 0 no final
        printf("meu_shell> ");
        linha = read_line();
        linha = verifica_espaco(linha);
        qtd_virgula=verifica_virgulas(linha);


        //esse segmento de código faz a separação da linha digitada em vários comandos
        //se é uma entrada vazia (exempo: ,,,,,,,) nada é armazenado
            comando = strtok(linha, ",");
            while (comando != NULL) {
                if (comando[i] == ' ') { //verifica se é entrada vazia
                    i++;
                } else {
                    comandos[i] = comando;
                    i++;
                }

                comando = strtok(NULL, ",");
            }

            //comandos esta armazenando strings separadas pela virgula
            comandos[i]=NULL;

                i = 0;
                    for(int z=0; z<(qtd_virgula+1); z++) {
                        comando = strtok(comandos[z], " ");

                        while (comando != NULL) { //pega todas as palavras da string
                            comandos2[i] = comando;
                            i++;
                            comando = strtok(NULL, " ");
                        }

                        //aqui tem que ficar a parte de executar processos


                    }

            //comandos2 esta armazenando a string toda sem virgula e sem espaço
            comandos2[i] = NULL;

        free(comando);
        free(comandos);
        free(comandos2);
        free(linha);
        return 0;
    }
}

// conta quantas virgulas tem - nao esta sendo usada no momento
int verifica_virgulas(char* linha){
    int x=0, i;
    for(i=0;i<strlen(linha); i++){
        if(linha[i] == ',')
            x++;
    }
    return x;
}


//ESSA FUNÇÃO VERIFICA SE HÁ ESPAÇOS SEGUIDOS NA LINHA INSERIDA
char* verifica_espaco(char* linha){
    int i, posicao;

        for (i=0, posicao = 0; i < strlen(linha); i++, posicao++) {
            if (linha[posicao] == ' ')
                if(linha[posicao+1] == ' '){
                    while(linha[posicao+1] == ' ')
                        posicao++;
                }
            linha[i] = linha[posicao];
        }

    return linha;

}



//LÊ UMA LINHA INTEIRA, CARACTERE POR CARACTERE, E FAZ UMA ALOCAÇÃO DINÂMICA
char *read_line(void){
    int posicao = 0;
    char c;

    char *buffer = malloc(sizeof(char) * 512);


    if (!buffer) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }
    //ler caractere por caractere
    while (1) {

        c = getchar();

        // se chegar no EOF para e retorna a linha
        if (c == EOF || c == '\n') {
            buffer[posicao] = '\0';
            return buffer;
        } else {
            buffer[posicao] = c;
        }
        posicao++;

        // caso exceda o limite de 512 caracteres da linha deve exibir um erro
        if (posicao >= 512) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        }
    }

