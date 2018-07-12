#ifndef _GDT_H_
#define _GDT_H_


#include "stdint.h"
#include "mmu.h"

extern "C" uint32_t kernelCodeSeg;
extern "C" uint32_t kernelDataSeg;
extern "C" uint32_t userCodeSeg;
extern "C" uint32_t userDataSeg;

extern "C" uint32_t tssDS;
extern "C" Descriptor tssDescriptor;
extern "C" uint32_t gdtDesc;


#endif
