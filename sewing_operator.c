#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "factory.h"

SewingOperator *operator_head = NULL;

// Add new sewing operator to the system (front addition)
void add_sewing_operator(int operator_id, int machine_id, char *piece_type, int pieces_completed, float salary)
{
    SewingOperator *newNode = (SewingOperator *)malloc(sizeof(SewingOperator));
    newNode->operator_id = operator_id;
    newNode->machine_id = machine_id;
    strcpy(newNode->piece_type, piece_type);
    newNode->pieces_completed = pieces_completed;
    newNode->salary = salary;
    newNode->next = operator_head;

    operator_head = newNode;
    printf("New sewing operator with ID %d successfully added to the system", operator_id);
}

// Increments the number of pieces completed by the sewing operator with the new record
void increase_sewing_operator_pieces_completed(int operator_id, int new_pieces_completed)
{
    SewingOperator *current = operator_head;
    while (current != NULL)
    {
        if (current->operator_id == operator_id)
        {
            current->pieces_completed += new_pieces_completed;
            printf("The new %d pieces completed by the sewing operator %d successfully updated", new_pieces_completed, operator_id);
            return;
        }
        current = current->next;
    }
    printf("Error: sewing operator %d not found", operator_id);
}

// Update the details of the sewing operator
void update_sewing_operator_details(int operator_id, int new_machine_id, char *new_piece_type, float new_salary)
{
    /*
    NOTE: In update_sewing_operator_details,
    NULL can be used for fields that do not change (excluding operator_id) and
    for new_salary, 0 or negative values can be used to indicate no change.
    */
    SewingOperator *current = operator_head;
    while (current != NULL)
    {
        if (current->operator_id == operator_id)
        {
            if (new_machine_id != 0)
            {
                current->machine_id = new_machine_id;
            }
            if (new_piece_type[0] != '\0')
            {
                strcpy(current->piece_type, new_piece_type);
            }
            if (new_salary > 0)
            {
                current->salary = new_salary;
            }
            printf("The changed details of the sewing operator %d successfully updated", operator_id);
            return;
        }
        current = current->next;
    }
    printf("Error: sewing operator %d not found", operator_id);
}

// Delete a sewing operator from the system
void delete_sewing_operator(int operator_id)
{
    SewingOperator *current = operator_head;
    while (current != NULL)
    {
        if (current->operator_id == operator_id)
        {
            operator_head = current->next;
            free(current);
            printf("The sewing operator with ID %d successfully deleted from the system", operator_id);
            return;
        }
        current = current->next;
    }
    printf("Error: sewing operator %d not found", operator_id);
}

// Display all the sewing operators in the system
void display_sewing_operators()
{
    SewingOperator *current = operator_head;
    if (current == NULL)
    {
        printf("No sewing operators in the system");
        return;
    }
    printf("\n--- List of Sewing Operators ---\n");
    int count = 0;
    while (current != NULL)
    {
        printf("%d. Operator ID: %d | Machine ID: %d | Piece Type: %s | Pieces Completed: %d | Salary: %.2f\n",
               ++count, current->operator_id, current->machine_id, current->piece_type, current->pieces_completed, current->salary);
        current = current->next;
    }
    printf("--------------------------------------\n");
}

// Sort sewing operators by the number of pieces completed in descending order
void sort_sewing_operators_by_completed()
{
    if (operator_head == NULL || operator_head->next == NULL)
    {
        return; // No need to sort if the list is empty or has only one operator
    }
    SewingOperator *sorted = NULL; // New sorted list
    SewingOperator *current = operator_head;
    while (current != NULL)
    {
        SewingOperator *next = current->next; // Store next operator
        // Insert current operator into the sorted list
        if (sorted == NULL || current->pieces_completed > sorted->pieces_completed)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            SewingOperator *temp = sorted;
            while (temp->next != NULL && temp->next->pieces_completed >= current->pieces_completed)
            {
                temp = temp->next;
            }
            current->next = temp->next;
            temp->next = current;
        }
        current = next; // Move to the next operator
    }
    operator_head = sorted; // Update operator_head to the new sorted list
    printf("Sewing operators successfully sorted by pieces completed in descending order");
}
