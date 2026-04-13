#include "leitor.h"
#include <string.h>
#include <ctype.h>
#include "quadra.h"
#include "strdupi.h"
/*
#include "criarTxt.h"
#include "criarSvg.h"
#include "trataNomeArquivo.h"

Implementar dps usando de base os projetos anteriores
*/

static void construirCaminhoCompleto(const char* baseDir, const char* arquivo, char* caminhoCompleto){
    if(!baseDir || strlen(baseDir) == 0){
        strcpy(caminhoCompleto, arquivo);
        return;
    }
    
    if(baseDir[strlen(baseDir)-1] == '/'){
        snprintf(caminhoCompleto, PATH_LEN, "%s%s", baseDir, arquivo);
    }else{
        snprintf(caminhoCompleto, PATH_LEN, "%s/%s", baseDir, arquivo);
    }
}

/*
static double pontuacaoFinal = 0.0;
static int totalInstrucoes = 0;
static int totalDisparos = 0;
static int totalEsmagadas = 0;
static int totalClonadas = 0;

Dar rework dps
cep é alfanumérico
*/

static void cmdQ(inte cep, double x, double y, double l, double h, char corb[], char corp[], double espB){
    Quadra quadra = criaQuadra(cep, x, y, l, h, corb, corp, espB);
    printf("[GEO] Quadra %d criada em (%.2f, %.2f) dim %.2fx%.2f\n", cep, x, y, l, h);
}

/*
static void cmdCQ(int idDisp, double x, double y){
    totalInstrucoes++;
    if (idDisp >= 0 && idDisp < 100){
        disparadores[idDisp] = criaDisparador(idDisp, x, y);
        printf("[QRY] Disparador %d posicionado em (%.2f, %.2f)\n", idDisp, x, y);
    }
}

Dar rework após alterar módulo quadra e usar método semelhante do Text Style dos projetos anteriores.
*/




static void cmdP(int cpf, char nome[], char sobrenome[], char sexo, int nasc){  
    //Implementar dps, 2 registros distintos para morador/habitante, ou 1 registro com 1 bit especifico q diferencia
}

static void cmdM(int cpf, inte cep, char face, int num, char[] cmpl){
    //Implementar dps
}




static void cmdRQ(inte cep){
    //Implementar dps
}

static void cmdPQ(inte cep){
    //Implementar dps
}

static void cmdCenso(???){
    //Implementar dps
}

static void cmdH(int cpf){
    //Implementar dps
}

static void cmdNasc(int cpf, char[] nome, char[] sobrenome, char sexo, int nasc){
    //Implementar dps
}

static void cmdRIP(int cpf){
    //Implementar dps
}

static void cmdMud(int cpf, inte cep, char face, int num, char[] cmpl){
    //Implementar dps
}

static void cmdDspj(int cpf){
    //Implementar dps
}

void inicializarSistema(void){
    //Implementar dps, se for necessário
    printf("[SISTEMA] Sistema inicializado\n");
}

void finalizarSistema(void){
    //Implementar dps, msm caso acima
    printf("[SISTEMA] Sistema finalizado\n");
}

void abrirArquivo(FILE **f, const char *caminho){
    *f = fopen(caminho, "r");
    if (!(*f)){
        fprintf(stderr, "Erro: Não foi possível abrir %s\n", caminho);
        exit(1);
    }
}

