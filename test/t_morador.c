#include "unity.h"
#include "morador.h"
#include "habitante.h"
#include <stdlib.h>
#include <string.h>

static Morador m1, m2;

void setUp(void) {
    m1 = criaMorador("12345678901", "Joao", "Silva", 'M', "01/01/1990", "cep15", 'S', 45, "Apto 101");
    m2 = criaMorador("10987654321", "Maria", "Santos", 'F', "15/05/1985", "cep07", 'N', 120, NULL);
}

void tearDown(void) {
    if (m1) { freeMorador(m1); m1 = NULL; }
    if (m2) { freeMorador(m2); m2 = NULL; }
}

void test_validaFace_valida(void) {
    TEST_ASSERT_TRUE(validaFace('N'));
    TEST_ASSERT_TRUE(validaFace('n'));
    TEST_ASSERT_TRUE(validaFace('S'));
    TEST_ASSERT_TRUE(validaFace('s'));
    TEST_ASSERT_TRUE(validaFace('L'));
    TEST_ASSERT_TRUE(validaFace('l'));
    TEST_ASSERT_TRUE(validaFace('O'));
    TEST_ASSERT_TRUE(validaFace('o'));
}

void test_validaFace_invalida(void) {
    TEST_ASSERT_FALSE(validaFace('X'));
    TEST_ASSERT_FALSE(validaFace('A'));
    TEST_ASSERT_FALSE(validaFace('1'));
    TEST_ASSERT_FALSE(validaFace('\0'));
}

void test_validaNum_valido(void) {
    TEST_ASSERT_TRUE(validaNum(0));
    TEST_ASSERT_TRUE(validaNum(1));
    TEST_ASSERT_TRUE(validaNum(1000));
}

void test_validaNum_invalido(void) {
    TEST_ASSERT_FALSE(validaNum(-1));
    TEST_ASSERT_FALSE(validaNum(-100));
}

void test_criaMorador_sucesso(void) {
    TEST_ASSERT_NOT_NULL(m1);
    TEST_ASSERT_NOT_NULL(m2);
}

void test_criaMorador_cpf_invalido(void) {
    Morador m = criaMorador("123", "Teste", "Erro", 'M', "01/01/1990", "cep01", 'N', 10, NULL);
    TEST_ASSERT_NULL(m);
}

void test_criaMorador_cep_invalido(void) {
    Morador m = criaMorador("11122233344", "Teste", "Erro", 'M', "01/01/1990", "", 'N', 10, NULL);
    TEST_ASSERT_NULL(m);
    
    m = criaMorador("11122233344", "Teste", "Erro", 'M', "01/01/1990", NULL, 'N', 10, NULL);
    TEST_ASSERT_NULL(m);
}

void test_criaMorador_face_invalida(void) {
    Morador m = criaMorador("11122233344", "Teste", "Erro", 'M', "01/01/1990", "cep01", 'X', 10, NULL);
    TEST_ASSERT_NULL(m);
}

void test_criaMorador_numero_invalido(void) {
    Morador m = criaMorador("11122233344", "Teste", "Erro", 'M', "01/01/1990", "cep01", 'N', -5, NULL);
    TEST_ASSERT_NULL(m);
}

void test_criaMorador_data_invalida(void) {
    Morador m = criaMorador("11122233344", "Teste", "Erro", 'M', "32/13/1990", "cep01", 'N', 10, NULL);
    TEST_ASSERT_NULL(m);
}

void test_criaMorador_sem_complemento(void) {
    Morador m = criaMorador("11122233344", "Teste", "Sem", 'M', "01/01/1990", "cep01", 'N', 10, NULL);
    TEST_ASSERT_NOT_NULL(m);
    
    const char *compl = getComplMorador(m);
    TEST_ASSERT_NULL(compl);
    
    freeMorador(m);
}

