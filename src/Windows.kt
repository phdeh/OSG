fun List<ThreadTask>.toWindowsCode(variant: Int): String {
    val sb = StringBuilder()
    sb.append(
        "#include \"lab3.h\"\n" +
                "\n" +
                "#include <windows.h>\n" +
                "#include <iostream>\n" +
                "\n" +
                "#define MAX_SEM_COUNT "
    )
    sb.append(this.maxBy { it.waitedBy }?.waitedBy ?: 10)
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
                sb.append("semaphore_")
                sb.append(it.name)
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
                "    semaphore_${it.name} = CreateSemaphore(\n" +
                        "        NULL,\n" +
                        "        0,\n" +
                        "        MAX_SEM_COUNT,\n" +
                        "        NULL);\n" +
                        "    if (semaphore_${it.name} == NULL)\n" +
                        "    {\n" +
                        "        printf(\"CreateSemaphore ${it.name.capitalize()} error: %d\\n\", GetLastError());\n" +
                        "        return 1;\n" +
                        "    }\n\n"
            )
        }
    }
    this.sortedBy { it.name }.forEachIndexed { i, it ->
        sb.append("\n" +
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
                "    }\n")
    }
    sb.append(
            "\n    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);\n" +
            "    for( i=0; i < THREADCOUNT; i++ )\n" +
            "        CloseHandle(aThread[i]);\n" +
            "\n")
    this.sortedBy { it.name }.forEach {
        if (it.waitedBy > 0) {
            sb.append(
                "    CloseHandle(semaphore_${it.name});\n"
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
                    "    {\n"+
                            "        dwWaitResult = WAIT_OBJECT_0;\n"
                )
            } else if (it.waitsFor.size == 1) {
                sb.append(
                    "    while (TRUE) {\n"+
                            "        dwWaitResult = WaitForSingleObject(\n" +
                            "            semaphore_${it.waitsFor.first().name},\n" +
                            "            1000L\n" +
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
                            "            1000L\n" +
                            "        );\n"
                )
            }
            sb.append(
                "\n" +
                        "        switch (dwWaitResult)\n" +
                        "        {\n" +
                        "            case WAIT_OBJECT_0:\n" +
                        "                printf(\"Thread %d: wait succeeded\\n\", GetCurrentThreadId());\n" +
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
                        "                                printf(\"${it.name}\");\n" +
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
                            "                            semaphore_${it.name},\n" +
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

val windowsMain = "//\n" +
        "// main faunction is located here, please, DO NOT TOUCH this file\n" +
        "//\n" +
        "\n" +
        "#include \"lab3.h\"\n" +
        "\n" +
        "std::random_device rd;     // only used once to initialise (seed) engine\n" +
        "std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)\n" +
        "std::uniform_int_distribution<int> uni(0, sleep_time*2); // guaranteed unbiased\n" +
        "\n" +
        "#ifdef WIN32\n" +
        "#include <windows.h>\n" +
        "#elif _POSIX_C_SOURCE >= 199309L\n" +
        "#include <time.h>   // for nanosleep\n" +
        "#else\n" +
        "#include <unistd.h> // for usleep\n" +
        "#endif\n" +
        "\n" +
        "void sleep_ms(int milliseconds) // cross-platform sleep function\n" +
        "{\n" +
        "    auto random_integer = uni(rng);\n" +
        "    milliseconds += random_integer;\n" +
        "#ifdef WIN32\n" +
        "    Sleep(milliseconds);\n" +
        "#elif _POSIX_C_SOURCE >= 199309L\n" +
        "    struct timespec ts;\n" +
        "    ts.tv_sec = milliseconds / 1000;\n" +
        "    ts.tv_nsec = (milliseconds % 1000) * 1000000;\n" +
        "    nanosleep(&ts, NULL);\n" +
        "#else\n" +
        "    usleep(milliseconds * 1000);\n" +
        "#endif\n" +
        "}\n" +
        "\n" +
        "\n" +
        "int main(int argc, char **argv)\n" +
        "{\n" +
        "    return lab3_init();\n" +
        "}"

val windowsLabH = "//\n" +
        "// lab3 definitions header file\n" +
        "//\n" +
        "\n" +
        "#ifndef LAB3_LAB3_H\n" +
        "#define LAB3_LAB3_H\n" +
        "\n" +
        "// global includes\n" +
        "#include <iostream>\n" +
        "\n" +
        "#include <random>\n" +
        "\n" +
        "\n" +
        "const int sleep_time = 1;\n" +
        "\n" +
        "void sleep_ms(int milliseconds); // cross-platform sleep function\n" +
        "\n" +
        "int lab3_init();\n" +
        "\n" +
        "unsigned int lab3_task_number();\n" +
        "\n" +
        "#endif //LAB3_LAB3_H"

val windowsRunBat = "del lab3.h.gch\n" +
            "del test.exe\n" +
            "\"C:\\Program Files (x86)\\Dev-Cpp\\MinGW64\\bin\\g++.exe\" --std=c++11 -g main.cpp lab3.cpp -o test.exe\n" +
            "\"C:\\Program Files (x86)\\Dev-Cpp\\MinGW64\\bin\\gdb.exe\" -batch -ex run test.exe\n"