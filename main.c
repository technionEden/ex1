#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RLEList.h"
#include "AsciiArtTool.h"
#include "AsciiArtTool.c"

int checkMainInput(int argc, char **argv);

// RECEIVE THREE MANDATORY ARGUMENTS
// - flag:
//          -e : Write picture into target in encoded form
//          -i : Write picture in inverted form. [space] -> @ , @ -> [space], [other char] -> 'stays the same'
// - source:
//          Input file containing ASCII ART
// - target:
//          Output file onto which we want to write the result (compressed input or inverted)


// ./output -e dog.txt output.txt
int main(int argc, char **argv)
{
    
    if (!checkMainInput(argc,argv)) {
        return 0;
    }


    // READ
    FILE *readFile;
    readFile = fopen(argv[2], "r");
    RLEList asciiList = asciiArtRead(readFile);

    // WRITE

    if(!strcmp(argv[1],"-e")) {
        // WRITE - ENCODED
        FILE *writeFile = fopen(argv[3], "w");
        asciiArtPrintEncoded(asciiList, writeFile);
        fclose(writeFile);
    } else {
        // WRITE - INVERTED
        FILE *appendFile = fopen(argv[3], "a");
        asciiArtPrint(asciiList, appendFile);
        fclose(appendFile);
    }




    // CLOSE/FREE

    fclose(readFile);
    RLEListDestroy(asciiList);
    

    return 0;
    
}

int checkMainInput(int argc, char **argv)
{
    if (argc != 4) {
        printf("Didn't enter 3 arguments, entered %d\n", argc);
        for(int i=1; i<argc; i++){
            printf("%s",argv[i]);
        }
        printf("\n");
        return 0;
    }

    if(strcmp(argv[1],"-e")!=0 && strcmp(argv[1],"-i")!=0) {
        printf("Not appropriate flag\n");
        return 0;
    }
    // TODO: check other arguments too
    return 1;
}