#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>

// Custom memory allocator
typedef void *(*alloc_fn)(size_t);
typedef void (*free_fn)(void *);

// Linked List Node
typedef struct Node
{
    void *data;
    struct Node *next;
} Node;

// Linked List Structure
typedef struct
{
    Node *head;
    size_t data_size;
    pthread_mutex_t lock;
    alloc_fn alloc;
    free_fn dealloc;
} LinkedList;

// Function declarations
LinkedList *list_create(size_t data_size, alloc_fn alloc, free_fn dealloc);
bool list_insert(LinkedList *list, size_t index, void *data);
bool list_delete(LinkedList *list, size_t index);
void *list_get(LinkedList *list, size_t index);
void list_iterate(LinkedList *list, void (*callback)(void *));
void list_destroy(LinkedList *list);

#endif // LINKED_LIST_H
