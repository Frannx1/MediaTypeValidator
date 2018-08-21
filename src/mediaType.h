#ifndef MEDIA_TYPE_H
#define MEDIA_TYPE_H


typedef enum {APPLICATION, AUDIO, MULTIPART, TEXT, IMAGE, FONT, 
                                   VIDEO, TYPES_QTY, ERROR = -1} cathegoryType;

char * const cathegoryTypeTable[TYPES_QTY] = {
    "APPLICATION", "AUDIO", "MULTIPART", "TEXT", "IMAGE", "FONT", "VIDEO"
};

typedef struct mediaType {
    cathegoryType type;
    char * subtype;
} mediaType;

/*
 * Funcion que valida si el string recibido es un type valido
 * segun la table de catogorias de tipos.
 * Es case-insensitive
 */
cathegoryType convertStringToType(char * string);


#endif

