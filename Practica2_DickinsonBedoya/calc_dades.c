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
  if (var.type_value == NO_TYPE) {
    return strdup("Unknown type_value");
  } else if (var.type_value == INT_TYPE) {
    return strdup("Integer");
  } else if (var.type_value == FLOAT_TYPE) {
    return strdup("Float");
  } else if(var.type_value == STRING_TYPE){
    return strdup("String");
  } else if(var.type_value == ID_TYPE){
    return strdup("ID");
  }else {
    return strdup("Error: incorrect value for 'var'");
  }
}


char *value_info_to_str(sym_value_type var)
{
  char buffer[STR_MAX_LENGTH];

  if (var.type_value == NO_TYPE) {
    sprintf(buffer, "Unknown value type_value");
  } else if (var.type_value == INT_TYPE) {
    sprintf(buffer, "Integer: %d", var.data_value.entero);
  } else if (var.type_value == FLOAT_TYPE) {
    sprintf(buffer, "Float: %f", var.data_value.real);
  } else if(var.type_value == ID_TYPE){
    sprintf(buffer,"ID: %s", var.data_value.ident.lexema);
  }else {
    sprintf(buffer, "Error: incorrect value for 'var.data_value'");
  }
  return strdup(buffer);
}
