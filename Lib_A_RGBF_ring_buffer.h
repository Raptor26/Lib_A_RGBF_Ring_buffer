/**
 * @file    %<%NAME%>%.%<%EXTENSION%>%
 * @author  %<%USER%>%
 * @version
 * @date    %<%DATE%>%, %<%TIME%>%
 * @brief
 */

#ifndef LIB_A_RGBF_RING_BUFFER_H
#define LIB_A_RGBF_RING_BUFFER_H

/*#### |Begin| --> Секция - "Include" ########################################*/
/*==== |Begin| --> Секция - "C libraries" ====================================*/
#include <stdint.h>
#include <stdio.h>
/*==== |End  | <-- Секция - "C libraries" ====================================*/

/*==== |Begin| --> Секция - "MK peripheral libraries" ========================*/
/*==== |End  | <-- Секция - "MK peripheral libraries" ========================*/

/*==== |Begin| --> Секция - "Extern libraries" ===============================*/
/*==== |End  | <-- Секция - "Extern libraries" ===============================*/
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Определение констант" ###########################*/
/*#### |End  | <-- Секция - "Определение констант" ###########################*/


/*#### |Begin| --> Секция - "Определение типов" ##############################*/
typedef struct
{
	void  *pStartBuff;
	void  *pEndBuff;
	void  *pWrite;
	void  *pRead;
} rgbf_buff_pointers_s;

typedef struct
{
	void *pStartBuff;
	size_t buffSize;
} rbgf_buff_pointers_init_s;
/*#### |End  | <-- Секция - "Определение типов" ##############################*/


/*#### |Begin| --> Секция - "Определение глобальных переменных" ##############*/
/*#### |End  | <-- Секция - "Определение глобальных переменных" ##############*/


/*#### |Begin| --> Секция - "Прототипы глобальных функций" ###################*/
extern void
RGBF_StructInit(
	rbgf_buff_pointers_init_s *pBuffInit_s);

extern void
RGBF_Init(
	rgbf_buff_pointers_s        *pBuff_s,
	rbgf_buff_pointers_init_s   *pBuffInit_s);

extern void
RGBF_WriteInBuf(
	rgbf_buff_pointers_s    *pBuff_s,
	void                    *pWriteData,
	size_t                   cnt);

extern void
RGBF_ReadFromBuf(
	rgbf_buff_pointers_s    *pBuff_s,
	void                    *pReadData,
	size_t                   cnt);

extern void*
RGBF_GetLastFromBuf(
	rgbf_buff_pointers_s *pBuff_s);

extern size_t
RGBF_GetCntDataInBuf(
	rgbf_buff_pointers_s *pBuff_s);

extern void
RGBF_CheckWriteBufBeyond(
	rgbf_buff_pointers_s *pBuff_s);

extern void
RBGF_CheckReadBufBeyond(
	rgbf_buff_pointers_s *pBuff_s);
/*#### |End  | <-- Секция - "Прототипы глобальных функций" ###################*/


/*#### |Begin| --> Секция - "Определение макросов" ###########################*/
#define __RGBF_CheckWriteBufBeyond(pBuff)       RGBF_CheckWriteBufBeyond(pBuff)
#define __RBGF_CheckReadBufBeyond(pBuff)        RBGF_CheckReadBufBeyond(pBuff)
/*#### |End  | <-- Секция - "Определение макросов" ###########################*/

#endif  /* LIB_A_RGBF_RING_BUFFER_H */

/*############################################################################*/
/*################################ END OF FILE ###############################*/
/*############################################################################*/
