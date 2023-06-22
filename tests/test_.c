#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include "../mystdio.h"

#define NUM_THREADS 10000

myFILE *file;
pthread_mutex_t mutex;

char buffer[NUM_THREADS * 10 + 1] = "";

void *readThread(void *arg)
{
   int n = *((int *)arg);

   // pthread_mutex_lock(&mutex);

   myfseek(file, (n - 2) * 10, SEEK_SET);
   myfread(buffer, sizeof(char), 10, file);
   //buffer[10] = '\0'; // Null-terminate the buffer
   // printf("Read Thread %d: %s\n", n, buffer);

   // pthread_mutex_unlock(&mutex);
   pthread_exit(NULL);
}

void *writeThread(void *arg)
{
   char data[11] = "ABCDEFGHI\n";
   int n = *((int *)arg);
   free(arg);
   // pthread_mutex_lock(&mutex);

   // myfseek(file, n * 10, SEEK_SET);
   if (myfwrite(data, sizeof(char), strlen(data), file) == 0)
   {
      printf("Write Thread %d: Failed to write.\n", n);
   }
   
   // else
      // printf("Write Thread %d: %s\n", n, data);

   // pthread_mutex_unlock(&mutex);
   pthread_exit(NULL);
}

int main()
{
   file = myfopen("test.txt", "w+");

   if (file == NULL)
   {
      printf("Failed to open file.\n");
      return 1;
   }

   pthread_t threads[NUM_THREADS];
   int thread_args[NUM_THREADS];

   // pthread_mutex_init(&mutex, NULL);

   for (int i = 0; i < NUM_THREADS; i++)
   {
      thread_args[i] = i;
      int * j = (int *) malloc(sizeof(int));
      *j = i;
      pthread_create(&threads[i], NULL, writeThread, (void *)j);
   }

   for (int i = 0; i < NUM_THREADS; i++)
   {
      pthread_join(threads[i], NULL);
   }
   myfseek(file, 0, SEEK_SET);

   for (int i = 2; i < NUM_THREADS; i++)
   {
      thread_args[i] = i;
      pthread_create(&threads[i], NULL, readThread, (void *)&thread_args[i]);
   }

   for (int i = 2; i < NUM_THREADS; i++)
   {
      pthread_join(threads[i], NULL);
   }

   // pthread_mutex_destroy(&mutex);

   myfseek(file, 0, SEEK_SET);
   myfread(buffer, sizeof(char), NUM_THREADS * 10, file);
   buffer[NUM_THREADS * 10 + 1] = '\0'; // Null-terminate the buffer
   // printf("Whole read : %s\n", buffer);

   myfwrite(buffer, sizeof(char), NUM_THREADS * 10, file);

   myfclose(file);

   return 0;
}

/*#include <pthread.h>
#include "../mystdio.h"
#include <stdio.h>

#define NUM_THREADS 10000

myFILE *file;
pthread_mutex_t mutex;

char buffer[20] = "";

void* readThread(void* arg) {
    int n = *((int*)arg);

    pthread_mutex_lock(&mutex);

    myfseek(file, (n - NUM_THREADS/2) * 10, SEEK_SET);
    myfread(buffer, sizeof(char), 10, file);
    buffer[10] = '\0'; // Null-terminate the buffer
    printf("Read Thread %d: %s\n", n, buffer);

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

void* writeThread(void* arg) {
    char data[10] = "AAAAAAAA\n";
    int n = *((int*)arg);

    pthread_mutex_lock(&mutex);

    myfseek(file, n * 10, SEEK_SET);
    myfwrite(data, sizeof(char), 10, file);
    printf("Write Thread %d: %s\n", n, data);

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
}

int main() {
    file = myfopen("data.txt", "w+");

    if (file == NULL) {
        printf("Failed to open file.\n");
        return 1;
    }

    pthread_t threads[NUM_THREADS];
    int thread_args[NUM_THREADS];

    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < NUM_THREADS/2; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, writeThread, (void*)&thread_args[i]);
    }

    for (int i = 0; i < NUM_THREADS/2; i++) {
        pthread_join(threads[i], NULL);
    }

    for (int i = NUM_THREADS/2; i < NUM_THREADS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, readThread, (void*)&thread_args[i]);
    }

    for (int i = NUM_THREADS/2; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex);

    myfclose(file);

    return 0;
}
*/
/*#include <stdio.h>
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
}*/