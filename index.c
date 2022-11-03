#include <stdio.h>
#include <malloc.h>

#define MAX_SIZE 1000

struct node
{
    int start, end;
    int len;
    struct node *suffix;
    struct node *label[26];
};
typedef struct node NODE;

NODE *new ()
{
    NODE *head = (NODE *)malloc(sizeof(NODE));
    head->start = -1;
    head->end = -1;
    head->len = -1;
    head->suffix = NULL;
    for (int i = 0; i < 26; ++i)
    {
        head->label[i] = NULL;
    }
    return head;
}

NODE *root1, *root2, *current;
int Suffix[MAX_SIZE + 2];
int Prefix[MAX_SIZE + 2]= {0};
int occ[MAX_SIZE + 2];

int insert(char *s, int pos)
{
    NODE *cur = current;
    int letter = s[pos] - 'a';

    while (1)
    {
        if (pos - 1 - cur->len >= 0 && s[pos - 1 - cur->len] == s[pos])
            break;
        cur = cur->suffix;
    }
    NODE *t = new ();
    t->len = cur->len + 2;
    t->end = pos;
    t->start = pos - t->len + 1;
    cur->label[letter] = t;

    if (t->len == 1)
    {
        t->suffix = root2;
        current = t;
        Suffix[pos] = 1;
        Prefix[pos]++;
        return 0;
    }

    while (1)
    {
        cur = cur->suffix;
        if ((pos - 1 - cur->len) >= 0 && s[pos - 1 - cur->len] == s[pos])
        {
            t->suffix = cur->label[letter];
            break;
        }
    }
    current = t;
    Suffix[pos] = 1 + Suffix[current->suffix->end];
    Prefix[t->start]++;
    occ[pos]++;
    return 0;
}

void print(char *s, NODE *head)
{
    if (head != root1 || head != root2)
    {
        for (int i = head->start; i <= head->end; ++i)
        {
            printf("%c", s[i]);
        }
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

void show(char *s)
{
    print(s, root1);
    print(s, root2);
}

int countDistinctPalindromes(NODE *head)
{
    int count = 0;
    for (int i = 0; i < 26; i++)
    {
        if (head->label[i] != NULL)
        {
            count += countDistinctPalindromes(head->label[i]);
        }
    }
    return count + 1;
}

int count()
{
    int count1 = countDistinctPalindromes(root1);
    int count2 = countDistinctPalindromes(root2);
    return count1 + count2 - 2;
}

int startAtIndex(int pos)
{
    return Prefix[pos];
}


int endAtIndex(int pos)
{
    return Suffix[pos];
}

int main()
{
    root1 = new ();
    root1->len = -1;
    root1->suffix = root1;
    root2 = new ();
    root2->len = 0;
    root2->suffix = root1;
    current = root2;

    char str;
    char word[MAX_SIZE];
    char *s = word;
    int i = 0;

    while (1)
    {
        printf("List: \n");
        printf("1) Press 1 to Insert: \n");
        printf("2) Press 2 to Print: \n");
        printf("3) Press 3 to see no of distinct palindromes: \n"); 
        printf("4) Press 4 to see no of palindromes ending at certain index: \n");
        printf("5) Press 5 to see no of palindromes starting at certain index: \n");
        printf("6) Press 6 to exit \n");

        int choice;
        printf("Enter your choice : ");
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:
        {
            printf("Append the string : ");
            while ((str = (char)getchar()) != '\n')
            {
                word[i] = str;
                ++i;
            }
            for (int j = 0; j < i; ++j)
            {
                insert(s, j);
            }
            break;
        }

        case 2:
        {   printf("\nString at the given moment : ");
            for(int j=0;j<i;j++)
            {
                printf("%c",word[j]);
            }
            printf("\n");
            printf("Distinct Palindromes : \n");
            show(s);
            break;
        }
        case 3:
        {
            printf("Total number of distinct palindromes : %d\n",count());
            break;
        }
        case 4:
        {
            printf("Enter the index to see number of palindromes ending at that index : ");
            int index;
            scanf("%d",&index);
            printf("Number of Palindromes ending at Index %d are : %d\n",index,endAtIndex(index));
            break;
        }
        case 5:
        {
            printf("Enter the index to see number of palindromes starting at that index : ");
            int index;
            scanf("%d",&index);
            printf("Number of Palindromes starting at Index %d are : %d\n",index,startAtIndex(index));
            break;
            
        }
        case 6:
        {
            exit(1);
        }
        default:
        {
            // for (int j = 0; j < i; j++)
            // {
            //     printf("%d ", endAtIndex(j));
            // }
            printf("Please Enter valid input\n");
            break;
        }
        }
    }

    // show(s);

    return 0;
}
