/********************************************************************************
* @file    viterby.h
* @author  Pospelova
* @version V1.0.0
* @date    March-2017
  ******************************************************************************
  * @attention
  *	Файл описывает основные переменные и методы, необходимые для работы  декоди-
  * рования по алгоритму Витерби
  *
  ******************************************************************************
*/

#ifndef VITERBY
#define VITERBY

#include <stdio.h>
#include "tables.h"

//*******************************Макросы******************************************
/**
 * @brief максимальная глубина поиска предположительно верной последовательности
 */
#define DEPTH 10

//*****************************Структуры******************************************

/**
 * @brief структура sPath описывает путь от текущего узла до узла, в котором  схо-
 *        дятся другие пути.
 * Члены структуры:
 *  metric      - метрика Хэмминга текущего пути
 *  nodeSize    - количество записанных вершин
 *  currentNode - перечень текущих вершин
 */
typedef struct
{
    unsigned int metric;
    unsigned int nodeSize;
    unsigned int currentNode[S];
}sPath;

/**
 * @brief структура sTree описывает дерево вероятных путей
 * Члены структуры:
 *  data        - значение посещенного узла
 *  metric      - метрика Хэмминга для текущего узла
 *  codeIndex   - индекс массива последовательностей, при котором произошло ветвление дерева путей
 *  left        - указатель на левое поддерево
 *  right       - указатель на правое поддерево
 *  parent      - указатель на родительский узел
 */
typedef struct
{
    unsigned int data;
    unsigned int metric;
    unsigned int codeIndex;
    struct sTree *left;
    struct sTree *right;
    struct sTree *parent;
} sTree;

//*****************************Переменные*****************************************
/**
 * @brief дерево вероятных путей от текущего узла
 */
sTree *pathTree;

/**
 * @brief перечень последовательностей, разбивающих кодовое слово на N символов
 *
 *        ПРИМЕЧАНИЕ: по-хорошему, должна быть динамической, так как размер кодового
 *        слова изначально неизвестен
 */
unsigned int NSequences[S][N];

/**
 * @brief реальное количество массива последовательностей из N-символов
 *
 *        ПРИМЕЧАНИЕ: является костылем. Если NSequences будет динамической,
 *        нужда в этой переменной отпадет
 */
unsigned int NSize;

//******************************Функции*******************************************
/**
 * @brief фкнуция запускает декодирование слова по алгоритму Витерби
 * @param
 *  codeWord - массив кодовых символов
 *  codeWordSize - размер мдекодированный массив
 *  decodeWordSize - размер выходного декодированного массива
 *  decodeWord - декодированное слово
 */
void getDecode(unsigned int *codeWord, unsigned int codeWordSize,
               unsigned int *decodeWord, unsigned int decodeWordSize);

/**
 * @brief фкнуция получения вероятных путей по алгоритму Витерби
 * @param
 *  tree - указатель на текущий узел дерева возможных путей
 *  NSInd - текущий индекс массива последовательносте из N-символов
 *  depth - глубина поиска
 */
//void viterby(unsigned int *pathInd, unsigned int *NSInd);
sTree *viterby(sTree *tree, unsigned int *NSInd, unsigned int *depth);

/**
 * @brief функция добавляет в дерево вероятных путей новый узел
 * @param
 *  data - значение нового узла дерева
 *  codeIndex - индекс массива последовательностей, при котором произошло ветвление
 *  node - указатель на новый узел дерева
 *  left -  флаг, указывающий, в какое поддерево будет добавлен нвый узел.
 *          При left = true узел будет добавлен в левое поддерево, иначе - в правое.
 */
sTree *addNode(unsigned int data, unsigned int codeIndex, sTree *node, bool left);

/**
 * @brief функция добавляет в поддерево вероятных путей новый узел
 * @param
 *  data - значение нового узла дерева
 *  codeIndex - индекс массива последовательностей, при котором произошло ветвление
 *  node - указатель на новый узел дерева
 *  left -  флаг, указывающий, в какое поддерево будет добавлен нвый узел.
 *  parent - указатель на родительский узел
 */
sTree *createBranch(unsigned int data, unsigned int codeIndex, sTree *node, sTree *parent, bool left);

/**
 * @brief фкнуция, очищающая массив вероятных путей
 * @param
 *  sPath path[S] - массив верочтных путей
 *  pathSize - размер массива вероятныз путей
 */
void clearPath(sPath path[S], unsigned int pathSize);

/**
 * @brief фкнуция подсчета метрики Хэмминга.
 *        Метрика Хэмминга рассчитывается как количество
 *        различающихся символов в двух массивах.
 * @param
 *  tree - указатель на текущий узел дерева путей
 *  array_1 - указатель на первый массив
 *  array_2 - указатель на второй массив
 */
void hammingCounter(sTree *tree, unsigned int *array_1, unsigned int *array_2);

/**
 * @brief функция разбивает слово на массив последовательностей
 *        из N символов
 * @param
 *  word - разбиваемое слово
 *  wordSize - размер разбиваемого слова
 *  split - массив получившихся последовательностей из N-символов
 *  splitSize - размер массива последовательностей из N-символов
 */
void splitWord(unsigned int *word, unsigned int wordSize,
               unsigned int split[S][N], unsigned int *splitSize);

/**
 * @brief Функция удаляет дерево
 * @param
 *  tree - указатель на дерево
 */
void removeTree(sTree *tree);

/**
 * @brief Функция проверяет полученный массив путей и выбирает из него наиболее оптимальный.
 *        Также функция возвращает последний посещенный узел наиболее вероятного пути
 * @param
 *  checked - указатель на массив, куда будет записан проверенный путь
 *  checkedSize - размер этого массива
 *  chIndex - указательн на текущий индекс этого массива
 *  path - массив вероятных путей
 *  pathSize - размер массива вероятных путей
 */
int checkPath(unsigned int *checked, unsigned int checkedSize, unsigned int *chIndex,
               sPath path[S], unsigned int pathSize);

/**
 * @brief Функция анализирует дерево путей и строит на его основе массив вероятных путей
 * @param
 *  tree - указатель на дерево возможных путей
 *  path - массив путей
 *  size - размер массива путей
 *  visit - флаг посещения узла
 *  isFirst - флаг первого посещения дерева
 */
void getPaths(sTree* tree, sPath path[S], unsigned int *size,
              bool *visit, bool *isFirst);

/**
 * @brief Функция добавляет в массив путей новое значение
 * @param
 *  path - массив путей
 *  size - текущий размер массива путей
 *  value - указатель на соответствующий узер дерева путей
 */
void appendValue(sPath path[S], unsigned int size, sTree *value);

/**
 * @brief Функция возвращает минимальный индекс массива вероятных путей
 * @param
 *  size - размер массива
 */
unsigned int getMin(sPath path[S], unsigned int size);

/**
 * @brief Функция декодирует выходное слово на основании полученного
 *        наиболее оптимального пути
 * @param
 *  decodeWord - указатель на массив декодированных символов
 *  decodeWordSize - размер массива декодированных символов
 *  checkedPath - указатель на массив узлов наиболее оптимального пути
 *  chSize - размер массива узлов наиболее оптимального пути
 */
void decode(unsigned int *decodeWord, unsigned int decodeWordSize,
            unsigned int *checkedPath, unsigned int chSize);

#endif // VITERBY

