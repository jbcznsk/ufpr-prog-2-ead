# GRR20190372 Jorge Lucas Vicilli Jabczenski

CFLAGS = -Wall -g
CC = gcc

objs = ortografia.o dicionario.o

# Regra Default
all: ortografia

# Regra de Ligação
ortografia: $(objs)

# Regra de Compilação
ortografia.o: dicionario.c dicionario.h ortografia.c 
dicionario.o: dicionario.c dicionario.h

# Remove Arquivos Temporários
clean:
	-rm -f $(objs) *~

# Remove tudo que não for o Código-Fonte
purge: clean
	-rm -f ortografia