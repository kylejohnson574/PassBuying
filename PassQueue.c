#include "PassQueue.h"

//Create a new queue for storing passes
// Return 0 if unsuccessful otherwise pointer to a new queue

pass_entry *entry = 0;

pass_queue *initQueue()
{
	pass_queue *pReturn = (pass_queue *)malloc(sizeof(pass_queue));

	if( pReturn != 0 )
	{
		
		pReturn->pQueueFront = 0;
		pReturn->pQueueEnd = 0;
		pReturn->ulSize = 0;
		pReturn->bIsValid = 1;	
		
	}

	return pReturn;
}

pass* getNext(pass_queue *queue)
{
	pass *pEntry = 0;
	if (!entry)
	{
		if (queue->pQueueFront)
		{
			pEntry = queue->pQueueFront->pEntry;
			entry = queue->pQueueFront;
		}
	}
	else
	{
		entry = entry->pNextEntry;
		if (entry)
		{
			pEntry = entry->pEntry;
		}
	}

	return pEntry;
}

unsigned short addItem(pass_queue *queue, pass *item)
{
	unsigned short bReturn = 0;
	if( queue != 0 && item != 0 )
	{
		pass_entry *pNew = (pass_entry *)malloc(sizeof(pass_entry));
		if( pNew != 0 )
		{
			pNew->pPrevEntry = queue->pQueueFront;
			if (queue->pQueueFront)
			{
				queue->pQueueFront->pNextEntry = pNew;
			}
			
			queue->pQueueFront = pNew;
			pNew->pNextEntry = 0;
			pNew->pEntry = item;
			bReturn = 1;
			queue->ulSize++;
		}
	}
	
	return bReturn;
}

pass_entry* findItem(pass_queue *queue , unsigned long id) 
{
	pass_entry *pReturn = 0;
	if (queue)
	{
		pass_entry *pEntry = queue->pQueueFront;
		if (pEntry)
		{
			while (pEntry)
			{
				pass *pPass = pEntry->pEntry;
				if (pPass)
				{
					if (pPass->ulID == id)
					{
						pReturn = pEntry;
						break;
					}
				}

				pEntry = (pass_entry *)pEntry->pNextEntry;
			}
		}
	}

	return pReturn;
}

pass* findPass(pass_queue *queue , unsigned long id) 
{
	pass *pReturn = 0;
    pass_entry *pEntry = findItem(queue, id );
    if (pEntry)
	{
        pReturn = pEntry->pEntry;
	}

	return pReturn;
}

unsigned short removeItem( pass_queue *queue, unsigned long id)
{
	unsigned short bRemoved = 0;
	pass_entry *pItem = findItem( queue, id );
	if( pItem != 0 )
	{
		free(pItem->pEntry);
		
		if( pItem->pNextEntry != 0 )
		{
			((pass_entry *)pItem->pPrevEntry)->pNextEntry = pItem->pNextEntry;
		}
		else
		{
			((pass_entry *)pItem->pPrevEntry)->pNextEntry = 0;
		}

		free(pItem);

		bRemoved = 1;
	}

	return bRemoved;
}