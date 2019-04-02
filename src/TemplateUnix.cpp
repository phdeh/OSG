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

unsigned int lab2_task_number() {
    return $variant;
}

void *thread_(void *ptr) {
    int iterations = ${it.iterations};

    sem_wait(semaphore_);

    for (int i = 0; i < 4 * plan; ) {
        pthread_mutex_lock(&lock);
        std::cout << (char) (threadIndex + 'a') << std::flush;
        pthread_mutex_unlock(&lock);
        sleep_ms(SLEEP_TIME);
    }

    for (int i = 0; i < ${it.waitedBy}; i++)
        sem_post(thread_${it.name}]);
    return ptr;
}

bool initProgram() {
    unsigned int post = 0;
    for (int i = 0; threadingProgram[i * 2][0] != '!'; i++) {
        unsigned int curr = 0;
        unsigned int cur2 = 0;
        for (int j = 0; threadingProgram[i * 2][j * 5] != '\0'; j++) {
            char v = threadingProgram[i * 2][j * 5] - 'A';
            if (!(0 <= v && v < letters))
                continue;
            threadPlan[v] += ACT_LENGTH;
            cur2 = setField(cur2, v);
            for (int k = 0; k < 5; k++) {
                switch (threadingProgram[i * 2 + 1][j * 5 + k]) {
                    case '^':
                        threadSemWait[v] = post;
                        for (int l = 0; l < letters; l++)
                            if (getField(post, l)) {
                                threadSemPost[l]++;
                                if (firstTry && logText)
                                    std::cerr << (char) (v + 'A') << " waits "
                                              << (char) (l + 'A') << " (" << threadSemPost[l]
                                              << ")\n";
                            }
                        break;
                    case '*':
                        if (i == 0)
                            joinTo = v;
                    case 'v':
                        curr = setField(curr, v);
                        break;
                }
            }
        }
        if (ductTape) {
            for (int k = 0; k < ACT_LENGTH; k++)
                for (int j = 0; j < letters; j++)
                    if (getField(cur2, j))
                        std::cout << (char) (j + 'a') << std::flush;
            continue;
        }
        post |= curr;
        timeout = ACT_LENGTH * (i + 3) * SLEEP_TIME * 3;
    }
    if (logText)
        std::cerr << "Try #" << ++tryNumber << '\n';
    return ductTape;
}

int lab2_init() {

    if (pthread_mutex_init(&lock, NULL) != 0) {
        std::cout << "Mutex init failed" << std::endl;
        return 1;
    }

    if (!nameAreInitialized) {
        nameAreInitialized = true;
        for (int i = 0; i < letters; i++) {
            char *c = threadSemaphoreName[i];
            snprintf(c, semaphoreNameLength, "/my_semaphore_%02d", i);
            if ((threadSemaphore[i] = sem_open("/my_semaphore", O_CREAT, 0777, 0)) == SEM_FAILED) {
                std::cerr << "Semaphore T" << i << " init failed" << std::endl;
                return 1;
            }
        }
    }

    if ((semA = sem_open("/my_semaphore_h1", O_CREAT, 0777, 1)) == SEM_FAILED) {
        std::cerr << "Semaphore #2 init failed" << std::endl;
        return 1;
    }
    if ((semB = sem_open("/my_semaphore_h2", O_CREAT, 0777, 0)) == SEM_FAILED) {
        std::cerr << "Semaphore #1 init failed" << std::endl;
        return 1;
    }

    if ((semC = sem_open("/my_semaphore_h3", O_CREAT, 0777, 0)) == SEM_FAILED) {
        std::cerr << "Semaphore #1 init failed" << std::endl;
        return 1;
    }

    if ((semD = sem_open("/my_semaphore_h4", O_CREAT, 0777, 0)) == SEM_FAILED) {
        std::cerr << "Semaphore #1 init failed" << std::endl;
        return 1;
    }

    initVariables();
    if (initProgram())
        return 0;

    int err;
    for (int i = 0; i < letters; i++) {
        if (threadPlan[i] == 0)
            continue;
        threadIndices[i] = i;
        err = pthread_create(&tid[i], NULL, thread, (void *) &threadIndices[i]);
        if (err != 0)
            std::cerr << "Can't create thread: " << strerror(err) << std::endl;
    }

    sleep_ms(timeout);

    for (int i = 0; i < letters; i++)
        pthread_cancel(tid[i]);

    pthread_mutex_destroy(&lock);
    sem_close(semA);
    sem_close(semB);
    sem_close(semC);
    sem_close(semD);

    for (int i = 0; i < letters; i++)
        sem_close(threadSemaphore[i]);

    sem_unlink("/my_semaphore_h1");
    sem_unlink("/my_semaphore_h2");
    sem_unlink("/my_semaphore_h3");
    sem_unlink("/my_semaphore_h4");

    for (int i = 0; i < letters; i++)
        sem_unlink(threadSemaphoreName[i]);

    firstTry = false;

    sleep_ms(SLEEP_TIME);

    return 0;
}