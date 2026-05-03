#include "svg.h"
#include "quadra.h"
#include "morador.h"
#include "hashfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void desenharQuadraSvg(FILE *svgFile, Quadra q) {
    double x = getXQuadra(q);
    double y = getYQuadra(q);
    double w = getLQuadra(q);
    double h = getHQuadra(q);
    const char *corP = getCorPQuadra(q);
    const char *corB = getCorBQuadra(q);
    double sw = getEspBQuadra(q);
    const char *cep = getCepQuadra(q);

    double svgX = x;
    double svgY = y;

    fprintf(svgFile, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" "
                     "fill=\"%s\" stroke=\"%s\" stroke-width=\"%.1f\" "
                     "fill-opacity=\"0.5\"/>\n",
            svgX, svgY, w, h, corP, corB, sw);

    double centroX = x - w / 2.0;
    double centroY = y - h / 2.0;
    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"6\" "
                     "text-anchor=\"middle\" fill=\"%s\">%s</text>\n",
            centroX, centroY, corB, cep);
}

static void callbackSvgGeo(const char *chave, const void *dado, sizeT tamDado, void *contexto) {
    FILE *svgFile = (FILE*)contexto;
    Quadra q = desserialQuadra((void*)dado, tamDado);
    if (q) {
        desenharQuadraSvg(svgFile, q);
        freeQuadra(q);
    }
}

void svgGeo(const char *caminhoCompleto, HashFile *hfQuadras) {
    FILE *svgFile = fopen(caminhoCompleto, "w");
    if (!svgFile) {
        fprintf(stderr, "Erro: não foi possível criar %s\n", caminhoCompleto);
        return;
    }

    fprintf(svgFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svgFile, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
                     "viewBox=\"0 0 1600 1100\">\n");

    iterarHF(hfQuadras, callbackSvgGeo, svgFile);

    fprintf(svgFile, "</svg>");
    fclose(svgFile);
}

void svgMarcarRemocaoQuadra(FILE *svgFile, Quadra q) {
    double x = getXQuadra(q);
    double y = getYQuadra(q);
    double tamanho = 8;

    fprintf(svgFile, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
                     "stroke=\"red\" stroke-width=\"2\"/>\n",
            x - tamanho, y - tamanho, x + tamanho, y + tamanho);
    fprintf(svgFile, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
                     "stroke=\"red\" stroke-width=\"2\"/>\n",
            x + tamanho, y - tamanho, x - tamanho, y + tamanho);
}

void svgMarcarMoradoresPorFace(FILE *svgFile, Quadra q, int faceN, int faceS, int faceL, int faceO) {
    double x = getXQuadra(q);
    double y = getYQuadra(q);
    double w = getLQuadra(q);
    double h = getHQuadra(q);

    double cx = x - w / 2.0;
    double cy = y - h / 2.0;
    int total = faceN + faceS + faceL + faceO;
    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"7\" "
                     "text-anchor=\"middle\" fill=\"black\" font-weight=\"bold\">%d</text>\n",
            cx, cy, total);

    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"5\" "
                     "text-anchor=\"middle\" fill=\"blue\">%d</text>\n",
            cx, y - h + 5, faceN);

    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"5\" "
                     "text-anchor=\"middle\" fill=\"blue\">%d</text>\n",
            cx, y - 5, faceS);

    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"5\" "
                     "text-anchor=\"start\" fill=\"blue\">%d</text>\n",
            x - w + 2, cy, faceO);

    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"5\" "
                     "text-anchor=\"end\" fill=\"blue\">%d</text>\n",
            x - 2, cy, faceL);
}

void svgMarcarMudanca(FILE *svgFile, double x, double y, const char *cpf) {
    double tamanho = 6;

    fprintf(svgFile, "<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" "
                     "fill=\"none\" stroke=\"red\" stroke-width=\"1\"/>\n",
            x - tamanho, y - tamanho, tamanho * 2, tamanho * 2);

    fprintf(svgFile, "<text x=\"%.2f\" y=\"%.2f\" font-size=\"3\" "
                     "text-anchor=\"middle\" fill=\"red\">%s</text>\n",
            x, y - tamanho - 2, cpf);
}

void svgMarcarDespejo(FILE *svgFile, double x, double y) {
    double raio = 4;

    fprintf(svgFile, "<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" "
                     "fill=\"black\"/>\n",
            x, y, raio);
}

void svgMarcarFalecimento(FILE *svgFile, double x, double y) {
    double tamanho = 6;

    fprintf(svgFile, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
                     "stroke=\"red\" stroke-width=\"1.5\"/>\n",
            x, y - tamanho, x, y + tamanho);
    fprintf(svgFile, "<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" "
                     "stroke=\"red\" stroke-width=\"1.5\"/>\n",
            x - tamanho, y, x + tamanho, y);
}

void desenharQuadrasSvg(HashFile *hfQuadras, FILE *svgFile) {
    iterarHF(hfQuadras, callbackSvgGeo, svgFile);
}

void svgQry(const char *caminhoCompleto, HashFile *hfQuadras, HashFile *hfMoradores) {
    FILE *svgFile = fopen(caminhoCompleto, "w");
    if (!svgFile) {
        fprintf(stderr, "Erro: não foi possível criar %s\n", caminhoCompleto);
        return;
    }

    fprintf(svgFile, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    fprintf(svgFile, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" "
                     "viewBox=\"0 0 1600 1100\">\n");

    iterarHF(hfQuadras, callbackSvgGeo, svgFile);

    fprintf(svgFile, "</svg>");
    fclose(svgFile);
}
