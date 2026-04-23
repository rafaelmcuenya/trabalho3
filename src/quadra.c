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
    double espessuraBorda;
} QuadraStruct;

static void preencherCor(char* dest, const char* fonte, const char* corPadrao) {
    if (fonte && strlen(fonte) > 0) {
        const char* cor = (fonte[0] == '#') ? fonte + 1 : fonte;
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

int validaCor(char *cor) {
    if (!cor || strlen(cor) == 0) return 0;
    
    const char* corLimpa = (cor[0] == '#') ? cor + 1 : cor;
    int len = strlen(corLimpa);
    
    if (len != 6) return 0;
    
    for (int i = 0; i < 6; i++) {
        if (!isxdigit(corLimpa[i])) return 0;
    }
    
    return 1;
}

int validaFace(char face) {
    return (face == 'N' || face == 'n' || 
            face == 'S' || face == 's' || 
            face == 'L' || face == 'l' || 
            face == 'O' || face == 'o');
}

static char normalizaFace(char face) {
    return toupper(face);
}

Quadra criaQuadra(char *cep, double x, double y, double l, double h, char *corB, char *corP, double espB) {
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
    
    if (x != x || y != y || isinf(x) || isinf(y) ||
        l != l || h != h || isinf(l) || isinf(h) || isinf(espB)) {
        fprintf(stderr, "Erro: coordenadas e/ou dimensões inválida(s)\n");
        return NULL;
    }
    
    QuadraStruct* q = (QuadraStruct*)malloc(sizeof(QuadraStruct));
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
    q->espessuraBorda = espB;
  
    preencherCor(q->corB, corB, "000000");
    preencherCor(q->corP, corP, "FFFFFF");
    
    return (Quadra)q;
}

char* getCepQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getCepQuadra\n");
        return NULL;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    char* cep = (char*)malloc(strlen(quad->cep) + 1);
    if (cep) {
        strcpy(cep, quad->cep);
    }
    return cep;
}

double getXQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getXQuadra\n");
        return -1000.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    return quad->x;
}

double getYQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getYQuadra\n");
        return -1000.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    return quad->y;
}

double getLQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getLQuadra\n");
        return -1.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    return quad->largura;
}

double getHQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getHQuadra\n");
        return -1.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    return quad->altura;
}

char* getCorBQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getCorBQuadra\n");
        return NULL;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    char* cor = (char*)malloc(7);
    if (cor) {
        strncpy(cor, quad->corB, 6);
        cor[6] = '\0';
    }
    return cor;
}

char* getCorPQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getCorPQuadra\n");
        return NULL;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    char* cor = (char*)malloc(7);
    if (cor) {
        strncpy(cor, quad->corP, 6);
        cor[6] = '\0';
    }
    return cor;
}

double getEspBQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getEspBQuadra\n");
        return -1.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    return quad->espessuraBorda;
}

double getXSVGQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getXSVGQuadra\n");
        return -1000.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    return quad->x - quad->largura;
}

double getYSVGQuadra(Quadra q) {
    if (!q) {
        fprintf(stderr, "Erro: quadra NULL em getYSVGQuadra\n");
        return -1000.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    return quad->y - quad->altura;
}

double getXFaceQuadra(Quadra q, char face) {
    if (!q || !validaFace(face)) {
        fprintf(stderr, "Erro: parâmetros inválidos em getXFaceQuadra\n");
        return -1.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    char f = normalizaFace(face);
    
    switch (f) {
        case 'N':
        case 'S':
            return quad->x - quad->largura / 2.0;
        case 'L':
            return quad->x;
        case 'O':
            return quad->x - quad->largura;
        default:
            return -1.0;
    }
}

double getYFaceQuadra(Quadra q, char face) {
    if (!q || !validaFace(face)) {
        fprintf(stderr, "Erro: parâmetros inválidos em getYFaceQuadra\n");
        return -1.0;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    char f = normalizaFace(face);
    
    switch (f) {
        case 'L':
        case 'O':
            return quad->y - quad->altura / 2.0;
        case 'N':
            return quad->y - quad->altura;
        case 'S':
            return quad->y;
        default:
            return -1.0;
    }
}

void getPontoEndQuadra(Quadra q, char face, double num, double *x, double *y) {
    if (!q || !validaFace(face) || !x || !y) {
        fprintf(stderr, "Erro: parâmetros inválidos em getPontoEndQuadra\n");
        return;
    }
    
    QuadraStruct* quad = (QuadraStruct*)q;
    char f = normalizaFace(face);
    double x_face = getXFaceQuadra(q, f);
    double y_face = getYFaceQuadra(q, f);
    
    switch (f) {
        case 'N':
            *x = x_face;
            *y = y_face - num;
            break;
        case 'S':
            *x = x_face;
            *y = y_face + num;
            break;
        case 'L':
            *x = x_face + num;
            *y = y_face;
            break;
        case 'O':
            *x = x_face - num;
            *y = y_face;
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
    QuadraStruct* quad = (QuadraStruct*)q;
    return quad->largura * quad->altura;
}

void setCorBQuadra(Quadra q, char *novaCor) {
    if (!q || !novaCor) {
        fprintf(stderr, "Erro: parâmetros inválidos em setCorBQuadra\n");
        return;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    preencherCor(quad->corB, novaCor, "000000");
}

void setCorPQuadra(Quadra q, char *novaCor) {
    if (!q || !novaCor) {
        fprintf(stderr, "Erro: parâmetros inválidos em setCorPQuadra\n");
        return;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    preencherCor(quad->corP, novaCor, "FFFFFF");
}

void setEspBQuadra(Quadra q, double novaEspessura) {
    if (!q || novaEspessura <= 0) {
        fprintf(stderr, "Erro: parâmetros inválidos em setEspBQuadra\n");
        return;
    }
    QuadraStruct* quad = (QuadraStruct*)q;
    quad->espessuraBorda = novaEspessura;
}

size_t tamSerialQuadra(void) {
    return sizeof(QuadraStruct);
}

int serialQuadra(Quadra q, void *buffer, size_t tamBuffer) {
    if (!q || !buffer || tamBuffer < sizeof(QuadraStruct)) {
        fprintf(stderr, "Erro: parâmetros inválidos em serialQuadra\n");
        return 0;
    }
    
    QuadraStruct* quad = (QuadraStruct*)q;
    memcpy(buffer, quad, sizeof(QuadraStruct));
    return 1;
}

Quadra desserialQuadra(void *buffer, size_t tamBuffer) {
    if (!buffer || tamBuffer < sizeof(QuadraStruct)) {
        fprintf(stderr, "Erro: parâmetros inválidos em desserialQuadra\n");
        return NULL;
    }
    
    QuadraStruct* q = (QuadraStruct*)malloc(sizeof(QuadraStruct));
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
    QuadraStruct* quad = (QuadraStruct*)q;
    free(quad);
}
