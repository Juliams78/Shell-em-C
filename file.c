#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> //só funcionam no linux
#include <sys/wait.h>




char *read_line (void);
char *verifica_espaco (char* linha);
int executa_processos(char **comandos);
int func_help();
int func_quit();



int main(){

    int ok=1;


    while(ok) {
        int i=0;
        int contador=0;
        char *linha;
        char *comando;
        char **comandos = malloc(sizeof(char*) * 30);
        char **comandos2 = malloc(sizeof(char*) * 30);

        if (!comandos) {
            fprintf(stderr, "lsh: erro de alocacao\n");
            return 0;
        }

        if (!comandos2) {
            fprintf(stderr, "lsh: erro de alocacao\n");
            return 0;
        }

        printf("meu_shell> ");
        linha = read_line();
        linha = verifica_espaco(linha);

        //esse segmento de código faz a separação da linha digitada em vários comandos
        //se é uma entrada vazia (exempo: ,,,,,,,) nada é armazenado
            comando = strtok(linha, ",");
            while (comando != NULL) {
                    comandos[i] = comando;
                    contador++;
                    i++;
                //printf("1:%s\n", comando); //apenas para verificação deve ser excluído depois
                comando = strtok(NULL, ",");
            }

            //comandos esta armazenando strings separadas pela virgula
            comandos[i]=NULL;

            //esse segmento de codigo separa as strings antes separados por virgula em palavras
            i = 0;
                for(int z=0; z<contador; z++) {
                    comando = strtok(comandos[z], " ");

                    while (comando != NULL) { //pega todas as palavras da string
                        comandos2[i] = comando;
                        i++;
                        //printf("2:%s\n",comando); //apenas para verificação deve ser excluído depois
                        comando = strtok(NULL, " ");
                    }


                }
            //comandos2 esta armazenando a string toda sem virgula e sem espaço
            comandos2[i] = NULL;

           ok=executa_processos(comandos2);



        free(comando);
        free(comandos);
        free(comandos2);
        free(linha);

    }

    return 0;
}



int func_help(){
    int i;
    printf("Shell da Julia e da Alice\n");
    printf("Digite os comandos e aperte enter para executar.\n");
    printf("O símbolo '|' foi substituído pela virgula ','.\n");
    printf("O comando para sair 'exit' foi substituído por 'quit'\n");
    printf("Os seguintes comandos são builtin:\n");
    printf("  help\n  quit\n");


    return 1;
}

int func_quit (){
    printf("Obrigada por utilizar o meu_shell. Ate mais!!\n");
    return 0;
}




 //funciona apenas com um comando
int executa_processos(char **comandos){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execvp(comandos[0], comandos) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Erro no fork
        perror("lsh");
    } else {
        // Processo pai
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1; //se deu tudo certo retorna 1
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

