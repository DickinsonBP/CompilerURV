#include <stdio.h>
#include <stdlib.h>
#include "calc_funcions.h" 
#include <math.h>
#include <string.h> 

/*
    COMPILADORES PRACTICA1 - URV - 2022 - DICKINSON BEDOYA PEREZ
*/

#define MAX 50

extern int yyparse();
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;

/* Variables extra */
extern char* instrucciones[1000]; // Array para ir almacenando instrucciones
extern unsigned int instructionLine;
extern unsigned int temporal;

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

  if(v1.type_value == NO_TYPE || v2.type_value == NO_TYPE){
    yyerror("Can't operate with these value type");
  } else {
      
    if(v1.type_value == STRING_TYPE && v2.type_value == STRING_TYPE){

      (*val).type_value = STRING_TYPE;
      strcat(strcpy((*val).data_value.ident.lexema, v1.data_value.ident.lexema), v2.data_value.ident.lexema);

    }else if(v1.type_value == STRING_TYPE && v2.type_value == INT_TYPE){

      (*val).type_value = STRING_TYPE;
      char int_str[50];
      sprintf(int_str, "%d", v2.data_value.entero);
      strcat(strcpy((*val).data_value.ident.lexema, v1.data_value.ident.lexema), int_str);

    }else if(v1.type_value == STRING_TYPE && v2.type_value == FLOAT_TYPE){

      (*val).type_value = STRING_TYPE;
      char int_str[50];
      sprintf(int_str, "%f", v2.data_value.real);
      strcat(strcpy((*val).data_value.ident.lexema, v1.data_value.ident.lexema), int_str);

    }else if (v1.type_value == INT_TYPE && v2.type_value == INT_TYPE){

      (*val).type_value = INT_TYPE;
      (*val).data_value.entero = v1.data_value.entero + v2.data_value.entero;

    } else if(v1.type_value == INT_TYPE && v2.type_value == FLOAT_TYPE){

      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.entero + v2.data_value.real;

    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == INT_TYPE){

      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.real + v2.data_value.entero;
    } else if (v1.type_value == FLOAT_TYPE && v2.type_value == FLOAT_TYPE){

      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.real + v2.data_value.real;

    } else{
      //ultimo caso
      type_val t1, t2;
      types(v1, v2, &t1, &t2);
      char *buff = (char*)malloc(10*sizeof(char));
      unsigned int temporal;
      if(buff){

        sprintf(buff, "%s", "ADDF"); //suma de floats
        (*val).data_value.temporal_type = FLOAT_TYPE;

        if(t1 == INT_TYPE && t2 == INT_TYPE){
          sprintf(buff, "%s", "ADDI");
          (*val).data_value.temporal_type = INT_TYPE;
        }
        if(t1 == FLOAT_TYPE && t2 == INT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "F2I", &v2);
          v2.data_value.temporal = temporal;
          v2.type_value = TEMPORAL_TYPE;
        }
        if(t1 == INT_TYPE && t2 == FLOAT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "I2F", &v1);
          v1.data_value.temporal = temporal;
          v1.type_value = TEMPORAL_TYPE;
        }

        temporal = temporalVariable();
        emet(NULL, temporal, &v1, buff, &v2);
        (*val).data_value.temporal = temporal;
        (*val).type_value = TEMPORAL_TYPE;

      }
      
    }
  }
}

