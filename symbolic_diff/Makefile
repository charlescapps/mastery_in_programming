CMD=gcc
OPTS=-g -pg -Wall
IN=main.c modules/*.c
OUT=main
LIBS=
FILES=main.c include/*.h modules/*.c
OPTIM=-O5

main: $(FILES)
	$(CMD) $(OPTIM) $(OPTS) $(IN) $(LIBS) -o $(OUT)

clean: 
	rm -f $(OUT)
