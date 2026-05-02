#include "habitante.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CPF_LEN 12
#define NOME_LEN 100
#define SOBRENOME_LEN 100
#define DATA_LEN 11
#define ID_MORADIA_LEN 64

typedef struct {
    char cpf[CPF_LEN];
    char nome[NOME_LEN];
    char sobrenome[SOBRENOME_LEN];
    char sexo;
    char nasc[DATA_LEN];
    char idMoradia[ID_MORADIA_LEN];
} HabitanteStruct;

int validaCpf(const char *cpf) {
    if (!cpf || strlen(cpf) == 0) return 0;
    return 1;
}

int validaSexo(char sexo) {
    return (sexo == 'M' || sexo == 'm' || sexo == 'F' || sexo == 'f');
}

int validaData(const char *data) {
    if (!data) return 0;
    if (strlen(data) != 10) return 0;
    if (data[2] != '/' || data[5] != '/') return 0;

    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit(data[i])) return 0;
    }
    
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');
    if (mes < 1 || mes > 12) return 0;
    
    int diasPorMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (ano % 4 == 0 && (ano % 100 != 0 || ano % 400 == 0)) {
        diasPorMes[1] = 29;   //Ano bixesto
    }
    
    if (dia < 1 || dia > diasPorMes[mes - 1]) return 0;
    return 1;
}

int comparaData(const char *data1, const char *data2) {
    if (!data1 || !data2) return 0;
    
    int ano1 = (data1[6] - '0') * 1000 + (data1[7] - '0') * 100 + (data1[8] - '0') * 10 + (data1[9] - '0');
    int mes1 = (data1[3] - '0') * 10 + (data1[4] - '0');
    int dia1 = (data1[0] - '0') * 10 + (data1[1] - '0');
    
    int ano2 = (data2[6] - '0') * 1000 + (data2[7] - '0') * 100 + (data2[8] - '0') * 10 + (data2[9] - '0');
    int mes2 = (data2[3] - '0') * 10 + (data2[4] - '0');
    int dia2 = (data2[0] - '0') * 10 + (data2[1] - '0');
    
    if (ano1 < ano2) return -1;
    if (ano1 > ano2) return 1;
    if (mes1 < mes2) return -1;
    if (mes1 > mes2) return 1;
    if (dia1 < dia2) return -1;
    if (dia1 > dia2) return 1;
    
    return 0;
}

int calculaIdade(const char *nasc, const char *dataReferencia) {
    if (!nasc || !dataReferencia) return -1;
    if (!validaData(nasc) || !validaData(dataReferencia)) return -1;
    
    int anoNasc = (nasc[6] - '0') * 1000 + (nasc[7] - '0') * 100 + (nasc[8] - '0') * 10 + (nasc[9] - '0');
    int mesNasc = (nasc[3] - '0') * 10 + (nasc[4] - '0');
    int diaNasc = (nasc[0] - '0') * 10 + (nasc[1] - '0');
    
    int anoRef = (dataReferencia[6] - '0') * 1000 + (dataReferencia[7] - '0') * 100 + (dataReferencia[8] - '0') * 10 + (dataReferencia[9] - '0');
    int mesRef = (dataReferencia[3] - '0') * 10 + (dataReferencia[4] - '0');
    int diaRef = (dataReferencia[0] - '0') * 10 + (dataReferencia[1] - '0');
    
    int idade = anoRef - anoNasc;
    if (mesRef < mesNasc || (mesRef == mesNasc && diaRef < diaNasc)) {
        idade--;
    }
    
    return idade;
}

