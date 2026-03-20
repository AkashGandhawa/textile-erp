#ifndef FACTORY_H
#define FACTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==========================================
// 1. Receiving Dock (Queue) - Themiya's Part
// ==========================================
/*
typedef struct Truck {
    int truck_id;
    char supplier[50];
    char material_type[30];
    char date[20];
    struct Truck* next;
} Truck;

void enqueue_truck(int id, char* supp, char* mat, char* date);
void dequeue_truck();
void display_dock();
*/

// ==========================================
// 2. Main Warehouse (DLL) - Anushka's Part
// ==========================================
typedef struct WarehouseItem {
    int slot_no;
    char material_type[30];
    float stock_kg;
    struct WarehouseItem* prev;
    struct WarehouseItem* next;
} WarehouseItem;

extern WarehouseItem* head;

void add_warehouse_item(int slot, char* mat, float stock);
void update_warehouse_item(int slot, float new_stock);
void delete_warehouse_item(int slot);
void display_warehouse();

// ==========================================
// 3. Secondary Stock (DLL) - Sasadhara's Part
// ==========================================

typedef struct SecondaryStockItem {
    char material_type[30];
    float stock_kg;
    struct SecondaryStockItem *prev, *next;
} SecondaryStockItem;

void add_secondary_item(char* mat, float stock);
void update_secondary_item(char* mat, float new_stock);
void delete_secondary_item(char* mat);
void display_secondary();


// ==========================================
// 4. Production Floor (Array) - Dulaksha's Part
// ==========================================
/*
#define MAX_MACHINES 100
typedef struct {
    int machine_id;
    char status[20];
    int maintenance_req;
} Machine;

void add_machine(int id, char* status, int req);
void update_machine(int id, char* status, int req);
void delete_machine(int id);
void display_machines();
*/

// ==========================================
// 5. Sewing Operator (Linked List) - Akash's Part
// ==========================================

typedef struct SewingOperator {
    int operator_id;
    int machine_id;
    char piece_type[30];
    int pieces_completed;
    float salary;
    struct SewingOperator* next;
} SewingOperator;

extern SewingOperator *head;

void add_sewing_operator(int operator_id, int machine_id, char* piece_type, int pieces_completed, float salary);
void increase_sewing_operator_pieces_completed(int operator_id, int new_pieces_completed);
void update_sewing_operator_details(int operator_id, int new_machine_id, char* new_piece_type, float new_salary);
/*
NOTE: In update_sewing_operator_details,
NULL can be used for fields that do not change (excluding operator_id) and
for new_salary, 0 or negative values can be used to indicate no change.
*/
void delete_sewing_operator(int operator_id);
void display_sewing_operators();
void sort_sewing_operators_by_completed();

// ==========================================
// 6. Order Dispatch (Linked List) - Prabuddha's Part
// ==========================================
/*
typedef struct Order {
    int order_id;
    char receiver[50];
    int priority;
    char item[30];
    int item_count;
    float price;
    struct Order* next;
} Order;

// Note: Sort by priority
void add_order(int id, char* rec, int priority, char* item, int count, float price);
void update_order(int id, int count);
void delete_order(int id);
void display_orders();
*/

// ==========================================
// 7. Security (Array) - Yasiru's Part
// ==========================================
/*
#define MAX_GUARDS 50
typedef struct {
    int guard_id;
    int is_active;
    char patrol_point[30];
    char shift[20];
} Guard;

void add_guard(int id, int active, char* point, char* shift);
void update_guard(int id, int active, char* point, char* shift);
void delete_guard(int id);
void display_security();
*/

#endif
