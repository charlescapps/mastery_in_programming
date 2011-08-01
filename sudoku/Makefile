CMD=gcc
OPTS=-g -Wall
IN=main.c modules/*.c
OUT=solve_sudoku
LIBS=-lm
FILES=main.c modules/*.c include/*.h
OPTIM=-O0


solve_sudoku: $(FILES)
	$(CMD) $(OPTIM) $(OPTS) $(IN) $(LIBS) -o $(OUT)

clean: 
	rm -f $(OUT)
