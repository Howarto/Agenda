program.exe: program.o Reloj.o Tarea.o Agenda.o comanda.o token.o
	g++ -o program.exe program.o Reloj.o Tarea.o Agenda.o comanda.o token.o
    
program.o: program.cc
	g++ -c -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x program.cc
    
Reloj.o: Reloj.hh Reloj.cc
	g++ -c -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x Reloj.cc
    
Tarea.o: Tarea.hh Tarea.cc
	g++ -c -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x Tarea.cc
    
Agenda.o: Agenda.hh Agenda.cc
	g++ -c -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x Agenda.cc
    
comanda.o: comanda.hh comanda.cc
	g++ -c -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x comanda.cc
    
token.o: comanda.hh token.cc
	g++ -c -D_JUDGE_ -D_GLIBCXX_DEBUG -ansi -O2 -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -std=c++0x token.cc

clean:
	rm *.o
	rm *.exe

rtar:
	rm practica.tar

tar:
	tar -cvf practica.tar Makefile equip.pdf html.zip utils Reloj.hh Reloj.cc Tarea.hh Tarea.cc Agenda.hh Agenda.cc program.cc jp_albert.ribes.marza_entrada.txt jp_albert.ribes.marza_sortida.txt jp_albert.ribes.marza_comentari.txt jp_diego.lao_entrada.txt jp_diego.lao_sortida.txt jp_diego.lao_comentari.txt