void op_resta(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  /*can't substart strings*/
  if(v1.type_value == NO_TYPE || v2.type_value == NO_TYPE || v1.type_value == STRING_TYPE || v2.type_value == STRING_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type_value == INT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = INT_TYPE;
      (*val).data_value.entero = v1.data_value.entero - v2.data_value.entero;
    } else if(v1.type_value == INT_TYPE && v2.type_value == FLOAT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.entero - v2.data_value.real;
    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.real - v2.data_value.entero;
    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == FLOAT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.real - v2.data_value.real;
    }else{
      //ultimo caso
      type_val t1, t2;
      types(v1, v2, &t1, &t2);
      char *buff = (char*)malloc(10*sizeof(char));
      unsigned int temporal;
      if(buff){

        sprintf(buff, "%s", "SUBF"); //suma de floats
        (*val).data_value.temporal_type = FLOAT_TYPE;

        if(t1 == INT_TYPE && t2 == INT_TYPE){
          sprintf(buff, "%s", "SUBI");
          (*val).data_value.temporal_type = INT_TYPE;
        }
        if(t1 == FLOAT_TYPE && t2 == INT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "F2I", &v2);
          v2.data_value.temporal = temporal;
          v2.type_value = TEMPORAL_TYPE;
        }
        if(t1 == INT_TYPE && t2 == FLOAT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "I2F", &v1);
          v2.data_value.temporal = temporal;
          v2.type_value = TEMPORAL_TYPE;
        }

        temporal = temporalVariable();
        emet(NULL, temporal, &v1, buff, &v2);
        (*val).data_value.temporal = temporal;
        (*val).type_value = TEMPORAL_TYPE;

      }
    }
  }
}

void op_mult(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type_value == NO_TYPE || v2.type_value == NO_TYPE || v1.type_value == STRING_TYPE || v2.type_value == STRING_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type_value == INT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = INT_TYPE;
      (*val).data_value.entero = v1.data_value.entero * v2.data_value.entero;
    } else if(v1.type_value == INT_TYPE && v2.type_value == FLOAT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.entero * v2.data_value.real;
    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.real* v2.data_value.entero;
    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == FLOAT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.real * v2.data_value.real;
    }else{
      type_val t1, t2;
      types(v1, v2, &t1, &t2);
      char *buff = (char*)malloc(10*sizeof(char));
      unsigned int temporal;
      if(buff){

        sprintf(buff, "%s", "MULTF");
        (*val).data_value.temporal_type = FLOAT_TYPE;

        if(t1 == INT_TYPE && t2 == INT_TYPE){
          sprintf(buff, "%s", "MULTI");
          (*val).data_value.temporal_type = INT_TYPE;
        }
        if(t1 == FLOAT_TYPE && t2 == INT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "F2I", &v2);
          v2.data_value.temporal = temporal;
          v2.type_value = TEMPORAL_TYPE;
        }
        if(t1 == INT_TYPE && t2 == FLOAT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "I2F", &v1);
          v1.data_value.temporal = temporal;
          v1.type_value = TEMPORAL_TYPE;
        }

        temporal = temporalVariable();
        emet(NULL, temporal, &v1, buff, &v2);
        (*val).data_value.temporal = temporal;
        (*val).type_value = TEMPORAL_TYPE;

      }
    }
  }
}

void op_div(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type_value == NO_TYPE || v2.type_value == NO_TYPE || v1.type_value == STRING_TYPE || v2.type_value == STRING_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type_value == INT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = INT_TYPE;
      (*val).data_value.entero = v1.data_value.entero / v2.data_value.entero;
    } else if(v1.type_value == INT_TYPE && v2.type_value == FLOAT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.entero / v2.data_value.real;
    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.real / v2.data_value.entero;
    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == FLOAT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.real = v1.data_value.real / v2.data_value.real;
    }else{
      //ultimo caso
      type_val t1, t2;
      types(v1, v2, &t1, &t2);
      char *buff = (char*)malloc(10*sizeof(char));
      unsigned int temporal;
      if(buff){

        sprintf(buff, "%s", "DIVF"); //suma de floats
        (*val).data_value.temporal_type = FLOAT_TYPE;

        if(t1 == INT_TYPE && t2 == INT_TYPE){
          sprintf(buff, "%s", "DIVI");
          (*val).data_value.temporal_type = INT_TYPE;
        }
        if(t1 == FLOAT_TYPE && t2 == INT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "F2I", &v2);
          v2.data_value.temporal = temporal;
          v2.type_value = TEMPORAL_TYPE;
        }
        if(t1 == INT_TYPE && t2 == FLOAT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "I2F", &v1);
          v1.data_value.temporal = temporal;
          v1.type_value = TEMPORAL_TYPE;
        }

        temporal = temporalVariable();
        emet(NULL, temporal, &v1, buff, &v2);
        (*val).data_value.temporal = temporal;
        (*val).type_value = TEMPORAL_TYPE;

      }
    }
  }
}

