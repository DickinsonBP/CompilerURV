#ifndef CALC_FUNCIONS_H
#define CALC_FUNCIONS_H
#include "symtab.h"
#include <math.h>

/*
    COMPILADORES PRACTICA1 - URV - 2022 - DICKINSON BEDOYA PEREZ
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

/* Otras funciones extra */

linked_list newList(int lines);
linked_list newEmptyList();
void completar(linked_list list, int num);
void lastCase(char *op, sym_value_type *val, sym_value_type v1, sym_value_type v2);
/* Funciones para C3A */
void emet(char* var, unsigned int tmp, sym_value_type* val, char* operation, sym_value_type* val2);
void emet_ir(int numLine);
void emet_if(char* operation, sym_value_type* val, sym_value_type* val2, int numLine);
unsigned int temporalVariable();
unsigned int searchInstruction();
void types(sym_value_type v1, sym_value_type v2, type_val *t1, type_val *t2);


#endif
