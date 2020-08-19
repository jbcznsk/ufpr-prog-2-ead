#!/bin/bash

make 

mkdir meus-testes

./ortografia < entradas/plutao.txt      > meus-testes/m-saida-plutao.txt
./ortografia < entradas/memoria.txt     > meus-testes/m-saida-memoria.txt
./ortografia < entradas/brascubas.txt   > meus-testes/m-saida-brascubas.txt
./ortografia < entradas/montesquieu.txt > meus-testes/m-saida-montesquieu.txt

echo "Diferencas Plutao"
diff meus-testes/m-saida-plutao.txt saidas/plutao-saida.txt

echo "Diferencas Memoria"
diff meus-testes/m-saida-memoria.txt saidas/memoria-saida.txt

echo "Diferencas BrasCubas"
diff meus-testes/m-saida-brascubas.txt saidas/brascubas-saida.txt

echo "Diferencas Montesquieu"
diff meus-testes/m-saida-montesquieu.txt saidas/montesquieu-saida.txt

rm -rf meus-testes

make clean
make purge