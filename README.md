# EERTree
CS201 project - EERTree implementation

## Team members
Sahil - 2021CSB1128
Prashant Singh - 2021CSB1124
Kartik Tiwari - 2021CSB1102

## Teaching Assistant
Sravanthi Chede

## EERTREE Implementation as a part of CS201(DSA) project.
This project implements an EERTREE, an online, linear-size graph based data structure which provides quick access 
to all the palindromic substrings of a string. This structure inherits some ideas from the construction of both the
suffix trie and suffix tree. Using this data structure, we then present efficient solutions of a number of palindrome 
related problems such as insertion into the tree, deletion of characters, printing distinct palindromes and their number 
of occurences in the strings and number of palindromes ending or starting from a given index.

## Functions Implemented - 
1. Insert() - appends a given string into the eertree
2. Multipop() - removes characters from the string and accordingly, nodes from the eertree
3. Print() - prints all the distinct palindromes and their respective occurrences
4. Count() - counts number of distinct palindromes 
5. StartAtIndex() - prints number of distinct palindromes starting at that index
6. EndAtIndex() - prints number of distinct palindromes ending at that index


## Average Time Complexity of Operations :
1. Insert : O(nlogσ)  where σ is number of distinct characters in the string
2. Pop : O(n)
3. Print : O(n)
4. Count : O(n)
5. StartAtIndex : O(1)
6. EndAtIndex : O(1)

## How to run the program
The program can be compiled and run directly in the terminal using gcc.

## Expected inputs and outputs
First the program will ask the user to enter which function user wants to perform:
1-Insert, 2-Multipop, 3-Print all unique palindromes, 4-Print No. of unique palindromes, 
5-Print No. of palindromes ending at desired index, 6-Print No. of palindromes starting at desired index,
7-To exit the program

The program will then ask about further specifications to perform functions like desired index in case 5 and 6 
and number of time to perform pop in case 2.

Desired Output will be printed followed by the time taken by the program to run the function.

The program will keep on asking user's choice to perform above mentioned function until the user hits 7 to exit the program.

