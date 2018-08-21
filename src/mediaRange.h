#ifndef MEDIA_RANGE_H
#define MEDIA_RANGE_H

#include "mediaType.h"


typedef struct mediaRangeCDT * mediaRangeADT;

typedef enum {CONTAINS, NOT_CONTAINS, BAD_FORMAT} result_t;


mediaRangeADT createMediaRange(void);

void addMediaType(mediaRangeADT mr, const mediaType mt);

result_t containsMediaType(const mediaRangeADT mr, const mediaType mt);


#endif

