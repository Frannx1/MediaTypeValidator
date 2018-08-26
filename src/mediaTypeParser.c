#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stringlib.h"
#include "mediaType.h"
#include "stateMachine.h"

#define BLOCK 10

typedef enum {STATE_TYPE, STATE_SUBTYPE, STATE_DONE, STATE_ERROR, NUM_STATES} state_t;

typedef enum {NO_ERROR, TYPE_ERROR, SUBTYPE_ERROR} errors_t;

typedef struct parserData {
    char * remaining;
    char * formedType;
    char * formedSubtype;
    size_t sizeType;
    size_t sizeSubtype;
    errors_t error;
} parserData;


static int doStateType(void * data);
static int doStateSubtype(void * data);
static int doStateDone(void * data);
static int doStateError(void * data);

static void doTypeToType(void * data);
static void doTypeToSubtype(void * data);
static void doSubtypeToSubtype(void * data);
static void doTypeToError(void * data);
static void doSubtypeToDone(void * data);
static void doSubtypeToError(void * data);

static bool isDone(state_t state, parserData * data);
static char * convertDataToMediaType(parserData * data, mediaType * mt);

stateFunc_t * const stateTable[NUM_STATES] = {
    doStateType, doStateSubtype, doStateDone, doStateError
};

transitionFunc_t * const transitionTable[NUM_STATES][NUM_STATES] = {
    {doTypeToType,  doTypeToSubtype,    NULL,            doTypeToError   },
    {NULL,          doSubtypeToSubtype, doSubtypeToDone, doSubtypeToError},
    {NULL,          NULL,               NULL,            NULL            },
    {NULL,          NULL,               NULL,            NULL            }
};

char * parseToMediaType(char * string, mediaType * mt) 
{
    stateMachineADT sm = createStateMachine((stateFunc_t **) stateTable, 
                           (transitionFunc_t ***) transitionTable, NUM_STATES);         
    parserData data = {.remaining = string, .sizeType = 0, .sizeSubtype = 0,
                                                            .error = NO_ERROR};
    initStateMachine(sm, STATE_TYPE, (void *) &data);
    while(!isDone(getState(sm) ,&data)) 
        feedStateMachine(sm);

    deleteStateMachine(sm);
    char * ret = convertDataToMediaType(&data, mt);
    return ret;
}

static char * convertDataToMediaType(parserData * data, mediaType * mt)
{
    char * ret = "Everything was ok.";
    switch(data->error)
    {
        case TYPE_ERROR:
            mt->type = ERROR_TYPE;
            ret = "Bad format in the type.";
            break;
        case SUBTYPE_ERROR:
            mt->type = ERROR_TYPE;
            ret = "Bad format in the subtype.";
            break;
        default:
            mt->type = convertStringToType(data->formedType);
            if(mt->type == ERROR_TYPE)
                ret = "The type inserted does not exist.";
            else
                mt->subtype = data->formedSubtype;
            break;
    }
    if(data->error == TYPE_ERROR)
        free(data->formedType);
    if(data->error == SUBTYPE_ERROR)
        free(data->formedSubtype);
    return ret;
}

static bool isDone(state_t state, parserData * data)
{
    if(data->error != NO_ERROR || state == STATE_DONE)
        return true;
    return false;
}

static int doStateType(void * data)
{
    parserData * myData = (parserData *) data;
    char c = myData->remaining[0];
    if(isalpha(c))
        return STATE_TYPE;
    if(c == '/')
        return STATE_SUBTYPE;
    return STATE_ERROR;
}

static int doStateSubtype(void * data)
{
    parserData * myData = (parserData *) data;
    char c = myData->remaining[0];
    if(c == 0)
        return STATE_DONE;
    return STATE_SUBTYPE;
}

static int doStateDone(void * data)
{
    return STATE_DONE;
}

static int doStateError(void * data)
{
    return STATE_ERROR;
}

static void doTypeToType(void * data)
{
    parserData * myData = (parserData *) data;
    checkStringSize(&(myData->formedType), myData->sizeType, BLOCK);
    myData->formedType[myData->sizeType++] = *(myData->remaining)++;
}

static void doTypeToSubtype(void * data)
{
    parserData * myData = (parserData *) data;
    fixStringSize(&(myData->formedType), myData->sizeType + 1);
    myData->formedType[myData->sizeType] = 0;
    myData->remaining++;
}

static void doSubtypeToSubtype(void * data)
{
    parserData * myData = (parserData *) data;
    checkStringSize(&(myData->formedSubtype), myData->sizeSubtype, BLOCK);
    myData->formedSubtype[myData->sizeSubtype++] = *(myData->remaining)++;
}

static void doSubtypeToDone(void * data)
{
    parserData * myData = (parserData *) data;
    fixStringSize(&(myData->formedSubtype), myData->sizeSubtype + 1);
    myData->formedSubtype[myData->sizeSubtype] = 0;
}

static void doTypeToError(void * data)
{
    parserData * myData = (parserData *) data;
    myData->error = TYPE_ERROR;
}

static void doSubtypeToError(void * data)
{
    parserData * myData = (parserData *) data;
    myData->error = SUBTYPE_ERROR;
}


