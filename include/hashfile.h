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
Função para criar o Hashfile
*/

void inserirItemHash(Hash *eh, int key, int value);
/*

*/

int  buscaItemHash(Hash *eh, int key, int *value);
/*

*/

void deletarItemHash(Hash *eh, int key);
/*

*/

/*
 int ??hash(int key);
necessário??
*/

void dobraDirectorio(Hash *eh);
/*

*/

void splitBucket(Hash *eh, int index);
/*

*/

Bucket* createBucket(int depth);
/*

*/

// Apagar dps
void eh_print(Hash *eh);
/*

*/


void freeHash(Hash *eh);
/*

*/

#endif


#endif
