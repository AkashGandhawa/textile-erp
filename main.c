#include "factory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Menu Functions ---
void show_menu()
{
    printf("\n--- Garment Factory Management System (Group Project) ---\n");
    printf("1. Receiving Dock\n");
    printf("2. Main Warehouse\n");
    printf("3. Secondary Stock\n");
    printf("4. Production Floor\n");
    printf("5. Sewing Operator\n");
    printf("6. Order Dispatch\n");
    printf("7. Security\n");
    printf("0. Exit\n");
}

void clear_input()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

// --- Operation Functions ---
// 1. Receiving Dock (Queue) - Themiya
void receiving_dock_menu()
{
    printf("\n--- Receiving Dock ---\n");
    Queue dockQueue;
    initialize_queue(&dockQueue);
    int subChoice;
    int id, priority;
    char supplier[50], material[30], date[20], groupType;
    while (1)
    { // Added a loop so the user stays in the menu until they choose 'Back'
        printf("1. Register New Truck (Enqueue)\n");
        printf("2. Release Next Truck (Dequeue)\n");
        printf("3. Display All Trucks in Dock\n");
        printf("4. Sort Queue by Priority\n");
        printf("5. Group Trucks (by Priority, Supplier, or Material)\n");
        printf("6. Exit\n");
        printf("Enter choice: ");

        if (scanf("%d", &subChoice) != 1)
        {
            clear_input();
            continue;
        }

        switch (subChoice)
        {
        case 1:
            printf("Enter Truck ID: ");
            scanf("%d", &id);
            printf("Enter Priority (1-high, 10-low): ");
            scanf("%d", &priority);
            clear_input(); // Clear before strings

            printf("Enter Supplier: ");
            fgets(supplier, sizeof(supplier), stdin);
            supplier[strcspn(supplier, "\n")] = 0; // Remove newline

            printf("Enter Material Type: ");
            fgets(material, sizeof(material), stdin);
            material[strcspn(material, "\n")] = 0;

            printf("Enter Date (DD/MM/YYYY): ");
            fgets(date, sizeof(date), stdin);
            date[strcspn(date, "\n")] = 0;

            enqueue_truck(&dockQueue, id, priority, supplier, material, date);
            printf("Truck registered successfully!\n");
            break;
        case 2:
            printf("Processing truck at the front of the queue...\n");
            dequeue_truck(&dockQueue);
            break;
        case 3:
            printf("--- Current Dock Queue ---\n");
            display_dock(&dockQueue);
            break;
        case 4:
            printf("Sorting queue by priority (Bubble Sort)... \n");
            sortByPriority(&dockQueue);
            printf("Queue sorted.\n");
            display_dock(&dockQueue);
            break;
        case 5:
            printf("Group by Priority: ");
            clear_input();
            scanf("%c", &groupType);
            groupBy(&dockQueue, groupType);
            break;
        case 6:
            return; // Exit back to main menu
        default:
            printf("Invalid choice.\n");
            break;
        }
    }
}

// 2. Main Warehouse (DLL) - Anushka
void warehouse_menu()
{
    int subChoice, id;
    char mat[30];
    float stock;
    int con = 1;

    printf("\n--- Main Warehouse ---\n");
    printf("1. Add Item\n");
    printf("2. Update Stock\n");
    printf("3. Delete Item\n");
    printf("4. Display\n");
    printf("5. Search Item\n");
    printf("6. Sort Items\n");
    printf("7. Back\n");
    printf("Choice: ");
    scanf("%d", &subChoice);

    switch (subChoice)
    {
    case 1:
        printf("Slot No, Material, Stock(kg): ");
        scanf("%d %s %f", &id, mat, &stock);
        add_warehouse_item(id, mat, stock);
        break;
    case 2:
        printf("Slot No, New Stock: ");
        scanf("%d %f", &id, &stock);
        update_warehouse_item(id, stock);
        break;
    case 3:
        while (con)
        {
            printf("Enter Slot No to delete (or -1 to stop): ");
            scanf("%d", &id);
            delete_warehouse_item(id, &con);
        }
        break;
    case 4:
        display_warehouse();
        break;
    case 5:
        printf("Enter material type to search: ");
        scanf("%s", mat);
        search_warehouse_item(mat);
        break;
    case 6:
        int criteria, order;
        printf("Sort by: 1=Slot No, 2=Material, 3=Stock\n");
        scanf("%d", &criteria);
        printf("Order: 1=Ascending, -1=Descending\n");
        scanf("%d", &order);
        sort_warehouse_items(criteria, order);
        break;
    case 7:
        return; // Back to main menu
    default:
        printf("Invalid choice. Please try again.\n");
        break;
    }
}

// 3. Secondary Stock (DLL) - Sasadhara
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
    printf("6. Find Max/Min Stock\n");
    printf("7. Back\n");
    printf("Choice: ");
    scanf("%d", &subChoice);

    switch (subChoice)
    {
    case 1:
        printf("Enter Material Type (one word) and Stock(kg): ");
        scanf("%s %f", mat, &stock);
        add_secondary_item(mat, stock);
        break;
    case 2:
        printf("Enter Material Type to Update and New Stock(kg): ");
        scanf("%s %f", mat, &stock);
        update_secondary_item(mat, stock);
        break;
    case 3:
        printf("Enter Material Type to Delete: ");
        scanf("%s", mat);
        delete_secondary_item(mat);
        break;
    case 4:
        display_secondary();
        break;
    case 5:
        count_secondary_items();
        break;
    case 6:
        find_max_min_stock();
        break;
    case 7:
        return; // Back to main menu
    default:
        printf("Invalid choice. Please try again.\n");
        break;
    }
}

