#ifndef BENCHMARK_UTILS_H
#define BENCHMARK_UTILS_H

#include <QElapsedTimer>
#include <QDebug>
#include <QString>

#ifdef Q_OS_WIN
#include <windows.h>
#include <psapi.h>
inline size_t getMemoryUsageBytes() {
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
    return pmc.WorkingSetSize;
}
#elif defined(Q_OS_UNIX)
#include <sys/resource.h>
inline size_t getMemoryUsageBytes() {
    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    return static_cast<size_t>(usage.ru_maxrss * 1024);
}
#else
inline size_t getMemoryUsageBytes() {
    return 0; // Fallback
}
#endif

template<typename Func>
QStringList benchmark(const QString& name, Func func, int repeat = 1) {
    QStringList results;
    for (int i = 0; i < repeat; ++i) {
        auto memBefore = getMemoryUsageBytes();
        QElapsedTimer timer;
        timer.start();

        func();

        auto memAfter = getMemoryUsageBytes();
        qint64 elapsed = timer.nsecsElapsed();


        QString result = QString("%1 (%2) => Time: %3 ns, Memory: %4 B")
                             .arg(name)
                             .arg(i + 1)
                             .arg(elapsed)
                             .arg(memAfter - memBefore);
        results << result;
    }
    return results;
}

#endif // BENCHMARK_UTILS_H
