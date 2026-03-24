#include "unity.h"
#include "hashfile.h"
#include <stdlib.h>
#include <string.h>

void setUp(void){}
void tearDown(void){}

void testCriarHash1(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    freeHash(hf);
}

void testCriarHash2(void){
    HashFile hf = createHashFile(0, 1);
    TEST_ASSERT_NULL(hf);
}

void testCriarHash3(void){
    HashFile hf = createHashFile(4, 0);
    TEST_ASSERT_NULL(hf);
}

void testCriarHash4(void){
    HashFile hf = createHashFile(4, 3);
    TEST_ASSERT_NOT_NULL(hf);
    int profundidade = getProfundidadeGlobal(hf);
    TEST_ASSERT_EQUAL_INT(3, profundidade);
    freeHash(hf);
}

void testCriarHash5(void){
    HashFile hf = createHashFile(4, 2);
    TEST_ASSERT_NOT_NULL(hf);
    int tamanho = getTamanhoDiretorio(hf);
    TEST_ASSERT_EQUAL_INT(4, tamanho); 
    freeHash(hf);
}

void testCriarHash6(void){
    HashFile hf = createHashFile(8, 1);
    TEST_ASSERT_NOT_NULL(hf);
    int tamanhoBucket = getTamanhoBucket(hf);
    TEST_ASSERT_EQUAL_INT(8, tamanhoBucket);
    freeHash(hf);
}

void testCriarHash6(void){
    HashFile hf = createHashFile(8, 1);
    TEST_ASSERT_NOT_NULL(hf);
    int tamanhoBucket = hashGetBucketSize? 
    freeHash(hf);
}



void testInserirItem(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    int resultado = inserirItemHash(hf, 10, 100);
    TEST_ASSERT_EQUAL_INT(1, resultado);
    
    freeHash(hf);
}

void testBuscaItem1(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    
    int valor;
    int encontrado = buscaItemHash(hf, 10, &valor);
    TEST_ASSERT_EQUAL_INT(1, encontrado);
    TEST_ASSERT_EQUAL_INT(100, valor);
    
    freeHash(hf);
}

void testBuscaItem2(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    
    int valor;
    int encontrado = buscaItemHash(hf, 99, &valor);
    TEST_ASSERT_EQUAL_INT(0, encontrado);
    
    freeHash(hf);
}

void testBuscaItem3(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    
    int encontrado = buscaItemHash(hf, 10, NULL);
    TEST_ASSERT_EQUAL_INT(1, encontrado);
    
    freeHash(hf);
}

void testInserirItens(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);

    int resultado1 = inserirItemHash(hf, 10, 100);
    int resultado2 = inserirItemHash(hf, 20, 200);
    int resultado3 = inserirItemHash(hf, 30, 300);
    int resultado4 = inserirItemHash(hf, 40, 400);
    
    TEST_ASSERT_EQUAL_INT(1, resultado1);
    TEST_ASSERT_EQUAL_INT(1, resultado2);
    TEST_ASSERT_EQUAL_INT(1, resultado3);
    TEST_ASSERT_EQUAL_INT(1, resultado4);
    
    int quantidade = getTotalElementos(hf);
    TEST_ASSERT_EQUAL_INT(4, quantidade);
    
    freeHash(hf);
}

void testInserirItemChave(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    inserirItemHash(hf, 10, 999);
    
    int valor;
    buscaItemHash(hf, 10, &valor);
    TEST_ASSERT_EQUAL_INT(999, valor);
    
    freeHash(hf);
}



void testDeletarItem1(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    
    int resultado = deletarItemHash(hf, 10);
    TEST_ASSERT_EQUAL_INT(1, resultado);
    
    freeHash(hf);
}

void testDeletarItem2(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    deletarItemHash(hf, 10);
    
    int valor;
    int encontrado = buscaItemHash(hf, 10, &valor);
    TEST_ASSERT_EQUAL_INT(0, encontrado);
    
    freeHash(hf);
}

void testDeletarItem3(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    
    int resultado = deletarItemHash(hf, 99);
    TEST_ASSERT_EQUAL_INT(0, resultado);
    
    freeHash(hf);
}

void testDeletarItem4(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    int resultado = deletarItemHash(hf, 10);
    TEST_ASSERT_EQUAL_INT(0, resultado);
    
    freeHash(hf);
}



