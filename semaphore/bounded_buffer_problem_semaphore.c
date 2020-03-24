#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <unistd.h>

#define BUFFER_SIZE 100
#define PRODUCED_ITEM 69 
#define RUN_TIME 10
#define PRODUCE_TIME 1
#define CONSUME_TIME 1

sem_t bufManip;
sem_t full;
sem_t empty;

bool runFlag = true;

struct buffer_t {
  int buffer[BUFFER_SIZE];
  unsigned int nextFull;
  unsigned int nextEmpty;
} widgets;

void* producer(void* arg){
  while (runFlag) {
    sleep(PRODUCE_TIME);
    sem_wait(&empty);
    sem_wait(&bufManip);
    widgets.buffer[widgets.nextEmpty] = (int) PRODUCED_ITEM;
    printf("Produced %d at index %d\n", PRODUCED_ITEM, widgets.nextEmpty);
    widgets.nextEmpty = (widgets.nextEmpty + 1) % BUFFER_SIZE;
    sem_post(&bufManip);
    sem_post(&full);
  }
  pthread_exit(0);
}

void* consumer(void* arg){
 while (runFlag) {
  sem_wait(&full); 
  sem_wait(&bufManip);
  widgets.nextFull = (widgets.nextFull +1) % BUFFER_SIZE;
  printf("Consumed item at index %d\n", widgets.nextFull - 1);
  sem_post(&bufManip);
  sleep(CONSUME_TIME);
  sem_post(&empty);
 } 
  pthread_exit(0);
}

int main() {
  /* initializing semaphores */
  sem_init(&bufManip, 0 , 1); 
  sem_init(&full, 0 , 0); 
  sem_init(&empty, 0 , BUFFER_SIZE); 
  
  /* initializing buffer */
  widgets.nextEmpty = 0;
  widgets.nextFull = 0;
  /* for (int i = 0; i<BUFFER_SIZE; i++) */
    /* widgets.buffer[i] = 0; */
 
  /* creating threads */ 
  pthread_t tid1, tid2;
  pthread_create(&tid1, NULL, producer, NULL);
  pthread_create(&tid2, NULL, consumer, NULL);

  /* sleeping while waiting to join threads */
  sleep(RUN_TIME);
  runFlag = false;
  /* join threads */
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
 
  /* destroy semaphores */ 
  sem_destroy(&bufManip);
  sem_destroy(&full);
  sem_destroy(&empty);

  printf("terminated");
  return 0;
}
