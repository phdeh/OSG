#include "lab3.h"

#include <windows.h>
#include <iostream>

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else

#include <unistd.h> // for usleep

#endif

const int SLEEP_TIME = 10;

HANDLE lock;
HANDLE semaphore_a,
      semaphore_b,
      semaphore_c,
      semaphore_d,
      semaphore_e,
      semaphore_f,
      semaphore_g,
      semaphore_h,
      semaphore_i,
      semaphore_k;
unsigned int lab2_task_number() {
    return 5;
}

DWORD WINAPI thread_a(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'a' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_a, 10, NULL);
    return TRUE;
}
DWORD WINAPI thread_b(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(semaphore_a, 0L);
    std::cerr << 'A' << std::flush;
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'b' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_b, 7, NULL);
    return TRUE;
}
DWORD WINAPI thread_c(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < 12; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'c' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_c, 5, NULL);
    return TRUE;
}
DWORD WINAPI thread_d(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[3] = {
        semaphore_a,
        semaphore_b,
        semaphore_e
    };
    WaitForMultipleObjects(3, semaphores, TRUE, 0L);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'd' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_d, 5, NULL);
    return TRUE;
}
DWORD WINAPI thread_e(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(semaphore_a, 0L);
    std::cerr << 'A' << std::flush;
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'e' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_e, 7, NULL);
    return TRUE;
}
DWORD WINAPI thread_f(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[3] = {
        semaphore_a,
        semaphore_b,
        semaphore_e
    };
    WaitForMultipleObjects(3, semaphores, TRUE, 0L);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'f' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_f, 5, NULL);
    return TRUE;
}
DWORD WINAPI thread_g(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(semaphore_a, 0L);
    std::cerr << 'A' << std::flush;
    for (int i = 0; i < 12; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'g' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_g, 3, NULL);
    return TRUE;
}
DWORD WINAPI thread_h(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[6] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
    };
    WaitForMultipleObjects(6, semaphores, TRUE, 0L);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'h' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_h, 3, NULL);
    return TRUE;
}
DWORD WINAPI thread_i(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[8] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g,
        semaphore_h
    };
    WaitForMultipleObjects(8, semaphores, TRUE, 0L);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'i' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_i, 1, NULL);
    return TRUE;
}
DWORD WINAPI thread_k(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[6] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
    };
    WaitForMultipleObjects(6, semaphores, TRUE, 0L);
    for (int i = 0; i < 8; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'k' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_k, 1, NULL);
    return TRUE;
}
DWORD WINAPI thread_m(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[8] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g,
        semaphore_h
    };
    WaitForMultipleObjects(8, semaphores, TRUE, 0L);
    for (int i = 0; i < 8; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'm' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    return TRUE;
}
DWORD WINAPI thread_n(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[10] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g,
        semaphore_h,
        semaphore_i,
        semaphore_k
    };
    WaitForMultipleObjects(10, semaphores, TRUE, 0L);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, 0L);
        std::cout << 'n' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    return TRUE;
}
int lab3_init() {
    DWORD ThreadID;
    HANDLE aThread[12];
    lock = CreateMutex( 
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex
    if (lock == NULL) {
        printf("CreateMutex error: %d\n", GetLastError());
        return 1;
    }

    semaphore_a = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        10,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_a == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_b = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        7,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_b == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_c = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        5,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_c == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_d = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        5,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_d == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_e = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        7,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_e == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_f = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        5,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_f == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_g = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        3,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_g == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_h = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        3,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_h == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_i = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        1,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_i == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_k = CreateSemaphore( 
        SEMAPHORE_MODIFY_STATE | SYNCHRONIZE,           // default security attributes
        0,  // initial count
        1,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_k == NULL) {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    int err;
    aThread[0] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_a, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[0] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[1] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_b, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[1] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[2] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_c, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[2] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[3] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_d, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[3] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[4] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_e, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[4] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[5] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_f, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[5] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[6] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_g, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[6] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[7] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_h, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[7] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[8] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_i, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[8] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[9] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_k, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[9] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[10] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_m, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[10] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[11] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_n, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[11] == NULL) {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    WaitForMultipleObjects(12, aThread, TRUE, INFINITE);
    CloseHandle(lock);
    for(int i = 0; i < 12; i++)
        CloseHandle(aThread[i]);
    CloseHandle(semaphore_a);
    CloseHandle(semaphore_b);
    CloseHandle(semaphore_c);
    CloseHandle(semaphore_d);
    CloseHandle(semaphore_e);
    CloseHandle(semaphore_f);
    CloseHandle(semaphore_g);
    CloseHandle(semaphore_h);
    CloseHandle(semaphore_i);
    CloseHandle(semaphore_k);
    return 0;
}
