#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "calc_dades.h"

/*
    COMPILADORES PRACTICA1 - URV - 2022 - DICKINSON BEDOYA PEREZ
*/

char *type_to_str(sym_value_type var)
{
  if (var.type == NO_TYPE) {
    return strdup("Unknown type");
  } else if (var.type == INT_TYPE) {
    return strdup("Integer");
  } else if (var.type == FLOAT_TYPE) {
    return strdup("Float");
  } else if(var.type == BOOL_TYPE){
    return strdup("Boolean");
  } else if(var.type == STRING_TYPE){
    return strdup("String");
  } else if(var.type == ID_TYPE){
    return strdup("ID");
  }else {
    return strdup("Error: incorrect value for 'var'");
  }
}


char *value_info_to_str(sym_value_type var)
{
  char buffer[STR_MAX_LENGTH];

  if (var.type == NO_TYPE) {
    sprintf(buffer, "Unknown value type");
  } else if (var.type == INT_TYPE) {
    sprintf(buffer, "Integer: %ld", var.data.entero);
  } else if (var.type == FLOAT_TYPE) {
    sprintf(buffer, "Float: %f", var.data.real);
  } else if(var.type == BOOL_TYPE){
    if(var.data.boolean == true) sprintf(buffer, "Boolean: True");
    if(var.data.boolean == false) sprintf(buffer, "Boolean: False");
  } else if(var.type == ID_TYPE){
    sprintf(buffer,"ID: %s", var.data.ident.lexema);
  }else {
    sprintf(buffer, "Error: incorrect value for 'var.data'");
  }
  return strdup(buffer);
}
