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
void del(link l);
void list(link l);

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

void del(link l)
{
	if (NULL == l)
    {
		return;
    }
	char buf[10];
	node * p = l;
	node * q = l;
	p = p->next;
	if(NULL == p)
	{
		printf("The list is empty\n");
		return;
    }
	printf("Input the name you want to find:");
	scanf("%s", buf);
	while(NULL != p)
	{
		if(strcmp(p->data.name, buf) == 0)
		{
			q->next = p->next;
			free(p);
            printf("del successful\n");
			return;
		}
		q = p;
		p = p->next;
	}

	if(NULL == p)
	{
		printf("Not found the address\n");
		return;
	}
}

void list(link l)
{
    if(NULL == l)
        return;
    node * p = l->next;
    p = p->next;
    while(NULL != p)
    {
        printf("%s\n", p->data.name);
        printf("%s\n", p->data.city);
        printf("%s\n", p->data.province);
        printf("%s\n", p->data.stat);
        printf("%s\n", p->data.tel);
        p = p->next;
    }
}

int main(int argc, char const *argv[])
{

    return 0;
}
