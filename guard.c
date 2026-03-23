#include <stdio.h>
#include <stdbool.h>
#include <windows.h>

struct guardd {
    int guard_id;
    bool is_active;
    char patrol_point[30];
    char shift[6];
};

// Function to clear input buffer
void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void delete_guard(struct guardd guard[], int *size, int id) {
    int idx = -1;
    for (int i = 0; i < *size; i++) {
        if (guard[i].guard_id == id) {
            idx = i;
            break;
        }
    }
    if (idx < 0) {
        printf("Guard with ID %d not found.\n", id);
        return;
    }
    for (int j = idx; j < *size - 1; j++) {
        guard[j] = guard[j + 1];
    }
    (*size)--;
    printf("Guard with ID %d deleted.\n", id);
}

void guard(void) {
    struct guardd guard[20];
    int input = 0;
    int size = 0;

menu:
    printf("\n=== Security Panel Menu ===\n");
    printf("1. Add details of a new guard\n");
    printf("2. Update details of an existing guard\n");
    printf("3. Delete a guard\n");
    printf("4. View all guard details\n");
    printf("5. Sort guards by ID\n");
    printf("0. Exit\n");
    printf("Enter your choice (0-5): ");
    scanf("%d", &input);
    clear_input_buffer();

    switch (input) {
    case 1:
        add_guard(guard, &size);
        goto menu;
    case 2:
        update_guard(guard, size);
        goto menu;
    case 3:
        printf("Enter guard ID to delete: ");
        scanf("%d", &input);
        clear_input_buffer();
        delete_guard(guard, &size, input);
        goto menu;
    case 4:
        display_guard(guard, size);
        goto menu;
    case 5:
        quick_sort_by_id(guard, 0, size - 1);
        printf("Guards sorted by ID.\n");
        goto menu;
    case 0:
        break;
    default:
        printf("Invalid input. Please enter a number between 0 and 5.\n");
        Sleep(1000);  // Shorter delay for better UX
        goto menu;
    }
}

// Function to add a new guard
void add_guard(struct guardd guard[], int *size) {
    printf("Enter guard ID: ");
    scanf("%d", &guard[*size].guard_id);
    clear_input_buffer();
    printf("Enter active status (0-> not active, 1-> active): ");
    scanf("%d", (int*)&guard[*size].is_active);
    clear_input_buffer();
    printf("Enter the patrol point: ");
    scanf("%29s", guard[*size].patrol_point);
    clear_input_buffer();
    printf("Enter the shift time: ");
    scanf("%5s", guard[*size].shift);
    clear_input_buffer();
    (*size)++;
    printf("Guard details saved successfully.\n");
}

// Function to update an existing guard
void update_guard(struct guardd guard[], int size) {
    int input;
    printf("Enter the guard ID to update: ");
    scanf("%d", &input);
    clear_input_buffer();
    for (int i = 0; i < size; i++) {
        if (guard[i].guard_id == input) {
            int field = 0;
            printf("Update which detail?\n");
            printf("1 - active status\n");
            printf("2 - patrol point\n");
            printf("3 - shift time\n");
            printf("4 - all\n");
            scanf("%d", &field);
            clear_input_buffer();
            switch (field) {
            case 1:
                printf("Enter new active status (0->not active, 1->active): ");
                scanf("%d", (int*)&guard[i].is_active);
                clear_input_buffer();
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
                scanf("%d", (int*)&guard[i].is_active);
                clear_input_buffer();
                printf("Enter new patrol point: ");
                scanf("%29s", guard[i].patrol_point);
                clear_input_buffer();
                printf("Enter new shift time: ");
                scanf("%5s", guard[i].shift);
                clear_input_buffer();
                break;
            default:
                printf("Invalid choice.\n");
                break;
            }
            printf("Guard details updated successfully.\n");
            return;  // Exit after updating
        }
    }
    printf("Guard with ID %d not found.\n", input);  // If not found
}

// Function to display all guards
void display_guard(struct guardd guard[], int size) {
    if (size == 0) {
        printf("No guards registered yet.\n");
    } else {
        printf("Guard details:\n");
        for (int i = 0; i < size; i++) {
            printf("ID: %d, Active: %s, Patrol: %s, Shift: %s\n",
                guard[i].guard_id,
                guard[i].is_active ? "Yes" : "No",
                guard[i].patrol_point,
                guard[i].shift);
        }
    }
}

void insertion_sort_by_id(struct guardd guard[], int size) {
    for (int i = 1; i < size; i++) {
        struct guardd key = guard[i];
        int j = i - 1;
        while (j >= 0 && guard[j].guard_id > key.guard_id) {
            guard[j + 1] = guard[j];
            j--;
        }
        guard[j + 1] = key;
    }
    printf("Guards sorted by ID.\n");
}

int partition_by_id(struct guardd guard[], int low, int high) {
    int pivot = guard[high].guard_id;
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (guard[j].guard_id <= pivot) {
            i++;
            // Swap guard[i] and guard[j]
            struct guardd temp = guard[i];
            guard[i] = guard[j];
            guard[j] = temp;
        }
    }
    // Swap guard[i+1] and guard[high]
    struct guardd temp = guard[i + 1];
    guard[i + 1] = guard[high];
    guard[high] = temp;
    return i + 1;
}

void quick_sort_by_id(struct guardd guard[], int low, int high) {
    if (low < high) {
        int pi = partition_by_id(guard, low, high);
        quick_sort_by_id(guard, low, pi - 1);
        quick_sort_by_id(guard, pi + 1, high);
    }
}

int main(void) {
    guard();
    return 0;
}
