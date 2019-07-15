all: no.o pilha.o expressao.o arvore_binaria.o calculadora.o
	gcc -g no.o pilha.o expressao.o arvore_binaria.o calculadora.o -o calculadora -Wall -lm

no.o:
	gcc -g -c no.c

pilha.o:
	gcc -g -c pilha.c

expressao.o:
	gcc -g -c expressao.c

arvore_binaria.o:
	gcc -g -c arvore_binaria.c

calculadora.o:
	gcc -g -c calculadora.c

clean:
	rm *.o calculadora

run:
	./calculadora

						 