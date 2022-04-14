#include "RLEList.h"


int main() {
    /*
    // FOR DEBUGGING, ERASE LATER !!
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

    printf("Remove index==5\n");
    RLEListRemove(myList,5);
    printRLEList(myList);

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

    printf("Remove index==4\n");
    RLEListRemove(myList,4);
    printRLEList(myList);

    printf("Remove index==1\n");
    RLEListRemove(myList,1);
    printRLEList(myList);

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

