// Copyright 2021 Jeisson Hidalgo-Cespedes <jeisson.hidalgo@ucr.ac.cr> CC-BY-4
// Creates an arbitrary amount of threads that greet in stdout

#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    size_t thread_count;
    char* message ;
} shared_data_t;

typedef struct
{
    size_t thread_number;
    shared_data_t *shared_data;
} private_data_t;

int create_threads(shared_data_t *shared_data);
void *run(void *data);
char generate_random_letter();


int main(int argc, char *argv[])
{
    int error = EXIT_SUCCESS;

    shared_data_t shared_data;
        
    shared_data.thread_count = sysconf(_SC_NPROCESSORS_ONLN);
    shared_data.message = calloc(shared_data.thread_count,sizeof(char)*shared_data.thread_count);
    if (argc == 2)
    {
        if (sscanf(argv[1], "%zu", &shared_data.thread_count) != 1 || errno)
        {
            fprintf(stderr, "error: invalid thread count\n");
            return EXIT_FAILURE;
        }
    }

    struct timespec start_time;
    clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &start_time);

    error = create_threads(&shared_data);

    struct timespec finish_time;
    clock_gettime(/*clk_id*/ CLOCK_MONOTONIC, &finish_time);

        for(int i=0 ; i < shared_data.thread_count ; i++){
        printf("%c,",shared_data.message[i]);
    }


    double elapsed = (finish_time.tv_sec - start_time.tv_sec) +
                     (finish_time.tv_nsec - start_time.tv_nsec) * 1e-9;
    printf("execution time: %.9lfs\n", elapsed);

    return error;
}

int create_threads(shared_data_t *shared_data)
{
    assert(shared_data);
    int error = EXIT_SUCCESS;
    pthread_t *threads = (pthread_t *)calloc(shared_data->thread_count, sizeof(pthread_t));
    private_data_t *private_data = (private_data_t *)calloc(shared_data->thread_count, sizeof(private_data_t));
    if (threads && private_data)
    {
        for (size_t index = 0; index < shared_data->thread_count; ++index)
        {
            private_data[index].thread_number = index;
            private_data[index].shared_data = shared_data;
            if (pthread_create(&threads[index], /*attr*/ NULL, run, &private_data[index]) == EXIT_SUCCESS)
            {
            }
            else
            {
                fprintf(stderr, "error: could not create thread %zu\n", index);
                error = 21;
                break;
            }
        }

        for (size_t index = 0; index < shared_data->thread_count; ++index)
        {
            pthread_join(threads[index], /*value_ptr*/ NULL);
        }
        free(threads);
        free(private_data);
    }
    else
    {
        fprintf(stderr, "error: could not allocate memory for %zu threads\n", shared_data->thread_count);
        error = 22;
    }

    return error;
}

void *run(void *data)
{
    const private_data_t *private_data = (private_data_t *)data;
    
   // printf("Hello from secondary thread %zu of %zu\n", private_data->thread_number, private_data->shared_data->thread_count);
    char letter = generate_random_letter();
    private_data->shared_data->message[private_data->thread_number] =letter;
    printf("Hello I'm thread %zu of and I wrote %c in index %zu \n", private_data->thread_number, letter,private_data->thread_number);
    return NULL;
}

char generate_random_letter()
{
    return 'A' + (random() % 26);
}
