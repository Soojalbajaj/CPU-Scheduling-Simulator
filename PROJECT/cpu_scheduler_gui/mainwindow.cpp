#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <QString>
#include <QTableWidgetItem>
#include <QTextStream>
#include <QPushButton>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainwindow)
{
    ui->setupUi(this);

    // Connect buttons to slots
    connect(ui->fcfsButton, &QPushButton::clicked, this, &MainWindow::runFCFS);
    connect(ui->sjfButton, &QPushButton::clicked, this, &MainWindow::runSJF);
    connect(ui->priorityButton, &QPushButton::clicked, this, &MainWindow::runPriority);
    connect(ui->rrButton, &QPushButton::clicked, this, &MainWindow::runRoundRobin);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readProcessData(int bt[], int at[], int pr[], int &n)
{
    n = 0;  // Start with 0 processes
    int totalRows = ui->processTable->rowCount();
    
    for(int i=0; i<totalRows; i++){
        // Only read if cell is not empty
        QTableWidgetItem *item = ui->processTable->item(i, 1);
        if(item && !item->text().isEmpty()) {
            at[n] = ui->processTable->item(i, 1)->text().toInt();
            bt[n] = ui->processTable->item(i, 2)->text().toInt();
            pr[n] = ui->processTable->item(i, 3)->text().toInt();
            n++;  // Increment only for valid rows
        }
    }
}

void MainWindow::printToResult(const QString &text)
{
    ui->resultText->append(text);
}

// ------------------- Slots -------------------
void MainWindow::runFCFS()
{
    int n, bt[10], at[10], pr[10];
    readProcessData(bt, at, pr, n);
    ui->resultText->clear();
    FCFS(bt, at, n);
}

void MainWindow::runSJF()
{
    int n, bt[10], at[10], pr[10];
    readProcessData(bt, at, pr, n);
    ui->resultText->clear();
    SJF(bt, at, n);
}

void MainWindow::runPriority()
{
    int n, bt[10], at[10], pr[10];
    readProcessData(bt, at, pr, n);
    ui->resultText->clear();
    Priority(bt, at, pr, n);
}

void MainWindow::runRoundRobin()
{
    int n, bt[10], at[10], pr[10];
    readProcessData(bt, at, pr, n);
    int tq = ui->timeQuantumSpin->value();
    ui->resultText->clear();
    RoundRobin(bt, at, n, tq);
}

// ------------------- FCFS -------------------
void MainWindow::FCFS(int bt[], int at[], int n) {
    printToResult("\n--- FCFS (First-Come, First-Served) ---\n");

    struct Process { int pid, at, bt; } proc[10];
    for(int i=0;i<n;i++){ proc[i].pid=i+1; proc[i].at=at[i]; proc[i].bt=bt[i]; }

    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(proc[j].at > proc[j+1].at)
                std::swap(proc[j], proc[j+1]);

    int wt[10], tat[10], ct[10];
    int time = proc[0].at;
    wt[0]=0;
    ct[0]=time+proc[0].bt;
    time=ct[0];

    for(int i=1;i<n;i++){
        if(time<proc[i].at) time=proc[i].at;
        wt[i]=time-proc[i].at;
        ct[i]=time+proc[i].bt;
        time=ct[i];
    }

    for(int i=0;i<n;i++) tat[i]=ct[i]-proc[i].at;

    printToResult("\nPID\tAT\tBT\tCT\tWT\tTAT");
    for(int i=0;i<n;i++)
        printToResult(QString("P%1\t%2\t%3\t%4\t%5\t%6")
                          .arg(proc[i].pid).arg(proc[i].at).arg(proc[i].bt)
                          .arg(ct[i]).arg(wt[i]).arg(tat[i]));

    double totalWT=0,totalTAT=0;
    for(int i=0;i<n;i++){ totalWT+=wt[i]; totalTAT+=tat[i]; }
    printToResult(QString("\nAverage WT = %1, Average TAT = %2")
                      .arg(totalWT/n).arg(totalTAT/n));

    // Gantt chart
    QString gantt="|";
    for(int i=0;i<n;i++) gantt+=QString(" P%1 |").arg(proc[i].pid);
    printToResult("\nGantt Chart:\n"+gantt);

    QString times="0";
    for(int i=0;i<n;i++){
        if(ct[i]<10) times+="    "+QString::number(ct[i]);
        else times+="   "+QString::number(ct[i]);
    }
    printToResult(times);
}
// ------------------- SJF -------------------
void MainWindow::SJF(int bt[], int at[], int n){
    printToResult("\n------ SJF (Shortest Job First) ------\n");

    int wt[10], tat[10], ct[10], pid[10], bt_copy[10], at_copy[10];
    bool completed[10] = {false};

    for(int i=0;i<n;i++) {
        pid[i] = i+1;
        bt_copy[i] = bt[i];
        at_copy[i] = at[i];
    }

    int time = 0, completedCount = 0;

    while(completedCount < n) {
        int shortest = -1;
        int minBurst = 9999;

        for(int i=0; i<n; i++) {
            if(!completed[i] && at_copy[i] <= time && bt_copy[i] < minBurst) {
                minBurst = bt_copy[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
        } else {
            wt[shortest] = time - at_copy[shortest];
            ct[shortest] = time + bt_copy[shortest];
            time = ct[shortest];
            tat[shortest] = ct[shortest] - at_copy[shortest];
            completed[shortest] = true;
            completedCount++;
        }
    }

    printToResult("\nPID\tAT\tBT\tCT\tWT\tTAT");
    for(int i=0;i<n;i++)
        printToResult(QString("P%1\t%2\t%3\t%4\t%5\t%6")
                          .arg(pid[i]).arg(at_copy[i]).arg(bt_copy[i])
                          .arg(ct[i]).arg(wt[i]).arg(tat[i]));

    double totalWT=0, totalTAT=0;
    for(int i=0;i<n;i++){
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    printToResult(QString("\nAverage WT = %1, Average TAT = %2").arg(totalWT/n).arg(totalTAT/n));

    //  GANTT CHART 
    time = 0;
    for(int i=0;i<10;i++) completed[i] = false;
    completedCount = 0;

    QString ganttBar = "|";
    while(completedCount < n) {
        int shortest = -1;
        int minBurst = 9999;

        for(int i=0; i<n; i++) {
            if(!completed[i] && at_copy[i] <= time && bt_copy[i] < minBurst) {
                minBurst = bt_copy[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            if(time == 0) ganttBar += " IDLE |";
            time++;
        } else {
            ganttBar += " P" + QString::number(pid[shortest]) + " |";
            time = ct[shortest];
            completed[shortest] = true;
            completedCount++;
        }
    }

    time = 0;
    for(int i=0; i<10; i++) completed[i] = false;
    completedCount = 0;
    bool first = true;

    QString ganttTimes = "0";
    while(completedCount < n) {
        int shortest = -1;
        int minBurst = 9999;

        for(int i=0; i<n; i++) {
            if(!completed[i] && at_copy[i] <= time && bt_copy[i] < minBurst) {
                minBurst = bt_copy[i];
                shortest = i;
            }
        }

        if(shortest == -1) {
            time++;
        } else {
            if(first) {
                if(time < 10)
                    ganttTimes += "    " + QString::number(time);
                else
                    ganttTimes += "   " + QString::number(time);
                first = false;
            }
            time = ct[shortest];

            if(time < 10)
                ganttTimes += "    " + QString::number(time);
            else if(time < 100)
                ganttTimes += "   " + QString::number(time);
            else
                ganttTimes += "  " + QString::number(time);

            completed[shortest] = true;
            completedCount++;
        }
    }

    printToResult("\nGantt Chart:");
    printToResult(ganttBar);
    printToResult(ganttTimes);



}
// ------------------- Priority -------------------
void MainWindow::Priority(int bt[], int at[], int pr[], int n){
    printToResult("\n--- Priority Scheduling ---\n");

    int wt[10], tat[10], ct[10], pid[10], bt_remaining[10], at_copy[10], pr_copy[10];
    bool completed[10]={false};
    for(int i=0;i<n;i++){ pid[i]=i+1; bt_remaining[i]=bt[i]; at_copy[i]=at[i]; pr_copy[i]=pr[i]; }

    int time=0, completedCount=0, current=-1;
    int ganttOrder[50], ganttStart[50], ganttEnd[50], ganttCount=0;

    while(completedCount<n){
        int highest=-1, maxPriority=-1;
        for(int i=0;i<n;i++)
            if(!completed[i] && at_copy[i]<=time && pr_copy[i]>maxPriority){ maxPriority=pr_copy[i]; highest=i; }
        if(highest==-1){ time++; continue; }

        if(current!=highest){
            if(current!=-1 && bt_remaining[current]>0) ganttEnd[ganttCount-1]=time;
            ganttOrder[ganttCount]=highest;
            ganttStart[ganttCount]=time;
            current=highest; ganttCount++;
        }

        bt_remaining[highest]--; time++;

        if(bt_remaining[highest]==0){
            ct[highest]=time;
            tat[highest]=ct[highest]-at_copy[highest];
            wt[highest]=tat[highest]-bt[highest];
            completed[highest]=true;
            completedCount++;
            ganttEnd[ganttCount-1]=time;
            current=-1;
        }
    }

    printToResult("\nPID\tAT\tBT\tPR\tCT\tWT\tTAT");
    for(int i=0;i<n;i++)
        printToResult(QString("P%1\t%2\t%3\t%4\t%5\t%6\t%7")
                          .arg(pid[i]).arg(at_copy[i]).arg(bt[i]).arg(pr_copy[i])
                          .arg(ct[i]).arg(wt[i]).arg(tat[i]));

    double totalWT=0,totalTAT=0;
    for(int i=0;i<n;i++){ totalWT+=wt[i]; totalTAT+=tat[i]; }
    printToResult(QString("\nAverage WT = %1, Average TAT = %2").arg(totalWT/n).arg(totalTAT/n));

    // Gantt chart
    QString gantt="|"; for(int i=0;i<ganttCount;i++) gantt+=QString(" P%1 |").arg(pid[ganttOrder[i]]);
    printToResult("\nGantt Chart:\n"+gantt);

    QString times = QString::number(ganttStart[0]);
    for(int i = 0; i < ganttCount; i++) {
        int currentTime = ganttEnd[i];
        if(currentTime < 10)
            times += "    " + QString::number(currentTime);  
        else if(currentTime < 100)
            times += "   " + QString::number(currentTime);   
        else
            times += "  " + QString::number(currentTime);  
    }
    printToResult(times);
}

// ------------------- Round Robin -------------------
void MainWindow::RoundRobin(int bt[], int at[], int n, int tq){
    printToResult("\n--- Round Robin Scheduling ---\n");

    int rem[10], wt[10]={0}, tat[10], ct[10]={0}, pid[10], at_copy[10];
    int time=0, completed=0;
    int queue[100], front=0, rear=0; bool inQueue[10]={false};
    for(int i=0;i<n;i++){ rem[i]=bt[i]; pid[i]=i+1; at_copy[i]=at[i]; }

    int ganttProcess[100], ganttTime[100], ganttIndex=0;

    int indices[10]; for(int i=0;i<n;i++) indices[i]=i;
    for(int i=0;i<n-1;i++)
        for(int j=0;j<n-i-1;j++)
            if(at_copy[indices[j]]>at_copy[indices[j+1]]) std::swap(indices[j],indices[j+1]);

    for(int i=0;i<n;i++){ if(at_copy[indices[i]]==0){ queue[rear++]=indices[i]; inQueue[indices[i]]=true; } }

    if(front==rear){
        int minAT=1000;
        for(int i=0;i<n;i++) if(at_copy[i]<minAT) minAT=at_copy[i];
        time=minAT;
        for(int i=0;i<n;i++){ if(at_copy[i]==time && !inQueue[i]){ queue[rear++]=i; inQueue[i]=true; } }
    }

    while(completed<n){
        if(front==rear){ time++; for(int i=0;i<n;i++){ if(at_copy[i]<=time && rem[i]>0 && !inQueue[i]){ queue[rear++]=i; inQueue[i]=true; } } continue; }

        int current=queue[front++]; inQueue[current]=false;

        ganttProcess[ganttIndex]=current; ganttTime[ganttIndex]=time; ganttIndex++;

        int execTime=(rem[current]>tq)?tq:rem[current];
        time+=execTime; rem[current]-=execTime;

        ganttProcess[ganttIndex]=current; ganttTime[ganttIndex]=time; ganttIndex++;

        for(int i=0;i<n;i++){ if(at_copy[i]<=time && rem[i]>0 && !inQueue[i] && i!=current){ queue[rear++]=i; inQueue[i]=true; } }

        if(rem[current]>0){ queue[rear++]=current; inQueue[current]=true; }
        else{ ct[current]=time; tat[current]=ct[current]-at_copy[current]; wt[current]=tat[current]-bt[current]; completed++; }
    }

    printToResult("\nPID\tAT\tBT\tCT\tWT\tTAT");
    for(int i=0;i<n;i++)
        printToResult(QString("P%1\t%2\t%3\t%4\t%5\t%6")
                          .arg(pid[i]).arg(at_copy[i]).arg(bt[i])
                          .arg(ct[i]).arg(wt[i]).arg(tat[i]));

    double totalWT=0,totalTAT=0;
    for(int i=0;i<n;i++){ totalWT+=wt[i]; totalTAT+=tat[i]; }
    printToResult(QString("\nAverage WT = %1, Average TAT = %2").arg(totalWT/n).arg(totalTAT/n));

    // Gantt chart
    QString gantt = "|";
    for(int i = 0; i < ganttIndex; i += 2) {
        gantt += QString(" P%1 |").arg(pid[ganttProcess[i]]);
    }
    printToResult(gantt);
    QString times = QString::number(ganttTime[0]);
    for(int i = 1; i < ganttIndex; i += 2) {
        int currentTime = ganttTime[i];
        if(currentTime < 10)
            times += "    " + QString::number(currentTime);  
        else if(currentTime < 100)
            times += "   " + QString::number(currentTime);   
        else
            times += "  " + QString::number(currentTime);    
    }
    printToResult(times);
}
