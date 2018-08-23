#include "stateMachine.h"
#include <stdlib.h>


typedef struct stateMachineCDT {
    void * data;
    int state; 
	stateFunc_t ** stateTable;
	transitionFunc_t *** transitionTable;
} stateMachineCDT;


stateMachineADT createStateMachine(stateFunc_t ** stateTable, transitionFunc_t *** transitionTable)
{
	stateMachineADT sm = malloc(sizeof(stateMachineCDT));
	sm->state = 0;
	sm->data = NULL;
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

int feedStateMachine(stateMachineADT sm) 
{
    int newState = sm->stateTable[sm->state](sm->data);

    transitionFunc_t * transition = sm->transitionTable[sm->state][newState];

    if(transition) 
        transition(sm->data);

    sm->state = newState;
    return newState;
}

