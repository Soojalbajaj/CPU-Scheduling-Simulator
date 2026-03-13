#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class mainwindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void runFCFS();
    void runSJF();
    void runPriority();
    void runRoundRobin();

private:
    Ui::mainwindow *ui;

    void readProcessData(int bt[], int at[], int pr[], int &n);
    void printToResult(const QString &text);

    void FCFS(int bt[], int at[], int n);
    void SJF(int bt[], int at[], int n);
    void Priority(int bt[], int at[], int pr[], int n);
    void RoundRobin(int bt[], int at[], int n, int tq);
};

#endif
