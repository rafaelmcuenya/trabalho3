#ifndef HASHFILE_H
#define HASHFILE_H

#include <stdio.h>
#include <stdlib.h>

/*
   Este TAD contém a documentação do hashfile extensível utilizado no projeto. 
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
Função para criar o hashfile
*/

void inserirItemHash(Hash *???, int chaveH, int info);
/*
Função para inserir um item no hasfile
*/

int  buscaItemHash(Hash *???, int chaveH, int *info);
/*
Função para procurar um item específica por meio de sua chave.
*/

void deletarItemHash(Hash *???, int chaveH);
/*
Função para deletar um item por meio da chave
*/

/*
 int ??hash(int chaveH);
necessário??
*/

void dobraDiretorio(Hash *???);
/*
Função para dobrar a capacidade do diretório
*/

void splitBucket(Hash *???, int index);
/*
Função para dividir e redistribuir automaticamente um bucket
*/

Bucket* createBucket(int nivel);
/*
Função para criar um novo bucket na profundidade repassada pelo parâmetro
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
