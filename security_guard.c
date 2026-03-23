#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include "factory.h"

void delete_guard(Guard guard[], int *size, int id)
{
    int idx = -1;
    for (int i = 0; i < *size; i++)
    {
        if (guard[i].guard_id == id)
        {
            idx = i;
            break;
        }
    }
    if (idx < 0)
    {
        printf("Guard with ID %d not found.\n", id);
        return;
    }
    for (int j = idx; j < *size - 1; j++)
    {
        guard[j] = guard[j + 1];
    }
    (*size)--;
    printf("Guard with ID %d deleted.\n", id);
}

// Function to add a new guard
void add_guard(Guard guard[], int *size)
{
    printf("Enter guard ID: ");
    scanf("%d", &guard[*size].guard_id);
    clear_input();
    printf("Enter active status (0-> not active, 1-> active): ");
    scanf("%d", (int *)&guard[*size].is_active);
    printf("Enter the patrol point: ");
    scanf("%29s", guard[*size].patrol_point);
    clear_input();
    printf("Enter the shift time: ");
    scanf("%5s", guard[*size].shift);
    clear_input();
    (*size)++;
    printf("Guard details saved successfully.\n");
}

// Function to update an existing guard
void update_guard(Guard guard[], int size)
{
    int input;
    printf("Enter the guard ID to update: ");
    scanf("%d", &input);
    for (int i = 0; i < size; i++)
    {
        if (guard[i].guard_id == input)
        {
            int field = 0;
            printf("Update which detail?\n");
            printf("1 - active status\n");
            printf("2 - patrol point\n");
            printf("3 - shift time\n");
            printf("4 - all\n");
            scanf("%d", &field);
            switch (field)
            {
            case 1:
                printf("Enter new active status (0->not active, 1->active): ");
                scanf("%d", (int *)&guard[i].is_active);
                break;
            case 2:
                printf("Enter new patrol point: ");
                scanf("%29s", guard[i].patrol_point);
                break;
            case 3:
                printf("Enter new shift time: ");
                scanf("%5s", guard[i].shift);
                break;
            case 4:
                printf("Enter new active status (0->not active, 1->active): ");
                scanf("%d", (int *)&guard[i].is_active);
                printf("Enter new patrol point: ");
                scanf("%29s", guard[i].patrol_point);
                clear_input();
                printf("Enter new shift time: ");
                scanf("%5s", guard[i].shift);
                clear_input();
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Guard details updated successfully.\n");
            return; // Exit after updating
        }
    }
    printf("Guard with ID %d not found.\n", input); // If not found
}

// Function to display all guards
void display_guard(Guard guard[], int size)
{
    if (size == 0)
    {
        printf("No guards registered yet.\n");
    }
    else
    {
        printf("Guard details:\n");
        for (int i = 0; i < size; i++)
        {
            printf("ID: %d, Active: %s, Patrol: %s, Shift: %s\n",
                   guard[i].guard_id,
                   guard[i].is_active ? "Yes" : "No",
                   guard[i].patrol_point,
                   guard[i].shift);
        }
    }
}

// Recursive quick sort used instead of insertion sort
// void insertion_sort_by_id(Guard guard[], int size)
// {
//     for (int i = 1; i < size; i++)
//     {
//         Guard key = guard[i];
//         int j = i - 1;
//         while (j >= 0 && guard[j].guard_id > key.guard_id)
//         {
//             guard[j + 1] = guard[j];
//             j--;
//         }
//         guard[j + 1] = key;
//     }
//     printf("Guards sorted by ID.\n");
// }

int partition_by_id(Guard guard[], int low, int high)
{
    int pivot = guard[high].guard_id;
    int i = low - 1;
    for (int j = low; j < high; j++)
    {
        if (guard[j].guard_id <= pivot)
        {
            i++;
            // Swap guard[i] and guard[j]
            Guard temp = guard[i];
            guard[i] = guard[j];
            guard[j] = temp;
        }
    }
    // Swap guard[i+1] and guard[high]
    Guard temp = guard[i + 1];
    guard[i + 1] = guard[high];
    guard[high] = temp;
    return i + 1;
}

void quick_sort_by_id(Guard guard[], int low, int high)
{
    if (low < high)
    {
        int pi = partition_by_id(guard, low, high);
        quick_sort_by_id(guard, low, pi - 1);
        quick_sort_by_id(guard, pi + 1, high);
    }
}