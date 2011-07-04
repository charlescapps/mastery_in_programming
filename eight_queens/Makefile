CMD=gcc
OPTS=-g -Wall
IN=*.c
OUT=main
LIBS=-lm
FILES=*.c include/*.h


eight_queens: $(FILES)
	$(CMD) $(OPTS) $(IN) $(LIBS) -o $(OUT)

clean: 
	rm -f $(OUT)
