#ifndef MEDIA_RANGE_H
#define MEDIA_RANGE_H

#include "mediaType.h"
#include <stdbool.h>

typedef struct mediaRangeCDT * mediaRangeADT;


mediaRangeADT createMediaRange(void);

void deleteMediaRange(mediaRangeADT mr);

void addMediaType(mediaRangeADT mr, const mediaType mt);

bool containsMediaType(const mediaRangeADT mr, const mediaType mt);


#endif

