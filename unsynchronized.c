#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define RUNS 10000000 /* this value is large enough to cause a race condition */

void* count(void* arg);

/* shared global variable */
long long total = 0;

/* add value to total RUNS times  */
void* count(void* arg) {
  long long value = *(long long*) arg;

  for (int i = 0 ; i < RUNS ; i++)
    total += value;
  
  pthread_exit(0);
}

int main() {
  pthread_t tid1, tid2;
  long long val1, val2;
  val1 = 1;
  val2 = -1; 

  pthread_create(&tid1, NULL, count, &val1);
  pthread_create(&tid2, NULL, count, &val2);
  
  pthread_join(tid1, NULL); 
  pthread_join(tid22, NULL); 

  printf("Total is %lld\n", total);

  return 0;
}
