#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logsLib.h"
#include "Tree.h"
#include <assert.h>


Node *nodeCtor(Node *parent, type_t value, Node *new_node, int is_left)
{
    assert(parent);

    new_node = (Node *) calloc(1, sizeof(Node));

    new_node->parent      = parent;
    new_node->left_child  = nullptr;
    new_node->right_child = nullptr;
    new_node->value       = (char *) calloc(128, sizeof(char));
    memcpy(new_node->value, value, strlen(value) + 1);

    if (is_left) 
        parent->left_child  = new_node;
    else         
        parent->right_child = new_node;

    return new_node; 
}


int treeCtor(Tree *tree)
{
    assert(tree);

    tree->root.value  = (char *) calloc(32, sizeof(char));
    tree->root.parent = nullptr;
    tree->size = 1;
    tree->status |= EMPTY_TREE;
    return 0;
}


void treeDump(Tree *tree)
{
    assert(tree);
     
    openLogs("LOGS/logs.dot");  
    writeLogs("digraph G{\n");

    printNode(&(tree->root));

    writeLogs("}\n");

    closeLogs();

    system("dot -T png LOGS/logs.dot -o pic.png");
    system("eog pic.png");
}


void printNode(Node *node)
{
    assert(node);
    
    writeLogs("    elem_%x[style = \"filled\", fillcolor = \"green\", label = \"%s\"];\n", node, node->value);

    if (node->left_child)
    {
        printNode(node->left_child);
        writeLogs("    elem_%x -> elem_%x [label = \"YES\", color = \"green\"];\n", node, node->left_child);
    }
    
    if (node->right_child)
    {
        printNode(node->right_child);
        writeLogs("    elem_%x -> elem_%x [label = \"NO\", color = \"red\"];\n", node, node->right_child);
    }
}


int treeDtor(Tree *tree)
{
    assert(tree);

    nodeDtor(&(tree->root));
    free(tree->root.value);

    tree->size = -1;
    tree->status |= DESTRUCTED_TREE;

    return 0;
}


int nodeDtor (Node *node)
{
    assert(node);

    if (node->left_child)
    {
        nodeDtor(node->left_child);
        free(node->left_child->value);    
        free(node->left_child);
    }

    if (node->right_child)
    {
        nodeDtor(node->right_child);
        free(node->right_child->value);
        free(node->right_child);
    }

    return 0;
}


int saveTree(Tree *tree)
{
    assert(tree);

    openLogs("Base");
    writeLogs("{%s", tree->root.value);

    if (tree->root.left_child)
    {
        saveNode(tree->root.left_child);
    }
    if (tree->root.right_child)
    {
        saveNode(tree->root.right_child);
    }

    writeLogs("}");
    closeLogs();

    return 0;
}


int saveNode(Node *node)
{
    assert(node);

    writeLogs("{%s", node->value);

    if (node->left_child)
    {
        saveNode(node->left_child);
    }
    if (node->right_child)
    {
        saveNode(node->right_child);
    }

    writeLogs("}");

    return 0;
}


Node *searchElem(Node *node, type_t elem)
{
    assert(node);
    assert(elem);

    if (strcmp(node->value, elem))
    {
        if (node->left_child)
        {
            Node *elem_ptr = nullptr;
            if (elem_ptr = searchElem(node->left_child, elem))
            {
                return elem_ptr;
            }
            if (elem_ptr = searchElem(node->right_child, elem))
            {
                return elem_ptr;
            }
        }
    }
    else
    {
        return node;
    }

    return nullptr;
}
