#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "factory.h"

int insert_at(Machine arr[], int position, int id, char status[20], int maintain, int size, int max)
{
    if (size >= max)
    {
        printf("Machine array overflow !");
        return size;
    }
    if (position < 1 || position > size + 1)
    {
        printf("Invalid position !");
        return size;
    }
    for (int i = 0; i < size; i++)
    {
        if (arr[i].id == id)
        {
            printf("Duplicate ID not allowed!\n");
            return size;
        }
    }
    struct machine temp;
    temp.id = id;
    strcpy(temp.status, status);
    temp.maintenance_req = maintain;
    int index = position - 1;

    int i;

    for (i = size - 1; i >= index; i--)
    {
        arr[i + 1] = arr[i];
    }
    arr[index] = temp;

    printf("Machine input successful !");
    return size + 1;
}

int delete_by_position(Machine arr[], int position, int size)
{
    if (size ==0)
    {
        printf("No machines to delete.\n");
        return;
    }
    if (position > size || position < 1)
    {
        printf("Position out of range .");
        return size;
    }
    int index = position - 1;
    for (int i = index; i < size - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    size = size - 1;
    printf("Delete Successful .");
    return size;
}

int delete_by_id(Machine arr[], int id, int size)
{
    if (size ==0)
    {
        printf("No machines to delete.\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        if (id == arr[i].id)
        {
            for (int j = i; j < size - 1; j++)
            {
                arr[j] = arr[j + 1];
            }

            printf("Delete Successful .");

            return size - 1;
        }
    }
    printf("Id not found.");
    return size;
}

void traverse(Machine arr[], int size)
{
    if (size ==0)
    {
        printf("No machines to display.\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {

        printf("Machine Id : %d\n", arr[i].id);
        printf("Machine State : %s\n", arr[i].status);
        if (arr[i].maintenance_req == 1)
        {
            printf("Machine Maintenances Requirement : Required\n");
        }
        else
        {
            printf("Machine Maintenances Requirement : Not Required\n");
        }
        printf("\n");
    }
}

void update_by_position(Machine arr[], int position, int size, char status[20], int maintain)
{
    if (size ==0)
    {
        printf("No machines to update.\n");
        return;
    }
    if (position > size || position < 1)
    {
        printf("Position out of bounds");
        return;
    }
    strcpy(arr[position - 1].status, status);
    arr[position - 1].maintenance_req = maintain;
}

void update_by_id(Machine arr[], int id, int size, char status[20], int maintain)
{
    if (size ==0)
    {
        printf("No machines to update.\n");
        return;
    }
    for (int i = 0; i < size; i++)
    {
        if (id == arr[i].id)
        {
            arr[i].maintenance_req = maintain;
            strcpy(arr[i].status, status);
            printf("Machine updated successfully");
            return;
        }
    }
    printf("Id not found.");
}

void bubble_sort_by_id(Machine arr[], int size)
{
    if (size ==0)
    {
        printf("No machines to sort.\n");
        return;
    }
    int i, j;
    struct machine temp;
    bool swapped = false;

    for (i = 0; i < size - 1; i++)
    {
        swapped = false;
        for (j = 0; j < size - 1 - i; j++)
        {
            if (arr[j].id > arr[j + 1].id)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }
    printf("Sorted successfully.\n");
}

void show_maintenance(Machine arr[], int size)
{
    if (size ==0)
    {
        printf("No machines to display.\n");
        return;
    }
    int found = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i].maintenance_req == 1)
        {
            printf("Machine ID : %d \n", arr[i].id);
            found++;
        }
    }
    if (found == 0)
    {
        printf("No machines need maintenance.\n");
    }
}
