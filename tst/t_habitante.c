#include "unity.h"
#include "habitante.h"
#include <stdlib.h>
#include <string.h>

static Habitante h1, h2;

void setUp(void) {
    h1 = criaHabitante("12345678901", "Joao", "Silva", 'M', "15/03/1985");
    h2 = criaHabitante("10987654321", "Maria", "Santos", 'F', "20/07/1990");
}

void tearDown(void) {
    if (h1) { freeHabitante(h1); h1 = NULL; }
    if (h2) { freeHabitante(h2); h2 = NULL; }
}

void test_criaHabitante_sucesso(void) {
    TEST_ASSERT_NOT_NULL(h1);
    TEST_ASSERT_NOT_NULL(h2);
}

void test_criaHabitante_cpf_invalido(void) {
    Habitante h = criaHabitante("123", "Teste", "Erro", 'M', "01/01/1990");
    TEST_ASSERT_NULL(h);

    h = criaHabitante(NULL, "Teste", "Erro", 'M', "01/01/1990");
    TEST_ASSERT_NULL(h);

    h = criaHabitante("1234567890a", "Teste", "Erro", 'M', "01/01/1990");
    TEST_ASSERT_NULL(h);
}

void test_criaHabitante_nome_invalido(void) {
    Habitante h = criaHabitante("11122233344", "", "Erro", 'M', "01/01/1990");
    TEST_ASSERT_NULL(h);

    h = criaHabitante("11122233344", NULL, "Erro", 'M', "01/01/1990");
    TEST_ASSERT_NULL(h);
}

void test_criaHabitante_sobrenome_invalido(void) {
    Habitante h = criaHabitante("11122233344", "Teste", "", 'M', "01/01/1990");
    TEST_ASSERT_NULL(h);

    h = criaHabitante("11122233344", "Teste", NULL, 'M', "01/01/1990");
    TEST_ASSERT_NULL(h);
}

void test_criaHabitante_sexo_invalido(void) {
    Habitante h = criaHabitante("11122233344", "Teste", "Erro", 'X', "01/01/1990");
    TEST_ASSERT_NULL(h);
}

void test_criaHabitante_data_invalida(void) {
    Habitante h = criaHabitante("11122233344", "Teste", "Erro", 'M', "32/01/1990");
    TEST_ASSERT_NULL(h);

    h = criaHabitante("11122233344", "Teste", "Erro", 'M', "01/13/1990");
    TEST_ASSERT_NULL(h);

    h = criaHabitante("11122233344", "Teste", "Erro", 'M', "01/01/199");
    TEST_ASSERT_NULL(h);

    h = criaHabitante("11122233344", "Teste", "Erro", 'M', NULL);
    TEST_ASSERT_NULL(h);
}

void test_criaHabitante_sexo_minusculo(void) {
    Habitante h = criaHabitante("11122233344", "Teste", "Minusculo", 'm', "01/01/1990");
    TEST_ASSERT_NOT_NULL(h);
    TEST_ASSERT_EQUAL_CHAR('M', getSexoHabitante(h));
    freeHabitante(h);

    h = criaHabitante("11122233344", "Teste", "Minusculo", 'f', "01/01/1990");
    TEST_ASSERT_NOT_NULL(h);
    TEST_ASSERT_EQUAL_CHAR('F', getSexoHabitante(h));
    freeHabitante(h);
}

void test_getCpfHabitante(void) {
    TEST_ASSERT_EQUAL_STRING("12345678901", getCpfHabitante(h1));
    TEST_ASSERT_EQUAL_STRING("10987654321", getCpfHabitante(h2));
}

void test_getNomeHabitante(void) {
    TEST_ASSERT_EQUAL_STRING("Joao", getNomeHabitante(h1));
    TEST_ASSERT_EQUAL_STRING("Maria", getNomeHabitante(h2));
}

void test_getSobrenomeHabitante(void) {
    TEST_ASSERT_EQUAL_STRING("Silva", getSobrenomeHabitante(h1));
    TEST_ASSERT_EQUAL_STRING("Santos", getSobrenomeHabitante(h2));
}

