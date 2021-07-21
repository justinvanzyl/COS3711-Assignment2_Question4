#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->statusbar->showMessage("Ready");
    connect(ui->startButton, SIGNAL(released()),this, SLOT(startButtonReleased()));
}

MainWindow::~MainWindow() {
    cleanUp();
    delete ui;
/*  The default closeEvent() function will invoke this destructor,
 *  so it is not necessary to overload it. cleanUp() can be called
 *  here and will do all required housekeeping if the UI is closed
 *  while threads are still running.
 */
}

void MainWindow::startButtonReleased() {

    // some UI housekeeping:
    ui->thread1TextEdit->clear();
    ui->thread2TextEdit->clear();
    ui->thread3TextEdit->clear();
    ui->thread4TextEdit->clear();
    ui->statusbar->showMessage("finding prime numbers...");

    // fetch some input values and calculate some others:
    threadCount = ui->threadsSpinBox->value();
    int start = ui->startSpinBox->value();
    int end = ui->endSpinBox->value();
    int workload = (end - start + 1) / threadCount;
    int thStart, thEnd;

    // assign each job (primefinder instance) to a thread and run it:
    for (int i = 0; i < threadCount; i++) {
        thStart = start+workload*i;
        if (threadCount == i+1)
            thEnd = end;
        else
            thEnd = start+workload*(i+1);
        threads.append(new QThread());
        jobs.append(new PrimeFinder(thStart, thEnd, i));
        connect(threads.at(i), SIGNAL(started()), jobs.at(i), SLOT(findPrime()));
        connect(jobs.at(i), SIGNAL(jobDone()), this, SLOT(threadComplete()));
        connect(jobs.at(i), SIGNAL(primeFound(int,int)), this, SLOT(addPrimeToUI(int,int)));
        jobs.at(i)->moveToThread(threads.at(i));
        threads.at(i)->start();
    }
}

void MainWindow::addPrimeToUI(int p, int t) {
    switch (t) {
    case 0:
        ui->thread1TextEdit->appendPlainText(QString::number(p));
        break;
    case 1:
        ui->thread2TextEdit->appendPlainText(QString::number(p));
        break;
    case 2:
        ui->thread3TextEdit->appendPlainText(QString::number(p));
        break;
    case 3:
        ui->thread4TextEdit->appendPlainText(QString::number(p));
        break;
    }
}

void MainWindow::threadComplete() {
    threadCount--;
    if (threadCount == 0) {
        cleanUp();
        ui->statusbar->showMessage("Ready");
    }
}

void MainWindow::cleanUp() {
    foreach(QThread *thread, threads) {
        thread->quit();
        thread->wait();
    }
    qDeleteAll(jobs);
    jobs.clear();
    qDeleteAll(threads);
    threads.clear();
}
