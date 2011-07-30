CMD=gcc
OPTS=-g -Wall --coverage
IN=main.c modules/*.c
OUT=scc
LIBS=-lm
FILES=main.c modules/*.c include/*.h
OPTIM=-O5


scc: $(FILES)
	$(CMD) $(OPTIM) $(OPTS) $(IN) $(LIBS) -o $(OUT)

clean: 
	rm -f $(OUT)