void test_getNomeCompletoHabitante(void) {
    const char *completo1 = getNomeCompletoHabitante(h1);
    TEST_ASSERT_EQUAL_STRING("Joao Silva", completo1);
    free((void*)completo1);

    const char *completo2 = getNomeCompletoHabitante(h2);
    TEST_ASSERT_EQUAL_STRING("Maria Santos", completo2);
    free((void*)completo2);
}

void test_getSexoHabitante(void) {
    TEST_ASSERT_EQUAL_CHAR('M', getSexoHabitante(h1));
    TEST_ASSERT_EQUAL_CHAR('F', getSexoHabitante(h2));
}

void test_getNascimentoHabitante(void) {
    TEST_ASSERT_EQUAL_STRING("15/03/1985", getNascimentoHabitante(h1));
    TEST_ASSERT_EQUAL_STRING("20/07/1990", getNascimentoHabitante(h2));
}

void test_isMoradorHabitante_inicial(void) {
    TEST_ASSERT_EQUAL_INT(0, isMoradorHabitante(h1));
    TEST_ASSERT_EQUAL_INT(0, isMoradorHabitante(h2));
}

void test_setIdMoradiaHabitante(void) {
    TEST_ASSERT_NULL(getIdMoradiaHabitante(h1));
    TEST_ASSERT_EQUAL_INT(0, isMoradorHabitante(h1));

    setIdMoradiaHabitante(h1, "cep15/S/45");
    TEST_ASSERT_EQUAL_STRING("cep15/S/45", getIdMoradiaHabitante(h1));
    TEST_ASSERT_EQUAL_INT(1, isMoradorHabitante(h1));
}

void test_setIdMoradiaHabitante_NULL(void) {
    setIdMoradiaHabitante(h1, "cep15/S/45");
    TEST_ASSERT_EQUAL_INT(1, isMoradorHabitante(h1));

    setIdMoradiaHabitante(h1, NULL);
    TEST_ASSERT_NULL(getIdMoradiaHabitante(h1));
    TEST_ASSERT_EQUAL_INT(0, isMoradorHabitante(h1));
}

void test_validaCpf(void) {
    TEST_ASSERT_TRUE(validaCpf("12345678901"));
    TEST_ASSERT_TRUE(validaCpf("00000000000"));
    TEST_ASSERT_FALSE(validaCpf("1234567890"));
    TEST_ASSERT_FALSE(validaCpf("123456789012"));
    TEST_ASSERT_FALSE(validaCpf("1234567890a"));
    TEST_ASSERT_FALSE(validaCpf(NULL));
}

void test_validaSexo(void) {
    TEST_ASSERT_TRUE(validaSexo('M'));
    TEST_ASSERT_TRUE(validaSexo('m'));
    TEST_ASSERT_TRUE(validaSexo('F'));
    TEST_ASSERT_TRUE(validaSexo('f'));
    TEST_ASSERT_FALSE(validaSexo('X'));
    TEST_ASSERT_FALSE(validaSexo('1'));
    TEST_ASSERT_FALSE(validaSexo('\0'));
}

void test_validaData(void) {
    TEST_ASSERT_TRUE(validaData("01/01/1990"));
    TEST_ASSERT_TRUE(validaData("31/12/2020"));
    TEST_ASSERT_TRUE(validaData("29/02/2020"));
    TEST_ASSERT_FALSE(validaData("29/02/2021"));
    TEST_ASSERT_FALSE(validaData("31/04/1990"));
    TEST_ASSERT_FALSE(validaData("01/13/1990"));
    TEST_ASSERT_FALSE(validaData("01/01/99"));
    TEST_ASSERT_FALSE(validaData(NULL));
}

void test_comparaData(void) {
    TEST_ASSERT_EQUAL_INT(-1, comparaData("01/01/1990", "02/01/1990"));
    TEST_ASSERT_EQUAL_INT(1, comparaData("02/01/1990", "01/01/1990"));
    TEST_ASSERT_EQUAL_INT(0, comparaData("01/01/1990", "01/01/1990"));
    TEST_ASSERT_EQUAL_INT(-1, comparaData("01/01/1990", "01/01/1991"));
    TEST_ASSERT_EQUAL_INT(-1, comparaData("01/01/1990", "01/02/1990"));
}

