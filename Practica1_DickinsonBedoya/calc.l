/*
    COMPILADORES PRACTICA 1 - URV - 2022 - DICKINSON BEDOYA PEREZ
*/

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "calc.tab.h"
#include "calc_funcions.h"
#include "symtab.h"

%}

%option yylineno
%option noyywrap
%option noinput
%option nounput


letra [a-zA-Z]
entero [-+]?([0-9]+)
boolean (true|false)
float   [-+]?{entero}*\.{entero}+([eE][-+]?{entero}+)?
string   \"(.)*\"
comment "//".*"\n"

id {letra}({letra}|{entero})*

%%
{boolean}                   { if(strcmp(strdup(yytext),"true") == 0){
                                yylval.var.data.boolean = true;
                              }else{
                                yylval.var.data.boolean = false;
                              }
                              yylval.var.data.ident.type = BOOL_TYPE;
                              return BOOLEAN;
                            }

"+"                         { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return SUMA; }
"-"                         { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return RESTA; }
"*"                         { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return MUL; } 
"/"                         { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return DIV; }
"%"                         { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return MOD; }
"**"                        { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return POW; }                    
":="                        { return ASSIGN; }
"("                         { return OP; }
")"                         { return CP; }
">"                         { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return GT; }
">="                        { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return GE; }
"<"                         { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return LT; }
"<="                        { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return LE; }
"="                         { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return EQ; }
"<>"                        { yylval.var.type = STRING_TYPE; yylval.var.data.string = strdup(yytext); return NE; }
"not"                       { return NOT; }
"and"                       { return AND; }
"or"                        { return OR; }

{comment}            {}
{string}                    { yylval.var.data.ident.lexema = strdup(yytext); yylval.var.data.ident.lenght = yyleng; yylval.var.data.ident.type = STRING_TYPE; return STRING; } 
{float}                     { yylval.var.data.real = atof(yytext); return REAL; }
{entero}                    { yylval.var.data.entero = atoi(yytext); return INTEGER; }
{id}                        {
                              yylval.var.data.ident.lexema = strdup(yytext);
                              yylval.var.data.ident.lenght = yyleng;
                              yylval.var.data.ident.line = yylineno;
                              yylval.var.data.ident.type = NO_TYPE;
                              sym_value_type b;
                              if(sym_lookup(yylval.var.data.ident.lexema, &b) == SYMTAB_NOT_FOUND) return ID_ARITM;
                              if(b.type == BOOL_TYPE) return ID_BOOL;
                              return ID_ARITM;
                            }

^[ \t]*[\n]                 {}

[\n]                        { return ENDLINE; }

.                           {}

%%