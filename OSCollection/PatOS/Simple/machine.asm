; This file was automatically generated using att2intl
; Please see documentation, assuming there is any, if
; att2intl does something wrong
; Greg Velichansky
; (Hmaon / Xylem)
; With support from Cam Horn / Xylem and KeresztG 
;
; I MAKE NO WARRANTIES OF ANY KIND REGARDING THIS PRODUCT
; IN FACT I CAN GUARANTEE THAT IN SOME CASES IT WILL *NOT*
; WORK CORRECTLY!

[SECTION .text]
[BITS 32]

GDT_COUNT EQU 	 6
IDT_COUNT EQU 	 256


GLOBAL _syscallTrap
GLOBAL _switchToUser
GLOBAL _cs32
GLOBAL _contextSwitch
GLOBAL _fetchAndAdd32
GLOBAL _eflags
GLOBAL _outb
GLOBAL _inb
GLOBAL _inl
GLOBAL _ltr
GLOBAL _vmm_on
GLOBAL _getcr0
GLOBAL _getcr3
GLOBAL _invlpg
GLOBAL _cli
GLOBAL _sti
GLOBAL _gdtDesc

	   
GLOBAL _irq0
GLOBAL _irq1
GLOBAL _irq2
GLOBAL _irq3
GLOBAL _irq4
GLOBAL _irq5
GLOBAL _irq6
GLOBAL _irq7
GLOBAL _irq8
GLOBAL _irq9
GLOBAL _irq10
GLOBAL _irq11
GLOBAL _irq12
GLOBAL _irq13
GLOBAL _irq14
GLOBAL _irq15

GLOBAL _pit_do_init
GLOBAL _pageFaultHandler

GLOBAL _tssDS
GLOBAL _idt
GLOBAL _userDataSeg
GLOBAL _userCodeSeg
GLOBAL _kernelDataSeg
GLOBAL _kernelCodeSeg
GLOBAL _tssDescriptor

EXTERN _pic_irq
EXTERN _syscallHandler
EXTERN _vmm_pageFault

_syscallTrap:	
push 	ds

push 	ebp
push 	edi
push 	esi
push 	ebx

push 	edx
push 	ecx
push 	eax

mov 	eax, esp                        
push 	eax


mov 	eax,	[_kernelDataSeg]
mov 	ds,	ax

 
call 	_syscallHandler

add 	esp,	32

pop 	ds
iret



 
_switchToUser:	; basic label
mov 	ecx	,	[4+esp]
mov 	ebx    ,	[8+esp]
mov 	eax   ,	[12+esp]

mov 	edx ,	[_userDataSeg]
push 	edx            

push 	ebx            

pushf 
or 	DWORD [esp],	0200h

mov 	edx,	[_userCodeSeg]
push 	edx          

mov 	edx,	[_userDataSeg]

push 	ecx               

mov 	ds            ,	dx

iret





cs32:	; basic label
mov 	ecx       ,	[4+esp]
mov 	eax       ,	[8+esp]
mov 	edx ,	[12+esp]
lock 	cmpxchg ecx, edx
ret 


_contextSwitch:	; basic label
mov 	eax    ,	[4+esp]
mov 	ecx    ,	[8+esp]
mov 	edx    ,	[12+esp]

cmp 	eax,	0
jz 	_activateNext

push 	ebx
push 	esi
push 	edi
push 	ebp

mov 	[eax],	esp

_activateNext:	; basic label
mov 	esp,	ecx

pop 	ebp
pop 	edi
pop 	esi
pop 	ebx

 ; // get the new flags, mostly used for interrupt flag
push 	edx
popf

ret



_fetchAndAdd32:	; basic label
mov 	ecx	,	[4+esp]
mov 	eax	,	[8+esp]
lock 	add ecx, eax
ret



_eflags:	; basic label
pushf
pop 	eax
ret


_outb:	; basic label
push 	edx
mov 	dx,	[8+esp]
mov 	al,	[12+esp]
out 	dx,	al
pop 	edx
ret



_inb:	; basic label
push 	edx
mov 	dx,	[8+esp]
in 	al,	dx
pop 	edx
and 	eax,	0ffh
ret


_inl:	; basic label
push 	edx
mov 	dx,	[8+esp]
in 	eax,	dx
pop 	edx
ret


_ltr:	; basic label
mov 	eax,	[4+esp]
ltr 	ax
ret





_vmm_on:	; basic label
mov 	eax,	[4+esp]
mov 	cr3,	eax

