# RGBF - библиотека, реализующая кольцевой буфер #

Пример работы с кольцевым буфером на языке Си:

```C
/* Подключение библиотеки кольцевого буфера */
#include "Lib_A_RGBF_ring_buffer.h"

/* Структура кольцевого буфера */
rgbf_buff_pointers_s    ringBuffForRx_s;    

/* Выделение памяти под кольцевой буфер */
char                    ringBuffForRx_a[256];

int main(void)
{
    ...
    /* Пример инициализации структуры кольцевого буфера */
    rbgf_buff_pointers_init_s ringBuffInit_s;
    RGBF_StructInit(
        &ringBuffInit_s);

    /* Указывается адрес массива который был выделен под кольцевой буфер */
    ringBuffInit_s.pStartBuff   = (void*) ringBuffForRx_a;

    /* Размер массива кольцевого буфера */
    ringBuffInit_s.buffSize     = sizeof(ringBuffForRx_a);

    /* Вызов функции инициализации */
    RGBF_Init(
        &ringBuffForRx_s, 
        &ringBuffInit_s);
    ...
    while(1)
    {
        ...
        char message_a[] = "Hello World\r\n";
        /* Запись данных в буфер осуществляется следующим образом */
        RGBF_WriteInBuf(
            &ringBuffForRx_s, 
            (void*) message_a, 
            (size_t)srtlen(message_a));

        /* Чтение данных из буфера осуществляется следующим образом */
        char readMessage_a[strlen(message_a)];
        RGBF_ReadFromBuf(
            &ringBuffForRx_s, 
            (void*) readMessage_a,
            RGBF_GetCntDataInBuf(&ringBuffForRx_s));
        /* Где функция "RGBF_GetCntDataInBuf()" возвращает количество байт в кольцевом буфере */
        /* Теперь данные из кольцевого буфера записаны в массив "readMessage_a" */
        ...
    }
    return 1;
}
```