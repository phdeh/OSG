fun List<ThreadTask>.toWindowsCode(variant: Int): String {
    val sb = StringBuilder()
    sb.append(
        "#include \"lab3.h\"\n" +
                "\n" +
                "#include <stdio.h>\n" +
                "#include <windows.h>\n" +
                "#include <iostream>\n" +
                "\n" +
                "#ifdef WIN32\n" +
                "#include <windows.h>\n" +
                "#elif _POSIX_C_SOURCE >= 199309L\n" +
                "#include <time.h>   // for nanosleep\n" +
                "#else\n" +
                "\n" +
                "#include <unistd.h> // for usleep\n" +
                "\n" +
                "#endif\n" +
                "\n" +
                "const int SLEEP_TIME = 10;\n" +
                "\n" +
                "HANDLE lock;\n"
    )
    if (this.any { it.waitedBy > 0 }) {
        sb.append("HANDLE ")
        var first = true
        this.sortedBy { it.name }.forEach {
            if (it.waitedBy > 0) {
                if (first)
                    first = false
                else
                    sb.append(",\n      ")
                sb.append("semaphore_")
                sb.append(it.name)
            }
        }
        sb.append(";\n")
    }
    sb.append(
        "unsigned int lab2_task_number() {\n" +
                "    return $variant;\n" +
                "}\n" +
                "\n"
    )
    if (this.isNotEmpty()) {
        this.sortedBy { it.name }.forEach {
            sb.append(
                "DWORD WINAPI thread_${it.name}(LPVOID lpParam) {\n" +
                        "    UNREFERENCED_PARAMETER(lpParam);\n"
            )
            if (it.waitsFor.size <= 1)
                it.waitsFor.sortedBy { i -> i.name }.forEach { i ->
                    sb.append("    WaitForSingleObject(semaphore_${i.name}, INFINITE);\n")
                }
            else {
                sb.append("    HANDLE semaphores[${it.waitsFor.size}] = {\n")
                it.waitsFor.sortedBy { i -> i.name }.forEachIndexed { i, j ->
                    sb.append("        semaphore_${j.name}")
                    if (i != it.waitsFor.size - 1)
                        sb.append(",\n")
                    else
                        sb.append("\n")
                }
                sb.append("    };\n" +
                        "    WaitForMultipleObjects(${it.waitsFor.size}, semaphores, TRUE, INFINITE);\n")
            }
            sb.append(
                "    for (int i = 0; i < ${it.iterations * 4}; i++) {\n" +
                        "        WaitForSingleObject(lock, INFINITE);\n" +
                        "        std::cout << \'${it.name}\' << std::flush;\n" +
                        "        ReleaseMutex(lock);\n" +
                        "        sleep_ms(SLEEP_TIME);\n" +
                        "    }\n"
            )
            if (it.waitedBy >= 1)
                sb.append(
                    "    ReleaseSemaphore(semaphore_${it.name}, ${it.waitedBy}, NULL);\n"
                )
            sb.append(
                "    return TRUE;\n" +
                        "}\n"
            )
        }
    }
    sb.append(
        "int lab3_init() {\n" +
                "    DWORD ThreadID;\n" +
                "    HANDLE aThread[${this.size}];\n" +
                "    lock = CreateMutex( \n" +
                "        NULL,              // default security attributes\n" +
                "        FALSE,             // initially not owned\n" +
                "        NULL);             // unnamed mutex" +
                "\n" +
                "    if (lock == NULL) {\n" +
                "        std::cerr << \"CreateMutex error: \" << GetLastError() << '\\n';\n" +
                "        return 1;\n" +
                "    }\n\n"
    )
    if (this.any { it.waitedBy > 0 }) {
        this.sortedBy { it.name }.forEach {
            if (it.waitedBy > 0) {
                sb.append(
                    "    semaphore_${it.name} = CreateSemaphore( \n" +
                            "        NULL,           // default security attributes\n" +
                            "        0,  // initial count\n" +
                            "        ${it.waitedBy},  // maximum count\n" +
                            "        NULL);          // unnamed semaphore" +
                            "\n" +
                            "    if (semaphore_${it.name} == NULL) {\n" +
                            "        std::cerr << \"CreateSemaphore error: \" << GetLastError() << '\\n';\n" +
                            "        return 1;\n" +
                            "    }\n\n"
                )
            }
        }
    }
    if (this.isNotEmpty()) {
        sb.append("    int err;\n")
        this.sortedBy { it.name }.forEachIndexed { i, it ->
            sb.append(
                "    aThread[$i] = CreateThread( \n" +
                        "        NULL,       // default security attributes\n" +
                        "        0,          // default stack size\n" +
                        "        (LPTHREAD_START_ROUTINE) thread_${it.name}, \n" +
                        "        NULL,       // no thread function arguments\n" +
                        "        0,          // default creation flags\n" +
                        "        &ThreadID); // receive thread identifier" +
                        "\n" +
                        "    if(aThread[$i] == NULL) {\n" +
                        "        std::cerr << \"CreateThread error: \" << GetLastError() << '\\n';\n" +
                        "        return 1;\n" +
                        "    }\n\n"
            )
        }
    }

    sb.append("    WaitForMultipleObjects(${this.size}, aThread, TRUE, INFINITE);\n")

    sb.append(
        "    CloseHandle(lock);\n" +
                "    for(int i = 0; i < ${this.size}; i++)\n" +
                "        CloseHandle(aThread[i]);\n"
    )

    if (this.any { it.waitedBy > 0 }) {
        this.sortedBy { it.name }.forEach {
            if (it.waitedBy > 0) {
                sb.append(
                    "    CloseHandle(semaphore_${it.name});\n"
                )
            }
        }
    }
    sb.append("    return 0;\n}")
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