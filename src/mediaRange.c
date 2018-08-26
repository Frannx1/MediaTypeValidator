#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "mediaType.h"
#include "mediaRange.h"


typedef struct node_t {
    char * subtype;
    struct node_t * next;
} node_t;

typedef struct mediaRangeCDT {
    node_t * map[TYPES_QTY];
} mediaRangeCDT;


static node_t * addRecursive(node_t * current, node_t * newNode);
static int compareNodes(const node_t * current, const node_t * newNode);
static void deleteRecursive(node_t * node);


mediaRangeADT createMediaRange(void)
{
    mediaRangeADT mr = malloc(sizeof(mediaRangeCDT));
    for(int i = 0; i < TYPES_QTY; i++)
        mr->map[i] = NULL;
    return mr;
}

void deleteMediaRange(mediaRangeADT mr)
{
    for(int i = 0; i < TYPES_QTY; i++)
        deleteRecursive(mr->map[i]);
    free(mr);
}

void addMediaType(mediaRangeADT mr, const mediaType mt)
{
    node_t * newNode = malloc(sizeof(node_t));
    newNode->subtype = malloc(strlen(mt.subtype));

    strcpy(newNode->subtype, mt.subtype);
    mr->map[mt.type] = addRecursive(mr->map[mt.type], newNode);
}

bool containsMediaType(const mediaRangeADT mr, const mediaType mt)
{
	if(mt.type == ERROR_TYPE)
		return false;

	node_t * current = mr->map[mt.type];
	while(current != NULL)
	{
		if (current->subtype[0] == '*' || mt.subtype[0] == '*' || strcmp(current->subtype, mt.subtype) == 0)
			return true;
		current = current->next;
	}
	return false;
}


/*
 * Funciones de una lista ordenada
 */

static node_t * addRecursive(node_t * current, node_t * newNode)
{
	int c;
    if(current == NULL || (c = compareNodes(current, newNode)) < 0)
    {
        newNode->next = current;
        return newNode;
    }
    if(c == 0)
    	return current;

    current->next = addRecursive(current->next, newNode);
    return current;
}

static int compareNodes(const node_t * current, const node_t * newNode)
{
    if(newNode->subtype[0] == '*' && current->subtype[0] == '*')
        return 0;
    if(newNode->subtype[0] != '*' && current->subtype[0] == '*')
        return 1;
    if(newNode->subtype[0] == '*' && current->subtype[0] != '*')
        return -1;
        
    return strcmp(current->subtype, newNode->subtype);
}

static void deleteRecursive(node_t * node)
{
    if(node != NULL)
    {
        deleteRecursive(node->next);
        free(node->subtype);
        free(node);
    }
}

