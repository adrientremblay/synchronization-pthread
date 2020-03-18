#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#define RUNS 100

void* count(void* arg);


/* shared global variable */
long long total = 0;

/* add value to total RUNS times  */
void* count(void* arg) {
  long long *value_ptr = (long long*) arg;
  long long value = *value_ptr;

  
  printf("%lld\n", value);
  
  for (int i = 0 ; i < RUNS ; i++)
    total += value;
  
  pthread_exit(0);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <num1> <num2> <num3> ... <numn>\n", argv[0]);
    exit(-1);
  }

  pthread_t tids[argc - 1];
  long long vals[argc - 1];

  for (int i = 1 ; i < argc ; i++) {
    vals[i-1]  = atoll(argv[i]);
    pthread_create(&tids[i-1], NULL, count, &vals[i-1]);
  }
  
  for (int i = 1 ; i < argc ; i++) 
    pthread_join(tids[i-1], NULL); 

  printf("Total is %lld\n", total);

  return 0;
}
