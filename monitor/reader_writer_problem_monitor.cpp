#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <stdarg.h>
#define MAXTHREADS 100
#define READTIME 10
#define WRITETIME 10
using namespace std;

template <class C>
class Monitor {
  private:
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

  public:
    C slave;

    void run(void(C::*func)()) {
     /* gaining mutex */
      pthread_mutex_lock(&mutex);
     /* running func */
      void(C::*func_ptr)();
      func_ptr = func;
      (slave.*func_ptr)();
     /* releasing mutex */
      pthread_mutex_unlock(&mutex);
    };
};

class ReaderWriter {
  private:
    int numberOfReaders = 0;
    bool busy = false;
    int writersWaiting = 0; // need to have this variable vecause pthread_cond_t have no way to check the queue
    pthread_cond_t okToRead, okToWrite;
    pthread_mutex_t okToReadMutex, okToWriteMutex = PTHREAD_MUTEX_INITIALIZER;
  public:
    ReaderWriter() {  
      pthread_cond_init(&okToRead, NULL);
      pthread_cond_init(&okToWrite, NULL);
      pthread_mutex_init(&okToReadMutex, NULL);
      pthread_mutex_init(&okToWriteMutex, NULL);
    }

    void startRead() {
      if(busy || writersWaiting > 0) pthread_cond_wait(&okToRead, &okToReadMutex);
      numberOfReaders++;
      pthread_cond_signal(&okToRead); 
    }

    void finishRead() {
      numberOfReaders--; 
      if (numberOfReaders == 0) pthread_cond_signal(&okToWrite);
    }

    void startWrite() {
      if ((numberOfReaders !=0) || busy) {
        writersWaiting++;
        pthread_cond_wait(&okToWrite, &okToWriteMutex);
        writersWaiting--;
      }
      busy = true;
    }

    void finishWrite() {
      busy = false; 
      if ( writersWaiting > 0)
        pthread_cond_signal(&okToWrite); 
      else  
        pthread_cond_signal(&okToRead); 
    }
    

};

Monitor<ReaderWriter> m; /* global monitor */

void* reader(void* arg){
  m.slave.startRead();  
  printf("Reader thread #%ld starting read\n", pthread_self());
  sleep(READTIME);
  printf("Reader thread #%ld ending read\n", pthread_self());
  m.slave.finishRead();
}

void* writer(void* arg){
  m.slave.startWrite();  
  printf("Writer thread #%ld starting write\n", pthread_self());
  sleep(WRITETIME);
  printf("Writer thread #%ld ending write\n", pthread_self());
  m.slave.finishWrite();
}

int main() {
  pthread_t pids[MAXTHREADS];
  int c, nf;
  nf = 0;

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