void test_criaMorador_com_complemento_vazio(void) {
    Morador m = criaMorador("11122233344", "Teste", "Vazio", 'M', "01/01/1990", "cep01", 'N', 10, "");
    TEST_ASSERT_NOT_NULL(m);
    
    const char *compl = getComplMorador(m);
    TEST_ASSERT_NULL(compl);
    
    freeMorador(m);
}

void test_criaMorador_sexo_minusculo(void) {
    Morador m = criaMorador("11122233344", "Teste", "Minusculo", 'm', "01/01/1990", "cep01", 'S', 20, NULL);
    TEST_ASSERT_NOT_NULL(m);
    TEST_ASSERT_EQUAL_CHAR('M', getSexoMorador(m));
    freeMorador(m);
}

void test_getCpfMorador(void) {
    TEST_ASSERT_EQUAL_STRING("12345678901", getCpfMorador(m1));
    TEST_ASSERT_EQUAL_STRING("10987654321", getCpfMorador(m2));
}

void test_getNomeMorador(void) {
    TEST_ASSERT_EQUAL_STRING("Joao", getNomeMorador(m1));
    TEST_ASSERT_EQUAL_STRING("Maria", getNomeMorador(m2));
}

void test_getSobrenomeMorador(void) {
    TEST_ASSERT_EQUAL_STRING("Silva", getSobrenomeMorador(m1));
    TEST_ASSERT_EQUAL_STRING("Santos", getSobrenomeMorador(m2));
}

void test_getNomeCompletoMorador(void) {
    const char *completo1 = getNomeCompletoMorador(m1);
    TEST_ASSERT_EQUAL_STRING("Joao Silva", completo1);
    free((void*)completo1);
    
    const char *completo2 = getNomeCompletoMorador(m2);
    TEST_ASSERT_EQUAL_STRING("Maria Santos", completo2);
    free((void*)completo2);
}

void test_getSexoMorador(void) {
    TEST_ASSERT_EQUAL_CHAR('M', getSexoMorador(m1));
    TEST_ASSERT_EQUAL_CHAR('F', getSexoMorador(m2));
}

void test_getNascMorador(void) {
    TEST_ASSERT_EQUAL_STRING("01/01/1990", getNascMorador(m1));
    TEST_ASSERT_EQUAL_STRING("15/05/1985", getNascMorador(m2));
}

void test_getCepMorador(void) {
    TEST_ASSERT_EQUAL_STRING("cep15", getCepMorador(m1));
    TEST_ASSERT_EQUAL_STRING("cep07", getCepMorador(m2));
}

void test_getFaceMorador(void) {
    TEST_ASSERT_EQUAL_CHAR('S', getFaceMorador(m1));
    TEST_ASSERT_EQUAL_CHAR('N', getFaceMorador(m2));
}

void test_getNumMorador(void) {
    TEST_ASSERT_EQUAL_INT(45, getNumMorador(m1));
    TEST_ASSERT_EQUAL_INT(120, getNumMorador(m2));
}

void test_getComplMorador(void) {
    TEST_ASSERT_EQUAL_STRING("Apto 101", getComplMorador(m1));
    TEST_ASSERT_NULL(getComplMorador(m2));
}

void test_getEnderecoCompletoMorador_com_complemento(void) {
    const char *end = getEnderecoCompletoMorador(m1);
    TEST_ASSERT_EQUAL_STRING("cep15/S/45/Apto 101", end);
    free((void*)end);
}

void test_getEnderecoCompletoMorador_sem_complemento(void) {
    const char *end = getEnderecoCompletoMorador(m2);
    TEST_ASSERT_EQUAL_STRING("cep07/N/120", end);
    free((void*)end);
}

void test_getHabitanteMorador(void) {
    Habitante h1 = getHabitanteMorador(m1);
    TEST_ASSERT_NOT_NULL(h1);
    TEST_ASSERT_EQUAL_STRING("12345678901", getCpfHabitante(h1));
    TEST_ASSERT_EQUAL_STRING("Joao", getNomeHabitante(h1));
    
    Habitante h2 = getHabitanteMorador(m2);
    TEST_ASSERT_NOT_NULL(h2);
    TEST_ASSERT_EQUAL_STRING("10987654321", getCpfHabitante(h2));
    TEST_ASSERT_EQUAL_STRING("Maria", getNomeHabitante(h2));
}

