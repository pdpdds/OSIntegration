/*Created By Samuel -  17-12-2000
	1) Verified and modified using template rather than void pointer on 19-Jul-2001 12:19_57am
	2) Modified to structured chains on 25-Aug-2001 2:48_52pm
	3) Modified to function on Ace OS (new, delete operators are removed) on 17-Aug-2002 11:32 pm
*/

#include <Collect.h>

template<class PtrType> UINT16 Collection<PtrType>::Count()
{
	return ItemCount;
}
template<class PtrType> BOOLEAN Collection<PtrType>::Add(PtrType ptr, int Index, char * Key)
{
	CollectionData <PtrType> **ptrPrev, *ptrNext = 0, *ptrNew;
	UINT16 Pos = 0;
	if (StrLen(Key) > 14)
		Key[14] = 0;
	ptrPrev = &this->_Item;		//this loop will find the position where we have to put the new node
	while (Pos < Index && ptrPrev)
	{
		ptrPrev = &((*ptrPrev)->Next);
		Pos++;
	}
	ptrNext = (*ptrPrev == 0) ? 0 : (*ptrPrev)->Next; 	// you must insert before this node so keep this node's address

	//--------------Allocate New node and Initializing its values
	ptrNew = AllocHeap(sizeof(ptrNew));
	if (ptrNew == NULL)
		return NULL;
	ptrNew->Next = 0;
	ptrNew->ptr = 0;
	MemSet(ptrNew->Key, 0, 15);
	//----------------------------------------------------------

	ptrNew->ptr = ptr;
	StrCpy(ptrNew->Key, Key);
	ptrNew->Next = ptrNext;	  // placeing any other old nodes after that one

	if (*ptrPrev == 0)
		*ptrPrev = ptrNew;     // putting the new node in the correct place
	else
		(*ptrPrev)->Next = ptrNew;     // putting the new node in the correct place

	ItemCount++;		 // Incrementing the total

	return True;
}
template <class PtrType> BOOLEAN Collection<PtrType>::Add(PtrType ptr)
{
	return Add(ptr, ItemCount);
}





