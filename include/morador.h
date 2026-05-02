#ifndef MORADOR_H
#define MORADOR_H

#include "habitante.h"

#include <stdio.h>
#include <stddef.h>

/*
   Um morador é um habitante que mora em uma casa de algumas das quadras de Bitnópolis.
   
   Todas as operações utilizadas para um habitante são válidas para um morador,
   visto que todo morador é um habitante de Bitnópolis, mas nem todo habitante é um morador,
   como por exemplo, os sem-teto.

   Este módulo contém funções específicas para um morador, envolvendo principalmente elementos
   envolvendo o endereço, como face, número, dentre outros.
*/

typedef void* Morador;

Morador criaMorador(const char *cpf, const char *nome, const char *sobrenome, char sexo, const char *nasc, const char *cep, char face, int num, const char *compl);
/*
Cria um morador com os dados repassados pelos parâmetros.
Primeiro parâmetro é o CPF.
Segundo parâmetro é o nome do morador.
Terceiro parâmetro é o sobrenome do morador.
Quarto parâmetro é o sexo (M ou F).
Quinto parâmetro é a data de nascimento no formato "dd/mm/aaaa".
Sexto parâmetro é o CEP da quadra.
Sétimo parâmetro é a face da quadra (N, S, L ou O).
Oitavo parâmetro é o número do imóvel.
Nono parâmetro é o complemento (pode ser NULL ou string vazia).
Retorna um ponteiro para o morador criado, ou NULL em caso de algum erro.
*/

const char* getCpfMorador(Morador m);
/*
Retorna o CPF do morador repassado pelo parâmetro.
*/

const char* getNomeMorador(Morador m);
/*
Retorna o nome do morador repassado pelo parâmetro.
*/

const char* getSobrenomeMorador(Morador m);
/*
Retorna o sobrenome do morador repassado pelo parâmetro.
*/

const char* getNomeCompletoMorador(Morador m);
/*
Retorna o nome completo (nome + sobrenome) do morador.
O chamador é responsável por liberar a memória alocada.
*/

char getSexoMorador(Morador m);
/*
Retorna o sexo do morador repassado pelo parâmetro.
*/

const char* getNascMorador(Morador m);
/*
Retorna a data de nascimento do morador repassado pelo parâmetro.
*/

const char* getCepMorador(Morador m);
/*
Retorna o CEP da quadra onde o morador reside.
*/

char getFaceMorador(Morador m);
/*
Retorna a face da quadra onde o morador reside (N, S, L ou O).
*/

int getNumMorador(Morador m);
/*
Retorna o número do imóvel do morador.
*/

const char* getComplMorador(Morador m);
/*
Retorna o complemento do endereço do morador.
Retorna NULL se não houver complemento.
*/

const char* getEnderecoCompletoMorador(Morador m);
/*
Retorna o endereço completo do morador no formato "CEP/Face/Num/Compl".
O chamador é responsável por liberar a memória alocada.
*/

Habitante getHabitanteMorador(Morador m);
/*
Retorna o habitante associado ao morador.
Permite acesso às funções de Habitante quando necessário.
*/

int validaFace(char face);
/*
Verifica se um caractere representa uma face válida.
Primeiro parâmetro é o caractere a ser validado.
Retorna 1 se válido (N, n, S, s, L, l, O, o), 0 caso contrário.
*/

int validaNum(int num);
/*
Verifica se um número de imóvel é válido (positivo).
Primeiro parâmetro é o número a ser validado.
Retorna 1 se válido, 0 caso contrário.
*/

size_t tamSerialMorador(void);
/*
Retorna o tamanho em bytes necessário para serializar um morador.
*/

int serialMorador(Morador m, void *buffer, size_t tamBuffer);
/*
Serializa o morador em um buffer de bytes para armazenamento no HashFile.
Primeiro parâmetro é o ponteiro para o morador.
Segundo parâmetro é o buffer de destino.
Terceiro parâmetro é o tamanho do buffer.
Retorna 1 caso sucesso, 0 caso contrário.
*/

Morador desserialMorador(void *buffer, size_t tamBuffer);
/*
Reconstrói um morador a partir de um buffer de bytes.
Primeiro parâmetro é o buffer contendo os dados serializados.
Segundo parâmetro é o tamanho do buffer.
Retorna um ponteiro para o morador reconstruído, ou NULL em caso de erro.
*/

void freeMorador(Morador m);
/*
Libera toda a memória associada ao morador.
Primeiro parâmetro é o ponteiro para o morador.
*/

#endif
