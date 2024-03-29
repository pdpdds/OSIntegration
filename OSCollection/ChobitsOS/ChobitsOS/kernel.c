#include "chobits.h"

/*
 * GLOBAL FUNCTIONS
 */
BOOL KrnInitializeKernel(VOID);

/*
 * EXTERNEL FUNCTIONS
 */
extern BOOL HalInitializeHal(VOID);				/* hal.c */
extern BOOL MmkInitializeMemoryManager(VOID);	/* mmanager.c */
extern BOOL PskInitializeProcessManager(VOID);	/* process.c */
extern BOOL SysInitializeSyscall(VOID); /* syscall.c */

/*
 * DEFINITIONS
 */

/*
 * INTERNEL FUNCTIONS
 */

/*
 * GLOBAL VARIABLES
 */


/**********************************************************************************************************
 *                                            GLOBAL FUNTIONS                                             *
 **********************************************************************************************************/
BOOL KrnInitializeKernel(VOID)
{
	if(!HalInitializeHal()) {		/* first of all */
		DbgPrint("HalInitializeHal() returned an error.\r\n");
		return FALSE;
	}

	/*
	 * other parts of the kernel use dynamic memory alloc/dealloc functions, so we must initialize
	 * memory manager firstly than any others. (except HAL)
	 */
	if(!MmkInitializeMemoryManager()) {
		DbgPrint("MmkInitializeMemoryManager() returned an error.\r\n");
		return FALSE;
	}
	if(!PskInitializeProcessManager()) {
		DbgPrint("PskInitializeProcessManager() returned an error.\r\n");
		return FALSE;
	}
	if(!SysInitializeSyscall()) {
		DbgPrint("SysInitializeSyscall() returned an error.\r\n");
		return FALSE;
	}

	return TRUE;
}


/**********************************************************************************************************
 *                                           EXPORTED FUNTIONS                                            *
 **********************************************************************************************************/
KERNELAPI VOID KeDelay(DWORD MilliSec)
{
	DWORD start_tick, cur_tick;

	start_tick = PsGetTickCount();

	while(1) {
		cur_tick = PsGetTickCount();
		if(MilliSec < PsGetMilliSec(cur_tick-start_tick))
			break;
		HalTaskSwitch();
	}
}


/**********************************************************************************************************
 *                                           INTERNAL FUNTIONS                                            *
 **********************************************************************************************************/