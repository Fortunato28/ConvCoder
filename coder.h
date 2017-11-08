/********************************************************************************
* @file    coder.h
* @author  Pospelova
* @version V1.0.0
* @date    March-2017
  ******************************************************************************
  * @attention
  *	Файл описывает основные переменные и методы, необходимые для работы сверточ-
  * ного кодера
  *
  *
  ******************************************************************************
*/

#ifndef CODER
#define CODER

#include <stdio.h>
#include <stdbool.h>
#include "tables.h"

//*****************************Функции********************************************
/**
 * @brief запрос закодированного слова
 * @param
 *  word - указатель на исходное слово
 *  len  - длина исходного слова
 */
void getCodeWord(unsigned int *inputWord, unsigned int wordLen,
                 unsigned int *codeWord, unsigned int codeLen);

/**
 * @brief запрос закодированноо символа
 * @param
 *  registerState - текущее состояние регистра кодера
 *  state - текущее состояние конечного атвомата
 *  code - массив кодовых символов
 */
void getCodeSymbol(unsigned int registerState[SIZE], unsigned int *state,
                   unsigned int code[N]);

/**
 * @brief добавление в кодовый массив новых кодовых символов
 * @param
 *  codeWord - выходное кодовое слово
 *  codeLen - длина выходного кодового слова
 *  iterator - текущий итератор кодового слова
 *  currentCode - массив добавляемых закодированных символов
 */
void addToCodeWord(unsigned int *codeWord, unsigned int codeLen,
                   unsigned int *iterator, unsigned int *currentCode);

#endif // CODER

