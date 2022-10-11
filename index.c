#include<stdio.h>
#include<malloc.h>

#define MAX_SIZE 1000
int Idx = 0;
struct node {
    int start, end;
    int len;
    struct node* suffix;
    struct node* label[MAX_SIZE][26];
    int boolean[1000];
};

typedef struct node NODE;

NODE* new() {
    NODE* head = (NODE*)malloc(sizeof(NODE));
    head->start = -1; head->end = -1; head->len = -1;
    head->suffix = NULL;
    for(int j = 0; j < MAX_SIZE; ++j) for(int i = 0; i < 26; ++i) {
        head->label[j][i] = NULL;
    }
    for(int i=0;i<1000;i++){
        head->boolean[i] = 0;
    }
    return head;
}

NODE* root1, *root2, *current;
int Suffix[MAX_SIZE+2];
int occ[MAX_SIZE+2];

int insert(char *s, int pos) {
    NODE* cur = current;
    int letter = s[pos] - 'a';

    while(1) {
        if(pos - 1 - cur->len >= 0 && s[pos - 1 - cur->len] == s[pos]) break;
        cur = cur->suffix;
    }
    NODE* t = new();
    t->len = cur->len + 2;
    t->end = pos;
    t->start = pos - t->len + 1;
    cur->label[Idx][letter] = t;
    printf("%d ",Idx);
    printf("Start %d, End %d\n",t->start,t->end);
    if(t->len == 1) {
        t->suffix = root2;
        current = t;
        Suffix[pos] = 1;
        current->boolean[Idx] = 1;
        return 0;
    }

    while(1) {
        cur = cur->suffix;
        if((pos - 1 - cur->len) >= 0 && s[pos - 1 - cur->len] == s[pos]) {
            t->suffix = cur->label[Idx][letter]; break;
        }
    }
    current = t;
    // Suffix[pos] = 1 + Suffix[current->suffix->end[Idx]];
    current->boolean[Idx] = 1;
    // occ[pos]++;
    return 0;
}

void print(char *s, NODE* head,int pos) {
    if(head!=root1 || head!=root2) {
        if(head->boolean[pos]==1) {
        for(int i = head->start; i <= head->end; ++i){
            printf("%c",s[i]);
        }
        // printf("%c",s[i]);
        printf("\n");
        }
    }
    for(int i = 0; i < 26; ++i) {
        if(head->label[pos][i]!=NULL) {
            print(s, head->label[pos][i],pos);
        }
    }
}

void show(char *s,int pos) {
    print(s, root1,pos);
    print(s, root2,pos);
}

int main() {
    root1 = new();
    root1->len = -1; root1->suffix = root1;
    root2 = new();
    root2->len = 0; root2->suffix = root1;
    current = root2;

    char word[MAX_SIZE][MAX_SIZE];


    while(1){
        printf("HELLO");
        printf("Options : ");
        printf("1.) Insert");
        printf("3.) Print");
        printf("3.) quit");
        
        int choice;
        printf("Enter your choice\n");
        scanf("%d",&choice);
        fflush(stdin);
        switch(choice){
            case 1:{
                current = root2;
                char str; char word1[MAX_SIZE];
                char *s = word1;
                int i = 0;
                printf("Enter your word\n");
                while((str=(char)getchar()) != '\n') {
                    word[Idx][i] = str;
                    word1[i] = str; ++i;
                }
                for(int j = 0; j < i; ++j) {
                    insert(s, j);
                }
                Idx++;
                break;
            }

            case 2:{
                
                for(int i=0;i<Idx;i++){
                    int j=0;
                    while(word[i][j]!='\0'){
                        printf("%c",word[i][j]);
                        j++;
                    }
                    printf("\n");
                }

                for(int i=0;i<Idx;i++){
                    printf("WORD %d\n",i);
                    show(word[i],i);
                    printf("*****************");
                }
                break;
            }

            case 3: {
                exit(1);
                break;
            }
            default:{
                printf("Invalid statement");
                break;
            }
        }
    }


    return 0;
}