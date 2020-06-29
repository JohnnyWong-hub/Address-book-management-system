#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct stu
{
    char name[10];
    char city[10];
    char province[10];
    char stat[10];
    char tel[15];
};

typedef struct node
{
    struct stu data;
    struct node *next;
} node, *link;

void stringput(char *str, int lens, char *notice);
void enter(link l);
void stringput(char *str, int lens, char *notice)
{
    char buf[50];
    do
    {
        printf("%s", notice);
        scanf("%s", buf);
        if (strlen(buf) > lens)
        {
            printf("is too large than str\n");
        }
    } while (strlen(buf) > lens);
    strcpy(str, buf);
}

void enter(link l)
{
    node * p, *q;
    p = l;
    while(p->next !=NULL)
    {
        p = p->next;
    }
    while(1)
    {
        q = (struct node *)malloc(sizeof(struct node));
        if(NULL == q)
        {
            printf("malloc failed");
            return;
        }
        stringput(q->data.name, 10, "input name:");
        if(strcmp(q->data.name, "0") == 0)
        {
            free(q);
            break;;
        }
        stringput(q->data.city, 10, "input city:");
        stringput(q->data.province, 10, "input province:");
        stringput(q->data.stat, 10, "input stat:");
        stringput(q->data.tel, 15, "input tel:");
        q->next = p->next;
        p->next = q;
        p = q;
    }
}

int main(int argc, char const *argv[])
{

    return 0;
}
