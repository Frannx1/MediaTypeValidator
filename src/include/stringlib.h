#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdlib.h>

/*
 * Funcion que hace un split de un string segun el caracter enviado 
 * por parametro.
 * Retorna un vector de strings, recordar hacer free de estos. 
 */
char ** splitString(char * input, size_t * qty, char splitChar);

void checkStringSize(char ** string, size_t size, size_t block);

void fixStringSize(char ** string, size_t size);

void checkSize(void ** vec, size_t size, size_t block, size_t nbytes);

void fixSize(void ** vec, size_t size, size_t nbytes);


#endif

