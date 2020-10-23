#include <stdio.h>
#include <string.h>



int qtd_virgulas(char *str){
    int virgulas = 0;
    while(*str){
        if (*str == ','){
            virgulas++;
        }
        str++;
    }
    return virgulas;
}



int main() {
    char string[100]; //string de entrada
    char string1[5]= "quit";
    int retorno;
    int i=0;


    do {

        fflush(stdin);
        printf("Digite a string\n");
        scanf("%s", string);
        fflush(stdin);



        retorno = strcmp(string, string1); //compara se a string recebida é igual a 'quit'

        if (retorno != 0) {
            printf("ainda nao acabou\n");
        }

    }while(retorno); //como a função strcmp retorna 0 se as strings são iguais o programa termina se for digitado 'quit'


    return 0;
}
