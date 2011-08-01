CMD=gcc
OPTS=-g -Wall
IN=main.c modules/*.c
OUT=scc
LIBS=-lm
FILES=main.c modules/*.c include/*.h
OPTIM=-O0


scc: $(FILES)
	$(CMD) $(OPTIM) $(OPTS) $(IN) $(LIBS) -o $(OUT)

clean: 
	rm -f $(OUT)
