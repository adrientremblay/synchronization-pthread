#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>

#define MAXTHREADS 100
#define READTIME 10
#define WRITETIME 10

int readCount = 0;
int writeCount = 0;

sem_t mutex1, mutex2, readBlock, writeBlock, writePending;

void* reader(void* arg){
  sem_wait(&writePending);
    sem_wait(&readBlock);
      sem_wait(&mutex1);
        readCount++;        
        if(readCount == 1)
          sem_wait(&writeBlock);
      sem_post(&mutex1);
    sem_post(&readBlock);
  sem_post(&writePending);

  /* C.S. read resource */
  printf("Reader thread #%ld starting read\n", pthread_self());
  sleep(READTIME);
  printf("Reader thread #%ld ending read\n", pthread_self());

  sem_wait(&mutex1);
    readCount--;
    if (readCount == 0)
      sem_post(&writeBlock);
  sem_post(&mutex1);

  pthread_exit(0);
}

void* writer(void* arg){
  sem_wait(&mutex2);
    writeCount++;
    if(writeCount == 1)
      sem_wait(&readBlock);
  sem_post(&mutex2);

  sem_wait(&writeBlock); 
    /* C.S. write resource */
    printf("Writer thread #%ld starting write\n", pthread_self());
    sleep(WRITETIME);
    printf("Writer thread #%ld ending write\n", pthread_self());
  sem_post(&writeBlock);

  sem_wait(&mutex2);
    writeCount--;
    if(writeCount == 0)
      sem_post(&readBlock);
  sem_post(&mutex2);

  pthread_exit(0);
}

int main() {  
  pthread_t pids[MAXTHREADS];
  int c, nf;
  nf = 0;

  sem_init(&mutex1, 0, 1);
  sem_init(&mutex2, 0, 1);
  sem_init(&readBlock, 0, 1);
  sem_init(&writeBlock, 0, 1);
  sem_init(&writePending, 0, 1);

  while ((c=getchar()) != EOF){
    if (nf == MAXTHREADS || c == 'q') {
      /* go to end of program */ 
      printf("Termination sequence started, please wait for all threads to finish execution");
      break;
    } else if(c == 'r') {
      /* create a reader */ 
      pthread_create(&pids[nf++], NULL, reader, NULL);
    } else if (c == 'w') {
      /* create a writer */ 
      pthread_create(&pids[nf++], NULL, writer, NULL);
    }
  }
  
  /* join all running threads and terminate program */ 
  for (int i = 0 ; i < nf ; i++){
    pthread_join(pids[i], NULL); 
  }

  printf("Program Terminated");
  return 0;
}
