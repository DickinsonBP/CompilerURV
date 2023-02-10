/*
    COMPILADORES PRACTICA 1 - URV - 2022 - DICKINSON BEDOYA PEREZ
*/

%{

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern FILE *yyout;
extern int yylineno;
extern int yylex();
/*extern void yyerror(char*);*/

%}

%code requires {
  #include "calc_dades.h"
  #include "calc_funcions.h"
  #include "symtab.h"
}

%union{
    sym_value_type var;
}

%token <var.data.sin_valor> ASSIGN ENDLINE
%token <var.data.entero> INTEGER
%token <var.data.real> REAL
%token <var.data.ident> ID_ARITM
%token <var.data.ident> ID_BOOL
%token <var.data.ident> STRING
%token <var.data.boolean> BOOLEAN

%token SUMA RESTA MUL DIV MOD POW 
%token OP CP
%token GT GE LT LE EQ NE
%token NOT AND OR

%type <var> programa
%type <var> exp exp_aritm exp_bool
%type <var> valor
%type <var> sumaresta mult pow 
%type <var> and or boolval


%start programa

%%

programa : programa exp
         | exp

exp : exp_aritm
    | exp_bool

exp_bool : ID_ARITM ASSIGN or ENDLINE {

  $$.type = $3.type;
  sym_enter($1.lexema, &$3);
  $$ = $3;

  if($3.data.boolean == 1){
    fprintf(yyout, "ID: %s value: True\n",$1.lexema); 
  } else fprintf(yyout, "ID: %s value: False\n",$1.lexema);
}
      | or ENDLINE {
          $$.type = $1.type;
          
          if($1.data.boolean == 1)
            fprintf(yyout, "BOOL value: True\n"); 
          else fprintf(yyout, "BOOL value: False\n"); 
      }

exp_aritm : ID_ARITM ASSIGN sumaresta ENDLINE{
  
  $$.type = $3.type;
  sym_enter($1.lexema, &$3);
  $$ = $3;

  if($$.type == INT_TYPE){
    fprintf(yyout, "ID: %s value: %ld\n",$1.lexema, $3.data.entero);
  } else if($$.type == FLOAT_TYPE){

    fprintf(yyout, "ID: %s value: %.2f\n",$1.lexema, $3.data.real);

  } else if($$.type == BOOL_TYPE){

    if($$.data.boolean == 1){
      fprintf(yyout, "ID: %s value: True\n",$1.lexema); 
    } else {
      fprintf(yyout, "ID: %s value: False\n",$1.lexema);
    }

  }else if($$.type == STRING_TYPE){
   fprintf(yyout, "ID: %s value: %s\n",$1.lexema, $3.data.ident.lexema);
  }
}
      | sumaresta ENDLINE {
        $$.type = $1.type;

        if($$.type == INT_TYPE){

          fprintf(yyout, "INT value: %ld\n", $1.data.entero);
          $$.data.entero = $1.data.entero;

        } else if($$.type == FLOAT_TYPE){

          fprintf(yyout, "FLOAT value: %f\n", $1.data.real);
          $$.data.real = $1.data.real;

        } else if($$.type == BOOL_TYPE){

          $$.data.boolean = $1.data.boolean;
          if($$.data.boolean == 1){
            fprintf(yyout, "BOOL value: True\n"); 
          } else {
            fprintf(yyout, "BOOL value: False\n");
          }

        }else{
          fprintf(yyout, "STRING value: %s\n", $1.data.ident.lexema);
          $$.data.ident.lexema = $1.data.ident.lexema;
        }
      }

boolval : ID_BOOL { if(sym_lookup($1.lexema, &$$) == SYMTAB_NOT_FOUND) yyerror("Var doesn't exit"); }
        | BOOLEAN { $$.type = BOOL_TYPE; $$.data.boolean = $1; }
        | OP or CP { $$ = $2; }
        | sumaresta GT sumaresta { op_gt(&$$, $1, $3); }
        | sumaresta GE sumaresta { op_ge(&$$, $1, $3); }
        | sumaresta LT sumaresta { op_lt(&$$, $1, $3); }
        | sumaresta LE sumaresta { op_le(&$$, $1, $3); }
        | sumaresta EQ sumaresta { op_eq(&$$, $1, $3); }
        | sumaresta NE sumaresta { op_ne(&$$, $1, $3); }

or : or OR and { op_or(&$$, $1, $3); }
    | and

and : and AND boolval { op_and(&$$, $1, $3); }
    | NOT boolval     { op_not(&$$, $2); }
    | boolval

sumaresta : sumaresta SUMA mult { op_suma(&$$, $1, $3);}
          | sumaresta RESTA mult { op_resta(&$$, $1, $3); }
          | mult

mult : mult MUL pow { op_mult(&$$,$1,$3);}
     | mult DIV pow { op_div(&$$,$1,$3); }
     | mult MOD pow { op_mod(&$$,$1,$3); }
     | pow

pow : pow POW valor { op_pow(&$$,$1,$3); }
    | valor


valor : REAL              { $$.type = FLOAT_TYPE; $$.data.real = $1; }
      | INTEGER           { $$.type = INT_TYPE; $$.data.entero = $1; }
      | STRING            { $$.type = STRING_TYPE; $$.data.ident.lexema = $1.lexema; }
      | OP sumaresta CP   { $$ = $2; }
      | ID_ARITM          { if(sym_lookup($1.lexema, &$$) == SYMTAB_NOT_FOUND) yyerror("Var doesn't exit"); }
%%