Habitante criaHabitante(const char *cpf, const char *nome, const char *sobrenome, char sexo, const char *nasc) {
    if (!cpf || !validaCpf(cpf)) {
        fprintf(stderr, "Erro: CPF inválido\n");
        return NULL;
    }
    
    if (!nome || strlen(nome) == 0) {
        fprintf(stderr, "Erro: nome inválido\n");
        return NULL;
    }
    
    if (!sobrenome || strlen(sobrenome) == 0) {
        fprintf(stderr, "Erro: sobrenome inválido\n");
        return NULL;
    }
    
    if (!validaSexo(sexo)) {
        fprintf(stderr, "Erro: sexo inválido\n");
        return NULL;
    }
    
    if (!nasc || !validaData(nasc)) {
        fprintf(stderr, "Erro: data de nasc inválida\n");
        return NULL;
    }
    
    HabitanteStruct *h = (HabitanteStruct*)malloc(sizeof(HabitanteStruct));
    if (!h) {
        fprintf(stderr, "Erro: falha na alocação do habitante\n");
        return NULL;
    }
    
    strncpy(h->cpf, cpf, CPF_LEN - 1);
    h->cpf[CPF_LEN - 1] = '\0';
    
    strncpy(h->nome, nome, NOME_LEN - 1);
    h->nome[NOME_LEN - 1] = '\0';
    
    strncpy(h->sobrenome, sobrenome, SOBRENOME_LEN - 1);
    h->sobrenome[SOBRENOME_LEN - 1] = '\0';
    
    h->sexo = (sexo == 'm') ? 'M' : (sexo == 'f') ? 'F' : sexo;
    
    strncpy(h->nasc, nasc, DATA_LEN - 1);
    h->nasc[DATA_LEN - 1] = '\0';
    
    h->idMoradia[0] = '\0';
    return (Habitante)h;
}

const char* getCpfHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em getCpfHabitante\n");
        return NULL;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    return hab->cpf;
}

const char* getNomeHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em getNomeHabitante\n");
        return NULL;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    return hab->nome;
}

const char* getSobrenomeHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em getSobrenomeHabitante\n");
        return NULL;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    return hab->sobrenome;
}

const char* getNomeCompletoHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em getNomeCompletoHabitante\n");
        return NULL;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    
    size_t len = strlen(hab->nome) + strlen(hab->sobrenome) + 2;
    char *completo = (char*)malloc(len);
    if (!completo) {
        fprintf(stderr, "Erro: falha na alocação do nome completo\n");
        return NULL;
    }
    
    snprintf(completo, len, "%s %s", hab->nome, hab->sobrenome);
    return completo;
}

char getSexoHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em getSexoHabitante\n");
        return '\0';
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    return hab->sexo;
}

const char* getNascHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em getnascHabitante\n");
        return NULL;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    return hab->nasc;
}

const char* getIdMoradiaHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em getIdMoradiaHabitante\n");
        return NULL;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    if (hab->idMoradia[0] == '\0') return NULL;
    return hab->idMoradia;
}

int isMoradorHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em isMoradorHabitante\n");
        return -1;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    return (hab->idMoradia[0] != '\0') ? 1 : 0;
}

void setIdMoradiaHabitante(Habitante h, const char *idMoradia) {
    if (!h) {
        fprintf(stderr, "Erro: habitante NULL em setIdMoradiaHabitante\n");
        return;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    
    if (!idMoradia) {
        hab->idMoradia[0] = '\0';
    } else {
        strncpy(hab->idMoradia, idMoradia, ID_MORADIA_LEN - 1);
        hab->idMoradia[ID_MORADIA_LEN - 1] = '\0';
    }
}

size_t tamSerialHabitante(void) {
    return sizeof(HabitanteStruct);
}

int serialHabitante(Habitante h, void *buffer, size_t tamBuffer) {
    if (!h || !buffer || tamBuffer < sizeof(HabitanteStruct)) {
        fprintf(stderr, "Erro: parâmetros inválidos em serialHabitante\n");
        return 0;
    }
    
    HabitanteStruct *hab = (HabitanteStruct*)h;
    memcpy(buffer, hab, sizeof(HabitanteStruct));
    return 1;
}

Habitante desserialHabitante(void *buffer, size_t tamBuffer) {
    if (!buffer || tamBuffer < sizeof(HabitanteStruct)) {
        fprintf(stderr, "Erro: parâmetros inválidos em desserialHabitante\n");
        return NULL;
    }
    
    HabitanteStruct *h = (HabitanteStruct*)malloc(sizeof(HabitanteStruct));
    if (!h) {
        fprintf(stderr, "Erro: falha na alocação em desserialHabitante\n");
        return NULL;
    }
    memcpy(h, buffer, sizeof(HabitanteStruct));
    return (Habitante)h;
}

void freeHabitante(Habitante h) {
    if (!h) {
        fprintf(stderr, "Aviso: tentativa de liberar habitante NULL\n");
        return;
    }
    HabitanteStruct *hab = (HabitanteStruct*)h;
    free(hab);
}
