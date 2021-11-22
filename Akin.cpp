#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Tree.h"
#include "Akin.h"
#include "logsLib.h"
#include "textLib.h"


int readBase(FILE *sourse, Tree *tree)
{
    assert(sourse);
    assert(tree);

    long int file_length = 0;
    fileLength(&file_length, sourse);

    char *text = (char *) calloc(file_length + 1, sizeof(char));
    long int num_symb = fread(text, sizeof(char), file_length, sourse);

    text[num_symb] = '\0';

    assert(text);

    treeCtor(tree);
    Node *cur_node = &(tree->root);

    for (int i = 0; i < num_symb; i++)
    {
        i += skipSpace(text + i);

        if (text[i] == '{')
        {
            i += skipSpace(text + i + 1);
            char node_value[100] = {};
            sscanf(text + i, "%s", node_value);
            i += strlen(node_value);

            if (tree->status & EMPTY_TREE)
            {
                memcpy(tree->root.value, node_value, strlen(node_value) + 1);
                tree->status &= (~EMPTY_TREE);
                continue;
            }
            if (cur_node->left_child == nullptr)
            {
                cur_node = nodeCtor(cur_node, node_value, cur_node->left_child, 1);
                tree->size ++;
            }
            else
            {
                cur_node = nodeCtor(cur_node, node_value, cur_node->left_child, 0);
                tree->size ++;
            }
        }
        else if (text[i] == '}')
        {
            cur_node = cur_node->parent;
        }
    }

    return 0;
}


int akinator3000(Node *node)
{
    assert(node);

    if (!node->left_child)
    {
        printf("%s\n", node->value);
        if (isRight())
        {
            //тут должна быть дозапись в базу данных
        }

        return 0;

    }
    char buffer = 0;
    printf("%s\nEnter [y]es or [n]o\n", node->value);
    
    while (scanf(" %c", &buffer) == 0 && (buffer != 'y' || buffer != 'n'))
    {
        printf("!!! ERROR: Enter [y]es or [n]o !!!\n");
    }

    return 0;
}


int isRight()
{
    char buffer = 0;

    while (scanf(" %c", &buffer) == 0 && (buffer != 'y' || buffer != 'n'))
    {
        printf("!!! ERROR: Enter [y]es or [n]o !!!\n");
    }

    if (buffer == 'y')
    {
        printf("It was too easy pathetic man\n");
        return 0;
    }

    printf("My stupid creator didn't tell me about it. Are you ready to correct his mistakes?\n");
    return -1;
}