void test_calculaIdade(void) {
    TEST_ASSERT_EQUAL_INT(35, calculaIdade("15/03/1985", "15/03/2020"));
    TEST_ASSERT_EQUAL_INT(34, calculaIdade("15/03/1985", "14/03/2020"));
    TEST_ASSERT_EQUAL_INT(0, calculaIdade("01/01/2020", "01/01/2020"));
    TEST_ASSERT_EQUAL_INT(-1, calculaIdade(NULL, "01/01/2020"));
    TEST_ASSERT_EQUAL_INT(-1, calculaIdade("01/01/2020", NULL));
}

void test_serialDesserialHabitante(void) {
    setIdMoradiaHabitante(h1, "cep15/S/45");

    size_t tam = tamSerialHabitante();
    void *buffer = malloc(tam);
    TEST_ASSERT_NOT_NULL(buffer);

    int ret = serialHabitante(h1, buffer, tam);
    TEST_ASSERT_EQUAL_INT(1, ret);

    Habitante reconstruido = desserialHabitante(buffer, tam);
    TEST_ASSERT_NOT_NULL(reconstruido);

    TEST_ASSERT_EQUAL_STRING(getCpfHabitante(h1), getCpfHabitante(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getNomeHabitante(h1), getNomeHabitante(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getSobrenomeHabitante(h1), getSobrenomeHabitante(reconstruido));
    TEST_ASSERT_EQUAL_CHAR(getSexoHabitante(h1), getSexoHabitante(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getNascimentoHabitante(h1), getNascimentoHabitante(reconstruido));
    TEST_ASSERT_EQUAL_INT(isMoradorHabitante(h1), isMoradorHabitante(reconstruido));
    TEST_ASSERT_EQUAL_STRING(getIdMoradiaHabitante(h1), getIdMoradiaHabitante(reconstruido));

    freeHabitante(reconstruido);
    free(buffer);
}

void test_getters_com_NULL(void) {
    TEST_ASSERT_NULL(getCpfHabitante(NULL));
    TEST_ASSERT_NULL(getNomeHabitante(NULL));
    TEST_ASSERT_NULL(getSobrenomeHabitante(NULL));
    TEST_ASSERT_NULL(getNomeCompletoHabitante(NULL));
    TEST_ASSERT_EQUAL_CHAR('\0', getSexoHabitante(NULL));
    TEST_ASSERT_NULL(getNascimentoHabitante(NULL));
    TEST_ASSERT_NULL(getIdMoradiaHabitante(NULL));
    TEST_ASSERT_EQUAL_INT(-1, isMoradorHabitante(NULL));
}

void test_freeHabitante_NULL(void) {
    freeHabitante(NULL);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_criaHabitante_sucesso);
    RUN_TEST(test_criaHabitante_cpf_invalido);
    RUN_TEST(test_criaHabitante_nome_invalido);
    RUN_TEST(test_criaHabitante_sobrenome_invalido);
    RUN_TEST(test_criaHabitante_sexo_invalido);
    RUN_TEST(test_criaHabitante_data_invalida);
    RUN_TEST(test_criaHabitante_sexo_minusculo);
    RUN_TEST(test_getCpfHabitante);
    RUN_TEST(test_getNomeHabitante);
    RUN_TEST(test_getSobrenomeHabitante);
    RUN_TEST(test_getNomeCompletoHabitante);
    RUN_TEST(test_getSexoHabitante);
    RUN_TEST(test_getNascimentoHabitante);
    RUN_TEST(test_isMoradorHabitante_inicial);
    RUN_TEST(test_setIdMoradiaHabitante);
    RUN_TEST(test_setIdMoradiaHabitante_NULL);
    RUN_TEST(test_validaCpf);
    RUN_TEST(test_validaSexo);
    RUN_TEST(test_validaData);
    RUN_TEST(test_comparaData);
    RUN_TEST(test_calculaIdade);
    RUN_TEST(test_serialDesserialHabitante);
    RUN_TEST(test_getters_com_NULL);
    RUN_TEST(test_freeHabitante_NULL);

    return UNITY_END();
}
