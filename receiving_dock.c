void initialize_queue(Queue* queue){
    queue->front = NULL;
    queue->rear = NULL;
}

Truck* create_truck(int id, int priority, char supplier[], char material[], char date[]){
    Truck* newTruck = (Truck*)malloc(sizeof(Truck));

    if(newTruck == NULL){
        printf("Truck Allocation Failed.\n");
        return NULL;
    }
    newTruck->truck_id = id;
    newTruck->priority = priority;
    strcpy(newTruck->supplier, supplier);
    strcpy(newTruck->material_type, material);
    strcpy(newTruck->date, date);
    newTruck->next = NULL;

    return newTruck;
}

bool isEmpty(const Queue* queue){
    return queue->front == NULL;
}

void enqueue_truck(Queue *queue, int id, int priority, char supplier[], char material[], char date[]) {
    Truck* newTruck = create_truck(id, priority, supplier, material, date);

    if(newTruck == NULL) return;
    if(isEmpty(queue)){
        queue->front = newTruck;
        queue->rear = newTruck;
    }
    else{
        queue->rear->next = newTruck;
        queue->rear = newTruck;
    }
}

void dequeue_truck(Queue* queue){
    if(isEmpty(queue)){
        printf("Queue is empty.\n");
        return;
    }
    Truck* temp = queue->front;
    queue->front = temp->next;

    if (queue->front == NULL){
        queue->rear = NULL;
    }
    free(temp);
}

void display_dock(const Queue* queue) {
    if(isEmpty(queue)){
        printf("Queue is empty.\n");
        return;
    }

    Truck* temp = queue->front;

    printf("\n");
    while (temp != NULL) {
        printf("ID:%d Priority:%d\n\tSupplier:%s Material:%s Date:%s\n",
               temp->truck_id,
               temp->priority,
               temp->supplier,
               temp->material_type,
               temp->date);
        temp = temp->next;
    }
    printf("\n");
}

void sortByPriority(const Queue* queue) {
    if (isEmpty(queue) || queue->front == queue->rear){
        return;
    }

    bool swapped;
    Truck *current;
    Truck *endSorted = NULL;

    do {
        swapped = false;
        current = queue->front;

        while (current->next != endSorted) {
            if (current->priority > current->next->priority) {
                Truck temp = *current;
                current->truck_id = current->next->truck_id;
                current->priority = current->next->priority;
                strcpy(current->supplier, current->next->supplier);
                strcpy(current->material_type, current->next->material_type);
                strcpy(current->date, current->next->date);

                current->next->truck_id = temp.truck_id;
                current->next->priority = temp.priority;
                strcpy(current->next->supplier, temp.supplier);
                strcpy(current->next->material_type, temp.material_type);
                strcpy(current->next->date, temp.date);

                swapped = true;
            }
            current = current->next;
        }
        endSorted = current;
    } while (swapped);
}

//Priority: P/p
//Supplier: S/s
//Material: M/m
void groupBy(const Queue* queue, char type) {
    if (isEmpty((Queue*)queue)) {
        printf("Queue is empty.\n");
        return;
    }

    const Truck* temp = queue->front;
    type = tolower(type);

    Group *groups = NULL;
    int groupCount = 0;
    int pos = 1;

    while (temp != NULL) {
        char currentKey[50];
        switch (type) {
            case 'p':
                snprintf(currentKey, sizeof(currentKey), "%d", temp->priority);
                break;
            case 's':
                strcpy(currentKey, temp->supplier);
                break;
            case 'm':
                strcpy(currentKey, temp->material_type);
                break;
            default:
                printf("Invalid grouping type.\n");
                goto cleanup;
        }

        int found = -1;

        if (groups != NULL){
            for (int i = 0; i < groupCount; i++) {
                if (strcmp(groups[i].key, currentKey) == 0) {
                    found = i;
                    break;
                }
            }
        }

        if (found == -1) {
            Group *newGroups = realloc(groups, (groupCount + 1) * sizeof(struct Group));
            if (newGroups == NULL) {
                printf("Group Allocation Failed.\n");
                goto cleanup;
            }
            groups = newGroups;

            strcpy(groups[groupCount].key, currentKey);
            groups[groupCount].count = 0;
            groups[groupCount].positions = NULL;

            found = groupCount;
            groupCount++;
        }

        Group *g = &groups[found];

        int *newPos = realloc(g->positions, (g->count + 1) * sizeof(int));
        if (newPos == NULL) {
            printf("Position Allocation Failed.\n");
            goto cleanup;
        }
        g->positions = newPos;

        g->positions[g->count++] = pos;

        temp = temp->next;
        pos++;
    }

    if (groups != NULL){
        printf("\n--- Grouped Result ---\n");
        for (int i = 0; i < groupCount; i++) {
            switch(type) {
            case 'p':
                printf("Priority %s: ", groups[i].key);
                break;
            case 's':
                printf("Supplier %s: ", groups[i].key);
                break;
            case 'm':
                printf("Material %s: ", groups[i].key);
                break;
            default: ;
            }

            printf("%d trucks --> Positions: ", groups[i].count);
            for (int j = 0; j < groups[i].count; j++) {
                printf("%d ", groups[i].positions[j]);
            }
            printf("\n");
        }
    }

    cleanup:
        if (groups != NULL) {
            for (int i = 0; i < groupCount; i++) {
                free(groups[i].positions);
            }
            free(groups);
        }
}
