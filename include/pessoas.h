#ifndef HABITANTE_H
#define HABITANTE_H

#include <stddef.h>

/*
   Um habitante é uma pessoa que vive em Bitnópolis, podendo ser morador (possui endereço) ou sem-teto (não possui endereço).
   Cada habitante é identificado unicamente por seu CPF.
   Armazena dados pessoais como nome, sobrenome, sexo e data de nascimento.
   Por meio da função criaHabitante, cria-se um habitante.
   Pode ser encerrado com a função freeHabitante.
   Possui demais operações importantes (validação de CPF, serialização para HashFile, etc).
*/

typedef void* Habitante;

Habitante criaHabitante(const char *cpf, const char *nome, const char *sobrenome, char sexo, const char *nascimento);
/*
Cria um habitante com os dados repassados pelos parâmetros.
Primeiro parâmetro é o CPF, contendo exatamente 11 dígitos numéricos.
Segundo parâmetro é o nome do habitante.
Terceiro parâmetro é o sobrenome do habitante.
Quarto parâmetro é o sexo (M ou F).
Quinto parâmetro é a data de nascimento no formato "dd/mm/aaaa".
Retorna um ponteiro para o habitante criado, ou NULL em caso de algum erro.
*/

const char* getCpfHabitante(Habitante h);
/*
Retorna o CPF do habitante repassado pelo parâmetro.
*/

const char* getNomeHabitante(Habitante h);
/*
Retorna o nome do habitante repassado pelo parâmetro.
*/

const char* getSobrenomeHabitante(Habitante h);
/*
Retorna o sobrenome do habitante repassado pelo parâmetro.
*/

const char* getNomeCompletoHabitante(Habitante h);
/*
Retorna o nome completo (nome + sobrenome) do habitante.
O chamador é responsável por liberar a memória alocada.
*/

char getSexoHabitante(Habitante h);
/*
Retorna o sexo do habitante repassado pelo parâmetro.
*/

const char* getNascimentoHabitante(Habitante h);
/*
Retorna a data de nascimento do habitante repassado pelo parâmetro.
*/

const char* getIdMoradiaHabitante(Habitante h);
/*
Retorna o identificador da moradia onde o habitante reside.
Retorna NULL ou string vazia se for sem-teto.
*/

int isMoradorHabitante(Habitante h);
/*
Verifica se o habitante possui endereço de moradia.
Retorna 1 se for morador, 0 se for sem-teto, -1 em caso de erro.
*/

void setIdMoradiaHabitante(Habitante h, const char *idMoradia);
/*
Define o identificador da moradia onde o habitante reside.
Primeiro parâmetro é o ponteiro para o habitante.
Segundo parâmetro é o identificador da moradia (pode ser NULL para tornar sem-teto).
*/

int validaCpf(const char *cpf);
/*
Verifica se uma string contém um CPF válido (exatamente 11 dígitos numéricos).
Primeiro parâmetro é o CPF a ser validado.
Retorna 1 se válido, 0 caso contrário.
*/

int validaSexo(char sexo);
/*
Verifica se um caractere representa um sexo válido.
Primeiro parâmetro é o caractere a ser validado.
Retorna 1 se válido ('M', 'm', 'F', 'f'), 0 caso contrário.
*/

int validaData(const char *data);
/*
Verifica se uma string está no formato válido de data "dd/mm/aaaa".
Primeiro parâmetro é a string a ser validada.
Retorna 1 se válido, 0 caso contrário.
*/

int comparaData(const char *data1, const char *data2);
/*
Compara duas datas no formato "dd/mm/aaaa".
Retorna -1 se data1 < data2, 0 se iguais, 1 se data1 > data2.
*/

int calculaIdade(const char *nascimento, const char *dataReferencia);
/*
Calcula a idade com base na data de nascimento e uma data de referência.
Primeiro parâmetro é a data de nascimento ("dd/mm/aaaa").
Segundo parâmetro é a data de referência ("dd/mm/aaaa").
Retorna a idade em anos, ou -1 em caso de erro.
*/

size_t tamSerialHabitante(void);
/*
Retorna o tamanho em bytes necessário para serializar um habitante.
*/

int serialHabitante(Habitante h, void *buffer, size_t tamBuffer);
/*
Serializa o habitante em um buffer de bytes para armazenamento no HashFile.
Primeiro parâmetro é o ponteiro para o habitante.
Segundo parâmetro é o buffer de destino.
Terceiro parâmetro é o tamanho do buffer.
Retorna 1 caso sucesso, 0 caso contrário.
*/

Habitante desserialHabitante(void *buffer, size_t tamBuffer);
/*
Reconstrói um habitante a partir de um buffer de bytes.
Primeiro parâmetro é o buffer contendo os dados serializados.
Segundo parâmetro é o tamanho do buffer.
Retorna um ponteiro para o habitante reconstruído, ou NULL em caso de erro.
*/

void freeHabitante(Habitante h);
/*
Libera toda a memória associada ao habitante.
Primeiro parâmetro é o ponteiro para o habitante.
*/

#endif
