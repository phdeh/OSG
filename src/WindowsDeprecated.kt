@Deprecated("Use toWIndowsCode(variant: Int) instead")
fun List<ThreadTask>.toWindowsCodeDeprecated(variant: Int): String {
    val sb = StringBuilder()
    sb.append(
        "#include \"lab3.h\"\n" +
                "\n" +
                "#include <windows.h>\n" +
                "#include <iostream>\n" +
                "\n" +
                "#define MAX_SEM_COUNT "
    )
    sb.append((this.maxBy { it.waitedBy }?.waitedBy ?: 0) * 2)
    sb.append(
        "\n#define THREADCOUNT "
    )
    sb.append(this.size)
    sb.append('\n')
    if (this.any { it.waitedBy > 0 }) {
        sb.append("HANDLE ")
        var first = true
        this.sortedBy { it.name }.forEach {
            if (it.waitedBy > 0) {
                if (first)
                    first = false
                else
                    sb.append(",\n       ")
                sb.append("Semaphore")
                sb.append(it.name.capitalize())
            }
        }
        sb.append(";\n\n")
    }
    sb.append(
        "HANDLE ghMutex; // https://docs.microsoft.com/en-us/windows/desktop/sync/using-mutex-objects\n\n"
    )
    this.sortedBy { it.name }.forEach {
        sb.append("DWORD WINAPI ThreadProc${it.name.capitalize()}( LPVOID lpParam );\n")
    }

    sb.append(
        "\nunsigned int lab3_task_number()\n" +
                "{\n" +
                "    return $variant;\n" +
                "}\n" +
                "\n" +
                "int lab3_init()\n{\n" +
                "    HANDLE aThread[THREADCOUNT];\n" +
                "    DWORD ThreadID;\n" +
                "    int i;\n\n" +
                "    ghMutex = CreateMutex( \n" +
                "        NULL,\n" +
                "        FALSE,\n" +
                "        NULL);\n" +
                "\n" +
                "    if (ghMutex == NULL) \n" +
                "    {\n" +
                "        printf(\"CreateMutex error: %d\\n\", GetLastError());\n" +
                "        return 1;\n" +
                "    }\n\n"
    )
    this.sortedBy { it.name }.forEach {
        if (it.waitedBy > 0) {
            sb.append(
                "    Semaphore${it.name.capitalize()} = CreateSemaphore(\n" +
                        "        NULL,\n" +
                        "        0,\n" +
                        "        MAX_SEM_COUNT,\n" +
                        "        NULL);\n" +
                        "    if (Semaphore${it.name.capitalize()} == NULL)\n" +
                        "    {\n" +
                        "        printf(\"CreateSemaphore ${it.name.capitalize()} error: %d\\n\", GetLastError());\n" +
                        "        return 1;\n" +
                        "    }\n\n"
            )
        }
    }
    this.sortedBy { it.name }.forEachIndexed { i, it ->
        sb.append(
            "\n" +
                    "    aThread[$i] = CreateThread( \n" +
                    "    NULL,\n" +
                    "        0,\n" +
                    "        (LPTHREAD_START_ROUTINE) ThreadProc${it.name.capitalize()}, \n" +
                    "        NULL,\n" +
                    "        0,\n" +
                    "        &ThreadID" +
                    ");\n" +
                    "\n" +
                    "    if( aThread[$i] == NULL )\n" +
                    "    {\n" +
                    "        printf(\"CreateThread error: %d\\n\", GetLastError());\n" +
                    "        return 1;\n" +
                    "    }\n"
        )
    }
    sb.append(
        "\n    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);\n" +
                "    for( i=0; i < THREADCOUNT; i++ )\n" +
                "        CloseHandle(aThread[i]);\n" +
                "\n"
    )
    this.sortedBy { it.name }.forEach {
        if (it.waitedBy > 0) {
            sb.append(
                "    CloseHandle(Semaphore${it.name.capitalize()});\n"
            )
        }
    }
    sb.append(
        "    CloseHandle(ghMutex);\n"
    )
    sb.append(
        "    return 0;\n" +
                "}\n"
    )
    if (this.isNotEmpty()) {
        this.forEach {
            sb.append(
                "DWORD WINAPI ThreadProc${it.name.capitalize()}( LPVOID lpParam )\n" +
                        "{\n" +
                        "    UNREFERENCED_PARAMETER(lpParam);\n" +
                        "\n" +
                        "    DWORD dwWaitResult;\n" +
                        "\n"
            )
            if (it.waitsFor.size == 0) {
                sb.append(
                    "    {\n" +
                            "        dwWaitResult = WAIT_OBJECT_0;\n"
                )
            } else if (it.waitsFor.size == 1) {
                sb.append(
                    "    while (TRUE) {\n" +
                            "        dwWaitResult = WaitForSingleObject(\n" +
                            "            semaphore_${it.waitsFor.first().name},\n" +
                            "            10000L\n" +
                            "        );\n"
                )
            } else {
                sb.append("    HANDLE semaphores[${it.waitsFor.size}] = {\n")
                var first = true
                it.waitsFor.sortedBy { it.name }.forEach { i ->
                    if (first)
                        first = false
                    else
                        sb.append(",\n")
                    sb.append("        semaphore_${i.name}")
                }
                sb.append(
                    "\n    };\n" +
                            "    while (TRUE) {\n" +
                            "        dwWaitResult = WaitForMultipleObjects(\n" +
                            "            ${it.waitsFor.size},\n" +
                            "            semaphores,\n" +
                            "            TRUE,\n" +
                            "            10000L\n" +
                            "        );\n"
                )
            }
            sb.append(
                "\n" +
                        "        switch (dwWaitResult)\n" +
                        "        {\n" +
                        "            case WAIT_OBJECT_0:\n" +
                        "                for (int i = 0; i < ${it.iterations * 4}; i++)\n" +
                        "                {\n" +
                        "                    bool waitingForMutex = TRUE;\n" +
                        "                    while (waitingForMutex) {\n" +
                        "                        dwWaitResult = WaitForSingleObject(\n" +
                        "                            ghMutex,\n" +
                        "                            INFINITE\n" +
                        "                        );\n" +
                        "\n" +
                        "                        switch (dwWaitResult)\n" +
                        "                        {\n" +
                        "                            case WAIT_OBJECT_0:\n" +
                        "                                printf(\"${it.name.capitalize()}\");\n" +
                        "                                if (!ReleaseMutex(ghMutex))\n" +
                        "                                {\n" +
                        "                                    printf(\"ReleaseMutex error: %d\\n\", GetLastError());\n" +
                        "                                }\n" +
                        "                                waitingForMutex = FALSE;\n" +
                        "                                break;\n" +
                        "                            case WAIT_ABANDONED:\n" +
                        "                                return FALSE;\n" +
                        "                        }\n" +
                        "                        Sleep(10);\n" +
                        "                    }\n" +
                        "                }\n" +
                        "\n"
            )
            if (it.waitedBy > 0) {
                sb.append(
                    "                if (!ReleaseSemaphore(\n" +
                            "                            Semaphore${it.name.capitalize()},\n" +
                            "                            ${it.waitedBy},\n" +
                            "                            NULL))\n" +
                            "                {\n" +
                            "                    printf(\"ReleaseSemaphore error: %d\\n\", GetLastError());\n" +
                            "                }\n" +
                            "                break;\n" +
                            "\n"
                )
            }
            sb.append(
                "            case WAIT_TIMEOUT:\n" +
                        "                printf(\"Thread %d: wait timed out\\n\", GetCurrentThreadId());\n" +
                        "                break;\n" +
                        "        }\n" +
                        "    }\n" +
                        "    return TRUE;\n" +
                        "}\n\n"
            )
        }
    }
    return sb.toString()
}
