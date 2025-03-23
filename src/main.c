#include "linked_lists.h"
#include <stdio.h>

void print_int(void *data)
{
    printf("%d ", *(int *)data);
}

int main()
{
    LinkedList *list = list_create(sizeof(int), NULL, NULL);
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++)
    {
        list_insert(list, i, &values[i]);
    }

    printf("List elements: ");
    list_iterate(list, print_int);
    printf("\n");

    int *retrieved = list_get(list, 2);
    if (retrieved)
    {
        printf("Element at index 2: %d\n", *retrieved);
    }

    list_delete(list, 2);
    printf("List after deletion: ");
    list_iterate(list, print_int);
    printf("\n");

    list_destroy(list);
    return 0;
}
