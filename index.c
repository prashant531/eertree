/*  
Project:- EERTREE implementation and applications

Authors:- 
    Sahil 2021CSB1128
    Kartik Tiwari 2021CSB1102
    Prashant Singh 2021CSB1124
*/

#include <stdio.h>
#include <malloc.h>
#include <sys/time.h>

#define MAX_SIZE 1000
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define RESET "\x1B[0m"


//  structure of nodes in the tree   
struct node
{
    int start, end;     //starting and ending index of the substring associated with the node
    int len;            //length of the substring associated with the node
    int occ;                //occurrence of the substring associated with the node
    struct node *suffix;    //Suffix link of the node pointing to its longest palindromic suffix
    struct node *label[26];  //Edges between two nodes represented by the latin letters
};
typedef struct node NODE;


// Function to make new node
NODE *new ()
{
    NODE *head = (NODE *)malloc(sizeof(NODE));
    head->start = -1;
    head->end = -1;
    head->len = -1;
    head->occ = 0;
    head->suffix = NULL;
    for (int i = 0; i < 26; ++i)
    {
        head->label[i] = NULL;
    }
    return head;
}

/*
   root1 represnts tree of nodes containing palindromic substrings of odd length
   root2 represnts tree of nodes containing palindromic substrings of even length
   current is longest suffix palindrome of the string in present state
*/

NODE *root1, *root2, *current;
int Suffix[MAX_SIZE + 2];   // stores the number of palinromes ending at any index
int Prefix[MAX_SIZE + 2] = {0};    // stores the number of palinromes starting at any index
NODE *palSuf[MAX_SIZE + 2];   // stores a pointer to the longest suffix palindrome of the substring S[1...i] 


//Function to update EERTREE on addition of a character to the string
int insert(char *s, int pos)
{
    NODE *cur = current;
    int letter = s[pos] - 'a';

    
    //Iterating over suffix links to find node which will point to the the current longest suffix palindrome
    while (1)
    {
        if (pos - 1 - cur->len >= 0 && s[pos - 1 - cur->len] == s[pos])
            break;
        cur = cur->suffix;
    }

    //If the edge already exists between the nodes new node is not created
    
    if (cur->label[letter] != NULL)
    {
        palSuf[pos]=cur->label[letter];
        current = cur->label[letter];
        current->occ++;
        NODE *temp = current->suffix;

        //Occurrence of all suffix palindromes of current string is incremented by 1 
        //by iterating suffix links starting from longest suffix palindrome
        while (temp != root1 && temp != root2)
        {
            temp->occ++;
            temp = temp->suffix;
        }
        return 0;
    }

    //If the node doesn't exist, new node is created with respective parameters
    NODE *t = new ();
    t->len = cur->len + 2;  
    t->end = pos;           
    t->start = pos - t->len + 1;
    cur->label[letter] = t;
    palSuf[pos] = t;
    cur->label[letter]->occ++;

    //if length of new node is 1, suffix link is joined to empty string and current becomes equal to new node
    if (t->len == 1)
    {
        t->suffix = root2;
        current = t;
        Prefix[pos]++;
        Suffix[pos] = 1;
        return 0;
    }

    /*
    This loop finds the longest suffix palindrome of the new node formed 
    and connects it with the new node using suffix link.
    */
    while (1)
    {
        cur = cur->suffix;
        if ((pos - 1 - cur->len) >= 0 && s[pos - 1 - cur->len] == s[pos])
        {
            t->suffix = cur->label[letter];
            break;
        }
    }

    //Updating the Prefix array of all suffix palindromes formed due to addition of character at the end position
    cur = t;
    while (cur->start != -1)
    {
        Prefix[pos - cur->end + cur->start]++;
        cur = cur->suffix;
    }

    current = t;    
    Suffix[pos] = 1 + Suffix[current->suffix->end];  
    

    NODE *temp = current->suffix;
    //Updating the occurrence of all suffix palindromes formed due to addition of character at the end position
    while (temp != root1 && temp != root2)
    {
        temp->occ++;
        temp = temp->suffix;
    }
    return 0;
}


//Function to iterate over the EERTREE and print palindromic substrings
void print(char *s, NODE *head)
{

    if (head != root1 || head != root2)
    {
        //Printing palindromic substring corresponding to head
        for (int i = head->start; i <= head->end; ++i)
        {
            printf("%c", s[i]);
        }
        if (head->start != -1)
            printf("    %d times", head->occ); //Printing occurrence of given node
        printf("\n");
    }
    for (int i = 0; i < 26; ++i)
    {
        if (head->label[i] != NULL)
        {
            print(s, head->label[i]);
        }
    }
}

