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
        int status;
    };


    enum StatAndErrs
    {
        EMPTY_TREE = 1 << 0,
    };

    Node *nodeCtor (Node *parent, type_t value, Node *new_node, int is_left);
    int   treeCtor (Tree *tree);
    void  treeDump (Tree *tree);
    void  printNode(Node *node);
    int   treeDtor (Tree *tree);
    int   nodeDtor (Node *node);
    
#endif