void test_getters_com_NULL(void) {
    TEST_ASSERT_NULL(getCpfMorador(NULL));
    TEST_ASSERT_NULL(getNomeMorador(NULL));
    TEST_ASSERT_NULL(getSobrenomeMorador(NULL));
    TEST_ASSERT_NULL(getNomeCompletoMorador(NULL));
    TEST_ASSERT_EQUAL_CHAR('\0', getSexoMorador(NULL));
    TEST_ASSERT_NULL(getNascMorador(NULL));
    TEST_ASSERT_NULL(getCepMorador(NULL));
    TEST_ASSERT_EQUAL_CHAR('\0', getFaceMorador(NULL));
    TEST_ASSERT_EQUAL_INT(-1, getNumMorador(NULL));
    TEST_ASSERT_NULL(getComplMorador(NULL));
    TEST_ASSERT_NULL(getEnderecoCompletoMorador(NULL));
    TEST_ASSERT_NULL(getHabitanteMorador(NULL));
}

void test_freeMorador_NULL(void) {
    freeMorador(NULL);
}

void test_tamSerialMorador(void) {
    size_t tam = tamSerialMorador();
    TEST_ASSERT_GREATER_THAN(0, tam);
}

void test_serialDesserialMorador_com_complemento(void) {
    size_t tam = tamSerialMorador();
    void *buffer = malloc(tam);
    TEST_ASSERT_NOT_NULL(buffer);
    
    int ret = serialMorador(m1, buffer, tam);
    TEST_ASSERT_EQUAL_INT(1, ret);
    
    Morador reconstruido = desserialMorador(buffer, tam);
    TEST_ASSERT_NOT_NULL(reconstruido);
    
    TEST_ASSERT_EQUAL_STRING(getCpfMorador(m1), getCpfMorador(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getNomeMorador(m1), getNomeMorador(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getSobrenomeMorador(m1), getSobrenomeMorador(reconstruido));
    TEST_ASSERT_EQUAL_CHAR(getSexoMorador(m1), getSexoMorador(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getNascMorador(m1), getNascMorador(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getCepMorador(m1), getCepMorador(reconstruido));
    TEST_ASSERT_EQUAL_CHAR(getFaceMorador(m1), getFaceMorador(reconstruido));
    TEST_ASSERT_EQUAL_INT(getNumMorador(m1), getNumMorador(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getComplMorador(m1), getComplMorador(reconstruido));
    
    freeMorador(reconstruido);
    free(buffer);
}

void test_serialDesserialMorador_sem_complemento(void) {
    size_t tam = tamSerialMorador();
    void *buffer = malloc(tam);
    TEST_ASSERT_NOT_NULL(buffer);
    
    int ret = serialMorador(m2, buffer, tam);
    TEST_ASSERT_EQUAL_INT(1, ret);
    
    Morador reconstruido = desserialMorador(buffer, tam);
    TEST_ASSERT_NOT_NULL(reconstruido);
    
    TEST_ASSERT_EQUAL_STRING(getCpfMorador(m2), getCpfMorador(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getNomeMorador(m2), getNomeMorador(reconstruido));
    TEST_ASSERT_EQUAL_CHAR(getSexoMorador(m2), getSexoMorador(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getNascMorador(m2), getNascMorador(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getCepMorador(m2), getCepMorador(reconstruido));
    TEST_ASSERT_EQUAL_CHAR(getFaceMorador(m2), getFaceMorador(reconstruido));
    TEST_ASSERT_EQUAL_INT(getNumMorador(m2), getNumMorador(reconstruido));
    TEST_ASSERT_NULL(getComplMorador(reconstruido));
    
    freeMorador(reconstruido);
    free(buffer);
}

void test_serialMorador_buffer_insuficiente(void) {
    char buffer[10];
    int ret = serialMorador(m1, buffer, 10);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_serialMorador_NULL(void) {
    char buffer[100];
    int ret = serialMorador(NULL, buffer, 100);
    TEST_ASSERT_EQUAL_INT(0, ret);
    
    ret = serialMorador(m1, NULL, 100);
    TEST_ASSERT_EQUAL_INT(0, ret);
}

void test_desserialMorador_buffer_insuficiente(void) {
    char buffer[10];
    Morador m = desserialMorador(buffer, 10);
    TEST_ASSERT_NULL(m);
}

void test_desserialMorador_NULL(void) {
    Morador m = desserialMorador(NULL, 100);
    TEST_ASSERT_NULL(m);
}

void test_face_minuscula_normalizada(void) {
    Morador m = criaMorador("11122233344", "Teste", "Face", 'M', "01/01/1990", "cep01", 'n', 10, NULL);
    TEST_ASSERT_EQUAL_CHAR('N', getFaceMorador(m));
    freeMorador(m);
    
    m = criaMorador("11122233344", "Teste", "Face", 'M', "01/01/1990", "cep01", 's', 10, NULL);
    TEST_ASSERT_EQUAL_CHAR('S', getFaceMorador(m));
    freeMorador(m);
    
    m = criaMorador("11122233344", "Teste", "Face", 'M', "01/01/1990", "cep01", 'l', 10, NULL);
    TEST_ASSERT_EQUAL_CHAR('L', getFaceMorador(m));
    freeMorador(m);
    
    m = criaMorador("11122233344", "Teste", "Face", 'M', "01/01/1990", "cep01", 'o', 10, NULL);
    TEST_ASSERT_EQUAL_CHAR('O', getFaceMorador(m));
    freeMorador(m);
}

int main(void) {
    UNITY_BEGIN();
    
    RUN_TEST(test_validaFace_valida);
    RUN_TEST(test_validaFace_invalida);
    RUN_TEST(test_validaNum_valido);
    RUN_TEST(test_validaNum_invalido);
    
    RUN_TEST(test_criaMorador_sucesso);
    RUN_TEST(test_criaMorador_cpf_invalido);
    RUN_TEST(test_criaMorador_cep_invalido);
    RUN_TEST(test_criaMorador_face_invalida);
    RUN_TEST(test_criaMorador_numero_invalido);
    RUN_TEST(test_criaMorador_data_invalida);
    RUN_TEST(test_criaMorador_sem_complemento);
    RUN_TEST(test_criaMorador_com_complemento_vazio);
    RUN_TEST(test_criaMorador_sexo_minusculo);
    
    RUN_TEST(test_getCpfMorador);
    RUN_TEST(test_getNomeMorador);
    RUN_TEST(test_getSobrenomeMorador);
    RUN_TEST(test_getNomeCompletoMorador);
    RUN_TEST(test_getSexoMorador);
    RUN_TEST(test_getNascMorador);
    RUN_TEST(test_getCepMorador);
    RUN_TEST(test_getFaceMorador);
    RUN_TEST(test_getNumMorador);
    RUN_TEST(test_getComplMorador);
    RUN_TEST(test_getEnderecoCompletoMorador_com_complemento);
    RUN_TEST(test_getEnderecoCompletoMorador_sem_complemento);
    RUN_TEST(test_getHabitanteMorador);
    
    RUN_TEST(test_getters_com_NULL);
    RUN_TEST(test_freeMorador_NULL);
    
    RUN_TEST(test_tamSerialMorador);
    RUN_TEST(test_serialDesserialMorador_com_complemento);
    RUN_TEST(test_serialDesserialMorador_sem_complemento);
    RUN_TEST(test_serialMorador_buffer_insuficiente);
    RUN_TEST(test_serialMorador_NULL);
    RUN_TEST(test_desserialMorador_buffer_insuficiente);
    RUN_TEST(test_desserialMorador_NULL);
    
    RUN_TEST(test_face_minuscula_normalizada);
    
    return UNITY_END();
}
