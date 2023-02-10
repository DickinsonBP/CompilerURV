#include <stdio.h>
#include <stdlib.h>
#include "calc_funcions.h" 
#include <math.h>
#include <string.h> 

/*
    COMPILADORES PRACTICA1 - URV - 2022 - DICKINSON BEDOYA PEREZ
*/


extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;


int init_analisi_lexica(char *filename)
{
  int error;
  yyin = fopen(filename,"r");
  if(yyin == NULL) {
    error = EXIT_FAILURE;
  } else {
    error = EXIT_SUCCESS;
  }
  return error;
}


int end_analisi_lexica()
{
  int error;
  error = fclose(yyin);
  if (error == 0) {
    error = EXIT_SUCCESS;
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}


int init_analisi_sintactica(char* filename)
{
  int error = EXIT_SUCCESS;
  yyout = fopen(filename,"w");
  if (yyout == NULL) {
    error = EXIT_FAILURE;
  }
  return error;
}


int end_analisi_sintactica(void)
{
  int error;

  error = fclose(yyout);

  if(error == 0) {
    error = EXIT_SUCCESS;
  } else {
    error = EXIT_FAILURE;
  }
  return error;
}


int analisi_semantica(void)
{
  int error;
  /*yyparse() returns a value of 0 if the input it parses is valid according to the given grammar rules. 
  It returns a 1 if the input is incorrect and error recovery is impossible.*/
  if (yyparse() == 0) {
    error =  EXIT_SUCCESS;
  } else {
    error =  EXIT_FAILURE;
  }
  return error;
}


void yyerror(char *explanation)
{
  fprintf(stderr, "Error: %s , in line %d\n", explanation, yylineno);
}


/* Funciones Aritmeticas */
void op_suma(sym_value_type * val, sym_value_type v1, sym_value_type v2){

  if(v1.type == BOOL_TYPE || v2.type == BOOL_TYPE){
    yyerror("Can't operate with these value type");
  } else {
    if(v1.type == STRING_TYPE && v2.type == STRING_TYPE){

      (*val).type = STRING_TYPE;
      strcat(strcpy((*val).data.ident.lexema, v1.data.ident.lexema), v2.data.ident.lexema);

    }else if(v1.type == STRING_TYPE && v2.type == INT_TYPE){

      (*val).type = STRING_TYPE;
      char int_str[50];
      sprintf(int_str, "%ld", v2.data.entero);
      strcat(strcpy((*val).data.ident.lexema, v1.data.ident.lexema), int_str);

    }else if(v1.type == STRING_TYPE && v2.type == FLOAT_TYPE){

      (*val).type = STRING_TYPE;
      char int_str[50];
      sprintf(int_str, "%f", v2.data.real);
      strcat(strcpy((*val).data.ident.lexema, v1.data.ident.lexema), int_str);

    }else if(v1.type == STRING_TYPE && v2.type == BOOL_TYPE){

      (*val).type = STRING_TYPE;
      char *string;
      if(v2.data.boolean == 1)string = "True";
      else string = "False";
      strcat(strcpy((*val).data.ident.lexema, v1.data.ident.lexema), string);

    }else if (v1.type == INT_TYPE && v2.type == INT_TYPE){

      (*val).type = INT_TYPE;
      (*val).data.entero = v1.data.entero + v2.data.entero;

    } else if(v1.type == INT_TYPE && v2.type == FLOAT_TYPE){

      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.entero + v2.data.real;

    } else if(v1.type == FLOAT_TYPE && v2.type == INT_TYPE){

      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.real + v2.data.entero;
    } else if (v1.type == FLOAT_TYPE && v2.type == FLOAT_TYPE){

      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.real + v2.data.real;

    }
  }
}

void op_resta(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  /*can't substart strings*/
  if(v1.type == BOOL_TYPE || v2.type == BOOL_TYPE || v1.type == STRING_TYPE || v2.type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type == INT_TYPE && v2.type == INT_TYPE){
      (*val).type = INT_TYPE;
      (*val).data.entero = v1.data.entero - v2.data.entero;
    } else if(v1.type == INT_TYPE && v2.type == FLOAT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.entero - v2.data.real;
    } else if(v1.type == FLOAT_TYPE && v2.type == INT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.real - v2.data.entero;
    } else if(v1.type == FLOAT_TYPE && v2.type == FLOAT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.real - v2.data.real;
    }
  }
}

