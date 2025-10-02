#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Deque structure (stores indices)
typedef struct {
    int *data;
    int front, rear, size, capacity;
} Deque;

Deque* createDeque(int capacity) {
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    dq->data = (int*)malloc(capacity * sizeof(int));
    dq->front = 0;
    dq->rear = -1;
    dq->size = 0;
    dq->capacity = capacity;
    return dq;
}

int isEmpty(Deque* dq) {
    return dq->size == 0;
}

int front(Deque* dq) {
    return dq->data[dq->front];
}

int rear(Deque* dq) {
    return dq->data[dq->rear];
}

void popFront(Deque* dq) {
    dq->front = (dq->front + 1) % dq->capacity;
    dq->size--;
}

void popRear(Deque* dq) {
    dq->rear = (dq->rear - 1 + dq->capacity) % dq->capacity;
    dq->size--;
}

void pushRear(Deque* dq, int value) {
    dq->rear = (dq->rear + 1) % dq->capacity;
    dq->data[dq->rear] = value;
    dq->size++;
}

// Function to calculate sliding window maximum
int* maxSlidingWindow(int* nums, int n, int k, int* returnSize) {
    if (n == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* result = (int*)malloc((n - k + 1) * sizeof(int));
    *returnSize = 0;

    Deque* dq = createDeque(n);

    for (int i = 0; i < n; i++) {
        // Remove indices out of window
        if (!isEmpty(dq) && front(dq) <= i - k) {
            popFront(dq);
        }

        // Remove smaller values from rear
        while (!isEmpty(dq) && nums[rear(dq)] <= nums[i]) {
            popRear(dq);
        }

        // Add current index
        pushRear(dq, i);

        // Store result once window is ready
        if (i >= k - 1) {
            result[*returnSize] = nums[front(dq)];
            (*returnSize)++;
        }
    }

    free(dq->data);
    free(dq);
    return result;
}

int main() {
    int nums[] = {1,3,-1,-3,5,3,6,7};
    int n = sizeof(nums)/sizeof(nums[0]);
    int k = 3;
    int returnSize;

    int* result = maxSlidingWindow(nums, n, k, &returnSize);

    printf("Output: [");
    for (int i = 0; i < returnSize; i++) {
        printf("%d", result[i]);
        if (i < returnSize - 1) printf(",");
    }
    printf("]\n");

    free(result);
    return 0;
}
