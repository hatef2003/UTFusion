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
#include <unistd.h>
#include <fstream>
#include <string>

inline size_t getMemoryUsageBytes() {
    long rss = 0L;
    std::ifstream statm("/proc/self/statm");
    long total_pages = 0;
    if (statm >> total_pages >> rss) {
        return static_cast<size_t>(rss) * sysconf(_SC_PAGESIZE);
    }
    return 0;
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

#endif 
