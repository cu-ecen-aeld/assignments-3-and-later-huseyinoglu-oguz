#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...)
//#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{

    // TODO: wait, obtain mutex, wait, release mutex as described by thread_data structure
    // hint: use a cast like the one below to obtain thread arguments from your parameter
    //struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    printf("*******INSIDE FUNCTION***************\n");
    struct thread_data* thread_func_args = (struct thread_data *) thread_param;
    sleep(thread_func_args->_wait_to_obtain_ms);
    pthread_mutex_lock(thread_func_args->_mutex);
    sleep(thread_func_args->_wait_to_release_ms);
    pthread_mutex_unlock(thread_func_args->_mutex);
    pthread_join(thread_func_args->_thread,NULL);

    return thread_param;

}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,int wait_to_obtain_ms, int wait_to_release_ms)
{
    /**
     * TODO: allocate memory for thread_data, setup mutex and wait arguments, pass thread_data to created thread
     * using threadfunc() as entry point.
     *
     * return true if successful.
     *
     * See implementation details in threading.h file comment block
     */
    
    //allocate dynamic memory for thread parameter
     struct thread_data *thread_param = malloc(sizeof(struct thread_data));

     thread_param->_mutex = mutex;
     thread_param->_wait_to_obtain_ms = wait_to_obtain_ms;
     thread_param->_wait_to_release_ms = wait_to_release_ms;
     thread_param->thread_complete_success = false;

     int ret;

     ret = pthread_create(thread,NULL,threadfunc,(void *)thread_param);
     if(!ret)
     {
        printf("*********THREAD CREATE SUCCESFULL*****************\n");

        thread_param->thread_complete_success = true;
        return thread_param->thread_complete_success;
     }
     printf("RET VALUE --->>> %d",ret);

    perror("pthread_create");
    return false;
}

