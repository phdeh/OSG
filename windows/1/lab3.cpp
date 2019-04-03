#include "lab3.h"

#include <windows.h>
#include <iostream>

#define MAX_SEM_COUNT 11
#define THREADCOUNT 12
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

HANDLE ghMutex; // https://docs.microsoft.com/en-us/windows/desktop/sync/using-mutex-objects

unsigned int lab3_task_number()
{
    return 1;
}

int lab3_init()
{
    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;

    ghMutex = CreateMutex( 
        NULL,
        FALSE,
        NULL);

    if (ghMutex == NULL) 
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return 1;
    }

    semaphore_a = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_a == NULL)
    {
        printf("CreateSemaphore A error: %d\n", GetLastError());
        return 1;
    }

    semaphore_b = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_b == NULL)
    {
        printf("CreateSemaphore B error: %d\n", GetLastError());
        return 1;
    }

    semaphore_c = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_c == NULL)
    {
        printf("CreateSemaphore C error: %d\n", GetLastError());
        return 1;
    }

    semaphore_d = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_d == NULL)
    {
        printf("CreateSemaphore D error: %d\n", GetLastError());
        return 1;
    }

    semaphore_e = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_e == NULL)
    {
        printf("CreateSemaphore E error: %d\n", GetLastError());
        return 1;
    }

    semaphore_f = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_f == NULL)
    {
        printf("CreateSemaphore F error: %d\n", GetLastError());
        return 1;
    }

    semaphore_g = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_g == NULL)
    {
        printf("CreateSemaphore G error: %d\n", GetLastError());
        return 1;
    }

    semaphore_h = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_h == NULL)
    {
        printf("CreateSemaphore H error: %d\n", GetLastError());
        return 1;
    }

    semaphore_k = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_k == NULL)
    {
        printf("CreateSemaphore K error: %d\n", GetLastError());
        return 1;
    }

    semaphore_m = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_m == NULL)
    {
        printf("CreateSemaphore M error: %d\n", GetLastError());
        return 1;
    }

    semaphore_n = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_n == NULL)
    {
        printf("CreateSemaphore N error: %d\n", GetLastError());
        return 1;
    }

    return 0;
}
