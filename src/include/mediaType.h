#ifndef MEDIA_TYPE_H
#define MEDIA_TYPE_H


typedef enum {APPLICATION, AUDIO, MULTIPART, TEXT, IMAGE, FONT, 
                                   VIDEO, TYPES_QTY, ERROR_TYPE = -1} categoryType;

char * const categoryTypeTable[TYPES_QTY] = {
    "APPLICATION", "AUDIO", "MULTIPART", "TEXT", "IMAGE", "FONT", "VIDEO"
};

typedef struct mediaType {
    categoryType type;
    char * subtype;
} mediaType;

/*
 * Funcion que valida si el string recibido es un type valido
 * segun la table de catogorias de tipos.
 * Es case-insensitive
 */
categoryType convertStringToType(char * string);


#endif

