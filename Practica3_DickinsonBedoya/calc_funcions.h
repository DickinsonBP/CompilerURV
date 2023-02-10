#ifndef CALC_FUNCIONS_H
#define CALC_FUNCIONS_H
#include "symtab.h"
#include <math.h>

/*
    COMPILADORES PRACTICA 3 - URV - 2022 - DICKINSON BEDOYA PEREZ
*/


int init_analisi_lexica(char *);
int end_analisi_lexica();

int init_analisi_sintactica(char *);
int end_analisi_sintactica(void);

int analisi_semantica(void);

void yyerror(char *explanation);

/* Funciones Aritmeticas */
void op_suma(sym_value_type * val, sym_value_type v1, sym_value_type v2);
void op_resta(sym_value_type * val, sym_value_type v1, sym_value_type v2);
void op_mult(sym_value_type * val, sym_value_type v1, sym_value_type v2);
void op_div(sym_value_type * val, sym_value_type v1, sym_value_type v2);
void op_mod(sym_value_type * val, sym_value_type v1, sym_value_type v2);
void op_pow(sym_value_type * val, sym_value_type v1, sym_value_type v2);

/* Funciones Booleanas */
void op_not(sym_value_type * not, sym_value_type v1);
void op_and(sym_value_type * and, sym_value_type v1, sym_value_type v2);
void op_or(sym_value_type * or, sym_value_type v1, sym_value_type v2);
void op_gt(sym_value_type * gt, sym_value_type v1, sym_value_type v2);
void op_ge(sym_value_type * ge, sym_value_type v1, sym_value_type v2);
void op_lt(sym_value_type * lt, sym_value_type v1, sym_value_type v2);
void op_le(sym_value_type * le, sym_value_type v1, sym_value_type v2);
void op_eq(sym_value_type * eq, sym_value_type v1, sym_value_type v2);
void op_ne(sym_value_type * ne, sym_value_type v1, sym_value_type v2);

/* Otras funciones extra */

linked_list newList(int lines);
linked_list newEmptyList();
linked_list join(linked_list l1, linked_list l2);
void completar(linked_list list, int num);

/* Funciones para C3A */
void emet(char* var, unsigned int tmp, sym_value_type* val, char* operation, sym_value_type* val2);
void emet_ir(int numLine);
void emet_if(char* operation, sym_value_type* val, sym_value_type* val2, int numLine);
unsigned int temporalVariable();
unsigned int searchInstruction();
void types(sym_value_type v1, sym_value_type v2, type_val *t1, type_val *t2);


#endif
