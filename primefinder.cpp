#include "primefinder.h"
#include <QtMath>

PrimeFinder::PrimeFinder() {}

PrimeFinder::PrimeFinder(int s, int e, int t)
    : start(s), end(e), thread(t) {}

void PrimeFinder::findPrime() {
    for (int num = start; num <= end; num++)
        if(isPrime(num)) {
            emit primeFound(num, thread);

            // 2 & 3 are the only consecutive primes,
            // so we skip the next integer with an extra num++:
            // (this is much less work than another full loop)
            if (num >= 3)
                num++;
        }
    emit jobDone();
}

bool PrimeFinder::isPrime(int candidate) {
    if (candidate <= 1) // eliminate anything lower than 2
            return false;
    for (int i = 2; i < qSqrt(candidate); i++)
            if (candidate % i == 0)
                return false;
    return true;
}
