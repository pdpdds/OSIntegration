#include "Common.h"
#include "Console.h"

extern "C" void InitializeConstructors();

void kMain(unsigned long magic, unsigned long addr, unsigned int imageBase)
{
	InitializeConstructors();

	int i = 0;
	Console *c = new Console();
	const char *printingString = "Hello world!";

	c->Clear();
	while(printingString[i])
	{
		c->WriteChar(printingString[i], White, Black);
		i++;
	}
}
