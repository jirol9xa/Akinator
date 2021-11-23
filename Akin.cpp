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

    if (tree->status & DESTRUCTED_TREE)
    {
        printf("!!! ERROR Can't work with destructed tree\n");
        return -1;
    }

    long int file_length = 0;
    fileLength(&file_length, sourse);

    char *text = (char *) calloc(file_length + 1, sizeof(char));
    long int num_symb = fread(text, sizeof(char), file_length, sourse);

    text[num_symb] = '\0';

    assert(text);

    treeCtor(tree);
    Node *cur_node = &(tree->root);
    PRINT_LINE;

    for (int i = 0; i < num_symb; i++)
    {
        i += skipSpace(text + i);

        if (text[i] == '{')
        {
            i += (text[i] != '\0');
            i += skipSpace(text + i);
            char *node_value = nullptr;
            node_value = (char *) calloc(1000, sizeof(char));
            assert(node_value);

            i += readNodeValue(text + i, node_value);

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
    PRINT_LINE;
    return 0;
}


int akinator(Tree *tree)
{
    assert(tree);
    if (tree->status & DESTRUCTED_TREE)
    {
        printf("!!! ERROR Can't work with destructed tree\n");
        return -1;
    }
    
    tree->status |= akinator3000(&(tree->root));

    if (tree->status & UPDATED_TREE)
    {
        PRINT_LINE;
        saveTree(tree);
    }

    return 0;
}


int akinator3000(Node *node)
{
    assert(node);

    if (!node->left_child)
    {
        printf("%s\n", node->value);
        printf("Is that right?\n");
        printf("Enter [y]es or [n]o\n");
        if (isRight())
        {
            updateBase(node);
            return UPDATED_TREE;
        }

        return 0;

    }

    printf("%s\nEnter [y]es or [n]o\n", node->value);
    bool is_yes = isYes();
    int tree_status = 0;

    if (is_yes) tree_status += akinator3000(node->left_child);
    else tree_status += akinator3000(node->right_child);

    return tree_status;
}


int isRight()
{
    bool is_yes = isYes();

    if (is_yes)
    {
        printf("It was too easy pathetic human\n");
        return 0;
    }

    printf("My stupid creator didn't tell me about it. Are you ready to correct his mistakes?\n");
    return 1;
}


int readNodeValue(char *text, char *dest)
{
    assert(text);

    int i = 0;

    for (; text[i] != '{' && text[i] != '}' && text[i] != '\0'; i++)
    {
        dest[i] = text[i];
    }

    i --;
    return i;
}


bool isYes()
{
    char buffer[32] = {};

    scanf("%s", buffer);
    eatInputBuff();

    while (strcmp(buffer, "yes") && strcmp(buffer, "no") && !((strlen(buffer) == 1) && (buffer[0] == 'y' || buffer[0] == 'n')))
    {
        printf("!!! ERROR: Enter [y]es or [n]o !!!\n");
        scanf("%s", buffer);
        eatInputBuff();
    }

    return (buffer[0] == 'y') ? true : false;
}


int updateBase(Node *node)
{
    assert(node);

    char new_node_value[32] = {};
    Node *prnt = node->parent;

    printf("What word did you think of?\n");
    GetLine(new_node_value);

    char difference[32] = {};
    printf("How does a(an) %s differ from a(an) %s?\n", new_node_value, node->value);
    GetLine(difference);
    

    bool is_left = (prnt->left_child == node);
    Node *diff = nodeCtor(prnt, difference, (is_left) ? prnt->left_child : prnt->right_child, is_left);

    nodeCtor(diff, new_node_value, diff->left_child, 1);
    diff->right_child = node;

    return 0;
}
