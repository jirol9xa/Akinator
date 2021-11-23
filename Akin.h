#ifndef AKIN_H
    #define AKIN_H

    int  readBase(FILE *sorse, Tree *tree);
    int  akinator3000(Node *tree);
    int  isRight();
    int  readNodeValue(char *text, char *dest);
    bool getAnswer();
    int  akinator(Tree *tree);
    int  updateBase(Node *node);
    int  describtion(Tree *tree, const type_t elem);
    int  printPath(Node *node, int is_right);
    int  compare(Tree *tree, type_t elem1, type_t elem2);
    type_t getPath(Node *node, Path *elem_path, int is_right);
    int pathCtor(Path *path);


    
#endif