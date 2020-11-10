//CONSTRUINDO UM SHELL EM C

//DECLARAÇÃO DE BIBLIOTECAS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//BIBLIOTECAS ABAIXO SÓ FUNCIONAM NO LINUX
#include <unistd.h>
#include <sys/wait.h>

//DECLARAÇÃO DE FUNÇÕES
int func_help();
int func_quit();
char *read_line (void);
int executar(char **comandos);
char *verifica_espaco (char* linha);
int executa_processos(char **comandos);



//FUNÇÃO MAIN
int main(){

    int parada_loop=1; // variável para parar o loop do shell


    while(parada_loop) {
        int i=0;
        int contador=0;
        char *linha; //recebe a linha digitada
        char *comando; //ponteiro para os char**
        char **comandos = malloc(sizeof(char*) * 30);

        //verificar se comandos foi alocado corretamente
        if (!comandos) {
            fprintf(stderr, "lsh: erro de alocacao\n");
            return 0;
        }

        printf("meu_shell> ");
        linha = read_line(); //ler a linha digitada
        linha = verifica_espaco(linha); //tratar se a linha possui espaços em excesso


        //esse segmento de código faz a separação da linha digitada em vários comandos
        //se é uma entrada vazia (exempo: ,,,,,,,) nada é armazenado
        //há também uma variável contadora que armazena quantas virgulas tem na linha
        //ou seja, quantos comandos serão executados
            comando = strtok(linha, ",");
            while (comando != NULL) {
                    comandos[i] = comando;
                    contador++;
                    i++;
                comando = strtok(NULL, ",");
            }

            //comandos está armazenando strings separadas pela virgula
            //a liha abaixo é importante para que não seja armazenado lixo no vetor
            comandos[i]=NULL;
            i = 0;

            //esse segmento de codigo separa as strings antes separados por virgula em palavras
            //e manda os comandos serem executados até a próxima virgula

                for(int z=0; z<contador; z++) {
                    char **comandos2 = malloc(sizeof(char*) * 30);
                    if (!comandos2) {
                        fprintf(stderr, "lsh: erro de alocacao\n");
                        return 0;
                    }

                    comando = strtok(comandos[z], " ");

                    while (comando != NULL) { //pega todas as palavras da string
                        comandos2[i] = comando;
                        i++;
                        comando = strtok(NULL, " ");
                    }
                    comandos2[i] = NULL;
                    parada_loop=executar(comandos2);
                    free(comandos2);
                    i=0;
                }

        //liberar os ponteiros e alocações
        free(comando);
        free(comandos);
        free(linha);

    }

    return 0;
}


//COMANDO BUILTIN HELP
int func_help(){
    printf("\n\nShell da Julia e da Alice\n");
    printf("Digite os comandos e aperte enter para executar.\n");
    printf("O símbolo '|' foi substituído pela virgula ','.\n");
    printf("O comando para sair 'exit' foi substituído por 'quit'\n");
    printf("Os seguintes comandos são builtin:\n");
    printf("  help\n  quit\n");

    printf("Para consultar a documentação dos outros comandos utilize 'man <comando>'\n\n");
    return 1;
}

//FUNÇÃO BUILTIN QUIT
int func_quit (){
    printf("\nObrigada por utilizar o meu_shell. Ate mais!!\n\n");
    return 0;
}

//LÊ UMA LINHA INTEIRA, CARACTERE POR CARACTERE, E FAZ UMA ALOCAÇÃO DINÂMICA
char *read_line(void){
    int posicao = 0;
    char c;

    char *buffer = malloc(sizeof(char) * 512);

    if (!buffer) {
        fprintf(stderr, "lsh: erro de alocacao\n");
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
            fprintf(stderr, "lsh: erro !! muitos caracteres\n");
            exit(EXIT_FAILURE);
        }
    }
}

//FUNÇÃO QUE JUNTA A EXECUÇÃO DOS PROCESSOS COMUNS COM OS BUILTINS
int executar(char **comandos){
    int i;

    if (comandos[0] == NULL) {
        // An empty command was entered.
        return 1;
    }
    // se o comando digitado for igual a algum builtin ele executa a função específica
    for (i = 0; i < 2; i++) {
        if (strcmp(comandos[0], "help") == 0) {
            return func_help();
        }else if(strcmp(comandos[0], "quit") == 0){
            return func_quit();
        }
    }
    // se o comando digitado é um comando shell ele vai para essa função
    return executa_processos(comandos);
}

//ESSA FUNÇÃO VERIFICA SE HÁ ESPAÇOS SEGUIDOS NA LINHA INSERIDA E OS ELIMINA
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

//FUNÇÃO DE EXECUTAR PROCESSOS
int executa_processos(char **comandos){
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Processo filho tenta executar, se não conseguir sai com erro
        if (execvp(comandos[0], comandos) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Erro no fork
        perror("lsh");
    } else {
        // Processo pai espera processo filho executar
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1; //se deu tudo certo retorna 1
}
