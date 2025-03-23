#include "linked_lists.h"
#include <stdlib.h>
#include <string.h>

LinkedList *list_create(size_t data_size, alloc_fn alloc, free_fn dealloc)
{
    LinkedList *list = (alloc ? alloc : malloc)(sizeof(LinkedList));
    if (!list)
        return NULL;
    list->head = NULL;
    list->data_size = data_size;
    list->alloc = alloc ? alloc : malloc;
    list->dealloc = dealloc ? dealloc : free;
    pthread_mutex_init(&list->lock, NULL);
    return list;
}

bool list_insert(LinkedList *list, size_t index, void *data)
{
    pthread_mutex_lock(&list->lock);
    Node *new_node = list->alloc(sizeof(Node));
    if (!new_node)
    {
        pthread_mutex_unlock(&list->lock);
        return false;
    }
    new_node->data = list->alloc(list->data_size);
    if (!new_node->data)
    {
        list->dealloc(new_node);
        pthread_mutex_unlock(&list->lock);
        return false;
    }
    memcpy(new_node->data, data, list->data_size);

    if (index == 0)
    {
        new_node->next = list->head;
        list->head = new_node;
    }
    else
    {
        Node *current = list->head;
        for (size_t i = 0; current && i < index - 1; i++)
        {
            current = current->next;
        }
        if (!current)
        {
            list->dealloc(new_node->data);
            list->dealloc(new_node);
            pthread_mutex_unlock(&list->lock);
            return false;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
    pthread_mutex_unlock(&list->lock);
    return true;
}

bool list_delete(LinkedList *list, size_t index)
{
    pthread_mutex_lock(&list->lock);
    if (!list->head)
    {
        pthread_mutex_unlock(&list->lock);
        return false;
    }
    Node *temp = list->head;
    if (index == 0)
    {
        list->head = temp->next;
    }
    else
    {
        Node *prev = NULL;
        for (size_t i = 0; temp && i < index; i++)
        {
            prev = temp;
            temp = temp->next;
        }
        if (!temp)
        {
            pthread_mutex_unlock(&list->lock);
            return false;
        }
        prev->next = temp->next;
    }
    list->dealloc(temp->data);
    list->dealloc(temp);
    pthread_mutex_unlock(&list->lock);
    return true;
}

void *list_get(LinkedList *list, size_t index)
{
    pthread_mutex_lock(&list->lock);
    Node *current = list->head;
    for (size_t i = 0; current && i < index; i++)
    {
        current = current->next;
    }
    void *result = current ? current->data : NULL;
    pthread_mutex_unlock(&list->lock);
    return result;
}

void list_iterate(LinkedList *list, void (*callback)(void *))
{
    pthread_mutex_lock(&list->lock);
    Node *current = list->head;
    while (current)
    {
        callback(current->data);
        current = current->next;
    }
    pthread_mutex_unlock(&list->lock);
}

void list_destroy(LinkedList *list)
{
    pthread_mutex_lock(&list->lock);
    Node *current = list->head;
    while (current)
    {
        Node *next = current->next;
        list->dealloc(current->data);
        list->dealloc(current);
        current = next;
    }
    pthread_mutex_unlock(&list->lock);
    pthread_mutex_destroy(&list->lock);
    list->dealloc(list);
}
