# Textile ERP
Simple program that models a system of an textile manufacturing company to better understand the concepts and get hands on experience in practical applications of Data Structures and Algorithms

## Task:
* Create a console-based C program to store and process data in any industry.
* At least 4 data structures should be used. (Array, Linked List, Doubly Linked List, Queue)
* Data management tasks (insert/ delete/ search/ etc.) should be performed as well, and suitable sorting algorithms, control structures, etc, are to be used.

## System Overview:
### 1. Receiving Dock
* Data Structure: **Queue**
* Data Elements: `{truck_id, priority, supplier, material_type, date}`
* Special Task: Sorted by `priority`

### 2. Main Warehouse
* Data Structure: **Doubly Linked List**
* Data Elements: `{slot_no, material_type, stock_kg}`
* Special Task: Sorted by `slot_no`, `material_type`, or `stock_kg`

### 3. Secondary Stock
* Data Structure: **Doubly Linked List**
* Data Elements: `{material_type, stock_kg}`
* Special Task: Total of `stock_kg` counted

### 4. Production Floor
* Data Structure: **Array**
* Data Elements: `{machine_id, status, maintainance_req}`
* Special Task: Sorted by `machine_id`

### 5. Sewing Operator
* Data Structure: **Linked List**
* Data Elements: `{operator_id, machine_id, piece_type, pieces_completed, salary}`
* Special Task: Sorted by `pieces_completed`

### 6. Order Dispatch
* Data Structure: **Linked List**
* Data Elements: `{order_id, receiver, priority, item, item_count, price}`
* Special Task: Sorted by `priority`

### 7. Security
* Data Structure: **Array**
* Data Elements: `{guard_id, is_active, patrol_point, shift}`
* Special Task: *add task*
