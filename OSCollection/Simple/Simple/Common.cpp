#include "Common.h"



extern "C" void __cxa_pure_virtual()
{
	//This doesn't need to have an implementation. If a virtual call cannot be made, nothing needs to be done
}

//These methods will require an implementation when you implement a memory manager
void *operator new(size_t size)
{
	return (void *)0;
}

void *operator new[](size_t size)
{
	return (void *)0;
}

void operator delete(void *p)
{
}

void operator delete[](void *p)
{
}
