#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define RUNS 100

/* shared global variable */
long long total = 0;

/* add value to total RUNS times  */
void* add_value(void* arg) {
  int *value_ptr = (int*) arg;
  int value = *value_ptr;

  printf("%d\n:", value);

  for (int i = 0 ; i < RUNS ; i++)
    total += value;
  
  pthread_exit(0);
}

/* subract value from total RUNS times  */
void* sub_value(void* arg) {
  int *value_ptr = (int*) arg;
  int value = *value_ptr;

  printf("%d\n:", value);
  for (int i = 0 ; i < RUNS ; i++)
    total -= value;
  
  pthread_exit(0);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <num>\n", argv[0]); /* fix l8r */
    exit(-1);
  }

  int val1 = atoi(argv[1]);
  int val2 = atoi(argv[2]);
  
  pthread_t tid1, tid2;

  pthread_create(&tid1, NULL, add_value, &val1);
  pthread_create(&tid2, NULL, sub_value, &val2);
  
  pthread_join(tid1, NULL); 
  pthread_join(tid2, NULL); 

  printf("Total is %lld\n", total);

  return 0;
}
