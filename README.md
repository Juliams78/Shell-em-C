# Construindo um Interpretador Shell
>Status do projeto: Concluído :heavy_check_mark:

Alunas:
- Júlia Mendonça Silva - 5956
- Alice Santos Lemos Faria - 6365

Link do repositório Git: [Construindo um Interpretador Shell em C](https://github.com/Juliams78/TrabalhoSO-Shell-em-C)

### Tópicos
:white_circle: [Descrição do projeto](#descrição-do-projeto) <br/>
:white_circle: [Como rodar a aplicação](#como-rodar-a-aplicação) <br/>
:white_circle: [Problemas e bugs](#problemas-e-bugs) 
   
### Descrição do Projeto   
   O projeto consistiu em implementar um Interpretador Shell utilizando a linguagem C. <br/>
   Alguns requisitos foram impostos, como:
   - A quantidade de caracteres por linha de comando é limitada a 512; 
   - O Shell deverá ser encerrado quando o usuário digita o comando quit.
   - A concatenação de comandos deverá ser separada pelo caractere vírgula (,)

O código fonte do projeto foi testado em uma máquina virtual do aplicativo VirtualBox com um SO Linux Ubuntu 16.04.<br/>
Uma grande ajuda para o desenvolvimento do projeto foi o [Tutorial - Write a Shell in C](https://brennan.io/2015/01/16/write-a-shell-in-c/), portanto, 
seria injusto não referenciar e agradecer ao autor.


### Como rodar a aplicação
O código fonte do projeto está no arquivo _file.c_. Podemos ver que na pasta do repositório há um arquivo _Makefile_ com o qual é possível compilar o código.<br/>
Caso não tenha compilado o arquivo nenhuma vez, pode apenas utilizar o comando ``` make ``` no terminal Linux que o arquivo file (executável) será gerado.

Caso já tenha executado o código antes, ou seja, já tenha algum arquivo executável gerado. Recomendo que utilize o comando ``` make clean ``` seguido de ``` make ```.

Após a compilação do código, utilize o comando ``` ./file ```

Uma vez que o programa esteja executando, (quase) qualquer comando original do Linux pode ser utilizado, para mais informações, verifique a próxima seção.

### Problemas e bugs
Vários problemas surgiram durante o desenvolvimento do projeto, mas felizmente a maioria pôde ser solucionada.

Um problema encontrado foi que não é possível concatenar mais de um comando em uma linha digitada, por exemplo, 
em um Shell do Linux é possível concatenar os comandos ``` ls -l | cat file | grep foo file2 ``` e obter uma saída misturada devido ao uso do pipe. 
Porém, neste projeto, os comandos são executados um seguido do outro e como foi dito anteriormente, o símbolo de separação é a vírgula. Portanto, se for digitado 
``` ls -l , cat file , grep foo file2 ```, os comandos serão executados separadamente um seguido do outro.

Outro problema é que não foi possível implementar o comando ``` cd ```, utilizado para mudar de diretório no terminal. Outros _builtins_ como ```help``` e ```exit``` 
foram implementados, porém, o comando ``` exit``` foi substittuído por ```quit```. 