//Calls print function on roots of both trees
void show(char *s)
{
    print(s, root1);
    print(s, root2);
}

// Function to count distinct palindromes in the string entered by user
int countDistinctPalindromes(NODE *head)
{
    int count = 0;
    for (int i = 0; i < 26; i++)
    {
        if (head->label[i] != NULL)
        {
            count += countDistinctPalindromes(head->label[i]); // Adding up all the palindromes 
        }
    }
    return count + 1;
}

//Function to update EERTREE on deletion of a character to the string
void pop(int pos, char *s)
{
    int letter = s[pos] - 'a';
    Suffix[pos] = 0;
    NODE *cur = current;

    //Updating the Prefix array by decrementing the value at the starting index of all suffix palindromes by 1.
    while (cur->start != -1)
    {
        Prefix[pos - cur->end + cur->start]--;
        cur = cur->suffix;
    }

    /*
        If occurrence of the longest suffix palindrome is 1,
        the edge represented by the first character of this palindrome which 
        is pointing to the longest suffix palindrome is found using suffix links and deleted.
    */
    if (pos > 0 && current->occ == 1)
    {
        cur = palSuf[pos - 1];
        while (1)
        {
            if (pos - 1 - cur->len >= 0 && s[pos - 1 - cur->len] == s[pos])
                break;
            cur = cur->suffix;
        }
        cur->label[letter] = NULL;
    }

    //Decrementing the occurrence of all suffix palindromes created by the last character in the string
    cur = current;
    while (cur->start != -1)
    {
        cur->occ--;
        cur = cur->suffix;
    }

    if (current->occ == 0 && current!=root1 && current!=root2)
    {
        free(current);
    }

    //Updating current pointer
    if (pos > 0)
    {
        current = palSuf[pos - 1];
    }
    else
    {
        current = root2;
    }    
    return;
}

// It will call countPalindrome function on both the trees
int count()
{
    int count1 = countDistinctPalindromes(root1);
    int count2 = countDistinctPalindromes(root2);
    return count1 + count2 - 2;
}

/*
    Implementation of start at Index function
    Returns the number of palindromes starting at that index
*/
int startAtIndex(int pos)
{
    return Prefix[pos];
}

/*
    Implementation of end at Index function
    Returns the number of palindromes ending at that index
*/
int endAtIndex(int pos)
{
    return Suffix[pos];
}

