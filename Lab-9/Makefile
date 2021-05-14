all: pipe1 pipe3 pipe4 twoPipesParent twoPipesChild pipeFifo buildsm Removesm Process1 Process2

pipe1: pipe1.c
	gcc -Wall pipe1.c -o pipe1

pipe3: pipe3.c
	gcc -Wall pipe3.c -o pipe3

pipe4: pipe4.c
	gcc -Wall pipe4.c -o pipe4

twoPipesParent: twoPipesParent.c
	gcc -Wall twoPipesParent.c -o twoPipesParent

twoPipesChild: twoPipesChild.c
	gcc -Wall twoPipesChild.c -o twoPipesChild

pipeFifo: pipeFifo.c
	gcc -Wall pipeFifo.c -o pipeFifo

buildsm: buildsm.c header.h
	gcc -Wall buildsm.c -o buildsm

Removesm: Removesm.c header.h
	gcc -Wall Removesm.c -o Removesm

Process1: Process1.c header.h
	gcc -Wall Process1.c -o Process1

Process2: Process2.c header.h
	gcc -Wall Process2.c -o Process2

clean:
	rm pipe1 pipe3 pipe4 twoPipesParent twoPipesChild pipeFifo buildsm Removesm Process1 Process2