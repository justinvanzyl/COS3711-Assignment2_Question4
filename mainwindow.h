#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "primefinder.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startButtonReleased();
    void addPrimeToUI(int p, int t);
    void threadComplete();

private:
    void cleanUp();
    Ui::MainWindow *ui;
    int threadCount;
    QList<QThread*> threads;
    QList<PrimeFinder*> jobs;
};
#endif // MAINWINDOW_H
