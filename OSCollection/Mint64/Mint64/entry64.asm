[BITS 64] ;64��Ʈ �ڵ�

SECTION .text
extern kmain64 ; C++ Ŀ�� ��Ʈ������Ʈ
extern kmain64Stage2 ; C++ Ŀ�� �������� 2 ��Ʈ������Ʈ
extern kmain64Stage3 ; C++ Ŀ�� �������� 2 ��Ʈ������Ʈ
global main64 ; PE���� ��Ʈ�� ����Ʈ
global gdt_commit ;
global gdt_commit2 ;
main64:	
; IA-32e ��� Ŀ�� ������ ���׸�Ʈ ��ũ���� ����
; 32��Ʈ���� 64��Ʈ�� �����ϸ鼭 Ŀ�� ���׸�Ʈ ��ũ���ʹ� 0X08�� ������ ����
	mov ax, 0x10        
	mov ds, ax          
	mov es, ax          
	mov fs, ax          
	mov gs, ax          
	
	; ���� ���� 0x500000~0x600000
	mov ss, ax
	mov rsp, 0x600000   
	mov rbp, 0x600000  

	call kmain64 
	
	jmp $

gdt_commit:	
	jmp jmp_64k
	jmp_64k:
	call kmain64Stage3	
	jmp $

	
gdt_commit2:
	
	mov ax, ss
	push rax

	mov rax, rbp                        ; RBP�� ����� RSP �������� ����
	push rax

    pushfq                              ; RFLAGS �������� ����
    pop rax
	push rax

	mov ax, cs                          ; CS �������� ����
    push rax

    push rcx
	iretq

	jmp $