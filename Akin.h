#ifndef AKIN_H
    #define AKIN_H

    /*!
        \brief  Функция считывания базы из файла
        \param  [FILE *]sourse Файл с базой
        \param  [Tree *]tree Указатель на дерево
        \return 0 в случае успеха, -1 в противном
                случае
    */
    int  readBase(FILE *sorse, Tree *tree);
    /*!
        \brief  Функция акинатора
        \param  [Tree *]tree Указатель на дерево
        \return 0 в случае успеха и -1 в противном
                случае
    */
    int  akinator(Tree *tree);
    /*!
        \brief  Функция обновления базы, новая
                база будет записана в Base.txt
        \param  [Node *]node Указель на узел
        \return 0 в случае успеха, -1 в противном случае
    */
    int  updateBase(Node *node);
    /*!
        \brief  Фукнция, которая дает характеристику 
                элементу
        \param  [Tree *]tree Указатель на дерево
        \param  [const type_t]elem Элемент, которому
                нужно дать характеристику\
        \return 0 в случае успеха, -1 в противном
                случае
    */
    int  describtion(Tree *tree, const type_t elem);
    /*!
        \brief  Функция распечатки пути к элементу
        \param  [Node *]node Указатель на узел
        \param  [int]is_right 1, если узел является
                правым ребенком, 0 в противном случае
        \return 0 в случае успеха, -1 в противном случае
    */
    int  printPath(Node *node, int is_right);
    /*!
        \brief  Функция сравнения двух элементов
        \param  [Tree *]tree Указатель на дерево
        \param  [type_t]elem1 Первый элемент
        \param  [type_t]elem2 Второй элемент
        \return 0 в случае успеха, -1 в противном случае
    */
    int  compare(Tree *tree, type_t elem1, type_t elem2);
    /*!
        \brief  Функция получения пути к элементу
        \param  [Node *]node Указатель на узел
        \param  [Path *]elem_path Указатель на структуру
                пути
        \param  [int]is_right 1, если узел является
                правым ребенком, 0 в противном случае
        \return значение узла в случае успеха, -1
                в противном случае
    */
    type_t getPath(Node *node, Path *elem_path, int is_right);


    
#endif