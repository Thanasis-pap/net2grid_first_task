#include "linked_lists.h"
#include <stdio.h>
#include <assert.h>

void test_linked_list()
{
    LinkedList *list = list_create(sizeof(int), NULL, NULL);
    int val1 = 100, val2 = 200;

    assert(list_insert(list, 0, &val1) == true);
    assert(list_insert(list, 1, &val2) == true);

    int *retrieved = list_get(list, 1);
    assert(retrieved && *retrieved == 200);

    assert(list_delete(list, 1) == true);
    assert(list_get(list, 1) == NULL);

    list_destroy(list);
    printf("All tests passed!\n");
}

int main()
{
    test_linked_list();
    return 0;
}
