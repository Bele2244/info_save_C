#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct employee{
    char f_name[16];
    char l_name[16];
    int age;
    struct employee *next;
};
struct employee *first;
struct employee *current;
struct employee *new;
	 
struct employee *create(void);
void add_str(void);
void show_str(void);
void del_str(void);
void save(void);
void load(void);
int menu(void);

char *filename = "E.records.db";

int main()
{
    int choice = '\0';
    first = NULL;
    load();

    while(choice != 'Q')
    {
        choice = menu();
        switch(choice)
        {
            case 'A':
                add_str();;
                break;
            case 'S':
                show_str();
                break;
            case 'R':
                del_str();
                break;
            case 'Q':
                break;
            default:
                break;
        }
    }
    save();
    return (0);
}

/* Display Menu */
int menu(void)
{
    int ch;
    printf("(A) add (S) show (R) remove (Q) quit:");
    ch = getchar();
    while(getchar() != '\n')
        ;
    ch = toupper(ch);
    if(ch != 'A' && ch != 'S' && ch != 'R' && ch != 'Q')
    {
        puts("Wrong input!");
        menu();
    }

    return (ch);
}

/* Add new list to the end of the LL */
void add_str(void)
{
    if(first == NULL)
    {
        first = create();
        current = first;
    }
    else
    {
        current = first;
        while(current -> next)
            current = current -> next;
        new = create();
        current -> next = new;
        current = new;
    }
/* Fill in Data for the current list */
    printf("Type your first name: ");scanf("%s",current -> f_name);
    printf("Type your last name: ");scanf("%s",current -> l_name);
    printf("Type in your age: ");scanf("%d",&current -> age);
    current -> next = NULL;
    while(getchar() != '\n')
        ;
}

/* Show created lists if any */
void show_str(void)
{
    int count = 1;
    if(first == NULL)
    {
        puts("Nothing to show, list is empty!");
        return;
    }
    puts("Employes list:");
    printf("F.name\tL.name\tAge\n");
    current = first;
    while(current)
    {
        printf("%d.%s\t%s\t%d\n",count,
        current -> f_name,
        current -> l_name,
        current -> age);
        current = current -> next;
        count++;
    }
}

/* Allocate memory for new structs */
struct employee *create(void)
{
    struct employee *a;

    a = (struct employee *)malloc(sizeof(struct employee));
    if(a == NULL)
    {
        puts("Unable to allocate memory ");
        exit(1);
    }
    return (a);
}

/* Remove structure from linked list */
void del_str(void)
{
    struct employee *previous;
    int r, c;

    if(first == NULL)
    {
        puts("Nothing to remove");
        return;
    }
    puts("Chose a record to remove");
    printf("Record: ");scanf("%d",&r);
    while(getchar() != '\n')
        ;
    c = 1;
    previous = NULL;
    current = first;
    while(c != r)
    {
        previous = current;
        current = current -> next;
        c++;
        if(current == NULL)
        {
            puts("Record not found");
            main();
        }
    }
    if(previous == NULL)
        first = current -> next;
    else
        previous -> next = current -> next;
    printf("Record number: %d removed\n",r);
    free(current);
}
/* Save list to the file */
void save(void)
{
    int count = 1;
    FILE *to_file;

    to_file = fopen(filename,"w");
    if(first == NULL)
    {
        puts("Nothing to save");
        to_file = fopen(filename,"w");
        if(!to_file)
        {
            puts("File open error");
            exit(1);
        }
        fclose(to_file);
        return;
    }
    current = first;
    while(current)
    {
        fwrite(current,sizeof(struct employee),1,to_file);
        current = current -> next;
        count++;
    }
    count--;
    fclose(to_file);
    printf("%d Records writen\n",count);
}

/* Load Lists from a file */
void load(void)
{
    FILE *to_file;
    struct employee loaded;

    to_file = fopen(filename,"r");
    if(!to_file)
        return;

    while(fread(&loaded,sizeof(struct employee),1,to_file))
    {
        if(first == NULL)
        {
            first = create();
            current = first;
        }
        else
        {
            current = first;
            while(current -> next)
                current = current -> next;
            new = create();
            current-> next = new;
            current = new;
        }
        strcpy(current -> f_name,loaded.f_name);
        strcpy(current -> l_name,loaded.l_name);
        current -> age = loaded.age;
        current -> next = NULL;
    }
    fclose(to_file);
}




