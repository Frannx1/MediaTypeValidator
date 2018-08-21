#include <stdlib.h>
#include "mediaType.h"
#include "stateMachine.h"

typedef enum {STATE_TYPE, STATE_SUBTYPE, STATE_DONE, STATE_ERROR, NUM_STATES} state_t;

state_t doStateType(void * data);
state_t doStateSubtype(void * data);
state_t doStateDone(void * data);
state_t doStateError(void * data);

void doTypeToSubtype(void * data);
void doTypeToError(void * data);
void doSubtypeToDone(void * data);
void doSubtypeToError(void * data);

stateFunc_t * const stateTable[NUM_STATES] = {
    doStateType, doStateSubtype, doStateDone, doStateError
};

transitionFunc_t * const transitionTable[NUM_STATES][NUM_STATES] = {
    {NULL,      doTypeToSubtype, NULL,            doTypeToError   },
    {NULL,      NULL,            doSubtypeToDone, doSubtypeToError},
    {NULL,      NULL,            NULL,            NULL            },
    {NULL,      NULL,            NULL,            NULL            }
};

typedef struct parserData {
    char * remaining;
    char * formedType;
    char * formedSubtype;
} parserData;

void parseToMediaType(const char * string, mediaType * mt) {
    stateMachineADT sm = createStateMachine(stateTable, transitionTable);
    parserData data = {.remaining = string};
    initStateMachine(sm, STATE_TYPE, (void *) &data);

    /*
    while(buffer_can_read(b)) {
        const uint8_t c = buffer_read(b);
        st = hello_parser_feed(p, c);
        if (hello_is_done(st, errored)) {
            break;
        }
    }
    */

    convertDataToMediaType(data, mt);
    return mt;
}
