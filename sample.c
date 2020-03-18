#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long sum = 0;

void* do_action(void* arg) {
  long long *limit_ptr = (long long*) arg;
  long long limit = *limit_ptr;

  for (int i = 0; i <= limit ; i++)
    sum += i;

  pthread_exit(0);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <num>\n", argv[0]);
    exit(-1);
  }
  
  long long limit = atoll(argv[1]);

  pthread_t tid;
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  pthread_create(&tid, &attr, do_action, &limit);

  pthread_join(tid, NULL); 
  printf("Sum is %lld\n", sum);

  return 0;
}
