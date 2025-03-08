#include <stdio.h>
#include <pthread.h>

#define NUM_FACTORS 5
int arr[NUM_FACTORS] = {1, 2, 3, 4, 5};
int result = 0;

typedef struct {
    int num;
    int factorial;
} ThreadParams;

void *factorian(void *arg) {
    ThreadParams *params = (ThreadParams *)arg;
    int fact = 1;
    for (int i = 1; i <= params->num; ++i) {
        fact *= i;
    }
    params->factorial = fact;
    printf("Thread %d: Factorial of %d is %d\n", params->num, params->num, params->factorial);
    return NULL;
}

int main() {
    pthread_t threads[NUM_FACTORS];
    ThreadParams params[NUM_FACTORS];

    // Create threads
    for (int i = 0; i < NUM_FACTORS; ++i) {
        params[i].num = arr[i];
        pthread_create(&threads[i], NULL, factorian, &params[i]);
    }

    // Wait for threads to finish and calculate sum of squares of factorials
    for (int i = 0; i < NUM_FACTORS; ++i) {
        pthread_join(threads[i], NULL);
        result += params[i].factorial * params[i].factorial;
    }

    printf("Sum of squares of factorials: %d\n", result);
    
    return 0;
}
