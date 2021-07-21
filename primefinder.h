#ifndef PRIMEFINDER_H
#define PRIMEFINDER_H

#include <QObject>
#include <QThread>

class PrimeFinder : public QObject
{
    Q_OBJECT
public:
    explicit PrimeFinder();
    explicit PrimeFinder(int s, int e, int t);

public slots:
    void findPrime();

signals:
    void primeFound(int p, int t);
    void jobDone();

private:
    int start;
    int end;
    int thread;
    bool isPrime(int i);
};

#endif // PRIMEFINDER_H
