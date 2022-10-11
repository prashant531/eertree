#include<stdio.h>
#include<malloc.h>

#define MAX_SIZE 1000
//Sample test
struct node {
    int start, end;
    int len;
    struct node* suffix;
    struct node* label[26];
};
typedef struct node NODE;

NODE* new() {
    NODE* head = (NODE*)malloc(sizeof(NODE));
    head->start = -1; head->end = -1; head->len = -1;
    head->suffix = NULL;
    for(int i = 0; i < 26; ++i) {
        head->label[i] = NULL;
    }
    return head;
}

NODE* root1, *root2, *current;

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
    cur->label[letter] = t;

    if(t->len == 1) {
        t->suffix = root2;
        current = t;
        return 0;
    }

    while(1) {
        cur = cur->suffix;
        if((pos - 1 - cur->len) >= 0 && s[pos - 1 - cur->len] == s[pos]) {
            t->suffix = cur->label[letter]; break;
        }
    }
    current = t;
    return 0;
}

void print(char *s, NODE* head) {
    if(head!=root1 || head!=root2) {
        for(int i = head->start; i <= head->end; ++i) printf("%c",s[i]);
        printf("\n");
    }
    for(int i = 0; i < 26; ++i) {
        if(head->label[i]!=NULL) {
            print(s, head->label[i]);
        }
    }
}

void show(char *s) {
    print(s, root1);
    print(s, root2);
}

int main() {
    root1 = new();
    root1->len = -1; root1->suffix = root1;
    root2 = new();
    root2->len = 0; root2->suffix = root1;
    current = root2;

    char str; char word[MAX_SIZE];
    char *s = word;
    int i = 0;
    printf("Enter your word\n");
    while((str=(char)getchar()) != '\n') {
        word[i] = str; ++i;
    }
    for(int j = 0; j < i; ++j) {
        insert(s, j);
    }
    show(s);
    return 0;
}