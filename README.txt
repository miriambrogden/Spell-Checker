Student Name: Miriam Snow
Date: November 14, 2017

Description of the Assignment:
This program simulates a spell checker. Words for the dictionary are recieved through a text file at the beginning of the program, and can also be entered and removed by the user while the program is running. All words in the dictionary are placed in a hashmap. All words in the dictionary can be outputed to the user as well as their index and key in the hashmap. The user can also spell check a file by comparing an alternate file with the current dictionary to find out how many words are spelled correctly and inccorectly in the file. TestMain.c tests the functions corresponding to HashMap.h

How to Run the Program:
To run the main program, begin by downloading a .txt file with the dictionary information. Example files are in the docs directory. Then, type "make main" into the command line and execute the program by typing "./bin/runme insertpath/filename.txt". For example, to run the program with the first file in the docs folder, type "./bin/runme docs/file1.txt". Follow the prompts as they show up on the screen. The main menu will only accept integers 1-5.
To run the TestMain.c program, type "make test" then execute the program by typing "./bin/testme".
Type "make clean" to remove all files in the bin directory.

Hash function and collision resultion strategy:
My hash strategy takes the first letter of a word and generates a key based on the upper case ascii value of that letter. It then generates an index by computing key%sizeOfTable. Each index in the hashmap contains a linked list which has Nodes that each contain a HashNode as their data. Within HashNode is the word and the key of the word. Each linked list at each index will contain all the words in the dictionary that have the same letter. This speeds up the search because instead of searching through the entire dictionary each time, we can just search the linked list at the generated index value.

Assumptions or limitations: File input must have each individual word on a separate line and only contain letters.
