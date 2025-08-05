#include <QElapsedTimer>
#include <QDebug>

#ifdef Q_OS_WIN
#include <windows.h>
#include <psapi.h>

size_t getMemoryUsageKB() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize / 1024;
}
#elif defined(Q_OS_UNIX)
#include <sys/resource.h>
long getMemoryUsageKB() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return usage.ru_maxrss;
}
#endif

template<typename Func>
void benchmark(const QString& name, Func func) {
    auto memBefore = getMemoryUsageKB();
    QElapsedTimer timer;
    timer.start();

    func();

    auto memAfter = getMemoryUsageKB();
    qint64 elapsed = timer.elapsed();

    qDebug() << name << "→ Time:" << elapsed << "ms,"
             << "Memory:" << (memAfter - memBefore) << "KB";
}
