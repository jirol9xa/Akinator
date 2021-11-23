#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "stackLib.h"
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

    Node *cur_node = &(tree->root);

    for (int i = 0; i < num_symb; i++)
    {
        i += skipSpace(text + i);

        if (text[i] == '{')
        {
            i += (text[i] != '\0');
            i += skipSpace(text + i);
            char *node_value = nullptr;
            node_value = (char *) calloc(128, sizeof(char));
            assert(node_value);

            i += readNodeValue(text + i, node_value);

            if (tree->status & EMPTY_TREE)
            {
                memcpy(tree->root.value, node_value, strlen(node_value) + 1);
                tree->status &= (~EMPTY_TREE);
                free(node_value);
                continue;
            }
            if (cur_node->left_child == nullptr)
            {
                cur_node = nodeCtor(cur_node, node_value, cur_node->left_child, 1);
                tree->size ++;
            }
            else
            {
                cur_node = nodeCtor(cur_node, node_value, cur_node->right_child, 0);
                tree->size ++;
            }

            free(node_value);
        }
        else if (text[i] == '}')
        {
            cur_node = cur_node->parent;
        }
    }

    free(text);
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
    bool is_yes = getAnswer();
    int tree_status = 0;

    if (is_yes) tree_status += akinator3000(node->left_child);
    else tree_status += akinator3000(node->right_child);

    return tree_status;
}


int isRight()
{
    bool is_yes = getAnswer();

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


bool getAnswer()
{
    char buffer[5] = {};

    scanf("%4s", buffer);
    eatInputBuff();

    // todo: слишком длинная проверка, нужно кроче
    while (strcmp(buffer, "yes") && strcmp(buffer, "no") && !((strlen(buffer) == 1) && (buffer[0] == 'y' || buffer[0] == 'n')))
    {
        printf("!!! ERROR: Enter [y]es or [n]o !!!\n");
        scanf("%4s", buffer);
        eatInputBuff();
    }

    return buffer[0] == 'y';
}


int updateBase(Node *node)
{
    assert(node);

    char new_node_value[128] = {};
    Node *prnt = node->parent;

    printf("What word did you think of?\n");
    GetLine(new_node_value);

    char difference[256] = {};
    printf("How does a(an) %s differ from a(an) %s?\n", new_node_value, node->value);
    GetLine(difference);
    

    bool is_left = (prnt->left_child == node);
    Node *diff = nodeCtor(prnt, difference, is_left ? prnt->left_child : prnt->right_child, is_left);

    nodeCtor(diff, new_node_value, diff->left_child, 1);
    diff->right_child = node;

    return 0;
}


int describtion(Tree *tree, const type_t elem)
{
    assert(tree);
    assert(elem);


    Node *search_result = searchElem(&(tree->root), elem);

    if (search_result)
    {
        printPath(search_result->parent, search_result == search_result->parent->right_child);
        printf("\nIt's all about %s\n", search_result->value);

        return 0;
    }

    printf("A node with this value was not found\n");
    return 0;

}


int printPath(Node *node, int is_right)
{
    assert(node);

    if (node->parent)
    {
        printPath(node->parent, node == node->parent->right_child);
    }

    if (is_right) printf("не ");
    for (size_t i = 0; node->value[i] != '?' && i < strlen(node->value); i++)
    {
        putchar(node->value[i]);
    }
    printf(", ");

    return 0;
}


int compare(Tree *tree, type_t elem1, type_t elem2)
{
    assert(tree);

    Node *elem1_ptr = searchElem(&(tree->root), elem1);
    Node *elem2_ptr = searchElem(&(tree->root), elem2);

    if (!elem1_ptr)
    { 
        printf("!!! ERROR %s wasn't found in base. Can't compare !!!\n", elem1);
        return -1;
    }
    if (!elem2_ptr) 
    {
        printf("!!! ERROR %s wasn't found in base. Can't compare !!!\n", elem2);
        return -1;
    }

    Path elem1_path = {};
    getPath(elem1_ptr, &elem1_path, elem1_ptr == elem1_ptr->parent->right_child);
    Path elem2_path = {};
    getPath(elem2_ptr, &elem2_path, elem2_ptr == elem2_ptr->parent->right_child);

    for (int i = 0; i < elem1_path.size; i++)
    {
        printf("%s ", elem1_path.path[i]);
    }

    return 0;
}


int printCompare(Node *elem1_ptr, int is_right1, Node *elem2_ptr, int is_right2, int same)
{
    assert(elem1_ptr);
    assert(elem2_ptr);

    //if (node->)


    return 0;
}


type_t getPath(Node *node, Path *elem_path, int is_right)
{
    assert(node);
    assert(elem_path);

    if (node->parent)
    {
        elem_path->size ++;
        getPath(node->parent, elem_path, node == node->parent->right_child);
    }

    if (!node->parent)
    {
        pathCtor(elem_path);
    }

    if (is_right)
    {
        char *buffer = (char *) calloc(260, sizeof(char));
        strcpy(buffer, "не ");
        strcat(buffer, node->value);
        printf("%s\n", buffer);
        //printf("%s\n", elem_path->path[elem_path->iterator]);
        memcpy(elem_path->path[elem_path->iterator ++], buffer, strlen(buffer));
        free(buffer);
        return elem_path->path[elem_path->iterator - 1];
    }

    memcpy(elem_path->path[elem_path->iterator ++], node->value, strlen(node->value));

    return node->value;
}


int pathCtor(Path *path)
{
    assert(path);

    path->path = (type_t *) calloc(path->size, sizeof(type_t));
    for (int i = 0; i < path->size; i++)
    {
        path->path[i] = (type_t) calloc(260, sizeof(char));
    }
    return 0;
}