#ifndef FACTORY_H
#define FACTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ==========================================
// 1. Receiving Dock (Queue) - Themiya
// ==========================================
typedef struct Truck
{
    int truck_id;
    int priority;
    char supplier[50];
    char material_type[30];
    char date[20];
    struct Truck *next;
} Truck;

typedef struct Queue
{
    Truck *front;
    Truck *rear;
} Queue;

typedef struct Group
{
    char key[50];
    int count;
    int *positions;
} Group;

void initialize_queue(struct Queue *queue);
Truck *create_truck(int id, int priority, char supplier[], char material[], char date[]);
bool isEmpty(const struct Queue *queue);
void enqueue_truck(struct Queue *queue, int id, int priority, char supplier[], char material[], char date[]);
void dequeue_truck(struct Queue *queue);
void display_dock(const struct Queue *queue);
void sortByPriority(struct Queue *queue);
void groupBy(const struct Queue *queue, char type);

// ==========================================
// 2. Main Warehouse (DLL) - Anushka
// ==========================================
typedef struct WarehouseItem
{
    int slot_no;
    char material_type[30];
    float stock_kg;
    struct WarehouseItem *prev;
    struct WarehouseItem *next;
} WarehouseItem;

extern WarehouseItem *warehouse_head;

void add_warehouse_item(int slot, char *mat, float stock);
void update_warehouse_item(int slot, float new_stock);
void delete_warehouse_item(int slot);
void display_warehouse();
void search_warehouse_item(char *query);
void sort_warehouse_items(int criteria, int order);

// ==========================================
// 3. Secondary Stock (DLL) - Sasadhara
// ==========================================

typedef struct SecondaryStockItem
{
    char material_type[30];
    float stock_kg;
    struct SecondaryStockItem *prev, *next;
} SecondaryStockItem;

extern SecondaryStockItem *secondary_head;

void add_secondary_item(char *mat, float stock);
void update_secondary_item(char *mat, float new_stock);
void delete_secondary_item(char *mat);
void display_secondary();
void count_secondary_items();
void find_max_min_stock();

// ==========================================
// 4. Production Floor (Array) - Dulaksha
// ==========================================

#define MAX_MACHINES 100
typedef struct machine
{
    int id;
    char status[20];
    int maintenance_req;
} Machine;

int insert_at(Machine arr[], int position, int id, char status[20], int maintain, int size, int max);
int delete_by_position(Machine arr[], int position, int size);
int delete_by_id(Machine arr[], int id, int size);
void traverse(Machine arr[], int size);
void update_by_position(Machine arr[], int position, int size, char status[20], int maintain);
void update_by_id(Machine arr[], int id, int size, char status[20], int maintain);
void bubble_sort_by_id(Machine arr[], int size);
void show_maintenance(Machine arr[], int size);

// ==========================================
// 5. Sewing Operator (Linked List) - Akash
// ==========================================

typedef struct SewingOperator
{
    int operator_id;
    int machine_id;
    char piece_type[30];
    int pieces_completed;
    float salary;
    struct SewingOperator *next;
} SewingOperator;

extern SewingOperator *head;

void add_sewing_operator(int operator_id, int machine_id, char *piece_type, int pieces_completed, float salary);
void increase_sewing_operator_pieces_completed(int operator_id, int new_pieces_completed);
void update_sewing_operator_details(int operator_id, int new_machine_id, char *new_piece_type, float new_salary);
/*
NOTE: In update_sewing_operator_details,
NULL can be used for fields that do not change (excluding operator_id) and
for new_salary, 0 or negative values can be used to indicate no change.
*/
void delete_sewing_operator(int operator_id);
void display_sewing_operators();
void sort_sewing_operators_by_completed();

// ==========================================
// 6. Order Dispatch (Linked List) - Prabuddha
// ==========================================

typedef struct Order{
    int order_id;
    int receiver_id;
    int priority;
    char item_type;
    int item_count;
    float price;
struct Order* next;
}Order;

extern Order* orderhead;
void add_order(int order_id,int receiver_id,int priority,char item_type,int item_count,float price);
void update_order(int order_id,int receiver_id,int priority,char item_type,int item_count,float price);
void delete_order(int order_id);
void display_orders();

// ==========================================
// 7. Security (Array) - Yasiru's Part
// ==========================================

#define MAX_GUARDS 50
typedef struct
{
    int guard_id;
    int is_active;
    char patrol_point[30];
    char shift[20];
} Guard;

void add_guard(int id, int active, char *point, char *shift);
void update_guard(int id, int active, char *point, char *shift);
void delete_guard(int id);
void display_security();

#endif
