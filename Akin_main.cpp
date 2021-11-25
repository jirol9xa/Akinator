#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackLib.h"
#include "Tree.h"
#include "logsLib.h"
#include "Akin.h"

#define DEBUG_LVL 0

int main(const int argc, const char ** argv)
{
    Tree tree = {};
    if (argc < 2)
    {
        printf("!!! Can't run without input file !!!\n");
    }
    FILE *sourse = fopen(argv[1], "r");
    
    
    treeCtor(&tree);
    readBase(sourse, &tree);
    fclose(sourse);

    akinator(&tree);

    treeDump(&tree);
    describtion(&tree, "Леха");

    //compare(&tree, "Леха", "Егор");
    
    treeDtor(&tree);
    return 0;
}