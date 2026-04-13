#include "hashfile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CHAVE_MAX 64
#define TAM_NOMEBASE_MAX 256

typedef struct {
    char chave[TAM_CHAVE_MAX];
    uint32_t offset_dados;
    uint32_t tamDados;
    uint8_t ocupado;
} RegistroBucket;

typedef struct BucketStruct {
    int profLocal;
    int numRegistros;
    RegistroBucket *registros;
    int modificado;
} Bucket;

struct HashFileStruct {
    FILE *arqDados;
    FILE *arqCabecalho;
    char nomeBase[TAM_NOME_BASE_MAX];
    int profGlobal;
    int tamBucket;
    Bucket **diretorio;
    sizeT tamDiretorio;
    int modificado;
};

static uint32_t hashString(const char *str) {
    uint32_t hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

static int getBitsHash(uint32_t hash, int prof) {
    return hash & ((1 << prof) - 1);
}

static Bucket* criarBucket(int nivel, int tamBucket) {
    Bucket *b = (Bucket*)malloc(sizeof(Bucket));
    if (!b) return NULL;
    b->profLocal = nivel;
    b->numRegistros = 0;
    b->registros = (RegistroBucket*)calloc(tamBucket, sizeof(RegistroBucket));
    if (!b->registros) {
        free(b);
        return NULL;
    }
    b->modificado = 1;
    return b;
}

static void freeBucket(Bucket *b) {
    if (b) {
        free(b->registros);
        free(b);
    }
}

static int saveCabecalho(HashFile *hf) {
    if (!hf->arqCabecalho) return 0;
    rewind(hf->arqCabecalho);
    fwrite(&hf->profGlobal, sizeof(int), 1, hf->arqCabecalho);
    fwrite(&hf->tamBucket, sizeof(int), 1, hf->arqCabecalho);
    fwrite(&hf->tamDiretorio, sizeof(sizeT), 1, hf->arqCabecalho);
    fflush(hf->arqCabecalho);
    return 1;
}

static int loadCabecalho(HashFile *hf) {
    if (!hf->arqCabecalho) return 0;
    rewind(hf->arqCabecalho);
    sizeT lidos = 0;
    lidos += fread(&hf->profGlobal, sizeof(int), 1, hf->arqCabecalho);
    lidos += fread(&hf->tamBucket, sizeof(int), 1, hf->arqCabecalho);
    lidos += fread(&hf->tamDiretorio, sizeof(sizeT), 1, hf->arqCabecalho);
    return lidos == 3;
}

static int saveBucket(HashFile *hf, Bucket *b) {
    b->modificado = 0;
    return 1;
}

static Bucket* loadBucket(HashFile *hf, int indice) {
    return NULL;
}

static int dobraDiretorio(HashFile *hf) {
    sizeT newTam = hf->tamDiretorio * 2;
    Bucket **newDir = (Bucket**)malloc(newTam * sizeof(Bucket*));
    if (!newDir) return 0;
    
    for (sizeT i = 0; i < hf->tamDiretorio; i++) {
        newDir[i] = hf->diretorio[i];
        newDir[i + hf->tamDiretorio] = hf->diretorio[i];
    }
    
    free(hf->diretorio);
    hf->diretorio = newDir;
    hf->tamDiretorio = newTam;
    hf->profGlobal++;
    hf->modificado = 1;
    saveCabecalho(hf);
    return 1;
}

static int bucketCheio(HashFile *hf, int indice) {
    if (indice < 0 || indice >= (int)hf->tamDiretorio) return -1;
    Bucket *b = hf->diretorio[indice];
    if (!b) return -1;
    return b->numRegistros >= hf->tamBucket;
}

static int splitBucket(HashFile *hf, int indice) {
    Bucket *oldB = hf->diretorio[indice];
    if (!oldB) return 0;
    
    int newProf = oldB->profLocal + 1;
    
    if (newProf > hf->profGlobal) {
        if (!dobraDiretorio(hf)) return 0;
    }
    
    Bucket *novoB0 = criarBucket(newProf, hf->tamBucket);
    Bucket *novoB1 = criarBucket(newProf, hf->tamBucket);
    if (!novoB0 || !novoB1) {
        freeBucket(novoB0);
        freeBucket(novoB1);
        return 0;
    }
    
    for (int i = 0; i < oldB->numRegistros; i++) {
        RegistroBucket *reg = &oldB->registros[i];
        if (!reg->ocupado) continue;
        
        uint32_t h = hashString(reg->chave);
        int bit_extra = (h >> (newProf - 1)) & 1;
        
        Bucket *destino = bit_extra ? novoB1 : novoB0;
        int pos = destino->numRegistros;
        memcpy(&destino->registros[pos], reg, sizeof(RegistroBucket));
        destino->numRegistros++;
    }
    
    for (sizeT i = 0; i < hf->tamDiretorio; i++) {
        if (hf->diretorio[i] == oldB) {
            uint32_t h = hashString("");
            int bit = (i >> (newProf - 1)) & 1;
            hf->diretorio[i] = bit ? novoB1 : novoB0;
        }
    }
    
    freeBucket(oldB);
    hf->modificado = 1;
    return 1;
}

static int searchRegistro(Bucket *b, const char *chave) {
    for (int i = 0; i < b->numRegistros; i++) {
        if (b->registros[i].ocupado && strcmp(b->registros[i].chave, chave) == 0) {
            return i;
        }
    }
    return -1;
}

static int searchPosLivre(Bucket *b) {
    for (int i = 0; i < b->numRegistros; i++) {
        if (!b->registros[i].ocupado) {
            return i;
        }
    }
    return b->numRegistros;
}

HashFile* criarHF(const char *nomeBase, int tamBucket, int profInicial) {
    if (!nomeBase || tamBucket <= 0 || profInicial <= 0) return NULL;
    
    HashFile *hf = (HashFile*)malloc(sizeof(HashFile));
    if (!hf) return NULL;
    
    memset(hf, 0, sizeof(HashFile));
    strncpy(hf->nomeBase, nomeBase, TAM_NOME_BASE_MAX - 1);
    
    char nome_arq[TAM_NOME_BASE_MAX + 10];
    
    snprintf(nome_arq, sizeof(nome_arq), "%s.hf", nomeBase);
    hf->arqDados = fopen(nome_arq, "w+b");
    
    snprintf(nome_arq, sizeof(nome_arq), "%s.hfc", nomeBase);
    hf->arqCabecalho = fopen(nome_arq, "w+b");
    
    if (!hf->arqDados || !hf->arqCabecalho) {
        if (hf->arqDados) fclose(hf->arqDados);
        if (hf->arqCabecalho) fclose(hf->arqCabecalho);
        free(hf);
        return NULL;
    }
    
    hf->profGlobal = profInicial;
    hf->tamBucket = tamBucket;
    hf->tamDiretorio = 1 << profInicial;
    
    hf->diretorio = (Bucket**)malloc(hf->tamDiretorio * sizeof(Bucket*));
    if (!hf->diretorio) {
        fclose(hf->arqDados);
        fclose(hf->arqCabecalho);
        free(hf);
        return NULL;
    }
    
    Bucket *b_inicial = criarBucket(profInicial, tamBucket);
    if (!b_inicial) {
        free(hf->diretorio);
        fclose(hf->arqDados);
        fclose(hf->arqCabecalho);
        free(hf);
        return NULL;
    }
    
    for (sizeT i = 0; i < hf->tamDiretorio; i++) {
        hf->diretorio[i] = b_inicial;
    }
    
    hf->modificado = 1;
    saveCabecalho(hf);
    
    return hf;
}

void freeHF(HashFile *hf) {
    if (!hf) return;
    
    if (hf->diretorio) {
        for (sizeT i = 0; i < hf->tamDiretorio; i++) {
            if (hf->diretorio[i]) {
                int unico = 1;
                for (sizeT j = 0; j < i; j++) {
                    if (hf->diretorio[j] == hf->diretorio[i]) {
                        unico = 0;
                        break;
                    }
                }
                if (unico) {
                    freeBucket(hf->diretorio[i]);
                }
            }
        }
        free(hf->diretorio);
    }
    
    if (hf->arqDados) fclose(hf->arqDados);
    if (hf->arqCabecalho) fclose(hf->arqCabecalho);
    
    free(hf);
}

int insertHF(HashFile *hf, const char *chave, const void *dado, sizeT tamDado) {
    if (!hf || !chave || !dado || tamDado == 0) return -1;
    
    uint32_t h = hashString(chave);
    int indice = getBitsHash(h, hf->profGlobal);
    
    Bucket *b = hf->diretorio[indice];
    if (!b) return -1;
    
    if (searchRegistro(b, chave) != -1) {
        return 0;
    }
    
    if (bucketCheio(hf, indice)) {
        if (!splitBucket(hf, indice)) return -1;
        h = hashString(chave);
        indice = getBitsHash(h, hf->profGlobal);
        b = hf->diretorio[indice];
    }
    
    int pos = searchPosLivre(b);
    if (pos >= hf->tamBucket) {
        if (!splitBucket(hf, indice)) return -1;
        h = hashString(chave);
        indice = getBitsHash(h, hf->profGlobal);
        b = hf->diretorio[indice];
        pos = searchPosLivre(b);
    }
    
    if (pos >= hf->tamBucket) return -1;
    
    strncpy(b->registros[pos].chave, chave, TAM_CHAVE_MAX - 1);
    b->registros[pos].tamDados = tamDado;
    b->registros[pos].ocupado = 1;
    
    fseek(hf->arqDados, 0, SEEK_END);
    b->registros[pos].offset_dados = ftell(hf->arqDados);
    fwrite(dado, 1, tamDado, hf->arqDados);
    fflush(hf->arqDados);
    
    if (pos == b->numRegistros) {
        b->numRegistros++;
    }
    
    b->modificado = 1;
    hf->modificado = 1;
    saveBucket(hf, b);
    
    return 1;
}

int buscaHF(HashFile *hf, const char *chave, void *dadoSaida, sizeT *tamSaida) {
    if (!hf || !chave) return -1;
    
    uint32_t h = hashString(chave);
    int indice = getBitsHash(h, hf->profGlobal);
    
    Bucket *b = hf->diretorio[indice];
    if (!b) return -1;
    
    int pos = searchRegistro(b, chave);
    if (pos == -1) return 0;
    
    if (dadoSaida && tamSaida) {
        if (*tamSaida < b->registros[pos].tamDados) {
            return -1;
        }
        
        fseek(hf->arqDados, b->registros[pos].offset_dados, SEEK_SET);
        fread(dadoSaida, 1, b->registros[pos].tamDados, hf->arqDados);
        *tamSaida = b->registros[pos].tamDados;
    }
    
    return 1;
}

int deletarItremHF(HashFile *hf, const char *chave) {
    if (!hf || !chave) return -1;
    
    uint32_t h = hashString(chave);
    int indice = getBitsHash(h, hf->profGlobal);
    
    Bucket *b = hf->diretorio[indice];
    if (!b) return -1;
    
    int pos = searchRegistro(b, chave);
    if (pos == -1) return 0;
    
    b->registros[pos].ocupado = 0;
    b->modificado = 1;
    hf->modificado = 1;
    saveBucket(hf, b);
    
    return 1;
}

int refreshHF(HashFile *hf, const char *chave, const void *novoDado, sizeT tamDado) {
    if (!hf || !chave || !novoDado || tamDado == 0) return -1;
    
    if (deletarItremHF(hf, chave) != 1) return 0;
    
    return insertHF(hf, chave, novoDado, tamDado);
}

int gerarDumpHF(HashFile *hf) {
    if (!hf) return 0;
    
    char nome_dump[TAM_NOME_BASE_MAX + 10];
    snprintf(nome_dump, sizeof(nome_dump), "%s.hfd", hf->nomeBase);
    
    FILE *dump = fopen(nome_dump, "w");
    if (!dump) return 0;
    
    fprintf(dump, "=== DUMP DO HASHFILE ===\n");
    fprintf(dump, "Arquivo base: %s\n", hf->nomeBase);
    fprintf(dump, "Profundidade global: %d\n", hf->profGlobal);
    fprintf(dump, "Capacidade do bucket: %d\n", hf->tamBucket);
    fprintf(dump, "Tamanho do diretorio: %zu\n", hf->tamDiretorio);
    fprintf(dump, "Total de registros: %zu\n", totalRegistrosHF(hf));
    fprintf(dump, "\n");
    
    for (sizeT i = 0; i < hf->tamDiretorio; i++) {
        Bucket *b = hf->diretorio[i];
        fprintf(dump, "Diretorio[%zu] -> Bucket (profLocal=%d, registros=%d)\n", 
                i, b->profLocal, b->numRegistros);
        
        for (int j = 0; j < b->numRegistros; j++) {
            if (b->registros[j].ocupado) {
                fprintf(dump, "  [%d] chave='%s', tam=%u\n", 
                        j, b->registros[j].chave, b->registros[j].tamDados);
            }
        }
    }
    
    fclose(dump);
    return 1;
}

sizeT totalRegistrosHF(const HashFile *hf) {
    if (!hf) return 0;
    
    sizeT total = 0;
    for (sizeT i = 0; i < hf->tamDiretorio; i++) {
        Bucket *b = hf->diretorio[i];
        
        int unico = 1;
        for (sizeT j = 0; j < i; j++) {
            if (hf->diretorio[j] == b) {
                unico = 0;
                break;
            }
        }
        
        if (unico && b) {
            for (int j = 0; j < b->numRegistros; j++) {
                if (b->registros[j].ocupado) {
                    total++;
                }
            }
        }
    }
    
    return total;
}

int getProfGlobalHF(const HashFile *hf) {
    if (!hf) return -1;
    return hf->profGlobal;
}

int getTamBucketHF(const HashFile *hf) {
    if (!hf) return -1;
    return hf->tamBucket;
}

int getInfoBucketHF(const HashFile *hf, int indiceBucket, int *qtdRegistros, int *profLocal) {
    if (!hf || indiceBucket < 0 || indiceBucket >= (int)hf->tamDiretorio) return 0;
    
    Bucket *b = hf->diretorio[indiceBucket];
    if (!b) return 0;
    
    if (qtdRegistros) *qtdRegistros = b->numRegistros;
    if (profLocal) *profLocal = b->profLocal;
    
    return 1;
}

int iterarHF(HashFile *hf, callbackHF callback, void *contexto) {
    if (!hf || !callback) return -1;
    
    int processados = 0;
    void *buffer = malloc(65536);
    if (!buffer) return -1;
    
    for (sizeT i = 0; i < hf->tamDiretorio; i++) {
        Bucket *b = hf->diretorio[i];
        
        int unico = 1;
        for (sizeT j = 0; j < i; j++) {
            if (hf->diretorio[j] == b) {
                unico = 0;
                break;
            }
        }
        
        if (unico && b) {
            for (int j = 0; j < b->numRegistros; j++) {
                if (b->registros[j].ocupado) {
                    fseek(hf->arqDados, b->registros[j].offset_dados, SEEK_SET);
                    fread(buffer, 1, b->registros[j].tamDados, hf->arqDados);
                    callback(b->registros[j].chave, buffer, b->registros[j].tamDados, contexto);
                    processados++;
                }
            }
        }
    }
    
    free(buffer);
    return processados;
}
