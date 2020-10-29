#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <unistd.h> só funcionam no linux
//#include <sys/wait.h>

char *read_line (void);
char *verifica_espaco (char* linha);
char *verifica_virgula(char* linha);



int main(){
    char *linha;

    linha= read_line();
    linha= verifica_espaco(linha);



    free(linha);
    return 0;
}

//falta implementar
char *verifica_virgula(char* linha){

}



//ESSA FUNÇÃO VERIFICA SE HÁ ESPAÇOS SEGUIDOS NA LINHA INSERIDA
char* verifica_espaco(char* linha){
    int i=0, posicao;

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

