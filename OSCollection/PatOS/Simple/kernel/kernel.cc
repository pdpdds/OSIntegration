#include "debug.h"
#include "machine.h"
#include "u8250.h"
#include "u8250pp.h"
#include "heap.h"
#include "init.h"
#include "pic.h"
#include "pit.h"
#include "tss.h"
#include "kbd.h"
#include "vmm.h"
#include "syscall.h"
#include "fs.h"
#include "ide.h"
#include "idle.h"
#include "window.h"
#include "vga.h"
#include "process.h"
#include "windowmanager.h"
#include "gdt.h"

WindowManager* WindowManager::wm;

#define VGA_CRT_CURSOR_H_LOCATION 0x0E
#define VGA_CRT_CURSOR_L_LOCATION 0x0F
#define VGA_COLOR_CRT_ADDRESS 0x3D4

void MoveCursor(unsigned int  X, unsigned int  Y)
{
	int m_VideoCardType = VGA_COLOR_CRT_ADDRESS;	// color
	if (X > 80)
		X = 0;
	unsigned short Offset = (unsigned short)((Y*80) + (X - 1));

	kEnterCriticalSection();
	outb(m_VideoCardType, VGA_CRT_CURSOR_H_LOCATION);
	outb(m_VideoCardType + 1, Offset >> 8);
	outb(m_VideoCardType, VGA_CRT_CURSOR_L_LOCATION);
	outb(m_VideoCardType + 1, (Offset << 8) >> 8);
	kLeaveCriticalSection();

	
}

void Clear()
{
	static unsigned short* m_pVideoMemory = (unsigned short*)0xb8000;

	for (int i = 0; i < 80 * 25; i++)				//Remember, 25 rows and 80 columns
	{
		m_pVideoMemory[i] = (unsigned short)(0x20 | (15 << 8));
	}


}

extern "C"
void kernelMain(unsigned long magic, unsigned long addr, uint32_t imageBase)
{
    /* Here is the state:

          - we're running on the initial stack
          - there is no heap
          - interrupts are disabled
          - there are no processes

       Here is the plan:

          - direct debug output to COM1 so we can express ourselves
          - initialize the heap before someone starts saying new or malloc
          - initialize the interrupts controller and vectors
          - start the interval-timer ticking
          - create the first process and yield to it. This will implicitly
            enable interrupts
          - go away
    */
       
      
    Pic::off();             // make sure interrupts are disabled

    U8250 uart;
    U8250pp uartp;

    /* initialize serial console */
    U8250::init(&uart);
    U8250pp::init(&uartp);

    /* redirect debug output to COM1 */
    //Debug::init(U8250::it);
    Debug::init(U8250pp::it, U8250::it);
    Debug::debugAll = false;
    Debug::printf("\nWhat just happened? Who am I? Why am I here?\n");
    Debug::printf("I am K439, welcome to my world\n");

	_asm lgdt[gdtDesc]

    /* initialize the TSS */
    TSS::init();
	
    /* Initialize system calls */
    Syscall::init();

    /* Initialize the heap */
    Heap::init((void*)0x100000,0x100000);

    Debug::printf("I have a heap\n");

	
    /* Initialize video drivers */

    WindowManager::wm = new WindowManager();
    WindowManager::wm->init();

    /* Make the rest of memory available for VM */
    PhysMem::init(0x400000,0x600000);

    /* Initialize the process subsystem */
    Process::init();
    Process::DEBUG->off();
    Process::trace("Process tracing enabled");

    Pic::init();                // initialize the PIC, still disabled

    Keyboard::init();           // initialize the keyboard

    Pit::init(1000 /* Hz */);   // enable the PIT, interrupts still disabled
	
    /* hdd */
    IDE hdd(3);
    Process::trace("loaded driver for hdd");
	
    /* rootfs */
    FileSystem::init(new Fat439(&hdd));
    Process::trace("initialized root filesystem");
	
    /* Create the Primordial process */
    Process* initProcess = new Init();
	
    /* Create the idle process */
    Process::idleProcess = new IdleProcess();
	MoveCursor(0, 0);
	for (;;);
    Process::idleProcess->start();

    initProcess->start();

	
    /* Yield to it, it will start running with interrupts enabled */
    Process::trace("Let there be processes");
    Process::yield();

    Debug::panic("The impossible has happened");
}
