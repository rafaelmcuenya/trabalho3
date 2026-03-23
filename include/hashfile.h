#ifndef HASHFILE_H
#define HASHFILE_H

#include <stdio.h>
#include <stdlib.h>

/*
   Este TAD contém a documentação do HashFile extensível. 
   Um HashFile extensível é um método de armazenamento em dispositivos de memória secundários, tendo como exemplo mais notável, o disco rígido.
   Permite gerenciar de forma dinâmica o espalhamento a depender se necessita diminuir/aumentar o espaço reservado, de forma automática.
   
*/

typedef void* HashFile;
typedef void* Bucket;
typedef void* Diretorio;

HashFile createHashFile(int tamBucket, int profundidadeInicial);
/*
Função para criar o hashfile.
Possui como parâmetros o número máximo de elementos por bucket e a profundidade inicial, respectivamente.
Retorna um ponteiro para o hashfile, ou NULL em caso de erro.
*/

int inserirItemHash(HashFile hf, int chave, int valor);
/*
Função para inserir um item no hashfile.
Primeiro parâmetro é o ponteiro para o hashfile.
Segundo parâmetro a chave na qual será inserida o item.
Terceiro parâmetro o valor a ser inserido.
Retorna 1 caso a operação tenha sido bem sucedida, 0 caso contrário.
*/

int buscaItemHash(HashFile hf, int chave, int *valor);
/*
Função para procurar um item específico por meio de sua chave.
Primeiro parâmetro é o ponteiro para o hashfile.
Segundo parâmetro é a chave a ser buscada.
Terceiro parâmetro é um ponteiro para int onde o valor será armazenado.
Retorna 1 caso encontre, 0 caso contrário.
*/

int deletarItemHash(HashFile hf, int chave);
/*
Função para deletar um item por meio da chave.
Primeiro parâmetro é o ponteiro para o hashfile.
Segundo parâmetro é a chave a ser removida.
Retorna 1 caso sucedido, 0 caso contrário.
*/

int dobraDiretorio(HashFile hf);
/*
Função para dobrar a capacidade do diretório.
Primeiro parâmetro é o ponteiro para o hashfile.
Retorna 1 caso operação tenha sido bem sucedida, 0 em caso de falha.
*/

int splitBucket(HashFile hf, int indice);
/*
Função para dividir e redistribuir automaticamente um bucket.
Primeiro parâmetro é o ponteiro para o hashfile.
Segundo parâmetro é o índice do bucket a ser dividido.
Retorna 1 caso tenha sucesso, 0 caso falhe.
*/

Bucket createBucket(int nivel);
/*
Função para criar um novo bucket na profundidade repassada pelo parâmetro.
Primeiro parâmetro é a profundidade local do bucket.
Retorna um ponteiro para tal bucket caso criado corretamente.
Retorna NULL caso ocorra algum erro.
*/

void freeHash(HashFile hf);
/*
Função para liberar o hashfile.
Primeiro parâmetro é o ponteiro para o hashfile.
*/

//Funções temporárias (?) para os TU

int getProfundidadeGlobal(HashFile hf);
/*
Função para obter a profundidade global atual do diretório.
Primeiro parâmetro é o ponteiro para o hashfile.
Retorna a profundidade global, ou -1 em caso de erro.
*/

int getTamanhoDiretorio(HashFile hf);
/*
Função para obter o número de entradas no diretório.
Primeiro parâmetro é o ponteiro para o hashfile.
Retorna o tamanho do diretório, ou -1 em caso de erro.
*/

int getProfundidadeBucket(HashFile hf, int indice);
/*
Função para obter a profundidade local de um bucket específico.
Primeiro parâmetro é o ponteiro para o hashfile.
Segundo parâmetro é o índice do bucket no diretório.
Retorna a profundidade do bucket, ou -1 em caso de erro.
*/

int getQuantidadeBucket(HashFile hf, int indice);
/*
Função para obter o número de elementos armazenados em um bucket.
Primeiro parâmetro é o ponteiro para o hashfile.
Segundo parâmetro é o índice do bucket no diretório.
Retorna a quantidade de elementos, ou -1 em caso de erro.
*/

int bucketEstaCheio(HashFile hf, int indice);
/*
Função para verificar se um bucket atingiu sua capacidade máxima.
Primeiro parâmetro é o ponteiro para o hashfile.
Segundo parâmetro é o índice do bucket no diretório.
Retorna 1 se cheio, 0 caso contrário, -1 em caso de erro.
*/

int getTotalElementos(HashFile hf);
/*
Função para obter o número total de elementos no hashfile.
Primeiro parâmetro é o ponteiro para o hashfile.
Retorna o total de elementos, ou -1 em caso de erro.
*/

#endif
