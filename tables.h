/********************************************************************************
* @file    tables.h
* @author  Pospelova
* @version V1.0.0
* @date    March-2017
  ******************************************************************************
  * @attention
  *	Файл хранит информацию о таблицах конечного автомата и основных константах,
  * использующихся для кодирования и декодирования данных, а также методы
  * по работе с этими данными
  *
  *
  ******************************************************************************
*/

#ifndef TABLES
#define TABLES

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
//***************************Макросы*******************************************
/**
 * @brief размер регистра для кодирования (ITU-T п. 7.9.2)
 */
#define SIZE 6

/**
 * @brief количество сумматоров по модулю 2 в сверточном кодере
 */
#define N 2

/**
 * @brief количество существующих состояний
 * количество возможных состояний S рассчитывается как 2^m, где
 * m - размер регистра кодирования. В соответствии с ITU-T m = K - 1,
 * т.е. m = 6. Таким образом, количество состояний S = 2^6 = 64.
 * Каждому состоянию S соответствует своя выходная последовательность
 * кодовых символов.
 */
#define S 64

//**************************Переменные*******************************************
/**
 * @brief регистр кодирования
 */
unsigned int coderRegister[SIZE];

/**
 * @brief таблица состояний конечного автомата
 *        Так как возможное количество состояний составляет S,
 *        и размер регистра для каждого состояния равен SIZE,
 *        то для хранения таблицы состояний
 *        выбираем мтрицу размером SxSIZE.д
 */
extern int stateTable[S][SIZE];

/**
 * @brief таблица возможных кодов для каждого состояния
 *        Так как возможное количество состояний составляет S,
 *        и количество сумматоров кодера расна N,
 *        то один входной символ кодируется N выходными символами.
 *        Поэтому размер таблицы составляет SxN
 */
extern uint8_t codeTable[S][N];

/**
 * @brief таблица переходов конечного автомата
 *        Количество возможных состояний конечного автомата S.
 *        Каждое состояние атомата соответствует конкретному состоянию регистра
 *        кодера. Так как таких состояний тоже S, получаем таблицу переходов размером
 *        SxS
 */
extern int8_t jumpTable[S][S];


//*****************************Функции********************************************
/**
 * @brief сравнение двух целочисленных массивов
 *        Предполагается, что оба массива имеют одинаковую длину,
 *        равную SIZE
 * @param
 *  registerState - текущее состояние регистра кодера
 *  state - состояние, с которым идет сравнение
 */
bool arrCmp(unsigned int *array_1, unsigned int *array_2, unsigned int len);

/**
 * @brief инициализация массива
 * @param
 *  array - массив
 *  size - размер массива
 */
void initArray(unsigned int * array, unsigned int size);

/**
 * @brief сдвиг регистра на одну позицию влево
 * @param
 *  array - массив
 *  size - размер массива
 *  newValue - новый символ, помещаемый в начало регистра
 */
void shiftLeft(unsigned int * array, unsigned int size, unsigned int newValue);

#endif // TABLES