void op_mult(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type == BOOL_TYPE || v2.type == BOOL_TYPE || v1.type == STRING_TYPE || v2.type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type == INT_TYPE && v2.type == INT_TYPE){
      (*val).type = INT_TYPE;
      (*val).data.entero = v1.data.entero * v2.data.entero;
    } else if(v1.type == INT_TYPE && v2.type == FLOAT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.entero * v2.data.real;
    } else if(v1.type == FLOAT_TYPE && v2.type == INT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.real* v2.data.entero;
    } else if(v1.type == FLOAT_TYPE && v2.type == FLOAT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.real * v2.data.real;
    }
  }
}

void op_div(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type == BOOL_TYPE || v2.type == BOOL_TYPE || v1.type == STRING_TYPE || v2.type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type == INT_TYPE && v2.type == INT_TYPE){
      (*val).type = INT_TYPE;
      (*val).data.entero = v1.data.entero / v2.data.entero;
    } else if(v1.type == INT_TYPE && v2.type == FLOAT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.entero / v2.data.real;
    } else if(v1.type == FLOAT_TYPE && v2.type == INT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.real / v2.data.entero;
    } else if(v1.type == FLOAT_TYPE && v2.type == FLOAT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.real = v1.data.real / v2.data.real;
    }
  }
}

void op_mod(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type == BOOL_TYPE || v2.type == BOOL_TYPE || v1.type == STRING_TYPE || v2.type == STRING_TYPE || v1.type == FLOAT_TYPE || v2.type == FLOAT_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type == INT_TYPE && v2.type == INT_TYPE){
      (*val).type = INT_TYPE;
      (*val).data.entero = v1.data.entero % v2.data.entero;
    }
  }
}

void op_pow(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type == BOOL_TYPE || v2.type == BOOL_TYPE || v1.type == STRING_TYPE || v2.type == STRING_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type == INT_TYPE && v2.type == INT_TYPE){
      (*val).type = INT_TYPE;
      (*val).data.entero = pow(v1.data.entero, v2.data.entero);
    } else if(v1.type == INT_TYPE && v2.type == FLOAT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.entero = pow(v1.data.entero, v2.data.real);
    } else if(v1.type == FLOAT_TYPE && v2.type == INT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.entero = pow(v1.data.real, v2.data.entero);
    } else if(v1.type == FLOAT_TYPE && v2.type == FLOAT_TYPE){
      (*val).type = FLOAT_TYPE;
      (*val).data.entero = pow(v1.data.real, v2.data.real);
    }
  }
}

void op_intdiv(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type == BOOL_TYPE || v2.type == BOOL_TYPE || v1.type == STRING_TYPE || v2.type == STRING_TYPE || v1.type == FLOAT_TYPE || v2.type == FLOAT_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type == INT_TYPE && v2.type == INT_TYPE){
      (*val).type = INT_TYPE;
      (*val).data.entero = v1.data.entero / v2.data.entero;
    }
  }
}

/* Funciones Booleanas */

void op_and(sym_value_type * and, sym_value_type v1, sym_value_type v2){
  if(v1.type == BOOL_TYPE){
    (*and).type = BOOL_TYPE;
    if(v1.data.boolean == true && v1.data.boolean == true){
      (*and).data.boolean = true;
    }else if(v1.data.boolean == true && v1.data.boolean == false){
      (*and).data.boolean = false;
    }else if(v1.data.boolean == false && v1.data.boolean == true){
      (*and).data.boolean = false;
    }else if(v1.data.boolean == false && v1.data.boolean == false){
      (*and).data.boolean = false;
    }
  }else yyerror("The NOT operation can only be used with Booleans");
}

void op_or(sym_value_type * or, sym_value_type v1, sym_value_type v2){
  if(v1.type == BOOL_TYPE){
    (*or).type = BOOL_TYPE;
    if(v1.data.boolean == true && v1.data.boolean == true){
      (*or).data.boolean = true;
    }else if(v1.data.boolean == true && v1.data.boolean == false){
      (*or).data.boolean = true;
    }else if(v1.data.boolean == false && v1.data.boolean == true){
      (*or).data.boolean = true;
    }else if(v1.data.boolean == false && v1.data.boolean == false){
      (*or).data.boolean = false;
    }
  }else yyerror("The NOT operation can only be used with Booleans");
}

