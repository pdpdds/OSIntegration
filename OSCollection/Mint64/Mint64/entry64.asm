[BITS 64] ;64비트 코드

SECTION .text
extern kmain64 ; C++ 커널 엔트리포인트
extern kmain64Stage2 ; C++ 커널 스테이지 2 엔트리포인트
extern kmain64Stage3 ; C++ 커널 스테이지 2 엔트리포인트
global main64 ; PE포맷 엔트리 포인트
global gdt_commit ;
global gdt_commit2 ;
main64:	
; IA-32e 모드 커널 데이터 세그먼트 디스크립터 설정
; 32비트에서 64비트로 점프하면서 커널 세그먼트 디스크립터는 0X08로 설정된 상태
	mov ax, 0x10        
	mov ds, ax          
	mov es, ax          
	mov fs, ax          
	mov gs, ax          
	
	; 스택 설정 0x500000~0x600000
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

	mov rax, rbp                        ; RBP에 저장된 RSP 레지스터 저장
	push rax

    pushfq                              ; RFLAGS 레지스터 저장
    pop rax
	push rax

	mov ax, cs                          ; CS 레지스터 저장
    push rax

    push rcx
	iretq

	jmp $