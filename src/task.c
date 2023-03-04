#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "task.h"

/**
 * @brief Task Manager App Using Different Data Structures
 * @author Obaydur Rahman (213902018) <obayed.opu@gmail.com>
 * @date 2022-09-04 (13:52)
 *
 * @returns int
 */

int main()
{
    // create linked list
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;

    // load linked list
    load_linked_list(list);

    while (1)
    {
        // print menu
        printf("1. Add task \n");
        printf("2. Remove task \n");
        printf("3. Print tasks \n");
        printf("4. Search tasks \n");
        printf("5. Save & Exit \n");

        // get user input
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // process user input
        switch (choice)
        {
        case 1:
        {
            // get task name
            char name[100];
            printf("Enter task name: ");
            // allow space in task name
            scanf(" %[^\n]", name);

            // get task due
            char due[100];
            printf("Enter task due date [dd-mm-yyyy]: ");
            scanf(" %s", due);

            // add task
            add_task(list, name, due, generate_id());

            clear_console();
            printf("Task added successfully! \n\n");

            break;
        }
        case 2:
        {
            // get task id
            int id;
            printf("Enter task id: ");
            scanf("%d", &id);

            // remove task
            remove_task(list, id);

            clear_console();
            printf("Task removed successfully! \n\n");

            break;
        }

        case 3:
        {
            // sort tasks
            clear_console();
            sort_tasks(list);
            print_tasks(list);
            break;
        }

        case 4:
        {
            clear_console();
            // get task name
            char name[100];
            printf("Enter task name: ");
            scanf("%s", name);

            // search tasks
            search_tasks(list, name);

            break;
        }

        case 5:
        {
            clear_console();
            save_linked_list(list);
            printf("Goodbye! \n\n");
            exit(0);
            break;
        }

        default:
        {
            // invalid choice
            printf("Invalid choice! \n");
            break;
        }
        }
    }

    return 0;
}

int generate_id()
{
    // get old id
    int old_id = 0;
    FILE *fp = fopen("id.txt", "r");
    if (fp != NULL)
    {
        fscanf(fp, "%d", &old_id);
        fclose(fp);
    }

    // increment id
    int new_id = old_id + 1;

    // save new id
    fp = fopen("id.txt", "w");
    if (fp != NULL)
    {
        fprintf(fp, "%d", new_id);
        fclose(fp);
    }

    return new_id;
}

void save_linked_list(LinkedList *list)
{
    // open file
    FILE *fp = fopen("tasks.txt", "w");
    if (fp == NULL)
    {
        printf("Error opening file! \n");
        return;
    }

    // save linked list
    Node *current = list->head;
    while (current != NULL)
    {
        fprintf(fp, "%d\t%s\t%s", current->task->id, current->task->name, current->task->due);
        current = current->next;
    }

    // close file
    fclose(fp);
}

void load_linked_list(LinkedList *list)
{
    // open file
    FILE *fp = fopen("tasks.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file! \n");
        return;
    }

    // load linked list
    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        // if empty line then skip
        if (strcmp(line, "\n") == 0)
        {
            continue;
        }

        // get id
        char *token = strtok(line, "\t");
        int id = atoi(token);

        // get name
        token = strtok(NULL, "\t");
        char name[100];
        strcpy(name, token);

        // get due
        token = strtok(NULL, "\t");
        char due[100];
        strcpy(due, token);

        // add task to linked list
        add_task(list, name, due, id);
    }

    // close file
    fclose(fp);
}

void add_task(LinkedList *list, char *name, char *due, int id)
{
    // create task
    Task *task = (Task *)malloc(sizeof(Task));
    task->id = id;
    task->name = (char *)malloc(strlen(name) + 1);
    strcpy(task->name, name);
    task->due = (char *)malloc(strlen(due) + 1);
    strcpy(task->due, due);

    // create node
    Node *node = (Node *)malloc(sizeof(Node));
    node->task = task;
    node->next = NULL;

    // add node to linked list
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
    }
    else
    {
        list->tail->next = node;
        list->tail = node;
    }
}

void remove_task(LinkedList *list, int id)
{
    // find node
    Node *current = list->head;
    Node *previous = NULL;
    while (current != NULL)
    {
        if (current->task->id == id)
        {
            break;
        }
        previous = current;
        current = current->next;
    }

    // remove node
    if (current != NULL)
    {
        if (previous == NULL)
        {
            list->head = current->next;
        }
        else
        {
            previous->next = current->next;
        }
        free(current);
    }
}

void print_tasks(LinkedList *list)
{
    printf("+-----------------------------------+\n");
    printf("| ID\t|\tName\t|\tDue |\n");
    printf("+-----------------------------------+\n");
    // print tasks
    Node *current = list->head;
    while (current != NULL)
    {
        printf("  %d\t  %s\t  %s", current->task->id, current->task->name, current->task->due);
        current = current->next;
        printf("\n");
    }
    printf("+-----------------------------------+\n\n");
}

void sort_tasks(LinkedList *list)
{
    // bubble sort linked list using due date
    int swapped;
    Node *current;

    do
    {
        swapped = 0;
        current = list->head;

        while (current->next != NULL)
        {
            // convert current due from dd-mm-yyyy to yyyymmdd integer
            char due1[100];
            strcpy(due1, current->task->due);
            char *token = strtok(due1, "-");
            char year1[100];
            strcpy(year1, token);
            token = strtok(NULL, "-");
            char month1[100];
            strcpy(month1, token);
            token = strtok(NULL, "-");
            char day1[100];
            strcpy(day1, token);
            // yyyymmdd
            int due1_int = atoi(day1) * 10000 + atoi(month1) * 100 + atoi(year1);

            // convert next due from dd-mm-yyyy to yyyymmdd integer
            char due2[100];
            strcpy(due2, current->next->task->due);
            char *token2 = strtok(due2, "-");
            char year2[100];
            strcpy(year2, token2);
            token2 = strtok(NULL, "-");
            char month2[100];
            strcpy(month2, token2);
            token2 = strtok(NULL, "-");
            char day2[100];
            strcpy(day2, token2);
            // yyyymmdd
            int due2_int = atoi(day2) * 10000 + atoi(month2) * 100 + atoi(year2);

            // printf("%d > %d\n\n", due1_int, due2_int);
            if (due1_int > due2_int)

            {
                // swap tasks
                Task *temp = current->task;
                current->task = current->next->task;
                current->next->task = temp;
                swapped = 1;
            }
            current = current->next;
        }
    } while (swapped);
}

void search_tasks(LinkedList *list, char *name)
{
    printf("+-----------------------------------+\n");
    printf("| ID\t|\tName\t|\tDue |\n");
    printf("+-----------------------------------+\n");
    // search tasks
    Node *current = list->head;
    while (current != NULL)
    {
        if (strstr(current->task->name, name) != NULL)
        {
            printf("  %d\t  %s\t  %s", current->task->id, current->task->name, current->task->due);
        }
        current = current->next;
    }
    printf("\n+-----------------------------------+\n\n");
}

void clear_console()
{
// if windows cls else clear
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