void processarComando(const char* linha, int ehQry, const char* nomeBase, const char* outputDir){
    if (linha[0] == '\n' || linha[0] == '#' || linha[0] == '\0') return;
    
    char comando[10];
    sscanf(linha, "%s", comando);
    
    if (!ehQry){
        if (strcmp(comando, "c") == 0){
            int id; double x, y, r; char corb[32], corp[32];
            if (sscanf(linha, "%*s %d %lf %lf %lf %31s %31s", &id, &x, &y, &r, corb, corp) == 6){
                cmdCriaCirculo(id, x, y, r, corb, corp);
            }
        }
        else if (strcmp(comando, "r") == 0){
            int id; double x, y, l, h; char corb[32], corp[32];
            if (sscanf(linha, "%*s %d %lf %lf %lf %lf %31s %31s", &id, &x, &y, &l, &h, corb, corp) == 7){
                cmdCriaRetangulo(id, x, y, l, h, corb, corp);
            }
        }
        else if (strcmp(comando, "l") == 0){
            int id; double x1, y1, x2, y2; char cor[32];
            if (sscanf(linha, "%*s %d %lf %lf %lf %lf %31s", &id, &x1, &y1, &x2, &y2, cor) == 6){
                cmdCriaLinha(id, x1, y1, x2, y2, cor);
            }
        }
        else if (strcmp(comando, "t") == 0){
            int id; double x, y; char corb[32], corp[32], anchor, texto[256];
            if (sscanf(linha, "%*s %d %lf %lf %31s %31s %c %255[^\n]", &id, &x, &y, corb, corp, &anchor, texto) == 7){
                cmdCriaTexto(id, x, y, corb, corp, anchor, texto);
            }
        }
        else if (strcmp(comando, "ts") == 0){
            char family[32], weight[8]; double size;
            if (sscanf(linha, "%*s %31s %7s %lf", family, weight, &size) == 3){
                cmdTextoStyle(family, weight, size);
            }
        }
    }else if{
        if (strcmp(comando, "pd") == 0){
            int id; double x, y;
            if (sscanf(linha, "%*s %d %lf %lf", &id, &x, &y) == 3){
                cmdPD(id, x, y);
            }
        }
        else if (strcmp(comando, "lc") == 0){
            int id, n;
            if (sscanf(linha, "%*s %d %d", &id, &n) == 2){
                cmdLC(id, n);
            }
        }
        else if (strcmp(comando, "atch") == 0){
            int disp, esq, dir;
            if (sscanf(linha, "%*s %d %d %d", &disp, &esq, &dir) == 3){
                cmdATCH(disp, esq, dir);
            }
        }
        else if (strcmp(comando, "shft") == 0){
            int disp, n; char lado;
            if (sscanf(linha, "%*s %d %c %d", &disp, &lado, &n) == 3){
                cmdSHFT(disp, lado, n);
            }
        }
        else if (strcmp(comando, "dsp") == 0){
            int disp; double dx, dy; char flag[2];
            int res = sscanf(linha, "%*s %d %lf %lf %1s", &disp, &dx, &dy, flag);
            cmdDSP(disp, dx, dy, (res == 4 && strcmp(flag, "v") == 0));
        }
        else if (strcmp(comando, "rjd") == 0){
            int disp; char lado; double dx, dy, ix, iy;
            if (sscanf(linha, "%*s %d %c %lf %lf %lf %lf", &disp, &lado, &dx, &dy, &ix, &iy) == 6){
                cmdRJD(disp, lado, dx, dy, ix, iy);
            } else{
                printf("[ERRO] Formato inválido para rjd: %s\n", linha);
            }
        }
        else if (strcmp(comando, "calc") == 0){
            cmdCALC(nomeBase, outputDir);
        }
    }
}

void processarArquivo(const char* caminho, const char* inputDir, int ehQry, const char* nomeBase, const char* outputDir){
    char caminhoCompleto[PATH_LEN];
    construirCaminhoCompleto(inputDir, caminho, caminhoCompleto);
    
    FILE *f;
    abrirArquivo(&f, caminhoCompleto);
    
    if (ehQry){
        char nomeBaseQry[FILE_NAME_LEN];
        extrairNomeBase(caminho, nomeBaseQry);
        
        char caminhoTxt[PATH_LEN];
        gerarNomeQryTxt(nomeBase, nomeBaseQry, outputDir, caminhoTxt);
        iniciarTxt(caminhoTxt);
    }
    
    char linha[1024];
    while (fgets(linha, sizeof(linha), f)){
        processarComando(linha, ehQry, nomeBase, outputDir);
    }
    
    if (ehQry){
        txtFinal(getPontuacaoFinal(), getTotalInstrucoes(), getTotalDisparos(), getTotalEsmagadas(), getTotalClonadas());
        fecharTxt();
    
        char nomeBaseQry[FILE_NAME_LEN];
        extrairNomeBase(caminho, nomeBaseQry);
        
        char caminhoSvgFinal[PATH_LEN];
        gerarNomeQrySvg(nomeBase, nomeBaseQry, outputDir, caminhoSvgFinal);
        
        svgQry(caminhoSvgFinal, chao);
        printf("[SVG] Arquivo final com consulta gerado: %s\n", caminhoSvgFinal);
    } else{
        char caminhoSvg[PATH_LEN];
        gerarNomeGeoSvg(nomeBase, outputDir, caminhoSvg);
        svgGeo(caminhoSvg, chao);
    }
    fclose(f);
}
