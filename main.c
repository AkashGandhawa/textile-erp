#include "factory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Menu Functions ---
void show_menu()
{
    printf("\n--- Garment Factory Management System (Group Project) ---\n");
    printf("1. Receiving Dock (Themiya - Queue)\n");
    printf("2. Main Warehouse (Anushka - Doubly Linked List)\n");
    printf("3. Secondary Stock (Sasadhara - Doubly Linked List)\n");
    printf("4. Production Floor (Dulaksha - Array)\n");
    printf("5. Sewing Operator (Akash - Linked List)\n");
    printf("6. Order Dispatch (Prabuddha - Linked List)\n");
    printf("7. Security (Yasiru - Array)\n");
    printf("0. Exit\n");
}

void clear_input()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// --- Case Functions ---
void receiving_dock_menu()
{
    printf("\n--- Receiving Dock ---\n");
    // TODO: add receiving dock menu and logic here
    printf("Space for Themiya to add Enqueue/Dequeue logic.\n");
    // Example call: enqueue_truck(...);
}

void warehouse_menu()
{
    int subChoice, id;
    char mat[30];
    float stock;

    printf("\n--- Main Warehouse ---\n");
    printf("1. Add Item\n2. Update Stock\n3. Delete Item\n4. Display\n5. Back\nChoice: ");
    scanf("%d", &subChoice);

    if (subChoice == 1)
    {
        printf("Slot No, Material, Stock(kg): ");
        scanf("%d %s %f", &id, mat, &stock);
        add_warehouse_item(id, mat, stock);
    }
    else if (subChoice == 2)
    {
        printf("Slot No, New Stock: ");
        scanf("%d %f", &id, &stock);
        update_warehouse_item(id, stock);
    }
    else if (subChoice == 3)
    {
        printf("Slot No: ");
        scanf("%d", &id);
        delete_warehouse_item(id);
    }
    else if (subChoice == 4)
    {
        display_warehouse();
    }
}

void secondary_stock_menu()
{
    int subChoice;
    char mat[30];
    float stock;

    printf("\n--- Secondary Stock ---\n");
    printf("1. Add Material\n");
    printf("2. Update Stock\n");
    printf("3. Delete Material\n");
    printf("4. Display Inventory\n");
    printf("5. Count Total Material Types\n");
    printf("6. Back\n");
    printf("Choice: ");
    scanf("%d", &subChoice);

    if (subChoice == 1)
    {
        printf("Enter Material Type (one word) and Stock(kg): ");
        scanf("%s %f", mat, &stock);
        add_secondary_item(mat, stock);
    }
    else if (subChoice == 2)
    {
        printf("Enter Material Type to Update and New Stock(kg): ");
        scanf("%s %f", mat, &stock);
        update_secondary_item(mat, stock);
    }
    else if (subChoice == 3)
    {
        printf("Enter Material Type to Delete: ");
        scanf("%s", mat);
        delete_secondary_item(mat);
    }
    else if (subChoice == 4)
    {
        display_secondary();
    }
    else if (subChoice == 5)
    {
        count_secondary_items();
    }
    else if (subChoice == 6)
    {
        // Explicitly exits the function to go back to the main menu
        return; 
    }
    else
    {
        printf("Invalid choice! Returning to main menu...\n");
    }
}


Machine machines[MAX_MACHINES];
int machine_size = 0;
void production_floor_menu()
{
    int subChoice;

    printf("\n--- Production Floor ---\n");
    printf("1. Insert Machine\n");
    printf("2. Delete by Position\n");
    printf("3. Delete by ID\n");
    printf("4. Update by Position\n");
    printf("5. Update by ID\n");
    printf("6. Display Machines\n");
    printf("7. Sort by ID\n");
    printf("8. Show Maintenance Required\n");
    printf("9. Back\n");
    printf("Choice: ");
    scanf("%d", &subChoice);

    if (subChoice == 1)
    {
        int id, maintain, position;
        char status[20];

        printf("Enter Position, ID, Status, Maintenance(0/1): ");
        scanf("%d %d %s %d", &position, &id, status, &maintain);

        machine_size = insert_at(machines, position, id, status, maintain, machine_size, MAX_MACHINES);
    }
    else if (subChoice == 2)
    {
        int position;
        printf("Enter Position: ");
        scanf("%d", &position);

        machine_size = delete_by_position(machines, position, machine_size);
    }
    else if (subChoice == 3)
    {
        int id;
        printf("Enter ID: ");
        scanf("%d", &id);

        machine_size = delete_by_id(machines, id, machine_size);
    }
    else if (subChoice == 4)
    {
        int position, maintain;
        char status[20];

        printf("Enter Position, New Status, Maintenance(0/1): ");
        scanf("%d %s %d", &position, status, &maintain);

        update_by_position(machines, position, machine_size, status, maintain);
    }
    else if (subChoice == 5)
    {
        int id, maintain;
        char status[20];

        printf("Enter ID, New Status, Maintenance(0/1): ");
        scanf("%d %s %d", &id, status, &maintain);

        update_by_id(machines, id, machine_size, status, maintain);
    }
    else if (subChoice == 6)
    {
        traverse(machines, machine_size);
    }
    else if (subChoice == 7)
    {
        bubble_sort_by_id(machines, machine_size);
        
    }
    else if (subChoice == 8)
    {
        show_maintenance(machines, machine_size);
    }
}

