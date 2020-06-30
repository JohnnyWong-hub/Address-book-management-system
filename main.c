#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
void search(link l);
void save(link l);
void load(link l);
int menu_select();
void destory(link l);

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
    node *p, *q;
    p = l;
    while (p->next != NULL)
    {
        p = p->next;
    }
    while (1)
    {
        q = (struct node *)malloc(sizeof(struct node));
        if (NULL == q)
        {
            printf("malloc failed");
            return;
        }
        stringput(q->data.name, 10, "input name:");
        if (strcmp(q->data.name, "0") == 0)
        {
            free(q);
            break;
            ;
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
    node *p = l;
    node *q = l;
    p = p->next;
    if (NULL == p)
    {
        printf("The list is empty\n");
        return;
    }
    printf("Input the name you want to find:");
    scanf("%s", buf);
    while (NULL != p)
    {
        if (strcmp(p->data.name, buf) == 0)
        {
            q->next = p->next;
            free(p);
            printf("del successful\n");
            return;
        }
        q = p;
        p = p->next;
    }

    if (NULL == p)
    {
        printf("Not found the address\n");
        return;
    }
}

void list(link l)
{
    if (NULL == l)
        return;
    node *p = l->next;
    p = p->next;
    while (NULL != p)
    {
        printf("name:%s\n", p->data.name);
        printf("city:%s\n", p->data.city);
        printf("province:%s\n", p->data.province);
        printf("stat:%s\n", p->data.stat);
        printf("tel:%s\n", p->data.tel);
        p = p->next;
    }
}

void search(link l)
{
    if (NULL == l)
        return;
    struct node *p = l->next;
    char buf[10];
    if (NULL == p)
    {
        printf("记录为空");
        return;
    }

    printf("input the name you want to find:");
    scanf("%s", buf);
    while (getchar() != '\n')
        ;

    while (NULL != p)
    {
        if (strcmp(buf, p->data.name) == 0)
        {
            printf("name:%s\ncity:%s\nprovince:%s\nstat:%s\ntel:%s\n",
                   p->data.name,
                   p->data.city,
                   p->data.province,
                   p->data.stat,
                   p->data.tel);
            return;
        }
        p = p->next;
    }
    printf("Not found the record\n");
}

void save(link l)
{
    struct node *p;
    FILE *fp;
    p = l->next;
    if ((fp = fopen("./addresslist", "wb")) == NULL)
    {
        printf("can not open file\n");
        exit(1);
    }

    printf("\nSaveing file\n");
    while (p)
    {
        fwrite(p, sizeof(node), 1, fp);
        p = p->next;
    }
    fclose(fp);
    getchar();
}

void load(link l)
{
    struct node *p, *r;
    FILE *fp;
    l->next = NULL;
    r = l;
    if ((fp = fopen("./addresslist", "rb")) == NULL)
    {
        printf("can not open file\n");
        exit(1);
    }

    printf("\nLoading file\n");
    while (!feof(fp))
    {
        p = (struct node *)malloc(sizeof(node));
        if (!p)
        {
            printf("memory malloc fail\n");
            return;
        }
        if (fread(p, sizeof(node), 1, fp) != 1)
        {
            break;
        }
        else
        {
            p->next = NULL;
            r->next = p;
            r = p;
        }
    }
    fclose(fp);
    while (getchar() != '\n')
        ;
}

int menu_select()
{
    int i;
    printf("\n\n\t ********************************ADDRESS LIST****************************\n");
    printf("\t|*                        1.input record                                 *|\n");
    printf("\t|*                        2.delete record                                *|\n");
    printf("\t|*                        3.list record                                  *|\n");
    printf("\t|*                        4.search list                                  *|\n");
    printf("\t|*                        5.save record                                  *|\n");
    printf("\t|*                        6.load record                                  *|\n");
    printf("\t|*                        7.Quit                                         *|\n");
    printf("\t***************************************************************************\n");
    do
    {
        printf("\n\tEnter your choice:");
        scanf("%d", &i);
    } while (i < 0 || i > 7);
    return i;
}

void destory(link l)
{
    if (NULL == l)
        return;
    struct node * p = l->next;
    while(p){
        l->next = p->next;
        free(p);
        p = l->next;
    }
    free(l);
}

int main(int argc, char const *argv[])
{
    link l;
    l = (node *)malloc(sizeof(node));
    if (!l)
    {
        printf("\n allocate memory failer\n");
        return 0;
    }
    l->next = NULL;
    while (1)
    {
        switch (menu_select())
        {
        case 1:
            enter(l);
            break;
        case 2:
            del(l);
            break;
        case 3:
            list(l);
            break;
        case 4:
            search(l);
            break;
        case 5:
            save(l);
            break;
        case 6:
            load(l);
            break;
        case 7:
            destory(l);
            exit(0);
        }
    }
    return 0;
}
