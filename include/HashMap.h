/*
 @file HashMap.h
 @author Miriam Snow
 @date November 2017
 @brief File containing the function declarations of a hash map
 */
#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "LinkedListAPI.h"

/*
Struct definition of a HashTable Node
*/
typedef struct HNode
{
	int key;
	void * data;
} HNode;

/*
Struct definition of a hashTable
*/
typedef struct HTable HTable;
struct HTable
{
	size_t size;
	List ** table;
	void (*destroyData)(void *data);
	int (*hashFunction)(size_t tableSize, int key);
    void (*printNode)(void *toBePrinted);
};

/**Function to point the hash table to the appropriate functions. Allocates memory to the struct and table based on the size given.
*@return pointer to the hash table
*@param size size of the hash table
*@param hashFunction function pointer to a function to hash the data
*@param destroyData function pointer to a function to delete a single piece of data from the hash table
*@param printNode function pointer to a function that prints out a data element of the table
**/
HTable *createTable(size_t size, int (*hashFunction)(size_t tableSize, int key),void (*destroyData)(void *data),void (*printNode)(void *toBePrinted));

/**Function for creating a node for the hash table.
*@pre Node must be cast to void pointer before being added.
*@post Node is valid and able to be added to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data is a generic pointer to any data type.
*@return returns a node for the hash table
**/
HNode *createNode(int key, void *data);

/** Deletes the entire hash table and frees memory of every element.
*@pre Hash Table must exist.
*@param hashTable pointer to hash table containing elements of data
**/
void destroyTable(HTable *hashTable);

/**Inserts a Node in the hash table.
*@pre hashTable type must exist and have data allocated to it
*@param hashTable pointer to the hash table
*@param key integer that represents the data (eg 35->"hello")
*@param data pointer to generic data that is to be inserted into the list
**/
void insertData(HTable *hashTable, int index, void *data);


/**Function to remove a node from the hash table
 *@pre Hash table must exist and have memory allocated to it
 *@post Node at key will be removed from the hash table if it exists.
 *@param hashTable pointer to the hash table struct
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 **/
void removeData(HTable *hashTable, void * data);

/**Function to return the data from the index given.
 *@pre The hash table exists and has memory allocated to it
 *@param hashTable pointer to the hash table containing data nodes
 *@param key integer that represents a piece of data in the table (eg 35->"hello")
 *@return returns a pointer to the data in the hash table. Returns NULL if no match is found.
 **/
void *lookupData(HTable *hashTable, int index);


//The following functions are user defined functions placed in another .c file. For the purpose of this assignment, that file is called Dictionary.c

/*
Function: hash a node
@param: unsigned long integer value specifying the size of the table
@param: integer value specifying the key
@return: integer value of index in hashtable based on parameters
*/
int hashNode(size_t tableSize,int key);

/*
Function: destroy a node in the hash table
@param: data to be destroyNodeData
@return: no return value, data is destroyed
*/
void destroyNodeData(void *data);

/*
Function: print a node in the hash table
@param: data to be printed
@return: no return value, node is printed
*/
void printNodeData(void *toBePrinted);

/*
Function: print the entire hash map
@param: hash Map
@return: no return value, hashmap is printed
*/
void printTable(HTable * Map);

/*
Function: check to see if specific data exists within a specific hashmap
@param: hashmap
@param: data to find
@return: integer value. 1 if found, 0 if not found
*/
int dataExists(HTable *Map, void * data);

/*
Function: get a file to compare with the hashtable. Checks to see if any of the data in the file matches the data in the hashmap
@param: filename string of file to compare with hashmap
@param: hashmap to compare with file
@return: Integer value of 0 if error with file, or 1 if successful. This function will also print incorrect data and values of correct and incorrect data found.
*/
int compareFile(char * fileName, HTable * H1);

#endif
