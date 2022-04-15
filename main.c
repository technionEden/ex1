#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RLEList.h"
#include "AsciiArtTool.h"

int checkMainInput(int argc, char **argv);

// RECEIVE THREE MANDATORY ARGUMENTS
// - flag:
//          e : Write picture into target in encoded form
//          i : Write picture in inverted form. [space] -> @ , @ -> [space], [other char] -> 'stays the same'
// - source:
//          Input file containing ASCII ART
// - target:
//          Output file onto which we want to write the result (compressed input or inverted)

int main(int argc, char **argv)
{
    if (!checkMainInput(argc,argv)) {
        return 0;
    }


    return 0;
    
}

int checkMainInput(int argc, char **argv)
{
    if (argc != 3) {
        return 0;
    }

    if(strcmp(argv[0],"-e")!=0 && strcmp(argv[0],"-i")!=0) {
        return 0;
    }
    // TODO: check other arguments too
    return 1;
}