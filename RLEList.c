#include "RLEList.h"


int main() {

    // FOR DEBUGGING, ERASE LATER !!
    /*
	RLEList myList = RLEListCreate();
    printf("hello\n");
    RLEListAppend(myList,'W');
    RLEListAppend(myList,'W');
    RLEListAppend(myList,'A');
    RLEListAppend(myList,'A');
    RLEListAppend(myList,'A');
    RLEListAppend(myList,'B');
    RLEListAppend(myList,'B');
    RLEListAppend(myList,'C');
    RLEListAppend(myList,'C');
    printRLEList(myList);
    printf("size: %d\n",RLEListSize(myList));
    RLEListResult myResult = RLE_LIST_SUCCESS;

    printf("Letter at index 7\n");
    printf("Letter: %c\n",RLEListGet(myList,7,&myResult));

    printf("Letter at index 10\n");
    char let = RLEListGet(myList,10,&myResult);
    printf("Letter: %d Result: %i\n",let,myResult);

    printf("Remove index==5\n");
    RLEListRemove(myList,5);
    printRLEList(myList);

    printf("Letter at index 7\n");
    printf("Letter: %c\n",RLEListGet(myList,7,&myResult));

    printf("Remove index==5\n");
    RLEListRemove(myList,5);
    printRLEList(myList);

    printf("Remove index==5\n");
    RLEListRemove(myList,5);
    printRLEList(myList);

    printf("Append A\n");
    RLEListAppend(myList,'A');
    printRLEList(myList);

    printf("Remove index==1\n");
    RLEListRemove(myList,1);
    printRLEList(myList);

    printf("Append A\n");
    RLEListAppend(myList,'A');
    printRLEList(myList);

    printf("Print Export\n");
    char * myExport = RLEListExportToString(myList, &myResult);
    printf("Export: %s, Message: %d\n",myExport, myResult);
    free(myExport);

    printf("Remove index==4\n");
    RLEListRemove(myList,4);
    printRLEList(myList);

    printf("Remove index==1\n");
    RLEListRemove(myList,1);
    printRLEList(myList);

    printf("Letter at index 1\n");
    printf("Letter: %c\n",RLEListGet(myList,1,&myResult));


    printRLEListFullData(myList);

    RLEListDestroy(myList);
     */

	return 0;
}




struct RLEList_t{
    int amount;
    char letter;
    struct RLEList_t* next;
};

//implement the functions here

RLEList RLEListCreate()
{
    RLEList ptr = malloc(sizeof(*ptr));
	if(!ptr) {
		return NULL;
	}
	ptr->amount = 0;
    ptr->letter = '$'; // This way we can differentiate the HEAD
	ptr->next = NULL;
	return ptr;
}

void RLEListDestroy(RLEList list)
{
    while(list) {
		RLEList toDelete = list;
		list = list->next;
		free(toDelete);
	}
}


RLEListResult RLEListAppend(RLEList list, char value)
{
    if (!list || !value) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    RLEList ptr = list;
    while (ptr->next) {
        ptr = ptr->next;
    }

    // SAME CHAR AS CURRENT NODE

    if (ptr->letter == value) {
        ptr->amount = ptr->amount+1;
    }
    // DIFFERENT CHAR FROM CURRENT NODE
    
    else {
        RLEList newNode = RLEListCreate();
        if (!newNode){
            return RLE_LIST_OUT_OF_MEMORY;
        }
        ptr->next = newNode;
        newNode->amount = 1;
        newNode->letter = value;
    }

    return RLE_LIST_SUCCESS;

}


int RLEListSize(RLEList list)
{
    if(!list){
        return -1;
    }
    int count = 0;
    RLEList ptr = list;
     do {
        count += ptr->amount;
        ptr = ptr->next;
    } while (ptr);

     return count;
}

RLEListResult RLEListRemove(RLEList list, int index)
{
    if(!list) {
        return RLE_LIST_NULL_ARGUMENT;
    }
    if(RLEListSize(list)<index) {
        return RLE_LIST_INDEX_OUT_OF_BOUNDS;
    }

    RLEList ptr = list;
    RLEList prev = list;
    int amountLetters = 0;

    while(amountLetters + ptr->amount < index && ptr) {
        amountLetters += ptr->amount;
        prev=ptr;
        ptr = ptr->next;
    }
    ptr->amount = (ptr->amount) - 1;

    if(ptr->amount == 0) {
        RLEListCleanUp(prev);
    }


    return RLE_LIST_SUCCESS;

}

void RLEListCleanUp(RLEList prevNode)
{
    RLEList toDelete = prevNode->next;
    RLEList newNext = toDelete->next;
    prevNode->next = newNext;
    free(toDelete);
}


char RLEListGet(RLEList list, int index, RLEListResult *result)
{
    if(!list) {
        *result =  RLE_LIST_NULL_ARGUMENT;
        return 0;
    }
    if(RLEListSize(list)<index) {
        *result =  RLE_LIST_INDEX_OUT_OF_BOUNDS;
        return 0;
    }

    RLEList ptr = list;
    int amountLetters = 0;
    while(amountLetters + ptr->amount < index && ptr) {
        amountLetters += ptr->amount;
        ptr = ptr->next;
    }
    if(ptr->letter){
        *result =  RLE_LIST_SUCCESS;
        return ptr->letter;
    }
    return 0;

}


char* RLEListExportToString(RLEList list, RLEListResult* result)
{
    if (!list){
        *result = RLE_LIST_NULL_ARGUMENT;
        return NULL;
    }
    // BUGGY!!! If I just have the HEAD ('$'), does it count as a NULL or not? Here I act as if it's not NULL.
    int nodes = countNodes(list->next);

    char* exportStr = malloc(sizeof(char)*((nodes*3)+1)); // BUGGY!!! Where is the free?? Outside? Make Sure of It!
    RLEList ptr = list->next;
    for(int i=0; i<nodes*3;i+=3) {
        exportStr[i]=ptr->letter;
        exportStr[i+1]=ptr->amount+'0';
        exportStr[i+2]='\n';
        ptr=ptr->next;
    }
    exportStr[nodes*3] = '\0';
    *result = RLE_LIST_SUCCESS;
    return exportStr;
}

int countNodes(RLEList list)
{
    RLEList ptr = list;
    int count = 0;
    while(ptr) {
        count++;
        ptr = ptr->next;
    }
    return count;
}



// ----------------------------------------- FOR DEBUGGING !!! -----------------------------------------
// ERASE LATER!!!
void printRLEList(RLEList list)
{
    RLEList ptr = list;
    while(ptr) {
        for(int i=0; i< ptr->amount ;i++) {
            printf("%c",ptr->letter);
        }
        ptr = ptr->next;
    }
    printf("\n");
}

void printRLEListFullData(RLEList list)
{
    printf("Full Info:\n");
    RLEList ptr = list;
    printf("HEAD amount: %d (==0), letter: %c (==$)\n", ptr->amount, ptr->letter);
    while(ptr) {
        printf("Amount: %d Letter: %c\n",ptr->amount, ptr->letter);
        ptr = ptr->next;
    }
    printf("\n");
}

