#include "lab3.h"

#include <windows.h>
#include <iostream>

#define MAX_SEM_COUNT 8
#define THREADCOUNT 11
HANDLE SemaphoreA,
       SemaphoreB,
       SemaphoreC,
       SemaphoreD,
       SemaphoreE,
       SemaphoreF,
       SemaphoreG,
       SemaphoreH,
       SemaphoreI,
       SemaphoreK;

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
DWORD WINAPI ThreadProcK( LPVOID lpParam );
DWORD WINAPI ThreadProcM( LPVOID lpParam );

unsigned int lab3_task_number()
{
    return 4;
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

    SemaphoreA = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreA == NULL)
    {
        printf("CreateSemaphore A error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreB = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreB == NULL)
    {
        printf("CreateSemaphore B error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreC = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreC == NULL)
    {
        printf("CreateSemaphore C error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreD = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreD == NULL)
    {
        printf("CreateSemaphore D error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreE = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreE == NULL)
    {
        printf("CreateSemaphore E error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreF = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreF == NULL)
    {
        printf("CreateSemaphore F error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreG = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreG == NULL)
    {
        printf("CreateSemaphore G error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreH = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreH == NULL)
    {
        printf("CreateSemaphore H error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreI = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreI == NULL)
    {
        printf("CreateSemaphore I error: %d\n", GetLastError());
        return 1;
    }

    SemaphoreK = CreateSemaphore(
        NULL,
        0,
        MAX_SEM_COUNT,
        NULL);
    if (SemaphoreK == NULL)
    {
        printf("CreateSemaphore K error: %d\n", GetLastError());
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

    aThread[9] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcK, 
        NULL,
        0,
        &ThreadID);

    if( aThread[9] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    aThread[10] = CreateThread( 
    NULL,
        0,
        (LPTHREAD_START_ROUTINE) ThreadProcM, 
        NULL,
        0,
        &ThreadID);

    if( aThread[10] == NULL )
    {
        printf("CreateThread error: %d\n", GetLastError());
        return 1;
    }

    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);
    for( i=0; i < THREADCOUNT; i++ )
        CloseHandle(aThread[i]);

    CloseHandle(SemaphoreA);
    CloseHandle(SemaphoreB);
    CloseHandle(SemaphoreC);
    CloseHandle(SemaphoreD);
    CloseHandle(SemaphoreE);
    CloseHandle(SemaphoreF);
    CloseHandle(SemaphoreG);
    CloseHandle(SemaphoreH);
    CloseHandle(SemaphoreI);
    CloseHandle(SemaphoreK);
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
                                printf("A");
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
                            SemaphoreA,
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

DWORD WINAPI ThreadProcC( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    {
        dwWaitResult = WAIT_OBJECT_0;

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("C");
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
                            SemaphoreC,
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

DWORD WINAPI ThreadProcD( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    {
        dwWaitResult = WAIT_OBJECT_0;

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("D");
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
                            SemaphoreD,
                            4,
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

    {
        dwWaitResult = WAIT_OBJECT_0;

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("E");
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
                            SemaphoreE,
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

DWORD WINAPI ThreadProcB( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    while (TRUE) {
        dwWaitResult = WaitForSingleObject(
            semaphore_a,
            10000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("B");
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
                            SemaphoreB,
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
            10000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("G");
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
                            SemaphoreG,
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

DWORD WINAPI ThreadProcH( LPVOID lpParam )
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
            10000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("H");
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
                            SemaphoreH,
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

DWORD WINAPI ThreadProcF( LPVOID lpParam )
{
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwWaitResult;

    HANDLE semaphores[4] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            4,
            semaphores,
            TRUE,
            10000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("F");
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
                            SemaphoreF,
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

    HANDLE semaphores[7] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            7,
            semaphores,
            TRUE,
            10000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("I");
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
                            SemaphoreI,
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

    HANDLE semaphores[7] = {
        semaphore_a,
        semaphore_b,
        semaphore_c,
        semaphore_d,
        semaphore_e,
        semaphore_f,
        semaphore_g
    };
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            7,
            semaphores,
            TRUE,
            10000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("K");
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
                            SemaphoreK,
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
    while (TRUE) {
        dwWaitResult = WaitForMultipleObjects(
            10,
            semaphores,
            TRUE,
            10000L
        );

        switch (dwWaitResult)
        {
            case WAIT_OBJECT_0:
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
                                printf("M");
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


