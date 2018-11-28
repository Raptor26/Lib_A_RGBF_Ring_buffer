/**
 * @file    %<%NAME%>%.%<%EXTENSION%>%
 * @author  %<%USER%>%
 * @version
 * @date    %<%DATE%>%, %<%TIME%>%
 * @brief
 */


/*#### |Begin| --> Секция - "Include" ########################################*/
#include "Lib_A_RGBF_ring_buffer.h"
/*#### |End  | <-- Секция - "Include" ########################################*/


/*#### |Begin| --> Секция - "Глобальные переменные" ##########################*/
/*#### |End  | <-- Секция - "Глобальные переменные" ##########################*/


/*#### |Begin| --> Секция - "Локальные переменные" ###########################*/
/*#### |End  | <-- Секция - "Локальные переменные" ###########################*/


/*#### |Begin| --> Секция - "Прототипы локальных функций" ####################*/

/*#### |End  | <-- Секция - "Прототипы локальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание глобальных функций" ####################*/

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      28-ноя-2018
 *
 * @brief    { function_description }
 *
 * @param    pBuffInit_s    Буфер инициализирует s
 */
void
RGBF_InitStruct(
	rbgf_buff_pointers_init_s *pBuffInit_s)
{
	pBuffInit_s->buffSize   = 0u;
	pBuffInit_s->pStartBuff = 0u;
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      28-ноя-2018
 *
 * @brief    { function_description }
 *
 * @param    pBuff_s        Буфер s
 * @param    pBuffInit_s    Буфер инициализирует s
 */
void
RGBF_InitBuff(
	rgbf_buff_pointers_s        *pBuff_s,
	rbgf_buff_pointers_init_s   *pBuffInit_s)
{
	pBuff_s->pStartBuff     = pBuffInit_s->pStartBuff;
	pBuff_s->pEndBuff       = pBuff_s->pStartBuff + pBuffInit_s->buffSize - 1U;
	pBuff_s->pWrite         = pBuff_s->pStartBuff;
	pBuff_s->pRead          = pBuff_s->pStartBuff;
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      28-ноя-2018
 *
 * @brief    { function_description }
 *
 * @param        pBuff_s       Буфер s
 * @param        pWriteData    Данные записи
 * @param[in]    cnt           Счет
 */
void
RGBF_WriteInBuf(
	rgbf_buff_pointers_s    *pBuff_s,
	void                    *pWriteData,
	size_t                   cnt)
{
	while (cnt != 0u)
	{
		/* Проверка вылета за предела буфера  */
		__RGBF_CheckWriteBufBeyond(pBuff_s);

		/* Запись данных в кольцевой буфер */
		*((uint8_t*)pBuff_s->pWrite++) = *((uint8_t*) pWriteData++);

		/* Декремент счетчика */
		cnt--;
	}
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      28-ноя-2018
 *
 * @brief    { function_description }
 *
 * @param        pBuff_s      Буфер s
 * @param        pReadData    Чтение данных
 * @param[in]    cnt          Счет
 */
void
RGBF_ReadFromBuf(
	rgbf_buff_pointers_s    *pBuff_s,
	void                    *pReadData,
	size_t                   cnt)
{
	while (cnt != 0u)
	{
		__RBGF_CheckReadBufBeyond(pBuff_s);

		*((uint8_t*) pReadData++) = *((uint8_t*)pBuff_s->pRead++);

		cnt--;
	}
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      28-ноя-2018
 *
 * @brief    { function_description }
 *
 * @param    pBuff_s    Буфер s
 *
 * @return    { description_of_the_return_value }
 */
void*
RGBF_GetLastFromBuf(
	rgbf_buff_pointers_s *pBuff_s)
{
	/* Проверка вылета за предела буфера  */
	__RGBF_CheckWriteBufBeyond(pBuff_s);

	if (pBuff_s->pWrite == pBuff_s->pStartBuff)
	{
		return (pBuff_s->pEndBuff);
	}
	else
	{
		return (pBuff_s->pWrite - 1U);
	}
}


/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      28-ноя-2018
 *
 * @brief    { function_description }
 *
 * @param    pBuff_s    Буфер s
 *
 * @return    { description_of_the_return_value }
 */
size_t
RGBF_GetCntDataInBuf(
	rgbf_buff_pointers_s *pBuff_s)
{

	if (pBuff_s->pWrite >= pBuff_s->pRead)
	{
		return (pBuff_s->pWrite - pBuff_s->pRead);
	}
	else
	{
		return ((pBuff_s->pEndBuff - pBuff_s->pRead + 1U)
				+ (pBuff_s->pWrite - pBuff_s->pStartBuff));
	}

}
/*#### |End  | <-- Секция - "Описание глобальных функций" ####################*/


/*#### |Begin| --> Секция - "Описание локальных функций" #####################*/
void
RGBF_CheckWriteBufBeyond(
	rgbf_buff_pointers_s *pBuff_s)
{
	/* Если указатель на запись данных вышел за пределы буфера */
	if (pBuff_s->pWrite > pBuff_s->pEndBuff)
	{
		/* Указатель перемещается на начало буфера */
		pBuff_s->pWrite = pBuff_s->pStartBuff;
	}
}

void
RBGF_CheckReadBufBeyond(
	rgbf_buff_pointers_s *pBuff_s)
{
	/* Если указатель на чтение данных вышел за пределы буфера */
	if (pBuff_s->pRead > pBuff_s->pEndBuff)
	{
		/* Указатель перемещается на начало буфера */
		pBuff_s->pRead = pBuff_s->pStartBuff;
	}
}
/*#### |End  | <-- Секция - "Описание локальных функций" #####################*/


/*############################################################################*/
/*############################ END OF FILE  ##################################*/
/*############################################################################*/
