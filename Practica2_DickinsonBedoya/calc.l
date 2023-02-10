/*
    COMPILADORES PRACTICA2 - URV - 2022 - DICKINSON BEDOYA PEREZ
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

%x COMMENT

%%

"repeat"                    { return REPEAT; }
"do"                        { return DO; }
"done"                      { return DONE; }
"+"                         { yylval.var.st.type_value = STRING_TYPE; yylval.var.st.data_value.string = strdup(yytext); return SUMA; }
"-"                         { yylval.var.st.type_value = STRING_TYPE; yylval.var.st.data_value.string = strdup(yytext); return RESTA; }
"*"                         { yylval.var.st.type_value = STRING_TYPE; yylval.var.st.data_value.string = strdup(yytext); return MUL; } 
"/"                         { yylval.var.st.type_value = STRING_TYPE; yylval.var.st.data_value.string = strdup(yytext); return DIV; }
"%"                         { yylval.var.st.type_value = STRING_TYPE; yylval.var.st.data_value.string = strdup(yytext); return MOD; }
"**"                        { yylval.var.st.type_value = STRING_TYPE; yylval.var.st.data_value.string = strdup(yytext); return POW; }                    
":="                        { return ASSIGN; }
"("                         { return OP; }
")"                         { return CP; }

{comment}                   {}
{string}                    { yylval.var.st.data_value.ident.lexema = strdup(yytext); yylval.var.st.data_value.ident.lenght = yyleng; yylval.var.st.data_value.ident.type = STRING_TYPE; return STRING; } 
{float}                     { yylval.var.st.data_value.real = atof(yytext); return REAL; }
{entero}                    { yylval.var.st.data_value.entero = atoi(yytext); return INTEGER; }
{id}                        {
                              yylval.var.st.data_value.ident.lexema = strdup(yytext);
                              yylval.var.st.data_value.ident.lenght = yyleng;
                              yylval.var.st.data_value.ident.line = yylineno;
                              yylval.var.st.data_value.ident.type = NO_TYPE;
                              return ID_ARITM;
                            }

^[ \t]*[\n]                 {}

[\n]                        { return ENDLINE; }

.                           {}

%%