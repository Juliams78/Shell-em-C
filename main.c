#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <unistd.h> só funcionam no linux
//#include <sys/wait.h>

char *read_line(void);
int verifica_comando( char* linha);


int main(){
    char *linha;

    linha= read_line();



    free(linha);
    return 0;
}


//nao esta pronta
//ESSA FUNÇÃO VERIFICA SE HÁ VIRGULAS E SE HA COMANDOS NA LINHA INSERIDA
int verifica_comando(char* linha){
    int temcomando;

    char *comando = malloc(sizeof(char) * 512);
    if (!comando) {
        fprintf(stderr, "lsh: allocation error\n");
        exit(EXIT_FAILURE);
    }





        return temcomando;
}




//LÊ UMA LINHA INTEIRA, CARACTERE POR CARACTERE, E FAZ UMA ALOCAÇÃO DINÂMICA
char *read_line(void){
    int linha = 512;
    int posicao = 0;
    int c;

    char *buffer = malloc(sizeof(char) * linha);


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
        if (posicao >= linha) {
                fprintf(stderr, "lsh: allocation error\n");
                exit(EXIT_FAILURE);
            }
        
        }
    }

