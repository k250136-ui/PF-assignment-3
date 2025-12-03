#include <stdio.h>
#include <string.h>

struct Book
{
    int id;
    int popularity;
    int lastAccess;
};

int findBook(struct Book shelf[], int size, int id)
{
    for (int i = 0; i < size; i++)
    {
        if (shelf[i].id == id)
            return i;
    }
    return -1;
}

int findLRU(struct Book shelf[], int size)
{
    int minIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (shelf[i].lastAccess < shelf[minIndex].lastAccess)
            minIndex = i;
    }
    return minIndex;
}

int main()
{
    int capacity, Q;
    scanf("%d %d", &capacity, &Q);

    struct Book shelf[capacity];
    int currentSize = 0;
    int time = 1;

    for (int i = 0; i < capacity; i++) 
    {
        shelf[i].id = -1;
        shelf[i].popularity = 0;
        shelf[i].lastAccess = 0;
    }

    char command[10];

    while (Q--)
    {
        scanf("%s", command);

        if (strcmp(command, "ADD") == 0)
        {
            int id, pop;
            scanf("%d %d", &id, &pop);

            int index = findBook(shelf, currentSize, id);

            if (index != -1)
            {
                shelf[index].popularity = pop;
                shelf[index].lastAccess = time++;
            }
            else
            {
                if (currentSize < capacity)
                {
                    shelf[currentSize].id = id;
                    shelf[currentSize].popularity = pop;
                    shelf[currentSize].lastAccess = time++;
                    currentSize++;
                }
                else
                {
                    int lru = findLRU(shelf, currentSize);
                    shelf[lru].id = id;
                    shelf[lru].popularity = pop;
                    shelf[lru].lastAccess = time++;
                }
            }
        }
        else if (strcmp(command, "ACCESS") == 0)
        {
            int id;
            scanf("%d", &id);

            int index = findBook(shelf, currentSize, id);
            if (index == -1)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", shelf[index].popularity);
                shelf[index].lastAccess = time++;
            }
        }
    }
    return 0;
}