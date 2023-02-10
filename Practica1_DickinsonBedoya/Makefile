######################################################################
#
#                           Compiladors
#
######################################################################

CC = gcc
LEX = flex
YACC = bison
LIB = -lfl

SRC_LEX = calc.l
SRC_YACC = calc.y

LEX_OUT = lex.yy.c
YACC_OUT_C = calc.tab.c
YACC_OUT_H = calc.tab.h
YACC_OUT = $(YACC_OUT_C) $(YACC_OUT_H)

OTHERS = calc.output
OBJ = *.o

SRC = calc_main.c
BIN = calc.exe

SRC_EXTRA = calc_funcions.c calc_dades.c

LFLAGS =
YFLAGS = -d -v
CFLAGS = -Wall -g

SYM_TAB = symtab.o

EG_IN = entrada.txt
EG_OUT = salida.txt



######################################################################


all : yacc lex $(SYM_TAB)
	$(CC) -o $(BIN) $(CFLAGS) $(SRC) $(SRC_EXTRA) $(YACC_OUT_C) $(LEX_OUT) $(SYM_TAB) $(LIB) -lm
	
restart: clean all eg

$(SYM_TAB): symtab.c symtab.h 
	gcc -c symtab.c 

yacc : $(SRC_YACC)
	$(YACC) $(YFLAGS) $(SRC_YACC)

lex : $(SRC_LEX)
	$(LEX) $(LFLAGS) $(SRC_LEX)

clean :
	rm -f *~ $(BIN) $(OBJ) $(YACC_OUT) $(LEX_OUT) $(OTHERS) $(EG_OUT)

eg : $(EG_IN)
	./$(BIN) $(EG_IN) $(EG_OUT)
	cat $(EG_OUT)
