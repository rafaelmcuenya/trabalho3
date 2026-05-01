#include "morador.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CEP_LEN 32
#define COMPL_LEN 64

typedef struct {
    HabitanteStruct habitante;
    char cep[CEP_LEN];
    char face;
    int numero;
    char compl[COMPL_LEN];
} MoradorStruct;

int validaFace(char face) {
    return (face == 'N' || face == 'n' || face == 'S' || face == 's' || face == 'L' || face == 'l' || face == 'O' || face == 'o');
}

int validaNum(int num) {
    return num >= 0;
}

Morador criaMorador(const char *cpf, const char *nome, const char *sobrenome, char sexo,
                    const char *nasc, const char *cep, char face, int num, const char *compl) {
    if (!cep || strlen(cep) == 0) {
        fprintf(stderr, "Erro: CEP inválido\n");
        return NULL;
    }
    
    if (!validaFace(face)) {
        fprintf(stderr, "Erro: face inválida\n");
        return NULL;
    }
    
    if (!validaNum(num)) {
        fprintf(stderr, "Erro: número inválido\n");
        return NULL;
    }
    
    Habitante h = criaHabitante(cpf, nome, sobrenome, sexo, nasc);
    if (!h) {
        return NULL;
    }
    
    MoradorStruct *m = (MoradorStruct*)malloc(sizeof(MoradorStruct));
    if (!m) {
        fprintf(stderr, "Erro: falha na alocação do morador\n");
        freeHabitante(h);
        return NULL;
    }
    memcpy(&m->habitante, h, sizeof(HabitanteStruct));
    freeHabitante(h);
   
    strncpy(m->cep, cep, CEP_LEN - 1);
    m->cep[CEP_LEN - 1] = '\0';
    m->face = (face == 'n') ? 'N' : (face == 's') ? 'S' : (face == 'l') ? 'L' : (face == 'o') ? 'O' : face;
    m->numero = num;
    
    if (compl && strlen(compl) > 0) {
        strncpy(m->compl, compl, COMPL_LEN - 1);
        m->compl[COMPL_LEN - 1] = '\0';
    } else {
        m->compl[0] = '\0';
    }
    return (Morador)m;
}

const char* getCpfMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getCpfMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return mor->habitante.cpf;
}

const char* getNomeMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getNomeMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return mor->habitante.nome;
}

const char* getSobrenomeMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getSobrenomeMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return mor->habitante.sobrenome;
}

const char* getNomeCompletoMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getNomeCompletoMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    
    size_t len = strlen(mor->habitante.nome) + strlen(mor->habitante.sobrenome) + 2;
    char *completo = (char*)malloc(len);
    if (!completo) {
        fprintf(stderr, "Erro: falha na alocação do nome completo\n");
        return NULL;
    }
    snprintf(completo, len, "%s %s", mor->habitante.nome, mor->habitante.sobrenome);
    return completo;
}

char getSexoMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getSexoMorador\n");
        return '\0';
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return mor->habitante.sexo;
}

const char* getNascMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getNascMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return mor->habitante.nascimento;
}

const char* getCepMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getCepMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return mor->cep;
}

char getFaceMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getFaceMorador\n");
        return '\0';
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return mor->face;
}

int getNumMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getNumMorador\n");
        return -1;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return mor->numero;
}

const char* getComplMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getComplMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    if (mor->compl[0] == '\0') return NULL;
    return mor->compl;
}

const char* getEnderecoCompletoMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getEnderecoCompletoMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    
    size_t len = strlen(mor->cep) + 1 + 1 + 1 + 12 + 1;
    if (mor->compl[0] != '\0') {
        len += strlen(mor->compl) + 1;
    }
    
    char *endereco = (char*)malloc(len);
    if (!endereco) {
        fprintf(stderr, "Erro: falha na alocação do endereço completo\n");
        return NULL;
    }
    
    if (mor->compl[0] != '\0') {
        snprintf(endereco, len, "%s/%c/%d/%s", mor->cep, mor->face, mor->numero, mor->compl);
    } else {
        snprintf(endereco, len, "%s/%c/%d", mor->cep, mor->face, mor->numero);
    } 
    return endereco;
}

Habitante getHabitanteMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Erro: morador NULL em getHabitanteMorador\n");
        return NULL;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    return (Habitante)&mor->habitante;
}

size_t tamSerialMorador(void) {
    return sizeof(MoradorStruct);
}

int serialMorador(Morador m, void *buffer, size_t tamBuffer) {
    if (!m || !buffer || tamBuffer < sizeof(MoradorStruct)) {
        fprintf(stderr, "Erro: parâmetros inválidos em serialMorador\n");
        return 0;
    }
    
    MoradorStruct *mor = (MoradorStruct*)m;
    memcpy(buffer, mor, sizeof(MoradorStruct));
    return 1;
}

Morador desserialMorador(void *buffer, size_t tamBuffer) {
    if (!buffer || tamBuffer < sizeof(MoradorStruct)) {
        fprintf(stderr, "Erro: parâmetros inválidos em desserialMorador\n");
        return NULL;
    }
    
    MoradorStruct *m = (MoradorStruct*)malloc(sizeof(MoradorStruct));
    if (!m) {
        fprintf(stderr, "Erro: falha na alocação em desserialMorador\n");
        return NULL;
    }
    memcpy(m, buffer, sizeof(MoradorStruct));
    return (Morador)m;
}

void freeMorador(Morador m) {
    if (!m) {
        fprintf(stderr, "Aviso: tentativa de liberar morador NULL\n");
        return;
    }
    MoradorStruct *mor = (MoradorStruct*)m;
    free(mor);
}
