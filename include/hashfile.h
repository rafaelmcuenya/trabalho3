#ifndef HASHFILE_H
#define HASHFILE_H

#include <stdio.h>
#include <stdlib.h>

/*
   Este TAD contém a documentação do hashfile extensível. 
   Um hashfile extensível é um método de armazenamento em dispositivos de memória secundários, tendo como exemplo mais notável, o disco rígido.
   Permite gerenciar de forma dinÂmica o espalhamento a depender se necessita dimunuir/aumentar o espaço reservado, de forma automática.
   
*/

typedef void* Bucket;
typedef void* Diretorio;
typedef void* Hash;
typedef void* Dados;

// #define BUCKET_SIZE 4


Hash* createHash();
/*
Função para criar o hashfile. 
Retorna um ponteiro para o hashfile, ou NULL em caso de erro.
*/

void inserirItemHash(Hash *???, int chaveH, int info);
/*
Função para inserir um item no hasfile. 
*/

int  buscaItemHash(Hash *???, int chaveH, int *info);
/*
Função para procurar um item específica por meio de sua chave. 
Retorna o ponteiro do item caso encontre, retorna 0 caso contrário.
*/

void deletarItemHash(Hash *???, int chaveH);
/*
Função para deletar um item por meio da chave. 
Retorna 1 caso sucedido, 0 caso contrário.
*/

/*
 int ??hash(int chaveH);
necessário??
*/

void dobraDiretorio(Hash *???);
/*
Função para dobrar a capacidade do diretório. 
Retorna 1 caso operação tenha sido bem sucedida, 0 em caso de falha.
*/

void splitBucket(Hash *???, int index);
/*
Função para dividir e redistribuir automaticamente um bucket. 
Retorna 1 caso tenha sucesso, 0 caso falhe.
*/

Bucket* createBucket(int nivel);
/*
Função para criar um novo bucket na profundidade repassada pelo parâmetro. 
Retorna um ponteiro para tal bucket caso criado corretamente.
Retorna NULL caso ocorra algum erro.
*/

// Apagar dps
void ??print(Hash *???);
/*

*/


void freeHash(Hash *???);
/*
Função para liberar o hashfile
*/

#endif
