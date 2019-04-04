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
}DWORD WINAPI ThreadProcA( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    {
        dwWaitResult = WAIT_OBJECT_0;

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 4; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("a");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_a,
                            11,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcB( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    while (TRUE) {
        dwWaitResult = WaitForSingleObject(
            semaphore_a,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 20; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("b");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_b,
                            1,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcC( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    while (TRUE) {
        dwWaitResult = WaitForSingleObject(
            semaphore_a,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 4; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("c");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_c,
                            7,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcD( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    while (TRUE) {
        dwWaitResult = WaitForSingleObject(
            semaphore_a,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 8; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("d");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_d,
                            6,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcF( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    while (TRUE) {
        dwWaitResult = WaitForSingleObject(
            semaphore_a,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 8; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("f");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_f,
                            6,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcE( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[2] = {
        semaphore_a,
        semaphore_c
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            2,
            semaphores,
            TRUE,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 4; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("e");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_e,
                            6,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcG( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[5] = {
        semaphore_a,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            5,
            semaphores,
            TRUE,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 4; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("g");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_g,
                            3,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcK( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[5] = {
        semaphore_a,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            5,
            semaphores,
            TRUE,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 8; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("k");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_k,
                            2,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcM( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[5] = {
        semaphore_a,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            5,
            semaphores,
            TRUE,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 8; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("m");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_m,
                            2,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcH( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[6] = {
        semaphore_a,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            6,
            semaphores,
            TRUE,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 4; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("h");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_h,
                            2,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcN( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

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
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            9,
            semaphores,
            TRUE,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 4; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("n");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

                if (!ReleaseSemaphore(
                            semaphore_n,
                            1,
                            NULL))
                {
                    printf("ReleaseSemaphore error: %d\n", GetLastError());
                }
                break;

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

DWORD WINAPI ThreadProcP( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

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
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            11,
            semaphores,
            TRUE,
            1000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
                printf("Thread %d: wait succeeded\n", GetCurrentThreadId());
                for (int i = 0; i < 4; i++)
                {
                    bool waitingForMutex = TRUE;
                    while (waitingForMutex) {
                        dwWaitResult = WaitForSingleObject(
                            ghMutex,
                            INFINITE
                        );

                        switch (dwWaitResult)
                        {
                            case WAIT_OBJECT_0:
                                printf("p");
                                if (!ReleaseMutex(ghMutex))
                                {
                                    printf("ReleaseMutex error: %d\n", GetLastError());
                                }
                                waitingForMutex = FALSE;
                                break;
                            case WAIT_ABANDONED:
                                return FALSE;
                        }
                        Sleep(10);
                    }
                }

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}


