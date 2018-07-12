/**
 *  file    Utility.h
 *  date    2009/01/07
 *  author  kkamagui 
 *          Copyright(c)2008 All rights reserved by kkamagui
 *  brief   어셈블리어 유틸리티 함수들을 정의한 헤더 파일
 */

#ifndef __ASSEMBLYUTILITY_H__
#define __ASSEMBLYUTILITY_H__

#include "Types.h"
#include "Task.h"

////////////////////////////////////////////////////////////////////////////////
//
//  함수
//
////////////////////////////////////////////////////////////////////////////////
extern BYTE kInPortByte( WORD wPort );
extern void kOutPortByte( WORD wPort, BYTE bData );
extern WORD kInPortWord( WORD wPort );
extern void kOutPortWord( WORD wPort, WORD wData );
extern void kLoadGDTR( QWORD qwGDTRAddress );
extern void kLoadTR( WORD wTSSSegmentOffset );
extern void kLoadIDTR( QWORD qwIDTRAddress);
extern void kEnableInterrupt( void );
extern void kDisableInterrupt( void );
extern QWORD kReadRFLAGS( void );
extern QWORD kReadTSC( void );
extern void kSwitchContext( CONTEXT* pstCurrentContext, CONTEXT* pstNextContext );
extern void kHlt( void );
extern BOOL kTestAndSet( volatile BYTE* pbDestination, BYTE bCompare, BYTE bSource );
extern void kInitializeFPU( void );
extern void kSaveFPUContext( void* pvFPUContext );
extern void kLoadFPUContext( void* pvFPUContext );
extern void kSetTS( void );
extern void kClearTS( void );
extern void kEnableGlobalLocalAPIC( void );
extern void kPause( void );
extern void kReadMSR( QWORD qwMSRAddress, QWORD* pqwRDX, QWORD* pqwRAX );
extern void kWriteMSR( QWORD qwMSRAddress, QWORD qwRDX, QWORD qwRAX );

#endif /*__ASSEMBLYUTILITY_H__*/
