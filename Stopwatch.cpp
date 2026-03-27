#include "Stopwatch.h"

void Stopwatch::start() {
    startTime = std::chrono::steady_clock::now();
}

double Stopwatch::stop() {
    std::chrono::time_point endTime = std::chrono::steady_clock::now();
    long durationInNanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    double durationInSeconds = double(durationInNanoseconds)/1000000000.0;
    return durationInSeconds;
}