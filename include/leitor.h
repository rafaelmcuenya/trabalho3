#ifndef LEITOR_H
#define LEITOR_H

#include <stdio.h>
#include <stdbool.h>

/*
   O leitor é responsável por processar arquivos de comando (.geo, .pm e .qry) que definem as operações do projeto.
   Ele coordena as operações evolvendo as quadras, pessoas, moradores, entre outros.
*/

void inicializarSistema(void);
/*
   Inicializa todos os componentes do sistema. Deve ser chamado antes de processar qualquer um dos arquivos.
*/

void finalizarSistema(void);
/*
   Libera toda a memória alocada pelo sistema e finaliza todos os componentes. Deve ser chamado ao término da execução.
*/

//Fazer funções aqui posteriormente caso necessário

void abrirArquivo(FILE **f, const char *caminho);
/*
   Abre um arquivo para leitura, tratando erros de abertura durante o processo.
*/

void processarComando(const char* linha, int ehQry, const char* nomeBase, const char* outputDir);
/*
   Processa uma linha de comando individual de um arquivo de entrada.
*/

void processarArquivo(const char* caminho, const char* inputDir, int ehQry, const char* nomeBase, const char* outputDir);
/*
   Processa um arquivo completo de comandos de entrada.
*/

#endif
