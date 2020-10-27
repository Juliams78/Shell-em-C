#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comando_invalido; //Variavel global para verificar se o comando foi digitado errado ou invalido

//Área dos protótipos
void verifica_saida(char* comando);
void verifica_ls (char* comando);
void verifica__bin_ls (char* comando_);
void verifica_ls__l (char* comando);
void verifica_cat_file (char* comando);
void verifica_grep_foo_file2 (char* comando);
void verifica_comando (char* comando);
//Fim dos protótipos

int main(){
	
	char comando[512];//String para pegar o comando digitado

	do{
		comando_invalido = 0;
		printf("meu-shell> ");
		gets(comando);
		fflush(stdin);
		
		verifica_ls(comando);
		verifica__bin_ls(comando);
		verifica_ls__l(comando);
		verifica_cat_file (comando);
		verifica_grep_foo_file2 (comando);
		verifica_saida(comando);
		verifica_comando(comando);
			
	}while(1);// Mantendo em loop

	system("pause");
	return 0;
}

//Verificando QUIT 
void verifica_saida(char* comando){ 
	int i;
	for(i=0;comando[i] != '\0';i++){
		if(comando[i] == 'q' && 
		comando[i+1] == 'u' && 
		comando[i+2] == 'i' && 
		comando[i+3] == 't' && 
		(comando[i+4] == ' ' || comando[i+4] == '\0') &&
		(comando[i-1] == NULL || comando[i-1] == ' ') )
		{
			printf("\n O comando quit foi digitado\n");
			comando_invalido = 1;
			system ("pause");
			exit(0);
		}	
	}	
	return;
}

//Verificando LS
void verifica_ls (char* comando){
	int i;
	for(i=0;comando[i] != '\0';i++){
		if(comando[i] == 'l' &&
		comando[i+1] == 's' && 
		(comando[i+2] == ' ' || comando[i+2] == '\0') &&
		comando[i-1] != '/' &&
		comando[i+3] != '-' &&
		(comando[i-1] == NULL || comando[i-1] == ' '))
		{
			printf("\n O comando ls foi digitado\n");
			comando_invalido = 1;
		}
	}			
	return;
}

//Verificando /BIN/LS
void verifica__bin_ls (char* comando){
	int i;
	for(i=0;comando[i] != '\0';i++){
		if(comando[i] == '/' &&
		comando[i+1] == 'b' &&
		comando[i+2] == 'i' && 
		comando[i+3] == 'n' && 
		comando[i+4] == '/' && 
		comando[i+5] == 'l' && 
		comando[i+6] == 's' &&
		(comando[i+7] == ' ' || comando[i+7] == '\0') &&
		(comando[i-1] == NULL || comando[i-1] == ' '))
		{
			printf("\n O comando /bin/ls foi digitado\n");
			comando_invalido = 1;
		}	
	}
	return;
}

//Verificando LS -L
void verifica_ls__l (char* comando){
	int i;
	for(i=0;comando[i] != '\0';i++){
		if(comando[i] == 'l' && 
		comando[i+1] == 's' && 
		comando[i+2] == ' ' && 
		comando[i+3] == '-' && 
		comando[i+4] == 'l' &&
		(comando[i+5] == ' ' || comando[i+5] == '\0') &&
		(comando[i-1] == NULL || comando[i-1] == ' '))
		{
			printf("\n O comando ls -l foi digitado\n");
			comando_invalido = 1;
		}	
	}	
	return;
}

// Verificando cat file
void verifica_cat_file (char* comando){
	int i;
	for(i=0;comando[i] != '\0';i++){
		if(comando[i] == 'c' && 
		comando[i+1] == 'a' && 
		comando[i+2] == 't' && 
		comando[i+3] == ' ' && 
		comando[i+4] == 'f' && 
		comando[i+5] == 'i' && 
		comando[i+6] == 'l' && 
		comando[i+7] == 'e' &&
		(comando[i+8] == ' ' || comando[i+8] == '\0') &&		
		(comando[i-1] == NULL || comando[i-1] == ' '))
		{		
			printf("\n O comando cat file foi digitado\n");
			comando_invalido = 1;
		}	
	}	
	return;
}

//Verificando grep foo file2
void verifica_grep_foo_file2 (char* comando){
	int i;
	for(i=0;comando[i] != '\0';i++){
		if(comando[i] == 'g' &&
		 comando[i+1] == 'r' && 
		 comando[i+2] == 'e' &&
		 comando[i+3] == 'p' && 
		 comando[i+4] == ' ' && 
		 comando[i+5] == 'f' && 
		 comando[i+6] == 'o' && 
		 comando[i+7] == 'o' && 
		 comando[i+8] == ' ' && 
		 comando[i+9] == 'f' && 
		 comando[i+10] == 'i' && 
		 comando[i+11] == 'l' && 
		 comando[i+12] == 'e' && 
		 comando[i+13] == '2' &&
		(comando[i+14] == ' ' || comando[i+14] == '\0') &&		
		(comando[i-1] == NULL || comando[i-1] == ' '))
		{				 
			printf("\n O comando grep foo file2 foi digitado\n");
			comando_invalido = 1;
		}	
	}	
	return;
}

//Verificando o comando digitado
void verifica_comando (char* comando){
	if(comando_invalido == 0){
		printf("\nComando inexistente ou impossível de ser executado\n");
	}
}


