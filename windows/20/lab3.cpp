#include "lab3.h"

#include <windows.h>
#include <iostream>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 14
HANDLE semaphore_a,
       semaphore_b,
       semaphore_c,
       semaphore_f,
       semaphore_d,
       semaphore_e,
       semaphore_h,
       semaphore_r,
       semaphore_i,
       semaphore_m,
       semaphore_k;
unsigned int lab3_task_number()
{
    return 20;
}


int lab3_init()
{
    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;

    semaphore_a = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_a == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_b = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_b == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_c = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_c == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_f = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_f == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_d = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_d == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_e = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_e == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_g = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_g == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_h = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_h == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_r = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_r == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_i = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_i == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_m = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_m == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_n = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_n == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_k = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_k == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    semaphore_p = CreateSemaphore(
        NULL,
        MAX_SEM_COUNT,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_p == NULL)
    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return 1;
    }

    CreateThread(...);
    // ...

    WaitForMultipleObjects(...);
    // ...

    return 0;
}
