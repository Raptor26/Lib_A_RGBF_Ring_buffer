/** 
 * File:   Lib_A_RGBF_ring_buffer.h
 * Author: Isaev
 *
 * Created on 8 октября 2017 г., 19:45
 */

#ifndef LIB_A_RGBF_RING_BUFFER_H
#define	LIB_A_RGBF_RING_BUFFER_H

//******************************************************************************
//  Секция include (подключаем заголовочные файлы используемых модулей)
//------------------------------------------------------------------------------
//  Стандартные библиотеки языка С
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Библиотеки для работы с периферией микроконтроллера
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Внешние модули
//------------------------------------------------------------------------------
//******************************************************************************


//******************************************************************************
//  Секция определения констант
//******************************************************************************


//******************************************************************************
//  Секция определения типов

typedef struct {
    uint8_t * const pBeginBuf; //   Указатель на начало массива кольцевого буфера;
    uint8_t * const pEndBuf; //     Указатель на концец массива кольцевого буфера;
    uint8_t *pWriteDataInBuf; //    Указатель на место в буфере куда будут 
    //                              записываться данные;
    uint8_t *pReadDataFromBuf; //   Указатель на место в буфере откуда будут 
    //                              считываться данные;
} RGBF_ring_buf_s; /*  Структура, содержащая указатели для работы с кольцевым 
                    *  буфером;
                    * 
                    *  Пример инициализации массива кольцевого буфера и 
                    *  структуры указателей:
                    *  //-------------------------------------------------------
                    *  #define UART1_RING_BUFF_SIZE                    64
                    *  uint8_t uart1RingBuff[UART1_RING_BUFF_SIZE];
                    *  RGBF_ring_buf_s uart1RingBuffPointers = {uart1RingBuff,
                    *  &uart1RingBuff[UART1_RING_BUFF_SIZE - 1],
                    *  uart1RingBuff, uart1RingBuff};
                    *  //-------------------------------------------------------
                     */
//******************************************************************************


//******************************************************************************
//  Секция определения глобальных переменных
//******************************************************************************


//******************************************************************************
//  Секция прототипов глобальных функций
extern void RGBF_CopyDataInBuf(RGBF_ring_buf_s *pBufStruct,
        void *pByteToWriteInBuf,
        size_t lenght);
extern void RGBF_CopyDataOutBuf(RGBF_ring_buf_s *pBufStruct,
        void *pArrToWriteFromBuf,
        size_t lenght);
extern size_t RGBF_num_CheckDataNum(RGBF_ring_buf_s *pBufStruct);
extern void RGBF_ResetPointersToBegin(RGBF_ring_buf_s *pBufStruct);
//******************************************************************************


//******************************************************************************
//  Секция определения макросов
//******************************************************************************

#endif	/* LIB_A_RGBF_RING_BUFFER_H */

////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
