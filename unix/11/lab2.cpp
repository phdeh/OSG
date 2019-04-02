#include "lab2.h"

#include <iostream>
#include <bitset>
#include <cstring>
#include <pthread.h>
#include <fcntl.h>
#include <semaphore.h>
#include <stdint.h>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else

#include <unistd.h> // for usleep

#endif

const int SLEEP_TIME = 10;

pthread_mutex_t lock;
sem_t *semaphore_a,
      *semaphore_b,
      *semaphore_c,
      *semaphore_d,
      *semaphore_e,
      *semaphore_f,
      *semaphore_g,
      *semaphore_h,
      *semaphore_i;
pthread_t thread_id_a,
          thread_id_b,
          thread_id_c,
          thread_id_d,
          thread_id_e,
          thread_id_f,
          thread_id_g,
          thread_id_h,
          thread_id_i,
          thread_id_k,
          thread_id_m;
unsigned int lab2_task_number() {
    return 11;
}

void *thread_a(void *ptr) {
    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'a' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    for (int i = 0; i < 9; i++)
        sem_post(semaphore_a);
    return ptr;
}
void *thread_b(void *ptr) {
    sem_wait(semaphore_a);
    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'b' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    for (int i = 0; i < 6; i++)
        sem_post(semaphore_b);
    return ptr;
}
void *thread_c(void *ptr) {
    sem_wait(semaphore_a);
    for (int i = 0; i < 8; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'c' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    for (int i = 0; i < 5; i++)
        sem_post(semaphore_c);
    return ptr;
}
void *thread_d(void *ptr) {
    for (int i = 0; i < 20; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'd' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    sem_post(semaphore_d);
    return ptr;
}
void *thread_e(void *ptr) {
    sem_wait(semaphore_a);
    for (int i = 0; i < 12; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'e' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    for (int i = 0; i < 4; i++)
        sem_post(semaphore_e);
    return ptr;
}
void *thread_f(void *ptr) {
    sem_wait(semaphore_a);
    sem_wait(semaphore_b);
    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'f' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    for (int i = 0; i < 5; i++)
        sem_post(semaphore_f);
    return ptr;
}
void *thread_g(void *ptr) {
    sem_wait(semaphore_a);
    sem_wait(semaphore_b);
    sem_wait(semaphore_c);
    sem_wait(semaphore_f);
    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'g' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    for (int i = 0; i < 4; i++)
        sem_post(semaphore_g);
    return ptr;
}
void *thread_h(void *ptr) {
    sem_wait(semaphore_a);
    sem_wait(semaphore_b);
    sem_wait(semaphore_c);
    sem_wait(semaphore_e);
    sem_wait(semaphore_f);
    sem_wait(semaphore_g);
    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'h' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    sem_post(semaphore_h);
    return ptr;
}
void *thread_i(void *ptr) {
    sem_wait(semaphore_a);
    sem_wait(semaphore_b);
    sem_wait(semaphore_c);
    sem_wait(semaphore_e);
    sem_wait(semaphore_f);
    sem_wait(semaphore_g);
    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'i' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    sem_post(semaphore_i);
    return ptr;
}
void *thread_k(void *ptr) {
    sem_wait(semaphore_a);
    sem_wait(semaphore_b);
    sem_wait(semaphore_c);
    sem_wait(semaphore_e);
    sem_wait(semaphore_f);
    sem_wait(semaphore_g);
    for (int i = 0; i < 8; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'k' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    return ptr;
}
void *thread_m(void *ptr) {
    sem_wait(semaphore_a);
    sem_wait(semaphore_b);
    sem_wait(semaphore_c);
    sem_wait(semaphore_d);
    sem_wait(semaphore_e);
    sem_wait(semaphore_f);
    sem_wait(semaphore_g);
    sem_wait(semaphore_h);
    sem_wait(semaphore_i);
    for (int i = 0; i < 4; i++) {
        pthread_mutex_lock(&lock);
        std::cout << 'm' << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }
    return ptr;
}
int lab2_init() {
    if (pthread_mutex_init(&lock, NULL) != 0) {
        std::cout << "Mutex init failed" << std::endl;
        return 1;
    }
    if ((semaphore_a = sem_open("/my_semaphore_a", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore A init failed" << std::endl;
        return 1;
    }
    if ((semaphore_b = sem_open("/my_semaphore_b", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore B init failed" << std::endl;
        return 1;
    }
    if ((semaphore_c = sem_open("/my_semaphore_c", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore C init failed" << std::endl;
        return 1;
    }
    if ((semaphore_d = sem_open("/my_semaphore_d", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore D init failed" << std::endl;
        return 1;
    }
    if ((semaphore_e = sem_open("/my_semaphore_e", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore E init failed" << std::endl;
        return 1;
    }
    if ((semaphore_f = sem_open("/my_semaphore_f", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore F init failed" << std::endl;
        return 1;
    }
    if ((semaphore_g = sem_open("/my_semaphore_g", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore G init failed" << std::endl;
        return 1;
    }
    if ((semaphore_h = sem_open("/my_semaphore_h", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore H init failed" << std::endl;
        return 1;
    }
    if ((semaphore_i = sem_open("/my_semaphore_i", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore I init failed" << std::endl;
        return 1;
    }
    int err;
    err = pthread_create(&thread_id_a, NULL, thread_a, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread A: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_b, NULL, thread_b, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread B: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_c, NULL, thread_c, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread C: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_d, NULL, thread_d, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread D: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_e, NULL, thread_e, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread E: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_f, NULL, thread_f, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread F: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_g, NULL, thread_g, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread G: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_h, NULL, thread_h, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread H: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_i, NULL, thread_i, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread I: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_k, NULL, thread_k, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread K: " << strerror(err) << std::endl;
    err = pthread_create(&thread_id_m, NULL, thread_m, (void *) NULL);
    if (err != 0)
        std::cerr << "Can't create thread M: " << strerror(err) << std::endl;
    pthread_join(thread_id_a, NULL);
    pthread_join(thread_id_b, NULL);
    pthread_join(thread_id_c, NULL);
    pthread_join(thread_id_d, NULL);
    pthread_join(thread_id_e, NULL);
    pthread_join(thread_id_f, NULL);
    pthread_join(thread_id_g, NULL);
    pthread_join(thread_id_h, NULL);
    pthread_join(thread_id_i, NULL);
    pthread_join(thread_id_k, NULL);
    pthread_join(thread_id_m, NULL);
    pthread_mutex_destroy(&lock);
    sem_close(semaphore_a);
    sem_close(semaphore_b);
    sem_close(semaphore_c);
    sem_close(semaphore_d);
    sem_close(semaphore_e);
    sem_close(semaphore_f);
    sem_close(semaphore_g);
    sem_close(semaphore_h);
    sem_close(semaphore_i);
    sem_unlink("/my_semaphore_a");
    sem_unlink("/my_semaphore_b");
    sem_unlink("/my_semaphore_c");
    sem_unlink("/my_semaphore_d");
    sem_unlink("/my_semaphore_e");
    sem_unlink("/my_semaphore_f");
    sem_unlink("/my_semaphore_g");
    sem_unlink("/my_semaphore_h");
    sem_unlink("/my_semaphore_i");
    return 0;
}    
    

