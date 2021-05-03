// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Avoids race condition (concurrent modification of shared memory) by using
// mutual exclusion (mutex, lock)
#define _POSIX_C_SOURCE 199309L

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


typedef struct {
  size_t thread_count;
  size_t position;
  sem_t can_greet;
} shared_data_t;

typedef struct  {
  size_t thread_number;
  shared_data_t* shared_data;
} private_data_t;

int create_threads(shared_data_t* shared_data);
void* run(void* data);


int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;

  shared_data_t* shared_data = (shared_data_t*)
    calloc(1, sizeof(shared_data_t));

  if (shared_data) {
    shared_data->position = 0;
    shared_data->thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    if (error == EXIT_SUCCESS) {
      if (argc == 2) {
        if (sscanf(argv[1], "%zu", &shared_data->thread_count) != 1 || errno) {
          fprintf(stderr, "error: invalid thread count\n");
          error = 1;
        }
      }
      
      if (error == EXIT_SUCCESS) {
       sem_init(&shared_data->can_greet,0,3);
			
        // todo: check can_greet memory

        struct timespec start_time;
        clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &start_time);

        error = create_threads(shared_data);

        struct timespec finish_time;
        clock_gettime(/*clk_id*/CLOCK_MONOTONIC, &finish_time);

        double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
          (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
        printf("execution time: %.9lfs\n", elapsed);
		sem_destroy(&shared_data->can_greet);
        free(shared_data);
      }
    } else {
      fprintf(stderr, "error: could not init mutex\n");
    }
  }

  return error;
}

int create_threads(shared_data_t* shared_data) {
  assert(shared_data);
  int error = EXIT_SUCCESS;
  pthread_t* threads = (pthread_t*) calloc(shared_data->thread_count
    , sizeof(pthread_t));
  private_data_t* private_data = (private_data_t*)
    calloc(shared_data->thread_count, sizeof(private_data_t));
  if (threads && private_data) {
	for (size_t index = 0; index < shared_data->thread_count; ++index){
      private_data[index].thread_number = index;
      private_data[index].shared_data = shared_data;
      if (pthread_create(&threads[index], /*attr*/ NULL, run
        , &private_data[index]) == EXIT_SUCCESS) {
      } else {
        fprintf(stderr, "error: could not create thread %zu\n", index);
        error = 21;
        break;
      }
    }

    for (size_t index = 0; index < shared_data->thread_count; ++index) {
      pthread_join(threads[index], /*value_ptr*/ NULL);
      sem_destroy(&shared_data->can_greet);
    }
    free(threads);
    free(private_data);
  } else {
    fprintf(stderr, "error: could not allocate memory for %zu threads\n"
      , shared_data->thread_count);
    error = 22;
  }
  
  return error;
}

void* run(void* data) {
  const private_data_t* private_data = (private_data_t*)data;
  shared_data_t* shared_data = private_data->shared_data;
  const size_t my_thread_id = private_data->thread_number;
  const size_t thread_count = shared_data->thread_count;
  printf("car %zu/%zu: waiting to enter parking\n", my_thread_id, thread_count);

  sem_wait(&shared_data->can_greet);
  printf("car %zu/%zu: entered the parking\n", my_thread_id, thread_count);
  size_t duration = rand()%10;
  sleep(duration);
  sem_post(&shared_data->can_greet);
  printf("car %zu/%zu: left the parking\n", my_thread_id, thread_count);


  return NULL;
}