void op_mod(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type_value == NO_TYPE || v2.type_value == NO_TYPE || v1.type_value == STRING_TYPE || v2.type_value == STRING_TYPE || v1.type_value == FLOAT_TYPE || v2.type_value == FLOAT_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type_value == INT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = INT_TYPE;
      (*val).data_value.entero = v1.data_value.entero % v2.data_value.entero;
    }else{
      //ultimo caso
      type_val t1, t2;
      types(v1, v2, &t1, &t2);
      char *buff = (char*)malloc(10*sizeof(char));
      unsigned int temporal;
      if(buff){

        sprintf(buff, "%s", "MOD"); //suma de floats
        (*val).data_value.temporal_type = INT_TYPE;

        if(t1 == INT_TYPE && t2 == INT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "MOD", &v2);
          (*val).data_value.temporal = temporal;
          (*val).data_value.temporal_type = INT_TYPE;
          (*val).type_value = TEMPORAL_TYPE;
        }

        temporal = temporalVariable();
        emet(NULL, temporal, &v1, buff, &v2);
        (*val).data_value.temporal = temporal;
        (*val).type_value = TEMPORAL_TYPE;

      }
    }
  }
}

void op_pow(sym_value_type * val, sym_value_type v1, sym_value_type v2){
  if(v1.type_value == NO_TYPE || v2.type_value == NO_TYPE || v1.type_value == STRING_TYPE || v2.type_value == STRING_TYPE){
    yyerror("Can't operate with these value type");
  }else{
    if(v1.type_value == INT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = INT_TYPE;
      (*val).data_value.entero = pow(v1.data_value.entero, v2.data_value.entero);
    } else if(v1.type_value == INT_TYPE && v2.type_value == FLOAT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.entero = pow(v1.data_value.entero, v2.data_value.real);
    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == INT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.entero = pow(v1.data_value.real, v2.data_value.entero);
    } else if(v1.type_value == FLOAT_TYPE && v2.type_value == FLOAT_TYPE){
      (*val).type_value = FLOAT_TYPE;
      (*val).data_value.entero = pow(v1.data_value.real, v2.data_value.real);
    }else{
      //ultimo caso
       type_val t1, t2;
      types(v1, v2, &t1, &t2);
      char *buff = (char*)malloc(10*sizeof(char));
      unsigned int temporal;
      if(buff){
        sprintf(buff, "%s", "POWF");
        (*val).data_value.temporal_type = FLOAT_TYPE;

        if(v1.type_value == INT_TYPE && v2.type_value == INT_TYPE){
          sprintf(buff, "%s", "POWI");
          (*val).data_value.temporal_type = INT_TYPE;
        }
        if(v1.type_value == FLOAT_TYPE && v2.type_value == INT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "F2I", &v2);
          v2.data_value.temporal = temporal;
          v2.type_value = TEMPORAL_TYPE;
        }
        if(v1.type_value == INT_TYPE && v2.type_value == FLOAT_TYPE){
          temporal = temporalVariable(); //obtener variable temporal
          emet(NULL, temporal, NULL, "I2F", &v1);
          v1.data_value.temporal = temporal;
          v1.type_value = TEMPORAL_TYPE;
        }

        temporal = temporalVariable();
        emet(NULL, temporal, &v1, buff, &v2);
        (*val).data_value.temporal = temporal;
        (*val).type_value = TEMPORAL_TYPE;

      }
    }
  }
}

/* Funciones Booleanas */

/*
    No implementadas para la practica 2
*/

/* Otras funciones */

