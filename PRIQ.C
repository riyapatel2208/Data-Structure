#include <stdio.h>
#include <stdlib.h>
#define N 4

typedef struct {
    int age;
} Person;

void pqinsert(Person [], int *, int *, int, Person); 
Person pqdelete(Person [], int *, int *);
void display(Person [], int, int);
void modify(Person [], int, int, int, Person);

void main()
{
    Person sq[N], rq[N];
    int front_s = -1, rear_s = -1;
    int front_r = -1, rear_r = -1;
    Person data;
    int choice, position;
    clrscr();
    while (1)
    {
	printf("1. Insert Person\n");
	printf("2. Delete Person\n");
	printf("3. Display Queues\n");
	printf("4. Modify Person\n");
	printf("5. Exit\n");
	printf("Enter your choice: ");
	scanf("%d", &choice);

	switch (choice)
	{
	    case 1:
		printf("Enter person age to insert: ");
		scanf("%d", &data.age);
		if (data.age >= 40) {
		    pqinsert(sq, &front_s, &rear_s, N, data);
		} else {
		    pqinsert(rq, &front_r, &rear_r, N, data);
		}
		break;

	    case 2:
		if (front_s != -1) {
		    data = pqdelete(sq, &front_s, &rear_s);
		    printf("Deleted from Senior Citizens Queue: Age = %d\n", data.age);
		} else if (front_r != -1) {
		    data = pqdelete(rq, &front_r, &rear_r);
		    printf("Deleted from Regular Queue: Age = %d\n", data.age);
		} else {
		    printf("Both queues are empty.\n");
		}
		break;

	    case 3:
		printf("Senior Citizens Queue:\n");
		display(sq, front_s, rear_s);
		printf("Regular Queue:\n");
		display(rq, front_r, rear_r);
		break;

	    case 4:
		printf("Enter the position to modify (0-based index from front): ");
		scanf("%d", &position);
		printf("Enter the new age: ");
		scanf("%d", &data.age);
		if (position < (rear_s - front_s + 1)) {
		    modify(sq, front_s, rear_s, position, data);
		} else {
		    position -= (rear_s - front_s + 1);
		    modify(rq, front_r, rear_r, position, data);
		}
		break;

	    default:
		exit(0);
	}
    }
}

void pqinsert(Person q[], int *front, int *rear, int n, Person val)
{
    if ((*rear == n - 1 && *front == 0) || (*rear + 1 == *front)) {
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

Person pqdelete(Person q[], int *front, int *rear)
{
    Person data = {-1};

    if (*front == -1) {
	printf("Underflow\n");
	return data;
    }

    data = q[*front];

    if (*front == *rear) {
	*front = *rear = -1;
    } else if (*front == N - 1) {
	*front = 0;
    } else {
	*front = *front + 1;
    }

    return data;
}

void display(Person q[], int front, int rear)
{
    int i;
    if (front == -1) {
	printf("\nQueue Empty\n");
    } else {
	printf("\nFront(=%d) ->", front);
	if (front <= rear) {
	    for (i = front; i <= rear; i++) {
		printf(" [Age=%d]", q[i].age);
	    }
	} else {
	    for (i = front; i < N; i++) {
		printf(" [Age=%d]", q[i].age);
	    }
	    for (i = 0; i <= rear; i++) {
		printf(" [Age=%d]", q[i].age);
	    }
	}
	printf(" <- Rear(=%d)\n", rear);
    }
}

void modify(Person q[], int front, int rear, int position, Person newValue)
{
    int index;
    if (front == -1) {
	printf("Queue is empty, cannot modify\n");
	return;
    }
    index = (front + position) % N;

    if ((front <= rear && (index > rear || index < front)) || (front > rear && index < front && index > rear)) {
	printf("Invalid position\n");
	return;
    }

    q[index] = newValue;
    printf("Value at position %d modified to [Age=%d]\n", position, newValue.age);
}