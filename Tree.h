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
    struct Path
    {
        type_t *path;
        int    size;
        int    iterator;
    };
    


    enum StatAndErrs
    {
        EMPTY_TREE      = 1 << 0,
        UPDATED_TREE    = 1 << 1,
        DESTRUCTED_TREE = 1 << 2,
    };

    Node *nodeCtor (Node *parent, type_t value, Node *new_node, int is_left);
    int   treeCtor (Tree *tree);
    void  treeDump (Tree *tree);
    void  printNode(Node *node);
    int   treeDtor (Tree *tree);
    int   nodeDtor (Node *node);
    int   saveTree(Tree *tree);
    int saveNode(Node *node);
    Node *searchElem(Node *node, type_t elem);

#endif