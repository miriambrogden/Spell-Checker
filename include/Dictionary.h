/*
 @file Dictionary.h
 @author Miriam Snow
 @date November 2017
 @brief File containing the functions declarations of a dictionary
 */
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "HashMap.h"
#include "LinkedListAPI.h"

/*
Function: generate a key based on the data given. In this case, it is generated based on the ascii value of the first letter of the string given
@param: data to generate key from.
@return: integer value of key
*/
int generateKey(void * data);

/*
Function: remove a newline character from the end of a string
@param: string to have newline character removed
@return: no return value. newline is removed from string
*/
void removeNewline(char line[]);

/*
Function: turn a string into all lowercase characters
@param: string to convert
@return: no return value, string is converted
*/
void makeWordLower(char * word);

/*
Function: get integer input from the user
@param: a string prompt for the user to know what to enter
@param: a maxiumum integer value if required. If not, max is set to 0. Note: this is a character value, not an integer.
@return: proper integer input value from the user
*/
int getInt(char* prompt, char max);

/*
Function: print the menu to the user
@param: no parameters
@return: no return value, menu is printed
*/
void printMenu ();

/*
Function: count the number of nodes in a linked list
@param: list to be counted
@return: integer value of the number of nodes
*/
int count(List * L1);

/*
Function: make sure a string is only letters
@param: string to check
@return: integer value 1 if not all letters, 0 if all letters
*/
int checkString(char * string);

#endif