int main()
{
    root1 = new ();
    root1->len = -1;    // Length of imaginary string is -1
    root1->suffix = root1;
    root2 = new ();
    root2->len = 0;     // Length of empty string is 0
    root2->suffix = root1;
    current = root2;    
    
    struct timeval t0, t1;
    long mtime, secs, usecs;
    char str;
    char word[MAX_SIZE];
    char *s = word;
    int i = 0;
    int size = 0;

    while (1)
    {
        printf("\n");
        printf("List: \n");
        printf("1) Press 1 to Insert: \n");
        printf("2) Press 2 for Multipop: \n");
        printf("3) Press 3 to Print: \n");
        printf("4) Press 4 to see no of distinct palindromes: \n");
        printf("5) Press 5 to see no of palindromes ending at certain index: \n");
        printf("6) Press 6 to see no of palindromes starting at certain index: \n");
        printf("7) Press 7 to exit\n");

        int choice;
        printf("Enter your choice : ");
        scanf("%d", &choice);
        fflush(stdin);
        printf("\n");

        switch (choice)
        {
        case 1:
        {            
            printf("Append the string : ");
            //Loop runs till user enters characters and scans them in the string
            while ((str = (char)getchar()) != '\n')
            {
                //If capital letters are inserted, they are changed to small letters.
                if (str >= 'A' && str <= 'Z')
                {
                    str = str + 32;
                }

                word[i] = str;
                ++i;
            }
            gettimeofday(&t0, NULL);

            //Inserting them into tree by calling insert function one by one
            for (int j = size; j < i; ++j)
            {
                insert(s, j);
            }
            gettimeofday(&t1, NULL);
            secs = t1.tv_sec - t0.tv_sec;
            usecs = t1.tv_usec - t0.tv_usec;
            mtime = ((secs)*1000 + usecs / 1000.0) + 0.5;

            //Printing time taken by insert function
            printf(GRN "Time taken : %lf sec\n", mtime / 1000.0);
            printf(RESET);
            size = i;
            break;
        }
        case 2:
        {
            printf("Enter the number of times you want to pop : ");
            int num;
            scanf("%d", &num);
            gettimeofday(&t0, NULL);

            //Calls pop function min(number of times entered by user, length of the string) times
            for (int j = 0; j < num; j++)
            {
                if (i == 0)
                {
                    break;
                }
                pop(i - 1, s);
                i--;
                size--;
            }

            printf(YEL);
            printf(RESET);
            gettimeofday(&t1, NULL);
            secs = t1.tv_sec - t0.tv_sec;
            usecs = t1.tv_usec - t0.tv_usec;
            mtime = ((secs)*1000 + usecs / 1000.0) + 0.5;

            //Printing time taken in performing Multipop
            printf(GRN "Time taken : %lf sec\n", mtime / 1000.0);
            printf(RESET);
            break;
        }
        case 3:
        {
            gettimeofday(&t0, NULL);
            printf("\nString at the given moment : ");
            for (int j = 0; j < i; j++)
            {
                printf("%c", word[j]);
            }
            printf("\n");
            printf("Distinct Palindromes : \n");
            printf(YEL);
            show(s);    //Printing distinct palindromes by calling show function
            printf(RESET);
            gettimeofday(&t1, NULL);
            secs = t1.tv_sec - t0.tv_sec;
            usecs = t1.tv_usec - t0.tv_usec;
            mtime = ((secs)*1000 + usecs / 1000.0) + 0.5;

            //Printing time taken by show function
            printf(GRN "Time taken : %lf sec\n", mtime / 1000.0);
            printf(RESET);
            break;
        }
        case 4:
        {
            gettimeofday(&t0, NULL);
            printf("Total number of distinct palindromes : ");
            printf(YEL);
            printf("%d\n", count());
            printf(RESET);
            gettimeofday(&t1, NULL);
            secs = t1.tv_sec - t0.tv_sec;
            usecs = t1.tv_usec - t0.tv_usec;
            mtime = ((secs)*1000 + usecs / 1000.0) + 0.5;

            //Printing time taken by count function
            printf(GRN "Time taken : %lf sec\n", mtime / 1000.0);
            printf(RESET);
            break;
        }
        case 5:
        {
            printf("Enter the index to see number of palindromes ending at that index : ");
            int index;
            scanf("%d", &index);
            if (index >= i)
            {
                printf("Invalid...Index is greater than length\n");
                continue;
            }

            gettimeofday(&t0, NULL);
            printf("Number of Palindromes ending at Index %d are : ", index);
            printf(YEL);
            printf("%d\n", endAtIndex(index));
            printf(RESET);
            gettimeofday(&t1, NULL);
            secs = t1.tv_sec - t0.tv_sec;
            usecs = t1.tv_usec - t0.tv_usec;
            mtime = ((secs)*1000 + usecs / 1000.0) + 0.5;

            //Printing time taken by endAtIndex function
            printf(GRN "Time taken : %lf sec\n", mtime / 1000.0);
            printf(RESET);
            break;
        }
        case 6:
        {
            printf("Enter the index to see number of palindromes starting at that index : ");
            int index;
            scanf("%d", &index);
            if (index >= i)
            {
                printf("Invalid...Index is greater than length\n");
                continue;
            }
            gettimeofday(&t0, NULL);
            printf("Number of Palindromes starting at Index %d are : ", index);
            printf(YEL);
            printf("%d\n", startAtIndex(index));
            printf(RESET);
            gettimeofday(&t1, NULL);
            secs = t1.tv_sec - t0.tv_sec;
            usecs = t1.tv_usec - t0.tv_usec;
            mtime = ((secs)*1000 + usecs / 1000.0) + 0.5;

            //Printing time taken by startAtIndex function
            printf(GRN "Time taken : %lf sec\n", mtime / 1000.0);
            printf(RESET);
            break;
        }
        case 7:
        {
            exit(1);
        }
        default:
        {
            printf("Please enter valid input\n");
            break;
        }
        }
    }
    return 0;
}
//Contributors-
// Prashant Singh
// Sahil Mangla
// Kartik Tiwari