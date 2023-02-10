/*
    COMPILADORES PRACTICA2 - URV - 2022 - DICKINSON BEDOYA PEREZ
*/

%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern FILE *yyout;
extern int yylineno;
extern int yylex();
/*extern void yyerror(char*);*/

char* instrucciones[1000];
unsigned int temporal = 0;
unsigned int instructionLine = 0;
unsigned int numInstructions = 1;
%}

%code requires {
  #include "calc_dades.h"
  #include "calc_funcions.h"
  #include "symtab.h"
}

%union{
    control_list var;
}

%token <var.st.data_value.sin_valor> ASSIGN ENDLINE
%token <var.st.data_value.entero> INTEGER
%token <var.st.data_value.real> REAL
%token <var.st> ID_ARITM
%token <var.st.data_value.ident> STRING

%token SUMA RESTA MUL DIV MOD POW 
%token OP CP 
%token REPEAT DO DONE SPACE

%type <var.st> programa
%type <var> exp_aritm loop
%type <var> sentencias sentencia
%type <var.st> valor
%type <var.st> sumaresta mult pow
%type <var.st.data_value.entero> m

%type main

%start programa

%%

programa : main  {
                  emet(NULL,0,NULL,"HALT",NULL);
                  if(instrucciones != NULL){
                    for(int i = 0; i < instructionLine; i++){
                      fprintf(yyout, "%s\n", instrucciones[i]);
                      free(instrucciones[i]);
                    }

                  }else yyerror("Array de instrucciones nulo");
              }
              
main : sentencias {
                      completar($1.true_list, instructionLine);    
                  }


sentencias : sentencias m sentencia{
                                    completar($1.next_list, $2);
                                    $$.next_list = $3.next_list;
                                  }
          | sentencia

sentencia : loop
          | exp_aritm

exp_aritm : ID_ARITM ASSIGN sumaresta ENDLINE{
  
  $$.next_list = newEmptyList();
  type_val type;
  bool tmp = false;
  
  if($3.type_value == TEMPORAL_TYPE){
    type = $3.data_value.temporal_type;
    tmp = true;
  }else type = $3.type_value;

  if(type == INT_TYPE){
    if(tmp) emet($1.data_value.ident.lexema, $3.data_value.temporal,NULL,NULL,NULL);
    else emet($1.data_value.ident.lexema, 0, &$3, NULL, NULL);
    $3.data_value.identifier_type = INT_TYPE;
  }
  if(type == FLOAT_TYPE){
    if(tmp) emet($1.data_value.ident.lexema, $3.data_value.temporal,NULL,NULL,NULL);
    else emet($1.data_value.ident.lexema, 0, &$3, NULL, NULL);
    $3.data_value.identifier_type = FLOAT_TYPE;
  }
  if(type == STRING_TYPE){
    if(tmp) emet($1.data_value.ident.lexema, $3.data_value.temporal,NULL,NULL,NULL);
    else emet($1.data_value.ident.lexema, 0, &$3, NULL, NULL);
    $3.data_value.identifier_type = STRING_TYPE;
  }

  $3.data_value.ident.lexema = $1.data_value.ident.lexema;
  $3.type_value = ID_TYPE;
  sym_enter($1.data_value.ident.lexema, &$3);

}
      | sumaresta ENDLINE {

        $$.next_list = newEmptyList();
        type_val type;
        if($1.type_value == TEMPORAL_TYPE){
          type = $1.data_value.temporal_type;
        }else type = $1.type_value;

        sym_value_type param;

        param.type_value = INT_TYPE;
        param.data_value.entero = 1;

        if(type == INT_TYPE){
          emet(NULL, 0, NULL, "PARAM", &$1);
          emet(NULL, 0, NULL, "PUTI", &param);
        }else if(type == FLOAT_TYPE){
          emet(NULL, 0, NULL, "PARAM", &$1);
          emet(NULL, 0, NULL, "PUTF", &param);
        }else if(type == STRING_TYPE){
          emet(NULL, 0, NULL, "PARAM", &$1);
          emet(NULL, 0, NULL, "PUTS", &param);
        }else if(type == ID_TYPE){
          emet(NULL, 0, NULL, "PARAM", &$1);
          if($1.data_value.identifier_type == INT_TYPE) emet(NULL, 0, NULL, "PUTI", &param);
          else emet(NULL, 0, NULL, "PUTF", &param);
        } else yyerror("ERROR");
        
      }

m : { $$ = instructionLine; }

loop : REPEAT m sumaresta DO ENDLINE m sentencias DONE ENDLINE { 
                                    completar($7.next_list, $2);
                                    emet_if("LT",&$3,0,instructionLine + 2);
                                    emet_ir(0);
                                  }

sumaresta : sumaresta SUMA mult { op_suma(&$$, $1, $3); }
          | sumaresta RESTA mult { op_resta(&$$, $1, $3); }
          | mult

mult : mult MUL pow { op_mult(&$$,$1,$3);}
     | mult DIV pow { op_div(&$$,$1,$3); }
     | mult MOD pow { op_mod(&$$,$1,$3); }
     | pow

pow : pow POW valor { op_pow(&$$,$1,$3); }
    | valor


valor : REAL              { $$.type_value = FLOAT_TYPE; $$.data_value.real = $1; }
      | INTEGER           { $$.type_value = INT_TYPE; $$.data_value.entero = $1; }
      | STRING            { $$.type_value = STRING_TYPE; $$.data_value.ident.lexema = $1.lexema; }
      | OP sumaresta CP   { $$ = $2; }
      | ID_ARITM          { if(sym_lookup($1.data_value.ident.lexema, &$$) == SYMTAB_NOT_FOUND) yyerror("Var doesn't exit"); }
%%