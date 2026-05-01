#include "quadra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct {
    char cep[32];
    double x, y;
    double largura, altura;
    char corB[8];
    char corP[8];
    double espBorda;
} QuadraStruct;

static void preencherCor(char *dest, const char *fonte, const char *corPadrao) {
    if (fonte && strlen(fonte) > 0) {
        const char *cor = (fonte[0] == '#') ? fonte + 1 : fonte;
        int len = strlen(cor);

        if (len == 6) {
            strncpy(dest, cor, 6);
        } else if (len < 6) {
            int zeros = 6 - len;
            for (int i = 0; i < zeros; i++) {
                dest[i] = '0';
            }
            strncpy(dest + zeros, cor, len);
        } else {
            strncpy(dest, cor, 6);
        }
        dest[6] = '\0';
    } else {
        strcpy(dest, corPadrao);
    }
}

int validaCor(const char *cor) {
    if (!cor || strlen(cor) == 0) return 0;

    const char *corLimpa = (cor[0] == '#') ? cor + 1 : cor;
    int len = strlen(corLimpa);
    if (len != 6) return 0;

    for (int i = 0; i < 6; i++) {
        if (!isxdigit(corLimpa[i])) return 0;
    }

    return 1;
}

int validaFace(char face) {
    return (face == 'N' || face == 'n' || face == 'S' || face == 's' ||
            face == 'L' || face == 'l' || face == 'O' || face == 'o');
}

static char normalizaFace(char face) {
    return toupper(face);
}

static double getXFaceQuadra(const QuadraStruct *quad, char face) {
    switch (face) {
        case 'N': return quad->x;
        case 'S': return quad->x;
        case 'L': return quad->x;
        case 'O': return quad->x - quad->largura;
        default:  return 0;
    }
}

static double getYFaceQuadra(const QuadraStruct *quad, char face) {
    switch (face) {
        case 'N': return quad->y - quad->altura;
        case 'S': return quad->y;
        case 'L': return quad->y;
        case 'O': return quad->y;
        default:  return 0;
    }
}

Quadra criaQuadra(const char *cep, double x, double y, double l, double h,
                  const char *corB, const char *corP, double espB) {
    if (!cep || strlen(cep) == 0) {
        fprintf(stderr, "Erro: CEP inválido\n");
        return NULL;
    }

    if (!corB || !corP) {
        fprintf(stderr, "Erro: cores inválidas\n");
        return NULL;
    }

    if (l <= 0 || h <= 0) {
        fprintf(stderr, "Erro: largura e/ou altura inválida(s)\n");
        return NULL;
    }

    if (espB <= 0) {
        fprintf(stderr, "Erro: espessura da borda inválida\n");
        return NULL;
    }

    if (isnan(x) || isnan(y) || isnan(l) || isnan(h) || isnan(espB) ||
        isinf(x) || isinf(y) || isinf(l) || isinf(h) || isinf(espB)) {
        fprintf(stderr, "Erro: coordenadas e/ou dimensões inválida(s)\n");
        return NULL;
    }

    QuadraStruct *q = (QuadraStruct*)malloc(sizeof(QuadraStruct));
    if (!q) {
        fprintf(stderr, "Erro: falha na alocação da quadra\n");
        return NULL;
    }

    strncpy(q->cep, cep, 31);
    q->cep[31] = '\0';
    q->x = x;
    q->y = y;
    q->largura = l;
    q->altura = h;
    q->espBorda = espB;

    preencherCor(q->corB, corB, "000000");
    preencherCor(q->corP, corP, "FFFFFF");
    return (Quadra)q;
}

const char* getCepQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getCepQuadra\n");
        return NULL;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->cep;
}

double getXQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getXQuadra\n");
        return -1000.0;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->x;
}

double getYQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getYQuadra\n");
        return -1000.0;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->y;
}

double getLQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getLQuadra\n");
        return -1.0;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->largura;
}

double getHQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getHQuadra\n");
        return -1.0;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->altura;
}

const char* getCorBQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getCorBQuadra\n");
        return NULL;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->corB;
}

const char* getCorPQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getCorPQuadra\n");
        return NULL;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->corP;
}

double getEspBQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getEspBQuadra\n");
        return -1.0;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->espBorda;
}

void getPontoEndQuadra(Quadra q, char face, double num, double *x, double *y) {
    if (!q || !validaFace(face) || !x || !y) {
        fprintf(stderr, "Erro: parâmetros inválidos em getPontoEndQuadra\n");
        return;
    }

    QuadraStruct *quad = (QuadraStruct*)q;
    char f = normalizaFace(face);
    double x_face = getXFaceQuadra(quad, f);
    double y_face = getYFaceQuadra(quad, f);

    switch (f) {
        case 'N':
            *x = x_face + num;
            *y = y_face;
            break;
        case 'S':
            *x = x_face + num;
            *y = y_face;
            break;
        case 'L':
            *x = x_face;
            *y = y_face - num;
            break;
        case 'O':
            *x = x_face;
            *y = y_face - num;
            break;
        default:
            *x = 0;
            *y = 0;
    }
}

double areaQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em areaQuadra\n");
        return -1.0;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    return quad->largura * quad->altura;
}

void setCorBQuadra(Quadra q, const char *novaCor) {
    if (!q || !novaCor) {
        fprintf(stderr, "Erro: parâmetros inválidos em setCorBQuadra\n");
        return;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    preencherCor(quad->corB, novaCor, "000000");
}

void setCorPQuadra(Quadra q, const char *novaCor) {
    if (!q || !novaCor) {
        fprintf(stderr, "Erro: parâmetros inválidos em setCorPQuadra\n");
        return;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    preencherCor(quad->corP, novaCor, "FFFFFF");
}

void setEspBQuadra(Quadra q, double novaEspessura) {
    if (!q || novaEspessura <= 0) {
        fprintf(stderr, "Erro: parâmetros inválidos em setEspBQuadra\n");
        return;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    quad->espBorda = novaEspessura;
}

size_t tamSerialQuadra(void) {
    return sizeof(QuadraStruct);
}

int serialQuadra(Quadra q, void *buffer, size_t tamBuffer) {
    if (!q || !buffer || tamBuffer < sizeof(QuadraStruct)) {
        fprintf(stderr, "Erro: parâmetros inválidos em serialQuadra\n");
        return 0;
    }

    QuadraStruct *quad = (QuadraStruct*)q;
    memcpy(buffer, quad, sizeof(QuadraStruct));
    return 1;
}

Quadra desserialQuadra(void *buffer, size_t tamBuffer) {
    if (!buffer || tamBuffer < sizeof(QuadraStruct)) {
        fprintf(stderr, "Erro: parâmetros inválidos em desserialQuadra\n");
        return NULL;
    }

    QuadraStruct *q = (QuadraStruct*)malloc(sizeof(QuadraStruct));
    if (!q) {
        fprintf(stderr, "Erro: falha na alocação em desserialQuadra\n");
        return NULL;
    }

    memcpy(q, buffer, sizeof(QuadraStruct));
    return (Quadra)q;
}

void freeQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Aviso: tentativa de liberar quadra NULL\n");
        return;
    }
    QuadraStruct *quad = (QuadraStruct*)q;
    free(quad);
}