/* Funcion para crear una lista enlazada a partir del numero de linea */
linked_list newList(int lines){
  linked_list list;
  list.num_elem = 1;

  node *start = (node *)calloc(1, sizeof(node));
  if(start){
    (*start).numLine = lines;
    (*start).next_node = NULL;

    list.start = start;

  }else yyerror("Error en funcion newList(int lines). No se puede reservar memoria");

  return list;
}

/* Funcion para crear una lista enlazada vacia */
linked_list newEmptyList(){
  linked_list list;
  list.num_elem = 0;
  list.start = NULL;

  return list;
}

/* Funcion para completar instrucciones almacenadas en el array de instrucciones*/
void completar(linked_list list, int num){
  node *start;
  char *buff;


  for(start = list.start; start != NULL; start = (*start).next_node){
    buff = (char*)calloc(MAX, sizeof(char));
    if(buff){

      /*
        Copiar instrucciones en el buffer.
        Liberar memoria que usa la instruccion incompleta.
        Actualizar la instruccion en la posicion que toca.
      */
      sprintf(buff, "%s %d", instrucciones[(*start).numLine - 1], num);
      free(instrucciones[(*start).numLine - 1]);
      instrucciones[(*start).numLine - 1] = buff;
      //fprintf(yyout, "%s\n", instrucciones[(*start).numLine - 1]);

    }else yyerror("Error en funcion completar(linked_list list, int num). No se puede reservar memoria");
  }

}

/* Funciones C3A*/

/* Genera instruccion */
void emet(char* var, unsigned int tmp, sym_value_type* val, char* operation, sym_value_type* val2){

  char *buff = (char*)malloc(MAX * sizeof(char));

  if(var != NULL){

    if(val == NULL) sprintf(buff, "%d: %s := $t%d",instructionLine,var,tmp);
    else{
      if(val->type_value == INT_TYPE) sprintf(buff, "%d: %s := %d",instructionLine,var,val->data_value.entero);
      if(val->type_value == FLOAT_TYPE) sprintf(buff, "%d: %s := %f",instructionLine,var,val->data_value.real);
      if(val->type_value == ID_TYPE) sprintf(buff, "%d: %s := %d",instructionLine,var,val->data_value.temporal);
    }

  }else{
    //Caso en que var es nulo
    if(buff != NULL){

      char *buff1 = (char*)calloc(MAX, sizeof(char));
      char *buff2 = (char*)calloc(MAX, sizeof(char));
      
      if(buff1 != NULL && val != NULL){

        if(val->type_value == FLOAT_TYPE){
          sprintf(buff1, "%f", val->data_value.real);
        }else if(val->type_value == INT_TYPE){
          sprintf(buff1, "%d", val->data_value.entero);
        }else if(val->type_value == TEMPORAL_TYPE){
          sprintf(buff1, "t%d", val->data_value.temporal); //Usar t para mostrar instrucciones para C3A
        }else if(val->type_value == ID_TYPE){
          sprintf(buff1,"%s", val->data_value.ident.lexema);
        }/*Mirar booleano*/
      }

      if(buff2 != NULL && val2 != NULL){

        if(val2->type_value == FLOAT_TYPE){
          sprintf(buff2, "%f", val2->data_value.real);
        }else if(val2->type_value == INT_TYPE){
          sprintf(buff2, "%d", val2->data_value.entero);
        }else if(val2->type_value == TEMPORAL_TYPE){
          sprintf(buff2, "t%d", val2->data_value.temporal); //Usar t para mostrar instrucciones para C3A
        }else if(val2->type_value == ID_TYPE){
          sprintf(buff2,"%s", val2->data_value.ident.lexema);
        }/*Mirar booleano*/

      }

      //Comprobar valor temporal para emet
      if(tmp != 0){

        /* Si val nulo, operadore unario, si no, binario*/
        if(val == NULL) sprintf(buff, "%d: $t%d := %s %s", instructionLine, tmp, operation, buff2);
        else sprintf(buff, "%d: $t%d := %s %s %s", instructionLine, tmp, buff1, operation, buff2);
      
      }else{

        if(val == NULL) sprintf(buff, "%d: %s %s", instructionLine, operation, buff2);
        else if(val == NULL && val2 == NULL) sprintf(buff, "%d: %s", instructionLine, operation);
      
      }

    }else yyerror("Error en funcion emet. No se ha podido reservar memoria");
  }

  //actualizar buffer de instrucciones y incrementar el numero de linea
  instrucciones[instructionLine] = buff;
  instructionLine++;
}

