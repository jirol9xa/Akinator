#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Akin.h"
#include "Tree.h"
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

    createTree(tree);
    Node *cur_node = nullptr;

    for (int i = 0; i < num_symb; i++)
    {
        i += skipSpace(text + i);

        if (text[i] == '{')
        {
            i += skipSpace(text + i + 1);
            char node_value[100] = {};
            sscanf(text + i, "%s", node_value);
            i += strlen(node_value);

            if (cur_node->left_child == nullptr)
            {
                cur_node->left_child = createNode(cur_node, node_value);
            }
            else
            {
                cur_node->right_child = createNode(cur_node, node_value);
            }
        }
        else if (text[i] == '}')
        {
            cur_node = cur_node->parent;
        }
    }
}