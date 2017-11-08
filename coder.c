/********************************************************************************
* @file    coder.c
* @author  Pospelova
* @version V1.0.0
* @date    March-2017
  ******************************************************************************
  * @attention
  *	Файл описывает реализацию сверточного кодирования.
  * Реализация сверточного кодирования основана на конечных автоматах. Предполагается,
  * что существует конечный набор состояний. Конечный автомат одновеременно может
  * находиться только в одном из состояний этого набора. При поступлении на вход новых
  * данных, конечный автомат может переходить из одного состояния в другое. Правила
  * перехода из состояния в состояние описываются посредством таблицы переходов.
  * Количество состояний определены исходя из данных, предложенных в тандарте ITU-T.
  *
  *
  ******************************************************************************
*/
#include "coder.h"
#include <string.h>
#include <stdlib.h>

/**
 * @brief инициализация таблиц конечного автомата. Выполняется один раз при
 *        запуске программы
 * @param
 */
bool initTables()
{

    if(true)
    {
        if(true)
        {
            if(true)
            {
                return true;
            }
        }
    }

    return false;
}

/**
 * @brief получение таблиц из файла
 * @param
 *  filename - имя файла
 *  table - таблица
 *  cols - количество столбцов в таблице
 *  rows - количество строк в таблице
 */
bool getTable(unsigned int rows, unsigned int cols, char *filename, int table[rows][cols])
{
    FILE *file = fopen(filename, "r");  //переменная для работы с файлами
    if(file != NULL)    //если файл filename открыт для чтения
    {
        unsigned int i = 0;      //итератор строк таблицы переходов
        unsigned int j = 0;      //итератор столбцов таблицы переходов
        while((!feof(file)) && (i < rows))  //пока не конец файла и итератор меньше количества строк таблицы
        {
            char ch[N+1];            //строка для считывания символов   // пофикшен баг, было ch[N]
            fscanf(file, "%s", ch); //чтение строки символов из файла
            table[i][j] = atoi(ch); //перевод строки в число
            j = j + 1;              //увеличение итератора столбца
            if(j > cols - 1)        //если итератор столбца больше cols - 1
            {
                j = 0;              //сброс итератора столбца
                i = i + 1;          //увеличение итератора строк
            }
        }

        fclose(file);   //закрытие файла
        return true;
    }
    else
    {
        printf("Error! Can't open file %s", filename);  //вывод сообщения об ошибке                                  //закрытие файла
        return false;
    }
}

/**
 * @brief запрос закодированного слова
 * @param
 *  inputWord - указатель на исходное слово
 *  wordLen  - длина исходного слова
 *  codeWord - указатель на кодированное слово
 *  codeLen - длина кодированного слова
 */
void getCodeWord(unsigned int *inputWord, unsigned int wordLen, unsigned int *codeWord, unsigned int codeLen)
{
    initArray(coderRegister, SIZE);         //инициализация регистра кодера
    unsigned int len = wordLen + SIZE-1;    //расчет количества сдвигов регистра
    unsigned int state = 0;                 //установка конечного автомата в начальное состояние
    unsigned int j = 0;                     //инициализация итератора по закодированному слову
    unsigned int i;                         //итератор по возможному количеству сдвигов регистра
    int iterator = wordLen - 1;             //инизиализация итератора для работы с входным словом в обратном порядке

    for (i = 0; i < len; ++i)
    {
        if(iterator < 0)                                            //если итератор меньше длины входного слова
        {
            shiftLeft(coderRegister, SIZE, 0);                      //сдвиг регистра с добавлением нуля в начало
        }
        else
        {
            shiftLeft(coderRegister, SIZE, inputWord[iterator]);    //сдвиг регистра с добавлением i-го символа входного слова в начало
        }

        int codeState[N];                                   //закодированный символ входного слова
        getCodeSymbol(coderRegister, &state, codeState);    //получение закодрованного символа входного слова
        addToCodeWord(codeWord, codeLen, &j, codeState);    //добавление новых кодовых символов в выходное кодовое слово
        iterator = iterator - 1;                            //уменьшение итератора на единицу
    }
}

/**
 * @brief запрос закодированного символа
 * @param
 *  registerState - текущее состояние регистра кодера
 *  state - текущее состояние конечного автомата
 *  code - массив кодовых символов
 */
void getCodeSymbol(unsigned int registerState[SIZE], unsigned int *state,
                   unsigned int code[N])
{
    int j;  //итератор по столбцам таблицы переходов

    for(j = 0; j < S; j = j + 1)
    {
        if(jumpTable[*state][j] > -1)   //если переход для текущего состояния неотрицательный
        {
            int index = jumpTable[*state][j];               //индекс состояния для текущего перехода
            if(!memcmp(registerState, stateTable[index], SIZE))    //если текущее состояние регистра совпадает с возможным переходом в следующее состояние
            {
                int i;                          //итератор по таблице кодов
                 for(i = 0; i < N; i = i + 1)    //получение кода для текущего состояния
                {
                    code[i] = codeTable[j][i];   // пофикшено, было codeTable[index][i], из-зв чего кодирование происходило неправильно
                }
                *state = index;                 //переход в новое состояние
                return;                         //выход из функции
            }
        }
    }
    printf("Error state!\n");   //сообщение об ошибке, так как переход в следующее состояние невозможен
}

/**
 * @brief добавление в кодовый массив новых кодовых символов
 * @param
 *  codeWord - выходное кодовое слово
 *  codeLen - длина выходного кодового слова
 *  iterator - текущий итератор кодового слова
 *  currentCode - массив добавляемых закодированных символов
 */
void addToCodeWord(unsigned int *codeWord, unsigned int codeLen,
                   unsigned int *iterator, unsigned int *currentCode)
{
    int i = 0;  //итератор массива добавляемых символов
    while((*iterator < codeLen) && (i < N))  //добавление элементов в кодовое слово, пока позволяют размеры обоих массивов
    {
        codeWord[*iterator] = currentCode[i];
        *iterator = *iterator + 1;
        i = i + 1;
    }
}
