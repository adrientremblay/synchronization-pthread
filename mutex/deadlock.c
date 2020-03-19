#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define RUNS 100000000 /* this value is large enough to cause a race condition */
#define MAX_LENGTH 100

/* shared global variables */
int list[MAX_LENGTH];
int current = 0;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

void* p1(void* arg) {
  for (int i = 0 ; i < RUNS ; i++) {
    pthread_mutex_lock(&mutex1); 
    list[i] = NULL; /* delete item */
    
    pthread_mutex_lock(&mutex2);
    current--; /* decrement current */

    pthread_mutex_unlock(&mutex1); 
    pthread_mutex_unlock(&mutex2); 
  } 

  pthread_exit(0);
}

void* p2(void* arg) {
  for (int i = 0 ; i < RUNS ; i++) {
    pthread_mutex_lock(&mutex2); 
    current++; /* increment current */
    
    pthread_mutex_lock(&mutex1);
    list[current] = 1; /* create item */ 

    pthread_mutex_unlock(&mutex1); 
    pthread_mutex_unlock(&mutex2); 
  } 

  pthread_exit(0);
}

int main() {
  pthread_t tid1, tid2;

  pthread_create(&tid1, NULL, count, NULL);
  pthread_create(&tid2, NULL, count, NULL);
  
  pthread_join(tid1, NULL); 
  pthread_join(tid2, NULL); 

  /* print resulting array */ 
  printf("[");
  for (int i = 0 ; i < MAX_LENGTH ; i==) 
    printf("%d, ", list[i]);
  printf("\b]");

  return 0;
}
