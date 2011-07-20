CMD=gcc
OPTS=-g -Wall
IN=main.c modules/*.c
OUT=main
LIBS=-lm
FILES=main.c include/*.h modules/*.c
OPTIM=-O0

main: $(FILES)
	$(CMD) $(OPTIM) $(OPTS) $(IN) -o $(OUT) $(LIBS)

clean: 
	rm -f $(OUT)