mov 	eax,	cr0
or 	eax,	080000000h
mov 	cr0,	eax
ret

_getcr0:	; basic label
mov 	eax,	cr0
ret


_getcr3:	; basic label
mov 	eax,	cr3
ret

_invlpg:	; basic label
mov 	eax,	[4+esp]
invlpg 	[eax]
ret


_cli:	; basic label
cli
ret


_sti:	; basic label
sti
ret

 
_irq0:	; basic label
push 	eax
mov 	eax,	0
jmp 	irq_common


_irq1:	; basic label
push 	eax
mov 	eax,	1
jmp 	irq_common

 ; .global irq2
_irq2:	; basic label
push 	eax
mov 	eax,	2
jmp 	irq_common

 ; .global irq3
_irq3:	; basic label
push 	eax
mov 	eax,	3
jmp 	irq_common

 ; .global irq4
_irq4:	; basic label
push 	eax
mov 	eax,	4
jmp 	irq_common

 ; .global irq5
_irq5:	; basic label
push 	eax
mov 	eax,	5
jmp 	irq_common

 ; .global irq6
_irq6:	; basic label
push 	eax
mov 	eax,	6
jmp 	irq_common

 ; .global irq7
_irq7:	; basic label
push 	eax
mov 	eax,	7
jmp 	irq_common

 ; .global irq8
_irq8:	; basic label
push 	eax
mov 	eax,	8
jmp 	irq_common

 ; .global irq9
_irq9:	; basic label
push 	eax
mov 	eax,	9
jmp 	irq_common

 ; .global irq10
_irq10:	; basic label
push 	eax
mov 	eax,	10
jmp 	irq_common

 ; .global irq11
_irq11:	; basic label
push 	eax
mov 	eax,	11
jmp 	irq_common

 ; .global irq12
_irq12:	; basic label
push 	eax
mov 	eax,	12
jmp 	irq_common

 ; .global irq13
_irq13:	; basic label
push 	eax
mov 	eax,	13
jmp 	irq_common

 ; .global irq14
_irq14:	; basic label
push 	eax
mov 	eax,	14
jmp 	irq_common

 ; .global irq15
_irq15:	; basic label
push 	eax
mov 	eax,	15
jmp 	irq_common

irq_common:	; basic label
push 	ebx
push 	ecx
push 	edx
push 	esi
push 	edi
push 	ebp

push 	ds
mov 	ecx,	[_kernelDataSeg]
mov 	ds,	cx

mov 	ebp,	cr2
push 	ebp

push 	eax

 
call 	_pic_irq

add 	esp,	4

pop 	ebp
mov 	cr2,	ebp

pop 	ds

pop 	ebp
pop 	edi
pop 	esi
pop 	edx
pop 	ecx
pop 	ebx
pop 	eax
iret




 
_pit_do_init:	; basic label
pushf 
cli 
mov 	al	,	0b00110100

out 	0x43		,	al
mov 	al	,	BYTE [8+esp]
out 	040h,	al
mov 	al,	BYTE [9+esp]
out 	040h,	al
popf 
ret


_pageFaultHandler:	; basic label
push 	eax
push 	ebx
push 	ecx
push 	edx
push 	esi
push 	edi
push 	ebp


push 	ds
mov 	eax,	[_kernelDataSeg]
mov 	ds,	ax


mov 	eax,  cr2
push 	eax

mov 	eax,	esp
push 	eax

call 	_vmm_pageFault

add 	esp, 8   

pop 	ds

pop 	ebp
pop 	edi
pop 	esi
pop 	edx
pop 	ecx
pop 	ebx
pop 	eax
add 	esp, 4   
iret

 



_gdt:	; basic label
dd  0			
dd  0

dd  0x0000ffff	
dd  000cf9800h

dd  0x0000ffff	
dd  000cf9200h

dd  0x0000ffff	
dd  000cff800h

dd  0x0000ffff	
dd  000cff200h


_tssDescriptor:	; basic label
dd  0			

_gdtDesc:	; basic label
dw  GDT_COUNT * 8
dd  _gdt


_kernelCodeSeg:	; basic label
dd  1 * 8


_kernelDataSeg:	; basic label
dd  2 * 8


_userCodeSeg:	; basic label
dd  3 * 8 + 3


_userDataSeg:	; basic label
dd  4 * 8 + 3


_tssDS:	; basic label
dd  5 * 8



_idt:	; basic label
 ; .skip IDT_COUNT * 8
_idtDesc:	; basic label
dw  IDT_COUNT * 8
dd  _idt