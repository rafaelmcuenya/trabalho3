#include "unity.h"
#include "hashfile.h"
#include <stdlib.h>
#include <string.h>

static HashFile *hf;
static const char *nomeBase = "teste_hashfile";

void setUp(void) {
    hf = criarHF(nomeBase, 4, 2);
}

void tearDown(void) {
    if (hf) {
        freeHF(hf);
        hf = NULL;
    }
}

void test_criarHF_sucesso(void) {
    TEST_ASSERT_NOT_NULL(hf);
    TEST_ASSERT_EQUAL_INT(2, getProfGlobalHF(hf));
    TEST_ASSERT_EQUAL_INT(4, getTamBucketHF(hf));
}

void test_criarHF_parametros_invalidos(void) {
    HashFile *h = criarHF(NULL, 4, 2);
    TEST_ASSERT_NULL(h);

    h = criarHF("teste", 0, 2);
    TEST_ASSERT_NULL(h);

    h = criarHF("teste", 4, 0);
    TEST_ASSERT_NULL(h);
}

void test_insertHF_sucesso(void) {
    char dado[] = "dados_teste_123";
    int ret = insertHF(hf, "chave1", dado, strlen(dado) + 1);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_INT(1, (int)totalRegistrosHF(hf));
}

void test_insertHF_chave_duplicada(void) {
    char dado[] = "dados_teste";
    insertHF(hf, "chave1", dado, strlen(dado) + 1);
    int ret = insertHF(hf, "chave1", dado, strlen(dado) + 1);
    TEST_ASSERT_EQUAL_INT(0, ret);
    TEST_ASSERT_EQUAL_INT(1, (int)totalRegistrosHF(hf));
}

void test_insertHF_parametros_invalidos(void) {
    char dado[] = "dados";
    TEST_ASSERT_EQUAL_INT(-1, insertHF(NULL, "chave", dado, 5));
    TEST_ASSERT_EQUAL_INT(-1, insertHF(hf, NULL, dado, 5));
    TEST_ASSERT_EQUAL_INT(-1, insertHF(hf, "chave", NULL, 5));
    TEST_ASSERT_EQUAL_INT(-1, insertHF(hf, "chave", dado, 0));
}

void test_buscaHF_encontrado(void) {
    char dado[] = "dados_busca";
    insertHF(hf, "chaveX", dado, strlen(dado) + 1);

    char buffer[64];
    sizeT tam = sizeof(buffer);
    int ret = buscaHF(hf, "chaveX", buffer, &tam);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_STRING("dados_busca", buffer);
}

