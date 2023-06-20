#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../mystdio.h"

#define THREAD_COUNT 2
#define ITERATIONS 5

myFILE *file;

void* thread_func(void* arg) {
    int thread_id = *(int*)arg;
    char alpha[2][6] = {"Test1", "Test2"};

    for (int i = 0; i < ITERATIONS; i++) {
        myfwrite(alpha[thread_id], 1, 6, file);
    }

    pthread_exit(NULL);
}

int main() {
    file = myfopen("test.txt", "w+");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return 1;
    }
    char result[ITERATIONS*THREAD_COUNT];

    pthread_t threads[THREAD_COUNT];
    int thread_ids[THREAD_COUNT];

    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &thread_ids[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    myfseek(file, 0, SEEK_SET);
    myfread(result, sizeof(char), ITERATIONS*THREAD_COUNT*6, file);
    int length = lseek(file->fd, 0, SEEK_END);
    printf("Final length of the file: %d\n", length);
    printf("Final shared value:\n");
    for (size_t i=0; i<ITERATIONS*THREAD_COUNT*6; i++)
        printf("%c ", result[i]);
    printf("\n");
    myfclose(file);


    return 0;
}