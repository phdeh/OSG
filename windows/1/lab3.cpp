#include "lab3.h"

#include <stdio.h>
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
      semaphore_k,
      semaphore_m,
      semaphore_n;
unsigned int lab2_task_number() {
    return 1;
}

DWORD WINAPI thread_a(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'a' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_a, 11, NULL);
    return TRUE;
}
DWORD WINAPI thread_b(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(semaphore_a, INFINITE);
    for (int i = 0; i < 20; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'b' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_b, 1, NULL);
    return TRUE;
}
DWORD WINAPI thread_c(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(semaphore_a, INFINITE);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'c' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_c, 7, NULL);
    return TRUE;
}
DWORD WINAPI thread_d(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(semaphore_a, INFINITE);
    for (int i = 0; i < 8; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'd' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_d, 6, NULL);
    return TRUE;
}
DWORD WINAPI thread_e(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[2] = {
        semaphore_a,
        semaphore_c
    };
    WaitForMultipleObjects(2, semaphores, TRUE, INFINITE);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'e' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_e, 6, NULL);
    return TRUE;
}
DWORD WINAPI thread_f(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(semaphore_a, INFINITE);
    for (int i = 0; i < 8; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'f' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_f, 6, NULL);
    return TRUE;
}
DWORD WINAPI thread_g(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[5] = {
        semaphore_a,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
    };
    WaitForMultipleObjects(5, semaphores, TRUE, INFINITE);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, INFINITE);
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
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g
    };
    WaitForMultipleObjects(6, semaphores, TRUE, INFINITE);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'h' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_h, 2, NULL);
    return TRUE;
}
DWORD WINAPI thread_k(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[5] = {
        semaphore_a,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
    };
    WaitForMultipleObjects(5, semaphores, TRUE, INFINITE);
    for (int i = 0; i < 8; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'k' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_k, 2, NULL);
    return TRUE;
}
DWORD WINAPI thread_m(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[5] = {
        semaphore_a,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
    };
    WaitForMultipleObjects(5, semaphores, TRUE, INFINITE);
    for (int i = 0; i < 8; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'm' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_m, 2, NULL);
    return TRUE;
}
DWORD WINAPI thread_n(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[9] = {
        semaphore_a,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g,
        semaphore_h,
        semaphore_k,
        semaphore_m
    };
    WaitForMultipleObjects(9, semaphores, TRUE, INFINITE);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'n' << std::flush;
        ReleaseMutex(lock);
        sleep_ms(SLEEP_TIME);
    }
    ReleaseSemaphore(semaphore_n, 1, NULL);
    return TRUE;
}
DWORD WINAPI thread_p(LPVOID lpParam) {
    UNREFERENCED_PARAMETER(lpParam);
    HANDLE semaphores[11] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g,
        semaphore_h,
        semaphore_k,
        semaphore_m,
        semaphore_n
    };
    WaitForMultipleObjects(11, semaphores, TRUE, INFINITE);
    for (int i = 0; i < 4; i++) {
        WaitForSingleObject(lock, INFINITE);
        std::cout << 'p' << std::flush;
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
        std::cerr << "CreateMutex error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_a = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        11,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_a == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_b = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        1,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_b == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_c = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        7,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_c == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_d = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        6,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_d == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_e = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        6,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_e == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_f = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        6,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_f == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_g = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        3,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_g == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_h = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        2,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_h == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_k = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        2,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_k == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_m = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        2,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_m == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    semaphore_n = CreateSemaphore( 
        NULL,           // default security attributes
        0,  // initial count
        1,  // maximum count
        NULL);          // unnamed semaphore
    if (semaphore_n == NULL) {
        std::cerr << "CreateSemaphore error: " << GetLastError() << '\n';
        return 1;
    }

    aThread[0] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_a, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[0] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
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
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
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
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
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
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
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
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
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
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
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
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
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
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }

    aThread[8] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_k, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[8] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }

    aThread[9] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_m, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[9] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }

    aThread[10] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_n, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[10] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
        return 1;
    }

    aThread[11] = CreateThread( 
        NULL,       // default security attributes
        0,          // default stack size
        (LPTHREAD_START_ROUTINE) thread_p, 
        NULL,       // no thread function arguments
        0,          // default creation flags
        &ThreadID); // receive thread identifier
    if(aThread[11] == NULL) {
        std::cerr << "CreateThread error: " << GetLastError() << '\n';
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
    CloseHandle(semaphore_k);
    CloseHandle(semaphore_m);
    CloseHandle(semaphore_n);
    return 0;
}
