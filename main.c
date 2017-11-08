/********************************************************************************
* @file    main.c
* @author  Pospelova
* @version V1.0.0
* @date    March-2017
  ******************************************************************************
  * @attention
  *	Файл содержит пример работы со сверточным кодером
  *
  ******************************************************************************
*/

#include <stdio.h>
#include "coder.h"
#include "viterby.h"

/**
 * @brief отображение массива на экране
 * @param
 *  rows - количество строк
 *  cols - количество столбцов
 *  table[rows][cols] - отображаемый массив
 */
void output(unsigned int rows, unsigned int cols, int table[rows][cols])
{
    for(unsigned int i = 0; i < rows; i = i + 1)
    {
        for(unsigned int j = 0; j < cols; j = j + 1)
        {
            printf("%d ", table[i][j]);
        }
        printf("\n");
    }
}

/**
 * @brief главная функция
 * @param
 *
 */
int main(void)
{
      #define inputWordSize 1                            //определяем размер кодируемого слова
        unsigned int word[inputWordSize] = {1}; //определяем кодируемое слово
        //определяем размер закодированного слова. По стандарту ITU-T к кодируемому слову дописывается
        //SIZE избыточных бит. Так как в кодере N сумматоров, то на один кодируемый симвов приходится
        //N закодированных. Таким образом, получаем длину закодированного слова

        unsigned int codeWordSize = N*(inputWordSize + SIZE-1);
        unsigned int codeWord[codeWordSize];                        //массив закодированных символов
        getCodeWord(word, inputWordSize, codeWord, codeWordSize);   //вызов функции кодирования

        printf("Input word:\n");                //тестовый
        output(1, inputWordSize, word);         //вывод

        printf("\ncodeWord:\n");                //тестовый
        output(1, codeWordSize, codeWord);      //вывод

        unsigned int decodeWord[inputWordSize]; //массив декодированных символов
/*
        codeWord[0] = 0;            //искусственное внесение
        codeWord[1] = 1;            //шума для закодированной
        codeWord[2] = 1;           //последовательности символов
        codeWord[12] = 1;
        codeWord[4] = 0;
//*/

        printf("\ncodeWord with error:\n");                  //тестовый
        output(1, codeWordSize, codeWord);      //вывод

        getDecode(codeWord, codeWordSize, decodeWord, inputWordSize);   //вызов функции декодирования

        printf("\nDecoded word:\n");            //тестовый
        output(1, inputWordSize, decodeWord);   //вывод

    return 0;
}

