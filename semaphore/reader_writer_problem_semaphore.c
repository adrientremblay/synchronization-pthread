#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdbool.h>

#define MAXTHREADS 100
#define READTIME 1
#define WRITETIME 1

int readCount = 0;

sem_t mutex;
sem_t writeBlock;

void* reader(void* arg){
  while (true) {
    sem_wait(&mutex); 
      readCount ++;
      if (readCount == 1) 
        sem_wait(&writeBlock); 
    sem_post(&mutex);  
    /* C.S. read resource */
    printf("Thread #%ld read resource\n", pthread_self());
    sleep(READTIME);
    sem_wait(&mutex);
      readCount--;
      if (readCount ==0)
        sem_post(&writeBlock);
    sem_post(&mutex);
  }

  pthread_exit(0);
}

void* writer(void* arg){
  while (true) {
    sem_wait(&writeBlock); 
      printf("Thread #%ld wrote resource\n", pthread_self());
      sleep(WRITETIME);
    sem_post(&writeBlock);
  }
}

int main() {  
  pthread_t pids[MAXTHREADS];
  int c, nf;
  nf = 0;

  sem_init(&mutex, 0, 1);
  sem_init(&writeBlock, 0, 1);

  while ((c=getchar()) != EOF){
    if (nf == MAXTHREADS || c == 'q') {
      /* go to end of program */ 
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
  
  return 0;
}
