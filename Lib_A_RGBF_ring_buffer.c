/** 
 * File:   Lib_A_RGBF_ring_buffer.c
 * Author: Isaev
 *
 * Created on 8 октября 2017 г., 19:45
 */

//******************************************************************************
//  Секция include: здесь подключается заголовочный файл к модулю
//          Lib_A_RGBF_ring_buffer.h
#include   "Lib_A_RGBF_ring_buffer.h"
//******************************************************************************


//******************************************************************************
//------------------------------------------------------------------------------
//  Глобальные переменные
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//  Локальные переменные
//------------------------------------------------------------------------------
//******************************************************************************


//******************************************************************************
//  Секция прототипов локальных функций
//******************************************************************************


//******************************************************************************
//  Секция описания функций (сначала глобальных, потом локальных)
//==============================================================================

/**
 *  @brief  Функция выполняет запись заданного количества байтов в кольцевой буфер;
 *  @param  *pBufStruct:    Указатель на структуру, содержащую указатели для
 *                          работы с кольцевым буфером;
 *  @param  *pByteToWriteInBuf: Указатель на байты данных, которые необходимо 
 *                              записать в кольцевой буфер;
 *  @param  lenght: Количество байт, которое необходимо записать в кольцевой буфер;
 *  @warning    Следует первое условие "if (pBufPointsStruct->pWriteDataInBuf == pBufPointsStruct->endBuf)"
 *             заменить "if (pBufPointsStruct->pWriteDataInBuf <= pBufPointsStruct->endBuf)" а крайнее else убрать;
 */
void RGBF_CopyDataInBuf(RGBF_ring_buf_s *pBufStruct,
                        void *pByteToWriteInBuf,
                        size_t lenght)
{
    size_t i;
    for (i = 0; i < lenght; i++)
    {
        *pBufStruct->pWriteDataInBuf++;
        
        //  Если указатель указывает на адрес конца буфера:
        if (pBufStruct->pWriteDataInBuf == pBufStruct->pEndBuf)
        {
            //  Записываем по указанному адресу (в конец буфера) данные и 
            //  инкрементируем указатели;           
            *pBufStruct->pWriteDataInBuf = *(char*) pByteToWriteInBuf++;
        }
            //  Если "вылетели" за пределы массива буфера:
        else if (pBufStruct->pWriteDataInBuf > pBufStruct->pEndBuf)
        {
            //  Переносим указатель на адрес начала буфера;  
            pBufStruct->pWriteDataInBuf = pBufStruct->pBeginBuf;

            //  Записываем по указанному адресу (в конец буфера) данные и 
            //  инкрементируем указатели;       
            *pBufStruct->pWriteDataInBuf = *(char*) pByteToWriteInBuf++;
        }
        else
        {
            //  Записываем по указанному адресу (в конец буфера) данные и 
            //  инкрементируем указатели;        
            *pBufStruct->pWriteDataInBuf = *(char*) pByteToWriteInBuf++;
        }
    }
}

/**
 *  @brief  Функция выполяет копирование данных из кольцевого буфера;
 *  @param  *pBufStruct:    Указатель на структуру, содержащую указатели для работы 
 *                         с кольцевым буфером;
 *  @param  *pArrToWriteFromBuf:    Указатель на массив данных, куда необходимо 
 *                                  скопировать данные  из кольцевого буфера;
 *  @param  lenght: Количество байт, которое необходимо скопировать из кольцевого 
 *                  буфера;
 */
void RGBF_CopyDataOutBuf(RGBF_ring_buf_s *pBufStruct,
                         void *pArrToWriteFromBuf,
                         size_t lenght)
{
    size_t i;
    for (i = 0; i < lenght; i++)
    {
        *pBufStruct->pReadDataFromBuf++;
        
        //  //  Если указатель указывает на адрес конца буфера:
        if (pBufStruct->pReadDataFromBuf == pBufStruct->pEndBuf)
        {
            //  Записываем по указанному адресу данные из буфера и инкрементируем 
            //  указатели;
            *(char*) pArrToWriteFromBuf++ = *pBufStruct->pReadDataFromBuf;
        }
            //  Если "вылетели" за пределы массива буфера:
        else if (pBufStruct->pReadDataFromBuf > pBufStruct->pEndBuf)
        {
            //  Переносим указатель на адрес начала буфера;  
            pBufStruct->pReadDataFromBuf = pBufStruct->pBeginBuf;
            //  Записываем по указанному адресу данные из буфера и инкрементируем 
            //  указатели;
            *(char*) pArrToWriteFromBuf++ = *pBufStruct->pReadDataFromBuf;
        }
        else
        {
            //  Записываем по указанному адресу данные из буфера и инкрементируем 
            //  указатели;
            *(char*) pArrToWriteFromBuf++ = *pBufStruct->pReadDataFromBuf;
        }
    }
}

/**
 *  @brief  Функция проверяет количество байт в кольцевом буфере, которое не было 
 *          скопировано;
 *  @param  *pBufStruct:    Указатель на структуру, содержащую указатели для работы 
 *                          с кольцевым буфером;
 *  @return Количество необработаных байт в кольцевом буфере;
 */
size_t RGBF_num_CheckDataNum(RGBF_ring_buf_s *pBufStruct)
{

    //  Если указатель на запись больше чем указатель на чтение:
    if (pBufStruct->pWriteDataInBuf >= pBufStruct->pReadDataFromBuf)
    {
        return (pBufStruct->pWriteDataInBuf - pBufStruct->pReadDataFromBuf);
    }
        // Если указатель на запись меньше чем указатель на чтение (т.е. указатель 
        // на запись "перешагнул" через конец буфера):
    else
    {
        size_t bytesNum1, BytesNum2;
        bytesNum1 = pBufStruct->pEndBuf - pBufStruct->pReadDataFromBuf;
        BytesNum2 = pBufStruct->pWriteDataInBuf - pBufStruct->pBeginBuf;
        return (bytesNum1 + BytesNum2);
    }
}

/**
 *  @brief  Функция устанавливает указатели чтения и записи кольцевого буфера в 
 *          начало массива кольцевого буфера;
 *  @param  *pBufStruct:    Указатель на структуру, содержащую указатели для работы 
 *                          с кольцевым буфером;
 */
void RGBF_ResetPointersToBegin(RGBF_ring_buf_s *pBufStruct)
{
    pBufStruct->pReadDataFromBuf = pBufStruct->pBeginBuf;
    pBufStruct->pWriteDataInBuf = pBufStruct->pBeginBuf;
}
//==============================================================================
//******************************************************************************


////////////////////////////////////////////////////////////////////////////////
//  END OF FILE
////////////////////////////////////////////////////////////////////////////////
