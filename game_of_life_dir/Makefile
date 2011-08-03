CMD=gcc
OPTS=-g -pg -Wall
IN=main.c modules/*.c
OUT=main
LIBS=-lm
FILES=main.c include/*.h modules/*.c
OPTIM=-O0


main: $(FILES)
	$(CMD) $(OPTIM) $(OPTS) main.c modules/game_v4.c modules/input_rle.c $(LIBS) -o $(OUT)

v1o0: $(FILES)
	$(CMD) -O0 $(OPTS) main.c modules/game_v1.c modules/input_rle.c $(LIBS) -o $(OUT)

v2o0: $(FILES)
	$(CMD) -O0 $(OPTS) main.c modules/game_v2.c $(LIBS) -o $(OUT)

v3o0: $(FILES)
	$(CMD) -O0 $(OPTS) main.c modules/game_v3.c $(LIBS) -o $(OUT)

v4o0: $(FILES)
	$(CMD) -O0 $(OPTS) main.c modules/game_v4.c $(LIBS) -o $(OUT)

v1o5: $(FILES)
	$(CMD) -O5 $(OPTS) main.c modules/game_v1.c $(LIBS) -o $(OUT)

v2o5: $(FILES)
	$(CMD) -O5 $(OPTS) main.c modules/game_v2.c $(LIBS) -o $(OUT)

v3o5: $(FILES)
	$(CMD) -O5 $(OPTS) main.c modules/game_v3.c $(LIBS) -o $(OUT)

v4o5: $(FILES)
	$(CMD) -O5 $(OPTS) main.c modules/game_v4.c $(LIBS) -o $(OUT)

clean: 
	rm -f $(OUT)
