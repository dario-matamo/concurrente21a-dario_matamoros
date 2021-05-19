// Copyright [2021] <Donaldo Salas L.>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* run(void* data);

int main(void) {
  pthread_t thread;
  if (pthread_create(&thread, NULL, run, (void*)10) == EXIT_SUCCESS) {
    void *data;
    pthread_join(thread, &data);
    printf("%zu\n", (size_t) data);
  } else {
    fprintf(stderr, "Could not create run thread\n");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void* run(void* data) {
  size_t return_value = (size_t) data * 2;
  return (void*) return_value;
}
