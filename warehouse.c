#include "factory.h"

WarehouseItem *warehouse_head = NULL;

// Function to add a new item to the warehouse
void add_warehouse_item(int slot, char *mat, float stock)
{
    WarehouseItem *newNode = (WarehouseItem *)malloc(sizeof(WarehouseItem));
    newNode->slot_no = slot;
    strcpy(newNode->material_type, mat);
    newNode->stock_kg = stock;
    newNode->next = warehouse_head;
    newNode->prev = NULL;

    if (warehouse_head != NULL)
    {
        warehouse_head->prev = newNode;
    }
    warehouse_head = newNode;
    printf("Item added successfully to slot %d.\n", slot);
}

// Function to update stock in a specific slot
void update_warehouse_item(int slot, float new_stock)
{
    WarehouseItem *curr = warehouse_head;
    while (curr != NULL)
    {
        if (curr->slot_no == slot)
        {
            curr->stock_kg = new_stock;
            printf("Stock in slot %d updated to %.2f kg.\n", slot, new_stock);
            return;
        }
        curr = curr->next;
    }
    printf("Error: Slot %d not found.\n", slot);
}

// Function to delete an item from a specific slot
// If slot == -1, signal to exit the loop
void delete_warehouse_item(int slot, int *con)
{
    if (slot == -1)
    {
        *con = 0; // stop the loop
        return;
    }

    WarehouseItem *curr = warehouse_head;
    while (curr != NULL)
    {
        if (curr->slot_no == slot)
        {
            if (curr->prev != NULL)
            {
                curr->prev->next = curr->next;
            }
            else
            {
                warehouse_head = curr->next;
            }
            if (curr->next != NULL)
            {
                curr->next->prev = curr->prev;
            }
            free(curr);
            printf("Slot %d deleted successfully.\n", slot);
            return;
        }
        curr = curr->next;
    }
    printf("Error: Slot %d not found.\n", slot);
}

// Function to display all warehouse items
void display_warehouse()
{
    WarehouseItem *curr = warehouse_head;
    if (curr == NULL)
    {
        printf("Warehouse is empty.\n");
        return;
    }
    printf("\n--- Main Warehouse Inventory (Doubly Linked List) ---\n");
    while (curr != NULL)
    {
        printf("Slot No: %d | Material: %s | Stock: %.2f kg\n",
               curr->slot_no, curr->material_type, curr->stock_kg);
        curr = curr->next;
    }
    printf("----------------------------------------------------\n");
}

// Function to search for a warehouse item by material type
void search_warehouse_item(char *query)
{
    WarehouseItem *curr = warehouse_head;
    int found = 0;

    while (curr != NULL)
    {
        if (strcmp(curr->material_type, query) == 0)
        {
            printf("Found: Slot No: %d | Material: %s | Stock: %.2f kg\n",
                   curr->slot_no, curr->material_type, curr->stock_kg);
            found = 1;
        }
        curr = curr->next;
    }

    if (!found)
    {
        printf("No item found with material type '%s'.\n", query);
    }
}

// Function to sort warehouse items by criteria and order
void sort_warehouse_items(int criteria, int order)
{
    if (warehouse_head == NULL || warehouse_head->next == NULL)
    {
        printf("Warehouse has too few items to sort.\n");
        return;
    }

    int swapped;
    WarehouseItem *ptr;
    WarehouseItem *last = NULL;

    do
    {
        swapped = 0;
        ptr = warehouse_head;

        while (ptr->next != last)
        {
            int cmp = 0;
            if (criteria == 1) // slot number
                cmp = (ptr->slot_no - ptr->next->slot_no);
            else if (criteria == 2) // material type
                cmp = strcmp(ptr->material_type, ptr->next->material_type);
            else if (criteria == 3) // stock
                cmp = (ptr->stock_kg > ptr->next->stock_kg) ? 1 : (ptr->stock_kg < ptr->next->stock_kg ? -1 : 0);

            if ((order == 1 && cmp > 0) || (order == -1 && cmp < 0))
            {
                // Swap the contents of the nodes
                int tempSlot = ptr->slot_no;
                float tempStock = ptr->stock_kg;
                char tempMat[30];
                strcpy(tempMat, ptr->material_type);

                ptr->slot_no = ptr->next->slot_no;
                ptr->stock_kg = ptr->next->stock_kg;
                strcpy(ptr->material_type, ptr->next->material_type);

                ptr->next->slot_no = tempSlot;
                ptr->next->stock_kg = tempStock;
                strcpy(ptr->next->material_type, tempMat);

                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);

    printf("Warehouse items sorted successfully.\n");
}
