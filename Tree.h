#ifndef TREE_H
    #define THEE_H

    typedef char *type_t;
    struct Node 
    {
        type_t value;
        Node *left_child;
        Node *right_child;
        Node *parent;
    };
    struct Tree
    {
        Node root;
        int size;
    };
    

    Node *createNode(Node *parent, type_t value);
    int   createTree(Tree *tree);
    void treeDump(Tree *tree);
    void printNode(Node *node);
    
#endif