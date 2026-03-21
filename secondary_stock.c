#include "factory.h"

// 1. Add an item to the end of the DLL
void add_secondary_item(char *mat, float stock)
{
    SecondaryStockItem *newItem = (SecondaryStockItem *)malloc(sizeof(SecondaryStockItem));
    if (!newItem)
    {
        printf("Memory allocation failed!\n");
        return;
    }

    // Safely copy the string
    strncpy(newItem->material_type, mat, 29);
    newItem->material_type[29] = '\0';
    newItem->stock_kg = stock;
    newItem->next = NULL;

    // If the list is empty, this becomes the head
    if (secondary_head == NULL)
    {
        newItem->prev = NULL;
        secondary_head = newItem;
    }
    else
    {
        // Traverse to the end of the list
        SecondaryStockItem *temp = secondary_head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newItem;
        newItem->prev = temp;
    }
    printf("\n[SUCCESS] Material '%s' added to Secondary Stock.\n", mat);
}

// 2. Update stock level for a specific material
void update_secondary_item(char *mat, float new_stock)
{
    SecondaryStockItem *temp = secondary_head;
    while (temp != NULL)
    {
        if (strcmp(temp->material_type, mat) == 0)
        {
            temp->stock_kg = new_stock;
            printf("\n[SUCCESS] Updated '%s' stock to %.2f kg.\n", mat, new_stock);
            return;
        }
        temp = temp->next;
    }
    printf("\n[ERROR] Material '%s' not found in Secondary Stock.\n", mat);
}

// 3. Delete an item from the DLL
void delete_secondary_item(char *mat)
{
    SecondaryStockItem *temp = secondary_head;

    while (temp != NULL)
    {
        if (strcmp(temp->material_type, mat) == 0)
        {
            if (temp == secondary_head)
            {
                secondary_head = temp->next;
            }
            if (temp->next != NULL)
            {
                temp->next->prev = temp->prev;
            }
            if (temp->prev != NULL)
            {
                temp->prev->next = temp->next;
            }
            free(temp);
            printf("\n[SUCCESS] Material '%s' removed from Secondary Stock.\n", mat);
            return;
        }
        temp = temp->next;
    }
    printf("\n[ERROR] Material '%s' not found, deletion failed.\n", mat);
}

// 4. Display all items
void display_secondary()
{
    SecondaryStockItem *temp = secondary_head;
    printf("\n========================================\n");
    printf("       SECONDARY STOCK INVENTORY        \n");
    printf("========================================\n");

    if (temp == NULL)
    {
        printf("Stock is currently empty.\n");
        printf("========================================\n");
        return;
    }

    printf("%-20s | %-10s\n", "Material Type", "Stock (kg)");
    printf("----------------------------------------\n");
    while (temp != NULL)
    {
        printf("%-20s | %-10.2f\n", temp->material_type, temp->stock_kg);
        temp = temp->next;
    }
    printf("========================================\n");
}

// 5. Count the total number of material types
void count_secondary_items() {
    SecondaryStockItem* temp = secondary_head;
    int count = 0;
    
    // Traverse the list and count each node
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    printf("\n========================================\n");
    printf("Total Material Types in Stock: %d\n", count);
    printf("========================================\n");
}
