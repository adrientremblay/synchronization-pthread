#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h> 
#include <unistd.h>

#define THREADS 5
#define WAIT_TIME 5

void* child_thread(void*);

bool runFlag = true;

void* child_thread(void* arg) {
  printf("Thread starting with ID: %ld\n", pthread_self());

  while(runFlag) {
    /* one iteration of work */
    continue;
  }

  printf("Thread exiting with ID: %ld\n", pthread_self());

  pthread_exit(0);
}

int main() {
  pthread_t tids[THREADS];
  for (int i = 0; i < THREADS ; i++) {
   pthread_create(&tids[i], NULL, child_thread, NULL);
  }

  sleep(WAIT_TIME);

  runFlag = false;

  for (int i = 0; i < THREADS ; i++) {
   pthread_join(tids[i], NULL);
  }

  return 0;
}
