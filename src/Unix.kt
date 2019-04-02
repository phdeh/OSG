fun List<ThreadTask>.toUnixCode(variant: Int): String {
    val sb = StringBuilder()
    sb.append(
        "#include \"lab2.h\"\n" +
                "\n" +
                "#include <iostream>\n" +
                "#include <bitset>\n" +
                "#include <cstring>\n" +
                "#include <pthread.h>\n" +
                "#include <fcntl.h>\n" +
                "#include <semaphore.h>\n" +
                "#include <stdint.h>\n" +
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
                "pthread_mutex_t lock;\n"
    )
    if (this.any { it.waitedBy > 0 }) {
        sb.append("sem_t ")
        var first = true
        this.sortedBy { it.name }.forEach {
            if (it.waitedBy > 0) {
                if (first)
                    first = false
                else
                    sb.append(",\n      ")
                sb.append("*semaphore_")
                sb.append(it.name)
            }
        }
        sb.appendln(";")
    }
    if (this.isNotEmpty()) {
        sb.append("pthread_t ")
        var first = true
        this.sortedBy { it.name }.forEach {

                if (first)
                    first = false
                else
                    sb.append(",\n          ")
                sb.append("thread_id_")
                sb.append(it.name)

        }
        sb.appendln(";")
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
                "void *thread_${it.name}(void *ptr) {\n"
            )
            it.waitsFor.sortedBy { i -> i.name }.forEach { i ->
                sb.append("    sem_wait(semaphore_${i.name});\n")
            }
            sb.append(
                "    for (int i = 0; i < ${it.iterations * 4}; i++) {\n" +
                        "        pthread_mutex_lock(&lock);\n" +
                        "        std::cout << \'${it.name}\' << std::flush;\n" +
                        "        pthread_mutex_unlock(&lock);\n" +
                        "        sleep_ms(SLEEP_TIME);\n" +
                        "    }\n"
            )
            if (it.waitedBy > 1)
                sb.append(
                    "    for (int i = 0; i < ${it.waitedBy}; i++)\n" +
                            "        sem_post(semaphore_${it.name});\n"
                )
            else if (it.waitedBy == 1)
                sb.append(
                    "    sem_post(semaphore_${it.name});\n"
                )
            sb.append(
                "    return ptr;\n" +
                        "}\n"
            )
        }
    }
    sb.append(
        "int lab2_init() {\n" +
                "    if (pthread_mutex_init(&lock, NULL) != 0) {\n" +
                "        std::cout << \"Mutex init failed\" << std::endl;\n" +
                "        return 1;\n" +
                "    }\n"
    )
    if (this.any { it.waitedBy > 0 }) {
        this.sortedBy { it.name }.forEach {
            if (it.waitedBy > 0) {
                    sb.append(
                        "    if ((semaphore_${it.name} = sem_open(\"/my_semaphore_${it.name}\", O_CREAT, 0777, 1)) == SEM_FAILED) {\n" +
                            "        std::cerr << \"Semaphore ${it.name.capitalize()} init failed\" << std::endl;\n" +
                            "        return 1;\n" +
                            "    }\n"
                    )
            }
        }
    }
    if (this.isNotEmpty()) {
        sb.append("    int err;\n")
        this.sortedBy { it.name }.forEach {
            sb.append("    err = pthread_create(&thread_id_${it.name}, NULL, thread_${it.name}, (void *) NULL);\n" +
                    "    if (err != 0)\n" +
                    "        std::cerr << \"Can't create thread ${it.name.capitalize()}: \" << strerror(err) << std::endl;\n")
        }
    }
    if (this.isNotEmpty()) {
        this.sortedBy { it.name }.forEach {
            sb.append("    pthread_join(thread_id_${it.name}, NULL);\n")
        }
    }
    sb.append("    pthread_mutex_destroy(&lock);\n")
    if (this.any { it.waitedBy > 0 }) {
        this.sortedBy { it.name }.forEach {
            if (it.waitedBy > 0) {
                sb.append(
                    "    sem_close(semaphore_${it.name});\n"
                )
            }
        }
    }
    if (this.any { it.waitedBy > 0 }) {
        this.sortedBy { it.name }.forEach {
            if (it.waitedBy > 0) {
                sb.append(
                    "    sem_unlink(\"/my_semaphore_${it.name}\");\n"
                )
            }
        }
    }
    sb.append("    return 0;\n}")
    sb.append("    \n")
    sb.append("    \n")
    return sb.toString()
}