#include "RLEList.h"


int main() {
	RLEList head = RLEListCreate();
    RLEListDestroy(head);

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
    ptr->letter = 'A';
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