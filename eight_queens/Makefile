CMD=gcc
OPTS=-g -Wall
IN=*.c modules/*.c
OUT=main
LIBS=-lm
FILES=*.c modules/*.c include/*.h


eight_queens: $(FILES)
	$(CMD) $(OPTS) $(IN) $(LIBS) -o $(OUT)

clean: 
	rm -f $(OUT)
