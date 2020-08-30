CC = gcc
CFLAGS = -Wall -g -pedantic

progs = wavinfo wavvol wavnorm wavrev wavecho wavwide
objs = wavinfo.o wavvol.o wavnorm.o wavrev.o wavecho.o wavwide.o


all: $(progs)

wavinfo: acesso.c tratamento.c wavinfo.o 
wavvol:  acesso.c tratamento.c wavvol.o  
wavnorm: acesso.c tratamento.c wavnorm.o 
wavrev: acesso.c tratamento.c wavrev.o 
wavecho: acesso.c tratamento.c wavecho.o 
wavwide: acesso.c tratamento.c wavwide.o 

acesso.o: estruturas.h acesso.c 
tratamento.o: estruturas.h tratamento.c

wavinfo.o: wavinfo.c 
wavvol.o: wavvol.c 
wavnorm.o: wavnorm.c
wavrev.o: wavrev.c
wavecho.o: wavecho.c
wavwide.o: wavwide.c

clean:
	rm $(objs)

purge: clean
	rm $(progs)