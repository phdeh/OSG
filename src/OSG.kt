import java.io.File
import java.io.PrintWriter
import java.util.*

fun main() {
    (1..20).forEach {
        val program = readProgram(it)
        val tt = generateThreadTasks(program)
        println("Variant $it:")
        tt.forEach { i ->
            println(" | - Thread ${i.name}:")
            println(" |    | - starts on: ${i.startsOn}")
            println(" |    | - stops on:  ${i.stopsOn}")
            println(" |    | - lifetime:  ${i.iterations}")
            println(" |    | - waits for: ${i.waitsFor.join()}")
            println(" |    | - waited by: ${i.waitedBy}")
        }
        tt.toWindowsCode(it).writeTo("windows/$it/lab3.cpp")
        windowsMain.writeTo("windows/$it/main.cpp")
        windowsLabH.writeTo("windows/$it/lab3.h")
        windowsRunBat.writeTo("windows/$it/run.bat")

        tt.toUnixCode(it).writeTo("unix/$it/lab2.cpp")
    }
}

fun generateThreadTasks(program: List<List<String>>): List<ThreadTask> {
    val threads = program.toThreadTasks()
    program.forEachIndexed { step, list ->
        threads.forEach {
            if (it in list) {
                if (it.didNotStartedYet) {
                    it.startsOn = step
                    it.waitsFor += threads.filter { i -> i.alreadyDone && i.stopsOn != step }
                }
                it.iterations++
            } else if (it.alreadyStarted && it.didNotDoneYet)
                it.stopsOn = step - 1
        }
    }
    threads.forEach {
        if (it.didNotDoneYet)
            it.stopsOn = program.size - 1
        it.waitsFor.forEach { i ->
            i.waitedBy++
        }
    }
    return threads
}

fun readProgram(variant: Int): List<List<String>> {
    val columns = mutableListOf<List<String>>()
    val scanner = Scanner(File("task/task$variant.txt"))
    while (scanner.hasNextLine())
        columns += scanner.nextLine().split("").toList().filter { it.isNotEmpty() }
    return columns.toList()
}

fun String.writeTo(path: String) {
    File(path.substring(0, path.lastIndexOf('/'))).mkdirs()
    val pw = PrintWriter(File(path))
    this.split('\n').forEach {
        pw.println(it)
    }
    pw.close()
}

data class ThreadTask(
    var name: String,
    var startsOn: Int = -1,
    var stopsOn: Int = -1,
    var iterations: Int = 0,
    var waitedBy: Int = 0,
    val waitsFor: MutableSet<ThreadTask> = mutableSetOf()
) {
    val didNotStartedYet get() = startsOn == -1
    val alreadyStarted get() = startsOn != -1
    val didNotDoneYet get() = stopsOn == -1
    val alreadyDone get() = stopsOn != -1
}

operator fun List<ThreadTask>.get(index: String): ThreadTask {
    val v = this.find { it.name == index }
    if (v != null)
        return v
    throw IllegalStateException("$index should be in thread set")
}

fun List<List<String>>.toThreadTasks(): List<ThreadTask> {
    val ss = mutableSetOf<String>()
    this.forEach { it.forEach { j -> ss += j } }
    return List(ss.size) { ThreadTask(ss.toList()[it]) }
}

operator fun List<String>.contains(threadTask: ThreadTask): Boolean {
    this.forEach {
        if (it == threadTask.name)
            return true
    }
    return false
}

fun Set<ThreadTask>.join(): String {
    if (this.isEmpty())
        return "nothing"
    val s = this.toMutableList()
    s.sortBy { it.name }
    val sb = StringBuilder()
    s.forEachIndexed { i, it ->
        sb.append(it.name)
        if (i != s.size - 1)
            sb.append(", ")
    }
    return sb.toString()
}