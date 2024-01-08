#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "helper.h"


#define DEFAULT_SIZE 1


struct intBinaryTree {
    int *items;
    int size;
    int elementCount;
};

struct intBinaryTree CreateBinaryTree() {
    struct intBinaryTree tree = { (int*)calloc(DEFAULT_SIZE, sizeof(int)), DEFAULT_SIZE, 0};
    return tree;
}



int DoubleArraySize(struct intBinaryTree *tree) {
    int newSize = tree->size * 2;
    //Back up pointer in case of failure
    int *temp = tree->items;
    
    //Attempt to reallocate memory for array
    tree->items = realloc(tree->items, newSize * sizeof(int));
    if (tree->items == NULL) {
        printf("Couldn't reallocate additional memory");
        tree->items = temp;
        return 0;
    } else {
        printf("Successfully reallocated additional memory for array.\n");
        tree->size = newSize;
        return 1;
    }

}

int InsertIntoTree(int num, struct intBinaryTree *tree) {
    int numElements = tree->elementCount;
    int insertionSuccess = 1;

    //Expand available memory for tree if it is full
    if (numElements == tree->size) {
        insertionSuccess = DoubleArraySize(tree);
    }

    if (insertionSuccess) {
       tree->items[numElements] = num;
       tree->elementCount++;
       return insertionSuccess; 
    } else {
        return insertionSuccess;
    }
}

int GetLeftChild(int index, struct intBinaryTree *tree) {
    if (((2 * index) + 1) >= tree->size) {
        printf("Child doesn't exist!");
        return -1;
    } else {
        return (tree->items[2*index + 1]);
    }
}

int GetRightChild(int index, struct intBinaryTree *tree) {
    if (((2 * index) + 2) >= tree->size) {
        printf("Child doesn't exist!");
        return -1;
    } else {
        return (tree->items[2*index + 2]);
    }
}

int FindIndexByValue(int val, struct intBinaryTree tree) {
    int index = UnsortedSearch(val, &tree);
    return index;
}

void DeleteByIndex(int index, struct intBinaryTree *tree) {
    if (index >= tree->elementCount || index < 0) {
        printf("Array does not have index %d./n", index);
    } else {
        for (int i = index; i < tree->elementCount - 1; i++) {
            swap(&tree->items[i], &tree->items[i+1]);
        }
        tree->items[tree->elementCount] = rand();
        tree->elementCount--;
        
    }

}

void DeleteByValue(int val, struct intBinaryTree *tree) {
    int indexOfVal = UnsortedSearch(val, tree);
    DeleteByIndex(indexOfVal, tree);
}

//Returns index of value or NULL if nonexistent
//Searches for value specified by val argument.
int UnsortedSearch(int val, struct intBinaryTree *tree)
{
    for (int i = 0; i <= tree->elementCount; i++) {
        if (tree->items[i] == val) {
            return i;
        }
    }
    return -1;
}

//Returns index of the parent of a given node
int FindParent(int childIndex) {

    int parentIndex = 0;

    if (childIndex != 0) {
        parentIndex = (childIndex-1)/2;
    } else {
        parentIndex = -1;
    }
    
    return parentIndex;
}




int main() {

    int number_set[10] = {51, 27, 80, 93, 16, 4, 45, 99, 37, 1};

    struct intBinaryTree currTree = CreateBinaryTree();
    for (int i = 0; i < 10; i++) {
        InsertIntoTree(number_set[i], &currTree);
        printf("%u \n", currTree.items[i]);
        
    }

    DeleteByIndex(1, &currTree);
    DeleteByValue(93, &currTree);
    printf("%d", currTree.items[1]);
    printf("%d", currTree.items[3]);
    

    return 0;
}