//funcion para hacer el emet del if
void emet_if(char* operation, sym_value_type* val, sym_value_type* val2, int numLine){
  char *buff = (char*)calloc(MAX, sizeof(char));
  bool tmp = false;
  if(buff){
    char *buff1 = (char*)calloc(MAX,sizeof(char));
    char *buff2 = (char*)calloc(MAX,sizeof(char));

    if(val){
      
      if(val->type_value == INT_TYPE) sprintf(buff1, "%d", val->data_value.entero);
      else if(val->type_value == FLOAT_TYPE) sprintf(buff1, "%f", val->data_value.real);
      else if(val->type_value == TEMPORAL_TYPE) { sprintf(buff1, "%d", val->data_value.temporal); tmp = true; }
      else if(val->type_value == ID_TYPE) sprintf(buff1, "%s", val->data_value.ident.lexema);
    }
    if(val2){
      
      if(val2->type_value == INT_TYPE) sprintf(buff2, "%d", val2->data_value.entero);
      else if(val2->type_value == FLOAT_TYPE) sprintf(buff2, "%f", val2->data_value.real);
      else if(val2->type_value == TEMPORAL_TYPE) {sprintf(buff2, "%d", val2->data_value.temporal); tmp = true;}
      else if(val2->type_value == ID_TYPE) sprintf(buff2, "%s", val2->data_value.ident.lexema);
    }


    if(val2 == NULL){
      
      if(numLine == 0) sprintf(buff, "%d: IF %s GOTO", instructionLine, buff1);
      else if(tmp) sprintf(buff, "%d: IF $t%s GOTO %d", instructionLine, buff1, numLine);
      else sprintf(buff, "%d: IF %s GOTO %d", instructionLine, buff1, numLine);

    }else{

      if(numLine == 0) sprintf(buff, "%d: IF %s %s %s GOTO", instructionLine, buff1, operation, buff2);
      else if(tmp) sprintf(buff, "%d: IF $t%s GOTO %d", instructionLine, buff2, numLine);
      else sprintf(buff, "%d: IF %s %s %s GOTO %d", instructionLine, buff1, operation, buff2, numLine);

    }

    instrucciones[instructionLine] = buff;
    instructionLine++;

  }else yyerror("Error en funcion emet_if. No se puede reservar memoria");
}




// Funcion que realiza el GOTO
void emet_ir(int numLine){
  char *buff = (char*)calloc(MAX, sizeof(char));
  if(buff){
    
    if(numLine != 0) sprintf(buff, "GOTO %d", numLine);
    else sprintf(buff,"GOTO");

    emet(NULL,0,NULL, buff, NULL);
  }else yyerror("Error en funcion emet_ir(int numLine). No se puede reservar memoria");

}

unsigned int temporalVariable(){
  temporal++;
  return temporal;
}

void types(sym_value_type v1, sym_value_type v2, type_val *t1, type_val *t2){

  if(v1.type_value == ID_TYPE) (*t1) = v1.data_value.identifier_type;
  else if(v1.type_value == TEMPORAL_TYPE) (*t1) = v1.data_value.temporal_type;
  else (*t1) = v1.type_value;

  if(v2.type_value == ID_TYPE) (*t2) = v2.data_value.identifier_type;
  else if(v2.type_value == TEMPORAL_TYPE) (*t2) = v2.data_value.temporal_type;
  else (*t2) = v2.type_value;
}