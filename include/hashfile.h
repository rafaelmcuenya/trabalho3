#ifndef HASHFILE_H
#define HASHFILE_H

#include <stdio.h>
#include <stdlib.h>

/*
   Este TAD contém a documentação do hashfile utilizado no projeto. Um hashfile é ...
*/

typedef void* Bucket;
typedef void* Diretorio;
typedef void* Hash;
typedef void* Dados;

#define BUCKET_SIZE 4


Hash* createHash();
/*
Função para criar o hashfile
*/

void inserirItemHash(Hash *eh, int chaveH, int info);
/*
Função para inserir um item no hasfile
*/

int  buscaItemHash(Hash *eh, int chaveH, int *info);
/*
Função para procurar um item específica por meio de sua chave.
*/

void deletarItemHash(Hash *eh, int chaveH);
/*
Função para deletar um item por meio da chave
*/

/*
 int ??hash(int chaveH);
necessário??
*/

void dobraDiretorio(Hash *eh);
/*
Função para dobrar a capacidade do diretório
*/

void splitBucket(Hash *eh, int index);
/*

*/

Bucket* createBucket(int depth);
/*

*/

// Apagar dps
void ??print(Hash *eh);
/*

*/


void freeHash(Hash *eh);
/*

*/

#endif
#endif
