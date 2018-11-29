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
 * @brief    Функция сбрасывает поля структуры "rbgf_buff_pointers_init_s"
 *           в значения по умолчанию
 *
 * @param[out]  *pBuffInit_s:   Указатель на инициализирующую структуру кольцевого буфера
 * @return   None
 */
void
RGBF_StructInit(
	rbgf_buff_pointers_init_s *pBuffInit_s)
{
	pBuffInit_s->buffSize   = 0u;
	pBuffInit_s->pStartBuff = 0u;
}

/*-------------------------------------------------------------------------*//**
 * @author    Mickle Isaev
 * @date      28-ноя-2018
 *
 * @brief    Функция выполняет инициализацию структуры кольцевого буфера
 *
 * @param[out]  *pBuff_s:       Указатель на структуру кольцевого буфера
 * @param[in]   *pBuffInit_s:   Указатель на инициализирующую структуру
 *                              кольцевого буфера
 * @return  None
 */
void
RGBF_Init(
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
 * @brief    Функция выполняет запись байт в кольцевой буфер
 *
 * @param[in,out]   *pBuff_s:       Указатель на структуру кольцевого буфера
 * @param[in]       *pWriteData:    Указатель на область памяти, с которой будут
 *                                  записаны данные в кольцевой буфер
 * @param[in]   cnt:    Количество байт, которое будет записано в кольцевой буфер
 * @return  None
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
 * @brief    Функция выполняет чтение байт из кольцевого буфера
 *
 * @param[in,out]   *pBuff_s:       Указатель на структуру кольцевого буфера
 * @param[in]       *pWriteData:    Указатель на область памяти, с которой будут
 *                                  записаны данные в кольцевой буфер
 * @param[in]   cnt:    Количество байт, которое будет считано из буфера
 * @return  None
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
 * @brief    Функция возвращает количество байт в кольцевом буфере
 *
 * @param[in]   *pBuff_s:   Указатель на структуру кольцевого буфера
 *
 * @return   Количество байт в кольцевом буфере
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
