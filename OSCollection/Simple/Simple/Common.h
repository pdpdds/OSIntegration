#ifndef Common_h
#define Common_h

typedef unsigned long  ulong;			//64 bit integer
typedef unsigned int   uint;			//32 bit integer
typedef unsigned short ushort;			//16 bit integer
typedef unsigned char  uchar;			//8 bit integer

struct multibootInfo
{
	uint flags;
	uint memoryLow;
	uint memoryHigh;
	uint bootDevice;
	uint commandLine;
	uint moduleCount;
	uint moduleAddresses;
	uint syms0;
	uint syms1;
	uint syms2;
	uint memoryMapLength;
	uint memoryMapAddress;
	uint drivesLength;
	uint drivesAddress;
	uint configTable;
	uint bootloaderName;
	uint apmTable;
	uint vbeControlInformation;
	uint vbeModeInformation;
	ushort vbeMode;
	uint vbeInterfaceAddress;
	ushort vbeInterfaceLength;
};

void *operator new (size_t size);
void *operator new[] (size_t size);
void operator delete (void *p);
void operator delete[] (void *p);
#endif
