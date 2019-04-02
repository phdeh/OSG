fun List<ThreadTask>.toWindowsCode(variant: Int): String {
    val sb = StringBuilder()
    sb.append(
        "#include \"lab3.h\"\n" +
                "\n" +
                "#include <windows.h>\n" +
                "#include <iostream>\n" +
                "\n" +
                "#define MAX_SEM_COUNT 10\n" +
                "#define THREADCOUNT "
    )
    sb.appendln(this.size)
    if (this.any { it.waitedBy > 0 }) {
        sb.append("HANDLE ")
        var first = true
        this.forEach {
            if (it.waitedBy > 0) {
                if (first)
                    first = false
                else
                    sb.append(",\n       ")
                sb.append("semaphore_")
                sb.append(it.name)
            }
        }
        sb.appendln(";")
    }
    sb.append(
        "unsigned int lab3_task_number()\n" +
                "{\n" +
                "    return $variant;\n" +
                "}\n" +
                "\n" +
                "\n" +
                "int lab3_init()\n{\n" +
                "    HANDLE aThread[THREADCOUNT];\n" +
                "    DWORD ThreadID;\n" +
                "    int i;\n\n"
    )
    if (this.any { it.waitedBy > 0 }) {
        var first = true
        this.forEach {
            sb.append("    semaphore_${it.name} = CreateSemaphore(\n" +
                    "        NULL,\n" +
                    "        MAX_SEM_COUNT,\n" +
                    "        MAX_SEM_COUNT,\n" +
                    "        NULL);\n" +
                    "    if (semaphore_${it.name} == NULL)\n" +
                    "    {\n" +
                    "        printf(\"CreateSemaphore error: %d\\n\", GetLastError());\n" +
                    "        return 1;\n" +
                    "    }\n\n"
            )
        }
    }
    sb.append(
        "    CreateThread(...);\n" +
                "    // ...\n" +
                "\n" +
                "    WaitForMultipleObjects(...);\n" +
                "    // ...\n" +
                "\n" +
                "    return 0;\n" +
                "}"
    )
    return sb.toString()
}