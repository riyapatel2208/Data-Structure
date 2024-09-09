#include <stdio.h>
#include <stdlib.h>
#define N 4

typedef struct {
    int pid;
    int priority;
} Process;

void pqinsert(Process [], int *, int *, int, Process);
Process pqdelete(Process [], int *, int *, int);
void display(Process [], int, int, int);
void modify(Process [], int, int, int, int, Process);

void main() {
    Process q[N];
    int front = -1, rear = -1;
    Process data;
    int choice, position;
    clrscr();
    while (1) {
	printf("1. Insert Process\n");
	printf("2. Delete Process\n");
	printf("3. Display Processes\n");
	printf("4. Modify Process\n");
	printf("5. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice) {
	    case 1:
		printf("Enter process ID and priority to insert: ");
		scanf("%d %d", &data.pid, &data.priority);
		pqinsert(q, &front, &rear, N, data);
		break;
	    case 2:
		data = pqdelete(q, &front, &rear, N);
		if (data.pid != -1)
		    printf("Deleted Process ID: %d with Priority: %d\n", data.pid, data.priority);
		break;
	    case 3:
		display(q, front, rear, N);
		break;
	    case 4:
		printf("Enter the position to modify (0-based index from front): ");
		scanf("%d", &position);
		printf("Enter the new process ID and priority: ");
		scanf("%d %d", &data.pid, &data.priority);
		modify(q, front, rear, N, position, data);
		break;
	    default:
		exit(0);
	}
    }
}

void pqinsert(Process q[], int *front, int *rear, int n, Process val) {
    if ((*front == 0 && *rear == n - 1) || ((*rear + 1) == *front)) {
	printf("Overflow\n");
	return;
    }
    if (*rear == n - 1)
	*rear = 0;
    else
	*rear = *rear + 1;

    q[*rear] = val;
    if (*front == -1)
	*front = 0;
}

Process pqdelete(Process q[], int *front, int *rear, int n) {
    Process data = {-1, -1};
    if (*front == -1) {
	printf("Underflow\n");
	return data;
    }
    data = q[*front];
    if (*front == *rear) {
	*front = *rear = -1;
	return data;
    }
    if (*front == n - 1)
	*front = 0;
    else
	*front = *front + 1;

    return data;
}

void display(Process q[], int front, int rear, int n) {
    int i;
    if (front == -1)
	printf("\n\t\tQueue Empty\n");
    else {
	if (front <= rear) {
	    printf("\nFront(=%d)", front);
	    while (front <= rear) {
		printf("ProcessID=%d, Priority=%d] ", q[front].pid, q[front].priority);
		front++;
	    }
	    printf("<- Rear (= %d)\n", rear);
	} else {
	    printf("\n\t\tPos 0→");
	    i = 0;

	    while (i <= rear) {
		printf("[PID=%d, Priority=%d] ", q[i].pid, q[i].priority);
		i++;
	    }
	    printf("<- Rear (= %d)", rear);
	    if ((rear + 1) != front)
		printf(" - -");

	    i = front;
	    printf("Front (= %d)->", front);
	    while (i <= n - 1) {
		printf("[PID=%d, Priority=%d] ", q[i].pid, q[i].priority);
		i++;
	    }
	    printf("<- Pos N-1\n");
	}
    }
}

void modify(Process q[], int front, int rear, int n, int position, Process newValue) {
    int index;
    if (front == -1) {
	printf("Queue is empty, cannot modify\n");
	return;
    }
    index = (front + position) % n;

    if (position < 0 || (front <= rear && (index > rear || index < front)) || (front > rear && index < front && index > rear)) {
	printf("Invalid position\n");
	return;
    }

    q[index] = newValue;
    printf("Process at position %d modified to [PID=%d, Priority=%d]\n", position, newValue.pid, newValue.priority);
}