void test_buscaHF_nao_encontrado(void) {
    char buffer[64];
    sizeT tam = sizeof(buffer);
    int ret = buscaHF(hf, "inexistente", buffer, &tam);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_buscaHF_parametros_invalidos(void) {
    char buffer[64];
    sizeT tam = sizeof(buffer);
    TEST_ASSERT_EQUAL_INT(-1, buscaHF(NULL, "chave", buffer, &tam));
    TEST_ASSERT_EQUAL_INT(-1, buscaHF(hf, NULL, buffer, &tam));
}

void test_buscaHF_buffer_insuficiente(void) {
    char dado[] = "dados_grandes";
    insertHF(hf, "chaveG", dado, strlen(dado) + 1);

    char buffer[5];
    sizeT tam = 5;
    int ret = buscaHF(hf, "chaveG", buffer, &tam);
    TEST_ASSERT_EQUAL_INT(-1, ret);
}

void test_deletarItemHF_sucesso(void) {
    char dado[] = "para_deletar";
    insertHF(hf, "chaveDel", dado, strlen(dado) + 1);
    TEST_ASSERT_EQUAL_INT(1, (int)totalRegistrosHF(hf));

    int ret = deletarItemHF(hf, "chaveDel");
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_INT(0, (int)totalRegistrosHF(hf));
}

void test_deletarItemHF_nao_encontrado(void) {
    int ret = deletarItemHF(hf, "inexistente");
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_deletarItemHF_parametros_invalidos(void) {
    TEST_ASSERT_EQUAL_INT(-1, deletarItemHF(NULL, "chave"));
    TEST_ASSERT_EQUAL_INT(-1, deletarItemHF(hf, NULL));
}

void test_refreshHF_sucesso(void) {
    char dado[] = "original";
    insertHF(hf, "chaveRef", dado, strlen(dado) + 1);

    char novo[] = "atualizado";
    int ret = refreshHF(hf, "chaveRef", novo, strlen(novo) + 1);
    TEST_ASSERT_EQUAL_INT(1, ret);

    char buffer[64];
    sizeT tam = sizeof(buffer);
    buscaHF(hf, "chaveRef", buffer, &tam);
    TEST_ASSERT_EQUAL_STRING("atualizado", buffer);
}

void test_refreshHF_nao_encontrado(void) {
    char dado[] = "dado";
    int ret = refreshHF(hf, "inexistente", dado, strlen(dado) + 1);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_refreshHF_parametros_invalidos(void) {
    char dado[] = "dado";
    TEST_ASSERT_EQUAL_INT(-1, refreshHF(NULL, "chave", dado, 5));
    TEST_ASSERT_EQUAL_INT(-1, refreshHF(hf, NULL, dado, 5));
    TEST_ASSERT_EQUAL_INT(-1, refreshHF(hf, "chave", NULL, 5));
    TEST_ASSERT_EQUAL_INT(-1, refreshHF(hf, "chave", dado, 0));
}

void test_totalRegistrosHF(void) {
    TEST_ASSERT_EQUAL_INT(0, (int)totalRegistrosHF(hf));

    char dado[] = "dados";
    insertHF(hf, "c1", dado, strlen(dado) + 1);
    insertHF(hf, "c2", dado, strlen(dado) + 1);
    insertHF(hf, "c3", dado, strlen(dado) + 1);
    TEST_ASSERT_EQUAL_INT(3, (int)totalRegistrosHF(hf));

    deletarItemHF(hf, "c2");
    TEST_ASSERT_EQUAL_INT(2, (int)totalRegistrosHF(hf));
}

void test_totalRegistrosHF_NULL(void) {
    TEST_ASSERT_EQUAL_INT(0, (int)totalRegistrosHF(NULL));
}

void test_getProfGlobalHF(void) {
    TEST_ASSERT_EQUAL_INT(2, getProfGlobalHF(hf));
    TEST_ASSERT_EQUAL_INT(-1, getProfGlobalHF(NULL));
}

void test_getTamBucketHF(void) {
    TEST_ASSERT_EQUAL_INT(4, getTamBucketHF(hf));
    TEST_ASSERT_EQUAL_INT(-1, getTamBucketHF(NULL));
}

void test_getInfoBucketHF(void) {
    int qtd, prof;
    int ret = getInfoBucketHF(hf, 0, &qtd, &prof);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_INT(0, qtd);
    TEST_ASSERT_EQUAL_INT(2, prof);
}

void test_getInfoBucketHF_invalido(void) {
    int qtd, prof;
    TEST_ASSERT_EQUAL_INT(0, getInfoBucketHF(NULL, 0, &qtd, &prof));
    TEST_ASSERT_EQUAL_INT(0, getInfoBucketHF(hf, -1, &qtd, &prof));
    TEST_ASSERT_EQUAL_INT(0, getInfoBucketHF(hf, 999, &qtd, &prof));
}

void test_insercao_multipla_com_split(void) {
    char dado[32];
    for (int i = 1; i <= 20; i++) {
        char chave[16];
        snprintf(chave, sizeof(chave), "chave%d", i);
        snprintf(dado, sizeof(dado), "dados_numero_%d", i);
        insertHF(hf, chave, dado, strlen(dado) + 1);
    }
    TEST_ASSERT_EQUAL_INT(20, (int)totalRegistrosHF(hf));

    char buffer[64];
    sizeT tam = sizeof(buffer);
    int ret = buscaHF(hf, "chave10", buffer, &tam);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_STRING("dados_numero_10", buffer);
}

void test_deletar_e_reinserir(void) {
    char dado[] = "primeiro";
    insertHF(hf, "chaveX", dado, strlen(dado) + 1);
    deletarItemHF(hf, "chaveX");
    TEST_ASSERT_EQUAL_INT(0, (int)totalRegistrosHF(hf));

    char dado2[] = "segundo";
    int ret = insertHF(hf, "chaveX", dado2, strlen(dado2) + 1);
    TEST_ASSERT_EQUAL_INT(1, ret);
    TEST_ASSERT_EQUAL_INT(1, (int)totalRegistrosHF(hf));

    char buffer[64];
    sizeT tam = sizeof(buffer);
    buscaHF(hf, "chaveX", buffer, &tam);
    TEST_ASSERT_EQUAL_STRING("segundo", buffer);
}

void test_gerarDumpHF(void) {
    char dado[] = "dump_test";
    insertHF(hf, "chaveDump", dado, strlen(dado) + 1);
    int ret = gerarDumpHF(hf);
    TEST_ASSERT_EQUAL_INT(1, ret);
}

void test_gerarDumpHF_NULL(void) {
    TEST_ASSERT_EQUAL_INT(0, gerarDumpHF(NULL));
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_criarHF_sucesso);
    RUN_TEST(test_criarHF_parametros_invalidos);
    RUN_TEST(test_insertHF_sucesso);
    RUN_TEST(test_insertHF_chave_duplicada);
    RUN_TEST(test_insertHF_parametros_invalidos);
    RUN_TEST(test_buscaHF_encontrado);
    RUN_TEST(test_buscaHF_nao_encontrado);
    RUN_TEST(test_buscaHF_parametros_invalidos);
    RUN_TEST(test_buscaHF_buffer_insuficiente);
    RUN_TEST(test_deletarItemHF_sucesso);
    RUN_TEST(test_deletarItemHF_nao_encontrado);
    RUN_TEST(test_deletarItemHF_parametros_invalidos);
    RUN_TEST(test_refreshHF_sucesso);
    RUN_TEST(test_refreshHF_nao_encontrado);
    RUN_TEST(test_refreshHF_parametros_invalidos);
    RUN_TEST(test_totalRegistrosHF);
    RUN_TEST(test_totalRegistrosHF_NULL);
    RUN_TEST(test_getProfGlobalHF);
    RUN_TEST(test_getTamBucketHF);
    RUN_TEST(test_getInfoBucketHF);
    RUN_TEST(test_getInfoBucketHF_invalido);
    RUN_TEST(test_insercao_multipla_com_split);
    RUN_TEST(test_deletar_e_reinserir);
    RUN_TEST(test_gerarDumpHF);
    RUN_TEST(test_gerarDumpHF_NULL);

    return UNITY_END();
}