void sewing_operator_menu()
{
    int subChoice;
    printf("\n--- Sewing Operator ---\n");
    printf("1. Add Operator\n");
    printf("2. Increase Pieces Completed\n");
    printf("3. Update Operator Details\n");
    printf("4. Delete Operator\n");
    printf("5. Display Operators\n");
    printf("6. Sort by Pieces Completed\n");
    printf("7. Back\n");
    printf("Choice: ");
    scanf("%d", &subChoice);

    if (subChoice == 1)
    {
        int operator_id, machine_id, pieces_completed;
        char piece_type[30];
        float salary;
        printf("Enter Operator ID, Machine ID, Piece Type, Pieces Completed, Salary: ");
        scanf("%d %d %s %d %f", &operator_id, &machine_id, piece_type, &pieces_completed, &salary);
        add_sewing_operator(operator_id, machine_id, piece_type, pieces_completed, salary);
    }
    else if (subChoice == 2)
    {
        int operator_id, new_pieces;
        printf("Enter Operator ID and new pieces completed: ");
        scanf("%d %d", &operator_id, &new_pieces);
        increase_sewing_operator_pieces_completed(operator_id, new_pieces);
    }
    else if (subChoice == 3)
    {
        int operator_id, new_machine_id;
        char new_piece_type[30];
        float new_salary;
        printf("Enter Operator ID: ");
        scanf("%d", &operator_id);
        printf("Enter new Machine ID (or -1 to skip): ");
        scanf("%d", &new_machine_id);
        printf("Enter new Piece Type (or '-' to skip): ");
        scanf("%s", new_piece_type);
        printf("Enter new Salary (or <=0 to skip): ");
        scanf("%f", &new_salary);

        if (new_machine_id == -1)
            new_machine_id = -1; // skip
        if (strcmp(new_piece_type, "-") == 0)
            new_piece_type[0] = '\0'; // skip
        update_sewing_operator_details(operator_id, new_machine_id, new_piece_type, new_salary);
    }
    else if (subChoice == 4)
    {
        int operator_id;
        printf("Enter Operator ID to delete: ");
        scanf("%d", &operator_id);
        delete_sewing_operator(operator_id);
    }
    else if (subChoice == 5)
    {
        display_sewing_operators();
    }
    else if (subChoice == 6)
    {
        sort_sewing_operators_by_completed();
    }
}

void order_dispatch_menu()
{
    int subChoice;
    printf("\n---Order Dispatch ---\n");
    printf("1. Add Order\n");
    printf("2. Update Order\n");
    printf("3. Delete Order\n");
    printf("4. Display Order\n");
    printf("5. Sort by Priority\n");
    printf("6. Back\n");
    printf("Choice: ");
    scanf("%d", &subChoice);

    if (subChoice == 1)
    {
        int order_id, receiver_id, priority, item_count;
        char item_type[30];
        float price;
        printf("Enter Order ID, Receiver ID, Priority, Item Type, Item Count, Price: ");
        scanf("%d %d %d %s %d %f", &order_id, &receiver_id, &priority, item_type, &item_count, &price);
        add_order(order_id, receiver_id, priority, item_type, item_count, price);
    }
    else if (subChoice == 2)
    {
        int order_id, receiver_id, priority, item_count;
        char item_type[30];
        float price;
        printf("Enter Order ID, Receiver ID, Priority, Item Type, Item Count, Price: ");
        scanf("%d %d %d %s %d %f", &order_id, &receiver_id, &priority, item_type, &item_count, &price);
        update_order(order_id, receiver_id, priority, item_type, item_count, price);
    }
    else if (subChoice == 3)
    {
        int order_id;
        printf("Enter Order ID to delete: ");
        scanf("%d", &order_id);
        delete_order(order_id);
    }
    else if (subChoice == 4)
    {
        display_orders();
    }
    else if (subChoice == 5)
    {
        sort_orders_by_priority();
    }
    else if (subChoice == 6)
    {
        return;
    }
}

void security_menu()
{
    printf("\n--- Security ---\n");
    // TODO: add security guard menu and logic here
    printf("Space for Yasiru to add Add/Delete/Update logic.\n");
}

// --- Main ---
int main()
{
    int choice;
    while (1)
    {
        show_menu();
        printf("Enter choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input.\n");
            clear_input();
            continue;
        }

        switch (choice)
        {
        case 1:
            receiving_dock_menu();
            break;
        case 2:
            warehouse_menu();
            break;
        case 3:
            secondary_stock_menu();
            break;
        case 4:
            production_floor_menu();
            break;
        case 5:
            sewing_operator_menu();
            break;
        case 6:
            order_dispatch_menu();
            break;
        case 7:
            security_menu();
            break;
        case 0:
            printf("Exiting system...\n");
            exit(0);
        default:
            printf("Invalid choice. Please select 0-7.\n");
        }
    }
    return 0;
}
