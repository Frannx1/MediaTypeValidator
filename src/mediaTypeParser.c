

typedef enum {STATE_TYPE, STATE_SUBTYPE, STATE_DONE, STATE_ERROR, NUM_STATES} state_t;

state_t doStateType(instanceData_t * data);
state_t doStateSubtype(instanceData_t * data);
state_t doStateDone(instanceData_t * data);
state_t doStateError(instanceData_t * data);

void doTypeToSubtype(instanceData_t * data);
void do_foo_to_bar( instanceData_t *data );
void do_bar_to_initial( instanceData_t *data );
void do_bar_to_foo( instanceData_t *data );
void do_bar_to_bar( instanceData_t *data );

stateFunc_t * const stateTable[NUM_STATES] = {
    do_state_initial, do_state_foo, do_state_bar
};

transitionFunc_t * const transitionTable[NUM_STATES][NUM_STATES] = {
    { NULL,              doTypeToSubtype, NULL },
    { NULL,              NULL,              do_foo_to_bar },
    { do_bar_to_initial, do_bar_to_foo,     do_bar_to_bar }
};

