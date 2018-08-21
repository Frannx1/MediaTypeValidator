#include <stdio.h>
#include <stdlib.h>
#include "mediaType.h"
#include "mediaRange.h"

static node_t * addRecursive(node_t * current, node_t * newNode);

static int compareNodes(const node_t * current, const node_t * newNode);


void addMediaType(mediaRange_t * mediaRange, const mediaType * mt)
{
    node_t * newNode = malloc(sizeof(node_t));
    strcpy(newNode->subtype, mt->subtype);
    int c;
    
    mediaRange->map[mt->type] = addRecursive(mediaRange->map[mt->type], newNode);
}

result_t containsMediaType(const mediaRange_t * mediaRange, const mediaType * mt)
{
	if(mt == NULL)
		return BAD_FORMAT;

	node_t * current = mediaRange->map[mt->type];
	while(current != NULL)
	{
		if (current->subtype[0] == '*' || mt->subtype[0] == '*' || strcmp(current->subtype, mt->subtype) == 0)
			return CONTAINS;
		current = current->next;
	}
	return NOT_CONTAINS;
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