void testSplit1(void){
    HashFile hf = createHashFile(2, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    inserirItemHash(hf, 20, 200);
    inserirItemHash(hf, 30, 300);
    
    int valor;
    int encontrado = buscaItemHash(hf, 30, &valor);
    TEST_ASSERT_EQUAL_INT(1, encontrado);
    TEST_ASSERT_EQUAL_INT(300, valor);
    
    freeHash(hf);
}

void testSplit2(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    inserirItemHash(hf, 20, 200);
    inserirItemHash(hf, 30, 300);
    inserirItemHash(hf, 40, 400);
    
    int resultado = splitBucket(hf, 0);
    TEST_ASSERT_EQUAL_INT(1, resultado);
    
    freeHash(hf);
}

void testDobraDiretorio(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    int profundidadeAntes = getProfundidadeGlobal(hf);
    TEST_ASSERT_EQUAL_INT(1, profundidadeAntes);
    
    int resultado = dobraDiretorio(hf);
    TEST_ASSERT_EQUAL_INT(1, resultado);
    
    int profundidadeDepois = getProfundidadeGlobal(hf);
    TEST_ASSERT_EQUAL_INT(2, profundidadeDepois);
    
    int tamanhoDiretorio = getTamanhoDiretorio(hf);
    TEST_ASSERT_EQUAL_INT(4, tamanhoDiretorio);
    
    freeHash(hf);
}



void testCriaBucket1(void){
    Bucket b = createBucket(1);
    TEST_ASSERT_NOT_NULL(b);
}

void testCriaBucket2(void){
    Bucket b = createBucket(-1);
    TEST_ASSERT_NULL(b);
}




void testFreeHash1(void){
    freeHash(NULL);
    TEST_ASSERT_TRUE(1); 
}

void testFreeHash2(void){
    HashFile hf = createHashFile(4, 1);
    TEST_ASSERT_NOT_NULL(hf);
    
    inserirItemHash(hf, 10, 100);
    inserirItemHash(hf, 20, 200);
    inserirItemHash(hf, 30, 300);
    
    freeHash(hf);
    TEST_ASSERT_TRUE(1); 
}

void testGetProfundidadeBucket(void){
    HashFile hf = createHashFile(4, 2);
    TEST_ASSERT_NOT_NULL(hf);
    int profundidade = getProfundidadeBucket(hf, 0);
    TEST_ASSERT_EQUAL_INT(2, profundidade);
    freeHash(hf);
}

void testGetQuantidadeBucket(void){
    HashFile hf = createHashFile(4, 2);
    TEST_ASSERT_NOT_NULL(hf);
    inserirItemHash(hf, 10, 100);
    int quantidade = getQuantidadeBucket(hf, 0);
    TEST_ASSERT_EQUAL_INT(1, quantidade);
    freeHash(hf);
}

void testBucketEstaCheio(void){
    HashFile hf = createHashFile(2, 1);
    TEST_ASSERT_NOT_NULL(hf);
    inserirItemHash(hf, 10, 100);
    TEST_ASSERT_EQUAL_INT(0, bucketEstaCheio(hf, 0));
    inserirItemHash(hf, 20, 200);
    TEST_ASSERT_EQUAL_INT(1, bucketEstaCheio(hf, 0));
    freeHash(hf);
}

void testErro1(void){
    int resultado = inserirItemHash(NULL, 10, 100);
    TEST_ASSERT_EQUAL_INT(0, resultado);
}

void testErro2(void){
    int valor;
    int resultado = buscaItemHash(NULL, 10, &valor);
    TEST_ASSERT_EQUAL_INT(0, resultado);
}

void testErro3(void){
    int resultado = deletarItemHash(NULL, 10);
    TEST_ASSERT_EQUAL_INT(0, resultado);
}

void testErro4(void){
    int resultado = dobraDiretorio(NULL);
    TEST_ASSERT_EQUAL_INT(0, resultado);
}

void testErro5(void){
    int resultado = splitBucket(NULL, 0);
    TEST_ASSERT_EQUAL_INT(0, resultado);
}

void testErro6(void){
    int resultado = getProfundidadeGlobal(NULL);
    TEST_ASSERT_EQUAL_INT(-1, resultado);
}

void testErro7(void){
    int resultado = getTamanhoDiretorio(NULL);
    TEST_ASSERT_EQUAL_INT(-1, resultado);
}



int main(void){
    UNITY_BEGIN();
    
    RUN_TEST(testCriarHash1);
    RUN_TEST(testCriarHash2);
    RUN_TEST(testCriarHash3);
    RUN_TEST(testCriarHash4);
    RUN_TEST(testCriarHash5);
    RUN_TEST(testCriarHash6);
    
    RUN_TEST(testInserirItem);
    RUN_TEST(testBuscaItem1);
    RUN_TEST(testBuscaItem2);
    RUN_TEST(testBuscaItem3);
    RUN_TEST(testInserirItens);
    RUN_TEST(testInserirItemChave);
    
    RUN_TEST(testDeletarItem1);
    RUN_TEST(testDeletarItem2);
    RUN_TEST(testDeletarItem3);
    RUN_TEST(testDeletarItem4);
    
    RUN_TEST(testSplit1);
    RUN_TEST(testSplit2);
    RUN_TEST(testDobraDiretorio);
    
    RUN_TEST(testCriaBucket1);
    RUN_TEST(testCriaBucket2);
    RUN_TEST(testGetProfundidadeBucket);
    RUN_TEST(testGetQuantidadeBucket);
    RUN_TEST(testBucketEstaCheio);
    
    RUN_TEST(testFreeHash1);
    RUN_TEST(testFreeHash2);
    
    RUN_TEST(testErro1);
    RUN_TEST(testErro2);
    RUN_TEST(testErro3);
    RUN_TEST(testErro4);
    RUN_TEST(testErro5);
    RUN_TEST(testErro6);
    RUN_TEST(testErro7);
    
    return UNITY_END();
}
