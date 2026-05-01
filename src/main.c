#include "leitor.h"
#include "trataNomeArquivo.h"
#include "hashfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char *geoFile = NULL;
    char *qryFile = NULL;
    char *pmFile = NULL;
    char *outputDir = NULL;
    char *inputDir = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 && i + 1 < argc) {
            geoFile = argv[++i];
        } else if (strcmp(argv[i], "-q") == 0 && i + 1 < argc) {
            qryFile = argv[++i];
        } else if (strcmp(argv[i], "-pm") == 0 && i + 1 < argc) {
            pmFile = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            outputDir = argv[++i];
        } else if (strcmp(argv[i], "-e") == 0 && i + 1 < argc) {
            inputDir = argv[++i];
        }
    }

    if (!geoFile) {
        fprintf(stderr, "Uso: %s -f <arquivo.geo> [-pm <arquivo.pm>] [-q <arquivo.qry>] -o <diretorio> [-e <diretorio>]\n", argv[0]);
        return 1;
    }

    if (!outputDir) {
        outputDir = ".";
    }

    if (!inputDir) {
        inputDir = ".";
    }

    char nomeBase[FILE_NAME_LEN];
    extrairNomeBase(geoFile, nomeBase);

    inicializarSistema(nomeBase, outputDir);

    processarArquivoGeo(geoFile, inputDir, nomeBase, outputDir);

    if (pmFile) {
        processarArquivoPm(pmFile, inputDir, nomeBase);
    }

    if (qryFile) {
        processarArquivoQry(qryFile, inputDir, nomeBase, outputDir);
    }

    finalizarSistema();

    return 0;
}
