//
// Created by Assaf on 07/03/2022.
//

#ifndef HW1_RLELIST_H
#define HW1_RLELIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
* Run Length Encoding List
*
* Implements an RLE list containing a sequence of characters.
*
* The following functions are available:
*   RLEListCreate	        - Creates a new empty RLE list.
*   RLEListDestroy		    - Deletes an existing RLE list and frees all its resources.
*   RLEListAppend           - Appends a character to the end of the list.
*   RLEListSize		        - Returns the total number of characters a given RLE list holds.
*   RLEListRemove	        - Removes a character at a given index in the list.
*   RLEListGet              - Returns the character found at a given index.
*   RLEListExportToString   - Returns a string of all the characters in the RLE list.
*   RLEListMap              - Transforms the list by applying a given function to each character in the list.
*/


/** 
* Typedef for defining the RLE list.
* Complete the implementation of struct RLEList_t defined in RLEList.c
*/
typedef struct RLEList_t *RLEList;

/** Enum used for returning error codes from RLE list functions */
typedef enum {
    RLE_LIST_SUCCESS,
    RLE_LIST_OUT_OF_MEMORY,
    RLE_LIST_NULL_ARGUMENT,
    RLE_LIST_INDEX_OUT_OF_BOUNDS,
    RLE_LIST_ERROR
} RLEListResult;


/** 
 * Type of function for mapping characters.
 * This function should accept a character in the list and return the mapped character
 */
typedef char (*MapFunction)(char);


/**
* RLEListCreate: Allocates a new empty RLE list.
*
* The function allocates and returns a new RLEList struct containing a list with no characters.
* Note that the user must free the returned list using RLEListDestroy() once it is no longer needed.
*
* @return
* 	NULL if allocations failed.
* 	A new RLEList in case of success.
*/
RLEList RLEListCreate();


/**
* RLEListDestroy: Deallocates an existing RLE list.
*
* @param list - RLE list to be deallocated. If RLE list is NULL nothing will be done
*/
void RLEListDestroy(RLEList list);


/**
*   RLEListAppend: add a specified character at the end of the list.
*
* @param list - The RLE list for which to add the character
* @param value - The character which needs to be added.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
* 	RLE_LIST_OUT_OF_MEMORY if an allocation failed
* 	RLE_LIST_SUCCESS if the character has been inserted successfully
*/
RLEListResult RLEListAppend(RLEList list, char value);

/**
*   RLEListAppend_aux: Adds value to list.
*
* @param finalPtr - The final node in the list.
* @param value - The character which needs to be added.
* @return
* 	RLE_LIST_OUT_OF_MEMORY if an allocation failed
* 	RLE_LIST_SUCCESS if the character has been inserted successfully
*/
RLEListResult RLEListAppend_aux(RLEList finalPtr, char value);


/**
* RLEListSize: Returns the total number of characters in an RLE list.
* @param list - The RLE list whose size is requested
* @return
* 	-1 if a NULL pointer was sent.
* 	Otherwise the total number of characters in the list.
*/
int RLEListSize(RLEList list);


/**
*   RLEListRemove: Removes a character found at a specified index in an RLE list.
*
* @param list - The RLE list to remove the character from.
* @param index - The index at which the character to be removed is found.
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	RLE_LIST_SUCCESS the character found at index has been removed successfully.
*/
RLEListResult RLEListRemove(RLEList list, int index);



/**
*   RLEListCleanUp: Cleans up a node that has been emptied out
*
* @param prevNode - The node before the one that has just been emptied.
*/
void RLEListCleanUp(RLEList prevNode);


/**
*   RLEListGet: Returns the character found at a specified index in an RLE list.
*
* @param list - The RLE list to retrieve the character from.
* @param index - The index at which the character to be retrieved is found.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	RLE_LIST_INDEX_OUT_OF_BOUNDS if given index is not withing the list's bounds.
* 	LIST_SUCCESS the character found at index has been retrieved successfully.
* @return
* 	0 if result is not RLE_LIST_SUCCESS.
* 	The character found at given index in case of success.   
*/
char RLEListGet(RLEList list, int index, RLEListResult *result);


/**
*   RLEListExportToString: Returns the characters found in an RLE list as a string.
*
* @param list - The RLE list to be exported as a string.
* @param result - Pointer to be used to store the result of the operation, if it is NULL, the result will not be saved.
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent to the function as list.
* 	LIST_SUCCESS the RLE list has been successfuly exported as a string.
* @return
* 	NULL if result is not RLE_LIST_SUCCESS.
* 	The string that corresponds to the received RLE list.
*/
char* RLEListExportToString(RLEList list, RLEListResult* result);

/**
*   RLEListExportToString_aux: Creates export string for RLEListExportToString().
*
* @param exportStr - The string on which the necessary characters are added.
* @param ptr - Pointer to list from which the input to the exportStr is taken from.
* @param digits - The amount of digits in the 'amount' attribute of each node in the list.
* @param nodes - Amount of nodes in the list (not including HEAD).
* @param digitCount - Total amount of digits summed from all nodes's 'amount' attribute.
*/
void RLEListExportToString_aux(char* exportStr, RLEList ptr, int digits[], int nodes, int digitCount);


/**
*   countNodes: Returns the amount of nodes in list.
*
* @param list - The RLE list whose nodes we count.
* @return
* 	Amount of nodes.
*/
int countNodes(RLEList list);

/**
*   countDigits: Counts the amount of digits of the amount attribute of each node.
*
* @param list - The RLE list whose quantity of digits in 'amount' attribute we count.
* @param arr - The array were we fill the amount of digits in the 'amount' attribute of the node.
 *              Each index corresponds to the appropriate node from the list.
* @return
* 	Total amount of digits counted summed from the 'amount' attribute of all the nodes in the list.
*/
int countDigits(RLEList list, int arr[]);


/**
*   calcPow: Calculates a^b;
*
* @param a - The base.
* @param b - The exponent.
* @return
* 	a^b
*/
int calcPow(int a, int b);


/**
*   RLEListMap: Change the given RLE list's characters according to the received mapping function.
*               This function replaces each character of the give RLE list with its mapped character.
*
* @param list - The RLE list to edit.
* @param MapFunction - Pointer to a function of type MapFunction. 
* @return
* 	RLE_LIST_NULL_ARGUMENT if a NULL was sent as a paramater.
* 	LIST_SUCCESS if the mapping is done successfully.
*/
RLEListResult RLEListMap(RLEList list, MapFunction map_function);


#endif // HW1_RLELIST_H
