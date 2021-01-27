/*
 @file LinkedList.c
 @author Miriam Snow
 @date November 2017
 @brief File containing the functions of a doubly linked list
 */
#include <stdio.h>
#include <stdlib.h>
#include "LinkedListAPI.h"

Node * initializeNode(void *data){
    Node * n1 = malloc(sizeof(Node));
    n1->data = data;
    n1->next = NULL;
    n1->priorityValue = 0;
    n1->previous = NULL;
    return n1;
}

List * initializeList(void (*printFunction)(void *toBePrinted),void (*deleteFunction)(void *toBeDeleted),int (*compareFunction)(const void *first,const void *second)){
    List * L1 = malloc(sizeof(List));
    L1->head = NULL;
    L1->tail = NULL;
    L1->deleteNode = deleteFunction;
    L1->compare = compareFunction;
    L1->printNode = printFunction;
    return L1;
}

void insertSorted(List *list, void *toBeAdded){
    Node * nodeAdded = malloc(sizeof(Node));
    nodeAdded = (Node*)(toBeAdded);
    Node * curr = list->head;
    Node * temp = NULL;
    int y = -1;
    int x;

    if (list->head == NULL){
        list->head = nodeAdded;
        list->tail = nodeAdded;
    } else {
        while (curr != NULL) {
            x = compare(nodeAdded, curr);
            if (curr->next != NULL){
                y = compare (nodeAdded, curr->next);
            } else {
                y = -1;
            }
             if ((x == 1 && y == -1 )|| (x == 0 && y == -1)){
                temp = curr->next;
                curr->next = nodeAdded;
                nodeAdded->next = temp;

                if (list->tail->next != NULL){
                    list->tail = list->tail->next;
                }

                if (temp != NULL){
                    temp->previous = nodeAdded;
                }
                nodeAdded->previous = curr;
                curr = NULL;
                temp = NULL;
            }
            else if (x == -1){
                nodeAdded->next = curr;
                list->head = nodeAdded;
                curr->previous = nodeAdded;
                curr = NULL;
                temp = NULL;
            }
            else {
                curr = curr->next;
            }
        }
    }
}

void printForward(List *list){
    if (list->head != NULL) {
        Node * temp = list->head;
        while (temp != NULL) {
            printNode(temp->data);
            temp = temp->next;
        }
    }
}

void printBackwards(List *list){
    if (list->tail != NULL) {
        Node * temp = list->tail;
        while (temp != NULL) {
            printNode(temp->data);
            printf("\n");
            temp = temp->previous;
        }
    }
}

int deleteNodeFromList(List *list, void *toBeDeleted){
    Node * nodeDeleted = malloc(sizeof(Node));
    nodeDeleted = (Node*)(toBeDeleted);
    int x;

    if (list->head == NULL){
        return -1;
    } else {
        Node * temp = NULL;
        Node * temp2 = NULL;
        Node * curr = list->head;
        while (curr != NULL){
            x = compare(nodeDeleted->data, curr->data);
            if (x == 0){
                if (nodeDeleted == list->head && nodeDeleted == list->tail){
                    deleteList(list);
                }
                else if (nodeDeleted == list->head){
                    temp = nodeDeleted->next;
                    list->head = temp;
                    temp->previous = NULL;
                    free(nodeDeleted);
                    temp = NULL;
                }
                else if (nodeDeleted == list->tail){
                    temp = nodeDeleted->previous;
                    list->tail = temp;
                    temp->next = NULL;
                    free(nodeDeleted);
                    temp = NULL;
                } else {
                    temp = nodeDeleted->next;
                    temp2 = nodeDeleted->previous;
                    temp2->next = temp;
                    temp->previous = temp2;
                    free(nodeDeleted);
                    curr = NULL;
                }
                return 1;
            }
            curr = curr->next;
        }
        return -1;
    }
}

void insertFront(List *list, void *toBeAdded){
    Node * nodeAdded = malloc(sizeof(Node));
    nodeAdded = (Node*)(toBeAdded);
    Node * temp = NULL;
    if (list->head == NULL){
        list->head = nodeAdded;
        list->tail = nodeAdded;
    }
    else {
        temp = list->head;
        list->head = nodeAdded;
        nodeAdded->next = temp;
        temp->previous = nodeAdded;
    }
}

void insertBack(List *list, void *toBeAdded){
    Node * nodeAdded = malloc(sizeof(Node));
    nodeAdded = (Node*)(toBeAdded);
    if (list->tail == NULL){
        list->head = nodeAdded;
        list->tail = nodeAdded;
    } else {
        Node*temp = malloc(sizeof(Node));
        temp = list->tail;
        list->tail = nodeAdded;
        nodeAdded->previous = temp;
        temp->next = nodeAdded;
        temp = NULL;
    }
}

void deleteList(List * list){
    Node *  temp = list->head;
    Node * curr;
    while (temp != NULL){
        curr = temp->next;
        free(temp);
        temp = curr;
    }
    list->head = NULL;
    list->tail = NULL;
    list = NULL;
}

void *getFromFront(List *list){
    if (list->head != NULL){
        return list->head;
    }
    return NULL;
}

void *getFromBack(List *list){
    if (list->tail != NULL){
        return list->tail;
    }
    return NULL;
}
