CFLAGS=-Wall -g -Wextra -pedantic -O2
FICHEIROS=defines.h estado.h main.c Makefile score_board_main.c

install: main score_board_main
	sudo cp main /Users/ricardopetronilho/Sites
	sudo cp score_board_main /Users/ricardopetronilho/Sites
	cp -r images/ /Users/ricardopetronilho/Sites/images/
	touch install

score_board_main: score_board_main.o
	cc -o score_board_main score_board_main.o

main: main.o 
	cc -o main main.o

main.zip: $(FICHEIROS)
	zip -9 main.zip $(FICHEIROS)

doc:
	doxygen

clean:
	rm -rf *.o score_board_main main latex html install
	
main.o: main.c defines.h estado.h
score_board_main.o: score_board_main.c defines.h estado.h