// 4. Production Floor (Array) - Dulaksha
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

    switch (subChoice)
    {
    case 1:
    {
        int id, maintain, position;
        char status[20];
        printf("Enter Position, ID, Status, Maintenance(0/1): ");
        scanf("%d %d %s %d", &position, &id, status, &maintain);
        machine_size = insert_at(machines, position, id, status, maintain, machine_size, MAX_MACHINES);
        break;
    }
    case 2:
    {
        int position;
        printf("Enter Position: ");
        scanf("%d", &position);
        machine_size = delete_by_position(machines, position, machine_size);
        break;
    }
    case 3:
    {
        int id;
        printf("Enter ID: ");
        scanf("%d", &id);
        machine_size = delete_by_id(machines, id, machine_size);
        break;
    }
    case 4:
    {
        int position, maintain;
        char status[20];
        printf("Enter Position, New Status, Maintenance(0/1): ");
        scanf("%d %s %d", &position, status, &maintain);
        update_by_position(machines, position, machine_size, status, maintain);
        break;
    }
    case 5:
    {
        int id, maintain;
        char status[20];
        printf("Enter ID, New Status, Maintenance(0/1): ");
        scanf("%d %s %d", &id, status, &maintain);
        update_by_id(machines, id, machine_size, status, maintain);
        break;
    }
    case 6:
        traverse(machines, machine_size);
        break;
    case 7:
        bubble_sort_by_id(machines, machine_size);
        break;
    case 8:
        show_maintenance(machines, machine_size);
        break;
    case 9:
        return; // Back to main menu
    default:
        printf("Invalid choice. Please try again.\n");
        break;
    }
}

// 5. Sewing Operator (Linked List) - Akash
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

    switch (subChoice)
    {
    case 1:
    {
        int operator_id, machine_id, pieces_completed;
        char piece_type[30];
        float salary;
        printf("Enter Operator ID, Machine ID, Piece Type, Pieces Completed, Salary: ");
        scanf("%d %d %s %d %f", &operator_id, &machine_id, piece_type, &pieces_completed, &salary);
        add_sewing_operator(operator_id, machine_id, piece_type, pieces_completed, salary);
        break;
    }
    case 2:
    {
        int operator_id, new_pieces;
        printf("Enter Operator ID and new pieces completed: ");
        scanf("%d %d", &operator_id, &new_pieces);
        increase_sewing_operator_pieces_completed(operator_id, new_pieces);
        break;
    }
    case 3:
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
        break;
    }
    case 4:
    {
        int operator_id;
        printf("Enter Operator ID to delete: ");
        scanf("%d", &operator_id);
        delete_sewing_operator(operator_id);
        break;
    }
    case 5:
        display_sewing_operators();
        break;
    case 6:
        sort_sewing_operators_by_completed();
        break;
    case 7:
        return; // Back to main menu
    default:
        printf("Invalid choice. Please select 1-7.\n");
        break;
    }
}

// 6. Order Dispatch (Linked List) - Prabuddha
void order_dispatch_menu()
{
    int subChoice;
    printf("\n--- Order Dispatch ---\n");
    printf("1. Add Order\n");
    printf("2. Update Order\n");
    printf("3. Delete Order\n");
    printf("4. Display Orders\n");
    printf("5. Sort by Priority\n");
    printf("6. Back\n");
    printf("Choice: ");
    scanf("%d", &subChoice);

    switch (subChoice)
    {
    case 1:
    {
        int order_id, receiver_id, priority, item_count;
        char item_type[30];
        float price;
        printf("Enter Order ID, Receiver ID, Priority, Item Type, Item Count, Price: ");
        scanf("%d %d %d %s %d %f", &order_id, &receiver_id, &priority, item_type, &item_count, &price);
        add_order(order_id, receiver_id, priority, item_type, item_count, price);
        break;
    }
    case 2:
    {
        int order_id, receiver_id, priority, item_count;
        char item_type[30];
        float price;
        printf("Enter Order ID, Receiver ID, Priority, Item Type, Item Count, Price: ");
        scanf("%d %d %d %s %d %f", &order_id, &receiver_id, &priority, item_type, &item_count, &price);
        update_order(order_id, receiver_id, priority, item_type, item_count, price);
        break;
    }
    case 3:
    {
        int order_id;
        printf("Enter Order ID to delete: ");
        scanf("%d", &order_id);
        delete_order(order_id);
        break;
    }
    case 4:
        display_orders();
        break;
    case 5:
        sort_orders_by_priority();
        break;
    case 6:
        return; // Back to main menu
    default:
        printf("Invalid choice. Please select 1-6.\n");
        break;
    }
}

// 7. Security (Array) - Yasiru
void security_menu()
{
    printf("\n--- Security ---\n");
    Guard guard[20];
    int input = 0;
    int size = 0;

    while (1)
    {
        printf("You're in security panel. What do you want to do?\n");
        printf("Enter details of a new guard -> 1\n");
        printf("Update guard details -> 2\n");
        printf("Delete a guard -> 3\n");
        printf("View all guard details -> 4\n");
        printf("Exit -> -1\n");
        scanf("%d", &input);

        switch (input)
        {
        case 1:
            add_guard(guard, &size);
            break;
        case 2:
            update_guard(guard, size);
            break;
        case 3:
            printf("Enter guard ID to delete: ");
            scanf("%d", &input);
            delete_guard(guard, &size, input);
            break;
        case 4:
            display_guard(guard, size);
            break;
        case -1:
            return; // exit the function
        default:
            printf("Invalid input. Please try again.\n");
            Sleep(500);
            break;
        }
    }
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
            break;
        default:
            printf("Invalid choice. Please select 0-7.\n");
        }
    }
    return 0;
}
