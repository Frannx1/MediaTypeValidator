#ifndef MEDIA_RANGE_H
#define MEDIA_RANGE_H

#include "mediaType.h"

typedef enum {CONTAINS, NOT_CONTAINS, BAD_FORMAT} result_t;

typedef struct node_t {
    char * subtype;
    node_t * next;
} node_t;

typedef struct mediaRange_t {
    node_t * map[TYPES_QTY];
} mediaRange_t;

void addMediaType(mediaRange_t * mediaRange, const mediaType * mt);

result_t containsMediaType(const mediaRange_t * mediaRange, const mediaType * mt);


#endif

