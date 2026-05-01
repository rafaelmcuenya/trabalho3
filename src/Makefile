# Nome do executável
PROJ_NAME = ted
ALUNO = Nome Completo

# Compilador
CC = gcc

# Flags
CFLAGS = -ggdb -O0 -std=c99 -fstack-protector-all -Werror=implicit-function-declaration
LDFLAGS = -O0

# Diretórios
SRC_DIR = src
INC_DIR = include
TST_DIR = test

# Objetos
OBJETOS = main.o leitor.o hashfile.o quadra.o habitante.o morador.o \
          trataNomeArquivo.o svg.o

# Objetos de teste
TST_OBJETOS = t_hashfile.o t_quadra.o t_habitante.o t_morador.o

# Regra principal
$(PROJ_NAME): $(OBJETOS)
	$(CC) -o $(PROJ_NAME) $(LDFLAGS) $(OBJETOS) -lm
	@echo "Compilação bem sucedida."

%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@

# Módulo principal
main.o: $(SRC_DIR)/main.c $(INC_DIR)/leitor.h $(INC_DIR)/trataNomeArquivo.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/main.c -o $@

# Módulo leitor
leitor.o: $(SRC_DIR)/leitor.c $(INC_DIR)/leitor.h $(INC_DIR)/quadra.h \
           $(INC_DIR)/habitante.h $(INC_DIR)/morador.h $(INC_DIR)/hashfile.h \
           $(INC_DIR)/trataNomeArquivo.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/leitor.c -o $@

# Módulo hashfile
hashfile.o: $(SRC_DIR)/hashfile.c $(INC_DIR)/hashfile.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/hashfile.c -o $@

# Módulo quadra
quadra.o: $(SRC_DIR)/quadra.c $(INC_DIR)/quadra.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/quadra.c -o $@

# Módulo habitante
habitante.o: $(SRC_DIR)/habitante.c $(INC_DIR)/habitante.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/habitante.c -o $@

# Módulo morador
morador.o: $(SRC_DIR)/morador.c $(INC_DIR)/morador.h $(INC_DIR)/habitante.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/morador.c -o $@

# Módulo de tratamento de nomes
trataNomeArquivo.o: $(SRC_DIR)/trataNomeArquivo.c $(INC_DIR)/trataNomeArquivo.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/trataNomeArquivo.c -o $@

# Módulo SVG
svg.o: $(SRC_DIR)/svg.c $(INC_DIR)/svg.h $(INC_DIR)/quadra.h $(INC_DIR)/morador.h $(INC_DIR)/hashfile.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $(SRC_DIR)/svg.c -o $@

# Testes unitários
unity.o: $(TST_DIR)/unity.c $(TST_DIR)/unity.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) -I$(TST_DIR) $(TST_DIR)/unity.c -o $@

t_hashfile: unity.o hashfile.o t_hashfile.o
	$(CC) -o $@ $(LDFLAGS) unity.o hashfile.o t_hashfile.o -lm
	./t_hashfile

t_hashfile.o: $(TST_DIR)/t_hashfile.c $(INC_DIR)/hashfile.h $(TST_DIR)/unity.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) -I$(TST_DIR) $(TST_DIR)/t_hashfile.c -o $@

t_quadra: unity.o quadra.o t_quadra.o
	$(CC) -o $@ $(LDFLAGS) unity.o quadra.o t_quadra.o -lm
	./t_quadra

t_quadra.o: $(TST_DIR)/t_quadra.c $(INC_DIR)/quadra.h $(TST_DIR)/unity.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) -I$(TST_DIR) $(TST_DIR)/t_quadra.c -o $@

t_habitante: unity.o habitante.o t_habitante.o
	$(CC) -o $@ $(LDFLAGS) unity.o habitante.o t_habitante.o -lm
	./t_habitante

t_habitante.o: $(TST_DIR)/t_habitante.c $(INC_DIR)/habitante.h $(TST_DIR)/unity.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) -I$(TST_DIR) $(TST_DIR)/t_habitante.c -o $@

t_morador: unity.o habitante.o morador.o t_morador.o
	$(CC) -o $@ $(LDFLAGS) unity.o habitante.o morador.o t_morador.o -lm
	./t_morador

t_morador.o: $(TST_DIR)/t_morador.c $(INC_DIR)/morador.h $(INC_DIR)/habitante.h $(TST_DIR)/unity.h
	$(CC) -c $(CFLAGS) -I$(INC_DIR) -I$(TST_DIR) $(TST_DIR)/t_morador.c -o $@

tstall: t_hashfile t_quadra t_habitante t_morador
	@echo "Todos os testes executados."

# Regras utilitárias
clean:
	rm -f *.o $(PROJ_NAME) t_hashfile t_quadra t_habitante t_morador
	@echo "Limpeza realizada"

valgrind: $(PROJ_NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(PROJ_NAME) -f teste.geo -o saida

.PHONY: clean valgrind tstall
