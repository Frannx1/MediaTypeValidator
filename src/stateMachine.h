#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

/**
 *	Maquina de estados generica
 */
typedef stateMachineCDT * stateMachineADT;

/**
 *	Parametros para su construccion:
 *
 *	isDone: funcion que dado un estado retorna un boolean:true 
 *			si este es terminal.
 *
 *   stateTable: vector de funciones que dado los datos provistos
 *				retorne el estado que alcanza.
 *
 *	transitionTable: matriz de funciones de transicion de un estado
 *					 a otro, en caso de no implementar alguna, 
 *					 rellenar con NULL.
 */

typedef int stateFunc_t(void * data);

typedef void transitionFunc_t(void * data);

typedef bool isDoneFunc(void * data);


stateMachineADT createStateMachine(isDoneFunc * isDone, 
			  stateFunc_t ** stateTable, transitionFunc_t *** transitionTable);

void initStateMachine(stateMachineADT sm, int stateQ0, void * data);

int getState(stateMachineADT sm);

void * getData(stateMachineADT sm);

/**
 *	Funcion para correr la maquina de estados
 *	Devuelve el estado alcanzado
 */
int runState(stateMachineADT sm);


#endif

