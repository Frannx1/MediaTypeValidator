#include "stateMachine.h"
#include <stdlib.h>


typedef struct stateMachineCDT {
    /** permite al usuario del parser almacenar sus datos */
    void * data;
    /******** zona privada *****************/
    int state; 

    isDoneFunc * isDone;
	stateFunc_t ** stateTable;
	transitionFunc_t *** transitionTable;
} stateMachineCDT;


stateMachineADT createStateMachine(isDoneFunc * isDone, 
			   stateFunc_t ** stateTable, transitionFunc_t *** transitionTable)
{
	stateMachineADT sm = malloc(sizeof(stateMachineCDT));
	sm->state = 0;
	sm->data = NULL;
	sm->isDone = isDone;
	sm->stateTable = stateTable;
	sm->transitionTable = transitionTable;

	return sm;
}

void initStateMachine(stateMachineADT sm, int stateQ0, void * data)
{
	sm->state = stateQ0;
	sm->data = data;
}

int getState(stateMachineADT sm)
{
	return sm->state;
}

void * getData(stateMachineADT sm)
{
	return sm->data;
}

int runState(stateMachineADT sm) 
{
    int newState = sm->stateTable[sm->STATE](sm->data);

    transitionFunc_t * transition = sm->transitionTable[sm->state][newState];

    if(transition) 
        transition(sm->data);

    sm->state = newState;
    return newState;
}

