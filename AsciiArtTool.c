
#include "AsciiArtTool.h"


RLEList asciiArtRead(FILE* in_stream)
{
    RLEList asciiList = RLEListCreate();

    if (in_stream == NULL){
        return NULL; //could not open file
    }

    char tmpChar;
    while ((tmpChar = fgetc(in_stream)) != EOF) {
        RLEListAppend(asciiList, tmpChar);
     }


    return asciiList;

}


RLEListResult asciiArtPrint(RLEList list, FILE *out_stream)
{
    if(!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList ptr = list;
    while(ptr) {
        for(int i=0; i< ptr->amount ;i++) {
            if(ptr->letter == ' '){
                fputc ('@', out_stream);
            } else if(ptr->letter == '@'){
                fputc (' ', out_stream);
            } else {
               fputc (ptr->letter, out_stream);
            }
        }
        ptr = ptr->next;
    }
    return RLE_LIST_SUCCESS;
}


RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream)
{
    if (!list || !out_stream) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEListResult result;
    char * encoded = RLEListExportToString(list,&result);
    if (result != RLE_LIST_SUCCESS) {
        return result;
    }
    int writeResult = fputs(RLEListExportToString(list,&result), out_stream);
    if (result != RLE_LIST_SUCCESS) {
        return result;
    }
    if (writeResult == EOF) {
        // CHECK what happens for empty list
        return RLE_LIST_ERROR;
    }
    free(encoded);
    return result;
}

