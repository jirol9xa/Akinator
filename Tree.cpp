#include <stdio.h>
#include <stdlib.h>
#include "logsLib.h"
#include "Tree.h"
#include <assert.h>


Node *createNode(Node *parent, type_t value)
{
    assert(parent);

    Node new_node = {};

    new_node.parent      = parent;
    new_node.left_child  = nullptr;
    new_node.right_child = nullptr;
    new_node.value       = value;

    return &new_node; 
}


int createTree(Tree *tree)
{
    assert(tree);

    tree->root = {};
    tree->size = 1;
    return 0;
}


void treeDump(Tree *tree)
{
    assert(tree);
    
    openLogs("LOGS/logs.dot");
    writeLogs("digraph G{\n    rankdir = LR\n");

    printNode(&(tree->root));

    writeLogs("}\n");

    closeLogs();

    system("dot -T png LOGS/logs.dot -o pic.png");
    system("eog pic.png");
}


void printNode(Node *node)
{
    assert(node);

    writeLogs("    elem_%x[color = blue shape = record, label = \" %s | parent <prnt%x> " 
             "| {<l_child%x> left child | <r_child%x> right child} \" ];\n", node, node->value, node, node, node);

    if (node->parent == nullptr)
    {
        printNode(node->left_child);
        writeLogs("    elem_%x:<l_child%x> -> elem_%x:<prnt%x>;\n", node, node, node->left_child, node->left_child);
        printNode(node->right_child);
        writeLogs("    elem_%x:<r_child%x> -> elem_%x:<prnt%x>;\n", node, node, node->right_child, node->right_child);
    }
}