CC = gcc
CFLAGS = -Wall -g -pedantic

progs = wavinfo wavvol wavnorm wavrev
objs = wavinfo.o wavvol.o wavnorm.o wavrev.o


all: $(progs)

wavinfo: acesso.c tratamento.c wavinfo.o 
wavvol:  acesso.c tratamento.c wavvol.o  
wavnorm: acesso.c tratamento.c wavnorm.o 
wavrev: acesso.c tratamento.c wavrev.o 

acesso.o: estruturas.h acesso.c 
tratamento.o: estruturas.h tratamento.c

wavinfo.o: wavinfo.c 
wavvol.o: wavvol.c 
wavnorm.o: wavnorm.c
wavrev.o: wavrev.c

clean:
	rm $(objs)

purge: clean
	rm $(progs)