#ifndef HW1_ASCIIARTTOOL_H
#define HW1_ASCIIARTTOOL_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RLEList.h"
#include "RLEList.c"


// RECEIVE THREE MANDATORY ARGUMENTS for main()
// - flag:
//          -e : Write picture into target in encoded form
//          -i : Write picture in inverted form.
// - source:
//          Input file containing ASCII ART
// - target:
//          Output file onto which we want to write the result (compressed input or inverted)


/**
* Ascii Art Tool
*
* Implementing interface for reading/writing Ascii pictures that uses RLE.
*
* The following functions are available:
*   asciiArtRead	        - Reads file and compresses it using RLE.
*   asciiArtPrint		    - Writes picture using RLEList into a file.
*   asciiArtPrintEncoded    - Writes compressed picture format (from RLEListExportToString) into file.
*/



/**
* asciiArtRead: Reads file and compresses it using RLE.
*
* @param in_stream - Object of type FILE* containing picture we want to compress.
* @return
* 	List of type RLEList that contains all the characters in the picture.
*/
RLEList asciiArtRead(FILE* in_stream);


/**
* asciiArtPrint: Writes picture using RLEList into a file.
*
* @param list - List of type RLEList containing all characters in picture.
* @param out_stream - Object of type FILE* onto which we write the picture.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function.
* 	RLE_LIST_SUCCESS we have written onto out_stream successfully.
*/
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);


/**
* asciiInvertCharacter: Inverts characters per guidelines.
* Guidelines: [space] -> @ , @ -> [space], [other char] -> [stays the same]
*
* @param value - Ascii value that needs to be inverted.
* @return
* 	Inverted ascii value.
*/
char asciiInvertCharacter(char value);


/**
* asciiArtPrintEncoded: Writes compressed picture format (from RLEListExportToString) into file.
*
* @param list - List of type RLEList containing all characters in picture.
* @param out_stream - Object of type FILE* onto which we write the picture.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function.
* 	RLE_LIST_SUCCESS we have written onto out_stream successfully.
*/
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);


#endif // HW1_ASCIIARTTOOL_H