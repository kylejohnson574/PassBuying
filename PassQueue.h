#ifndef __pass_queue_h_
#define __pass_queue_h_
#include "PassDef.h"
typedef struct pass_queue_entry_t
{
	void *pPrevEntry;
	void *pNextEntry;
	pass *pEntry;
} pass_entry;
typedef struct pass_queue_t_
{
	unsigned short bIsValid;
	pass_entry *pQueueFront;
	pass_entry *pQueueEnd;
	unsigned long ulSize;
	//TODO
} pass_queue;
extern pass_queue *initQueue();
extern unsigned short addItem(pass_queue *queue , pass *item);
extern pass_entry* findItem(pass_queue *queue, unsigned long id);
extern pass* findPass(pass_queue *queue, unsigned long id);
extern unsigned short removeItem(pass_queue *queue, unsigned long id);
extern pass* getNext(pass_queue *queue);
#endif
