# eertree
CS201 project - EERTree implementation

This project implements an EERTREE, an online, linear-size graph based data structure which provides quick access to all the palindromic substrings of a string. This structure inherits some ideas from the construction of both the suffix trie and suffix tree. Using this data structure, we then present efficient solutions of a number of palindrome related problems such as insertion into the
tree, deletion of characters, printing distinct palindromes and their number of occurences in the strings and number of palindromes ending or starting from a given index.

The functions implemented here using this data structure are :
1. Insert() - appends a given string into the eertree
2. Multipop() - removes characters from the string and accordingly, nodes from the eertree
3. Print() - prints all the distinct palindromes and their respective occurrences
4. StartAtIndex() - prints number of distinct palindromes starting at that index
5. EndAtIndex() - prints number of distinct palindromes ending at that index