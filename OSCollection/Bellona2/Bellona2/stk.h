#ifndef MYASM_STACK_HERADER
#define MYASM_STACK_HERADER

#define SENT_OPERATOR	1
#define SENT_NUMBER		2
#define SENT_END		100		// ������ ��

#define MAX_SENT		64

typedef struct SEntTag {
	int		nType;
	DWORD	dwValue;
}SEntStt;

typedef struct StkTag {
	int nS;
	SEntStt	s[ MAX_SENT ];		// ���� ����ü
}StkStt;

extern int nInitStk();							
extern int nPushSEntOperator( SEntStt *pSEnt );	
extern int nPushSEnt( SEntStt *pSEnt );			
extern int nPopSEnt( SEntStt *pSEnt );			
extern int nCalcStk( DWORD *pR );

#endif
