#include "lab3.h"

#include <windows.h>
#include <iostream>

#define MAX_SEM_COUNT 8
#define THREADCOUNT 9
HANDLE semaphore_a,
       semaphore_b,
       semaphore_c,
       semaphore_d,
       semaphore_e,
       semaphore_f;

HANDLE ghMutex; // https://docs.microsoft.com/en-us/windows/desktop/sync/using-mutex-objects

DWORD WINAPI ThreadProcA( LPVOID lpParam );
DWORD WINAPI ThreadProcB( LPVOID lpParam );
DWORD WINAPI ThreadProcC( LPVOID lpParam );
DWORD WINAPI ThreadProcD( LPVOID lpParam );
DWORD WINAPI ThreadProcE( LPVOID lpParam );
DWORD WINAPI ThreadProcF( LPVOID lpParam );
DWORD WINAPI ThreadProcG( LPVOID lpParam );
DWORD WINAPI ThreadProcH( LPVOID lpParam );
DWORD WINAPI ThreadProcI( LPVOID lpParam );

unsigned int lab3_task_number()
{
    return 8;
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


    aThread[0] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcA, 
        NULL,
        0,
        &ThreadID);

    if( aThread[0] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[1] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcB, 
        NULL,
        0,
        &ThreadID);

    if( aThread[1] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[2] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcC, 
        NULL,
        0,
        &ThreadID);

    if( aThread[2] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[3] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcD, 
        NULL,
        0,
        &ThreadID);

    if( aThread[3] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[4] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcE, 
        NULL,
        0,
        &ThreadID);

    if( aThread[4] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[5] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcF, 
        NULL,
        0,
        &ThreadID);

    if( aThread[5] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[6] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcG, 
        NULL,
        0,
        &ThreadID);

    if( aThread[6] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[7] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcH, 
        NULL,
        0,
        &ThreadID);

    if( aThread[7] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[8] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcI, 
        NULL,
        0,
        &ThreadID);

    if( aThread[8] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);
    for( i=0; i < THREADCOUNT; i++ )
        CloseHandle(aThread[i]);

    CloseHandle(semaphore_a);
    CloseHandle(semaphore_b);
    CloseHandle(semaphore_c);
    CloseHandle(semaphore_d);
    CloseHandle(semaphore_e);
    CloseHandle(semaphore_f);
    CloseHandle(ghMutex);
    return 0;
}
DWORD WINAPI ThreadProcA( LPVOID lpParam )
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
                            8,
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

DWORD WINAPI ThreadProcE( LPVOID lpParam )
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

DWORD WINAPI ThreadProcD( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[3] = {
        semaphore_a,
        semaphore_b,
        semaphore_c
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            3,
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

    HANDLE semaphores[3] = {
        semaphore_a,
        semaphore_b,
        semaphore_c
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            3,
            semaphores,
            TRUE,
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

    HANDLE semaphores[5] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e
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

    HANDLE semaphores[5] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e
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

DWORD WINAPI ThreadProcI( LPVOID lpParam )
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

            case WAIT_TIMEOUT:
                printf("Thread %d: wait timed out\n", GetCurrentThreadId());
                break;
        }
    }
    return TRUE;
}

