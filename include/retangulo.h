#ifndef RETANGULO_H
#define RETANGULO_H

#include <stdio.h>

/*
   Um retângulo é uma forma geométrica composta por quatro pontos distintos entre si, interligados por segmentos de reta, e postos em um plano. 
   Tal forma possui uma âncora, uma cor de preenchimento e uma cor de borda.
   A âncora é dada pelo ponto criado mais próximo do ponto de origem (0,0).
   As cores de borda e preenchimento são descritas utilizando o padrão sRGB de 6 dígitos.
*/

typedef void* Retangulo;
typedef void* Aresta;

Retangulo criaRetangulo(int i, double x, double y, double w, double h, char* corb, char* corp);
/*
   Cria um retângulo com a âncora posicionada nos dados repassados pelos parâmetros 3 e 4, com tal forma possuindo um ID dado pelo primeiro parâmetro. 
   O mesmo terá comprimento e altura das informações enviadas pelos 4° e 5° parâmetros, respectivamente.
   As cores de borda e preenchimento são enviadas por meio dos parâmetros 6 e 7, e retorna um ponteiro para a forma recém criada.
*/

double areaRetangulo(Retangulo r);
/*
   Calcula a área de um retângulo, baseando-se na fórmula geral dada por A = l*c, sendo 'c' o comprimento do retângulo, 'A' a área final e 'l' a largura do mesmo.
*/

int idRetangulo(Retangulo r);
/*
   Coleta o ID de um retângulo específico para possíveis manipulações no mesmo, retornando tal identificador.
*/

double getXRetangulo(Retangulo r);
/*
   Retorna a coordenada X da âncora do retangulo.
*/

double getYRetangulo(Retangulo r);
/*
   Retorna a coordenada Y da âncora do retangulo.
*/

double getArestaRetangulo(Retangulo r, char c);
/*
   Recebe um retângulo na qual queremos obter uma de suas arestas.
   Recebe um character indicando qual aresta a função deve obter, baseado na orientação (Norte para baixo)
   Retorna ??? da aresta obtida.
*/

int validaRetangulo(void* r);
/*
   Função interna de validação para verificar se uma estrutura de retângulo é válida.
   Retorna 1 se válido, 0 caso contrário.
*/

void setCorBRetangulo(Retangulo r, char* novaCor);
/*
   Altera a cor da borda do retângulo.
*/

void setCorPRetangulo(Retangulo r, char* novaCor);
/*
   Altera a cor de preenchimento do retângulo.
*/

void liberaRetangulo(Retangulo r);
/*
   Libera toda a memória associada ao retangulo passado como parâmetro.
   Essa função deve ser utilizada sempre que o retangulo não for mais necessário.
*/

#endif