void op_not(sym_value_type * not, sym_value_type v1){
  if(v1.type == BOOL_TYPE){
    (*not).type = BOOL_TYPE;
    if(v1.data.boolean == false)(*not).data.boolean = true;
    else (*not).data.boolean = false;
  }else yyerror("The NOT operation can only be used with Booleans");
}

void op_gt(sym_value_type * gt, sym_value_type v1, sym_value_type v2){
  (*gt).type = BOOL_TYPE;
  
  if(v1.type == INT_TYPE){
    if(v2.type == INT_TYPE){
      (*gt).data.boolean = (v1.data.entero > v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*gt).data.boolean = (v1.data.entero > v2.data.real) ? true : false;
    }
  }
  if(v1.type == FLOAT_TYPE){
    if(v2.type == INT_TYPE){
      (*gt).data.boolean = (v1.data.real > v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*gt).data.boolean = (v1.data.real > v2.data.real) ? true : false;
    }
  }
}

void op_ge(sym_value_type * ge, sym_value_type v1, sym_value_type v2){
  (*ge).type = BOOL_TYPE;
  
  if(v1.type == INT_TYPE){
    if(v2.type == INT_TYPE){
      (*ge).data.boolean = (v1.data.entero >= v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*ge).data.boolean = (v1.data.entero >= v2.data.real) ? true : false;
    }
  }
  if(v1.type == FLOAT_TYPE){
    if(v2.type == INT_TYPE){
      (*ge).data.boolean = (v1.data.real >= v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*ge).data.boolean = (v1.data.real >= v2.data.real) ? true : false;
    }
  }
}

void op_lt(sym_value_type * lt, sym_value_type v1, sym_value_type v2){
  (*lt).type = BOOL_TYPE;
  
  if(v1.type == INT_TYPE){
    if(v2.type == INT_TYPE){
      (*lt).data.boolean = (v1.data.entero < v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*lt).data.boolean = (v1.data.entero < v2.data.real) ? true : false;
    }
  }
  if(v1.type == FLOAT_TYPE){
    if(v2.type == INT_TYPE){
      (*lt).data.boolean = (v1.data.real < v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*lt).data.boolean = (v1.data.real < v2.data.real) ? true : false;
    }
  }
}

void op_le(sym_value_type * le, sym_value_type v1, sym_value_type v2){
  (*le).type = BOOL_TYPE;
  
  if(v1.type == INT_TYPE){
    if(v2.type == INT_TYPE){
      (*le).data.boolean = (v1.data.entero <= v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*le).data.boolean = (v1.data.entero <= v2.data.real) ? true : false;
    }
  }
  if(v1.type == FLOAT_TYPE){
    if(v2.type == INT_TYPE){
      (*le).data.boolean = (v1.data.real <= v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*le).data.boolean = (v1.data.real <= v2.data.real) ? true : false;
    }
  }
}

void op_eq(sym_value_type * eq, sym_value_type v1, sym_value_type v2){
  (*eq).type = BOOL_TYPE;
  
  if(v1.type == INT_TYPE){
    if(v2.type == INT_TYPE){
      (*eq).data.boolean = (v1.data.entero == v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*eq).data.boolean = (v1.data.entero == v2.data.real) ? true : false;
    }
  }
  if(v1.type == FLOAT_TYPE){
    if(v2.type == INT_TYPE){
      (*eq).data.boolean = (v1.data.real == v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*eq).data.boolean = (v1.data.real == v2.data.real) ? true : false;
    }
  }
}

void op_ne(sym_value_type * ne, sym_value_type v1, sym_value_type v2){
  (*ne).type = BOOL_TYPE;
  
  if(v1.type == INT_TYPE){
    if(v2.type == INT_TYPE){
      (*ne).data.boolean = (v1.data.entero != v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*ne).data.boolean = (v1.data.entero != v2.data.real) ? true : false;
    }
  }
  if(v1.type == FLOAT_TYPE){
    if(v2.type == INT_TYPE){
      (*ne).data.boolean = (v1.data.real != v2.data.entero) ? true : false;
    }

    if(v2.type == FLOAT_TYPE){
        (*ne).data.boolean = (v1.data.real != v2.data.real) ? true : false;
    }
  }
}