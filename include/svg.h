#ifndef SVG_H
#define SVG_H

#include <stdio.h>
#include "quadra.h"
#include "hashfile.h"

/*
   Módulo responsável pela geração de arquivos SVG.
   Cria também possíveis símbolos para algumas das operações do arquivo qyr.
*/

void svgGeo(const char *caminhoCompleto, HashFile *hfQuadras);
/*
   Gera o arquivo SVG inicial com as quadras da cidade.
   Primeiro parâmetro é o caminho completo do arquivo SVG a ser gerado.
   Segundo parâmetro é o hashfile de quadras.
*/

void svgQry(const char *caminhoCompleto, HashFile *hfQuadras, HashFile *hfMoradores);
/*
   Gera o arquivo SVG final após processar o arquivo .qry, incluindo as quadras e as marcações das operações.
   Primeiro parâmetro é o caminho completo do arquivo SVG a ser gerado.
   Segundo parâmetro é o hashfile de quadras.
   Terceiro parâmetro é o hashfile de moradores.
*/

void svgMarcarRemocaoQuadra(FILE *svgFile, Quadra q);
/*
   Marca uma quadra removida com um X vermelho no local da âncora.
   Primeiro parâmetro é o arquivo SVG aberto para escrita.
   Segundo parâmetro é a quadra removida.
*/

void svgMarcarMoradoresPorFace(FILE *svgFile, Quadra q, int faceN, int faceS, int faceL, int faceO);
/*
   Anota o número de moradores por face próximo aos limites da quadra e o total no centro.
   Primeiro parâmetro é o arquivo SVG aberto para escrita.
   Segundo parâmetro é a quadra.
   Demais parâmetros são as contagens de moradores por face.
*/

void svgMarcarMudanca(FILE *svgFile, double x, double y, const char *cpf);
/*
   Marca o endereço de destino de uma mudança com um quadrado vermelho e o CPF dentro.
   Primeiro parâmetro é o arquivo SVG aberto para escrita.
   Segundo e terceiro parâmetros são as coordenadas do endereço.
   Quarto parâmetro é o CPF do morador.
*/

void svgMarcarDespejo(FILE *svgFile, double x, double y);
/*
   Marca o local de um despejo com um círculo preto.
   Primeiro parâmetro é o arquivo SVG aberto para escrita.
   Segundo e terceiro parâmetros são as coordenadas do endereço.
*/

void svgMarcarFalecimento(FILE *svgFile, double x, double y);
/*
   Marca o local de falecimento de um morador com uma cruz vermelha.
   Primeiro parâmetro é o arquivo SVG aberto para escrita.
   Segundo e terceiro parâmetros são as coordenadas do endereço.
*/

void desenharQuadrasSvg(HashFile *hfQuadras, FILE *svgFile);
/*
   Desenha a quadra no arquivo SVG.
   Primeiro parâmetro é o hashfile das quadras.
   Segundo parâmetro é o arquivo SVG aberto para escrita
*/

#endif
