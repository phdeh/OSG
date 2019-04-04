#include "lab3.h"

#include <windows.h>
#include <iostream>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 11
HANDLE semaphore_a,
       semaphore_b,
       semaphore_c,
       semaphore_d,
       semaphore_e,
       semaphore_f,
       semaphore_g,
       semaphore_i,
       semaphore_k;

HANDLE ghMutex; // https://docs.microsoft.com/en-us/windows/desktop/sync/using-mutex-objects

unsigned int lab3_task_number()
{
    return 7;
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

    semaphore_i = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (semaphore_i == NULL)
    {
        printf("CreateSemaphore I error: %d\n", GetLastError());
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
                            10,
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
                            5,
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
                for (int i = 0; i < 12; i++)
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

DWORD WINAPI ThreadProcG( LPVOID lpParam )
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
                for (int i = 0; i < 16; i++)
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

DWORD WINAPI ThreadProcE( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[2] = {
        semaphore_a,
        semaphore_b
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
                            5,
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

    HANDLE semaphores[4] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_e
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            4,
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

DWORD WINAPI ThreadProcI( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[4] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_e
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            4,
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
                                printf("i");
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
                            semaphore_i,
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

DWORD WINAPI ThreadProcK( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[6] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
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

DWORD WINAPI ThreadProcM( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[6] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f
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
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g,
        semaphore_i,
        semaphore_k
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

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}


