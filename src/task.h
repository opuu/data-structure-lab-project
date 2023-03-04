/**
 * @brief Task structure
 * @details This structure is used to store information about a task.
 *
 * @param name The name of the task.
 * @param due The due date of the task.
 */
typedef struct Task
{
    int id;
    char *name;
    char *due;
} Task;

/**
 * @brief Node of linked list
 *
 * @param task Task
 * @param next Next node
 * @param prev Previous node
 */
typedef struct Node
{
    struct Task *task;
    struct Node *next;
} Node;

/**
 * @brief Linked list
 *
 * @param head Head of the list
 * @param tail Tail of the list
 */
typedef struct LinkedList
{
    struct Node *head;
    struct Node *tail;
} LinkedList;

/**
 * @brief generate auto-incremented id
 *
 * @return int
 */
int generate_id();

/**
 * @brief save linked list to file
 *
 * @param list linked list
 * @return void
 */
void save_linked_list(LinkedList *list);

/**
 * @brief load linked list from file
 *
 * @param list linked list
 * @return void
 */
void load_linked_list(LinkedList *list);

/**
 * @brief add task to linked list
 *
 * @param list linked list
 * @param name name of task
 * @param due due date of task
 * @param id id of task (optional)
 *
 * @return void
 */
void add_task(LinkedList *list, char *name, char *due, int id);

/**
 * @brief remove task from linked list
 *
 * @param list linked list
 * @param id id of task
 * @return void
 */
void remove_task(LinkedList *list, int id);

/**
 * @brief print linked list
 *
 * @param list linked list
 * @return void
 */
void print_tasks(LinkedList *list);

/**
 * @brief sort the linked list
 *
 * @param list linked list
 * @return void
 */
void sort_tasks(LinkedList *list);

/**
 * @brief search the linked list
 *
 * @param list linked list
 * @param name name of task
 * @return void
 */
void search_tasks(LinkedList *list, char *name);

/**
 * @brief clear the console
 *
 * @return void
 */
void clear_console();
