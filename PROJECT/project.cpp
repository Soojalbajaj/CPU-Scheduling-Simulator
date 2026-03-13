#include <iostream>
#include <algorithm>
using namespace std;

/* ------------------ FCFS ------------------ */
void FCFS(int bt[], int at[], int n) {
    cout << "\n--- FCFS (First-Come, First-Served) ---\n";

    struct Process {
        int pid;
        int at;
        int bt;
    } proc[10];
    
    for(int i = 0; i < n; i++) {
        proc[i].pid = i + 1;
        proc[i].at = at[i];
        proc[i].bt = bt[i];
    }

    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(proc[j].at > proc[j+1].at) {
                swap(proc[j], proc[j+1]);
            }
        }
    }

    int wt[10], tat[10], ct[10];
    int time = proc[0].at;
    wt[0] = 0;
    ct[0] = time + proc[0].bt;
    time = ct[0];

    for(int i = 1; i < n; i++) {
        if(time < proc[i].at) {
            time = proc[i].at;
        }
        wt[i] = time - proc[i].at;
        ct[i] = time + proc[i].bt;
        time = ct[i];
    }

    for(int i = 0; i < n; i++) tat[i] = ct[i] - proc[i].at;

    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT\n";
    for(int i = 0; i < n; i++)
        cout << "P" << proc[i].pid << "\t" 
             << proc[i].at << "\t" 
             << proc[i].bt << "\t"
             << ct[i] << "\t" 
             << wt[i] << "\t" 
             << tat[i] << endl;

    double totalWT=0, totalTAT=0;
    for(int i = 0; i < n; i++){ 
        totalWT+=wt[i]; 
        totalTAT+=tat[i]; 
    }
    cout << "\nAverage WT = " << totalWT/n 
         << ", Average TAT = " << totalTAT/n << endl;

    cout << "\nGantt Chart:\n";
    cout << "|";
    for(int i = 0; i < n; i++) {
        cout << " P" << proc[i].pid << " |";
    }
    cout << endl;
    
    cout << "0";
    for(int i = 0; i < n; i++) {
        if(ct[i] < 10) {
            cout << "    " << ct[i];
        } else {
            cout << "   " << ct[i];
        }
    }
    cout << endl;
}
/* ------------------ SJF ------------------ */
void SJF(int bt[], int at[], int n) {
    cout << "\n------ SJF (Shortest Job First) ------\n";

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

    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT\n";
    for(int i=0;i<n;i++)
        cout << "P" << pid[i] << "\t" << at_copy[i] << "\t" << bt_copy[i] << "\t"
             << ct[i] << "\t" << wt[i] << "\t" << tat[i] << endl;

    double totalWT=0, totalTAT=0;
    for(int i=0;i<n;i++){ 
        totalWT += wt[i]; 
        totalTAT += tat[i]; 
    }
    cout << "Average WT = " << totalWT/n << ", Average TAT = " << totalTAT/n << endl;

    cout << "\nGantt Chart:\n";
    
    time = 0;
    for(int i=0;i<10;i++) completed[i] = false;
    completedCount = 0;
    
    cout << "|";
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
            if(time == 0) cout << " IDLE |";
            time++;
        } else {
            cout << " P" << pid[shortest] << " |";
            time = ct[shortest];
            completed[shortest] = true;
            completedCount++;
        }
    }
    cout << endl;
    
    time = 0;
    for(int i=0;i<10;i++) completed[i] = false;
    completedCount = 0;
    bool first = true;
    
    cout << "0";
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
                cout << "   " << time;
                first = false;
            }
            time = ct[shortest];
            cout << "   " << time;
            completed[shortest] = true;
            completedCount++;
        }
    }
    cout << endl;
}

/* ------------------ Priority ------------------ */
void Priority(int bt[], int at[], int pr[], int n) {
    cout << "\n------ Priority Scheduling ------\n";

    int wt[10], tat[10], ct[10], pid[10], bt_remaining[10], at_copy[10], pr_copy[10];
    bool completed[10] = {false};
    
    for(int i=0;i<n;i++) {
        pid[i] = i+1;
        bt_remaining[i] = bt[i];
        at_copy[i] = at[i];
        pr_copy[i] = pr[i];
    }

    int time = 0, completedCount = 0;
    int current = -1;
    int ganttOrder[50], ganttStart[50], ganttEnd[50], ganttCount = 0;
    
    while(completedCount < n) {
        int highest = -1;
        int maxPriority = -1;
        
        for(int i=0; i<n; i++) {
            if(!completed[i] && at_copy[i] <= time && pr_copy[i] > maxPriority) {
                maxPriority = pr_copy[i];
                highest = i;
            }
        }
        
        if(highest == -1) {
            time++;
            continue;
        }
        
        if(current != highest) {
            if(current != -1 && bt_remaining[current] > 0) {
                ganttEnd[ganttCount-1] = time;
            }
            ganttOrder[ganttCount] = highest;
            ganttStart[ganttCount] = time;
            current = highest;
            ganttCount++;
        }
        
        bt_remaining[highest]--;
        time++;
        
        if(bt_remaining[highest] == 0) {
            ct[highest] = time;
            tat[highest] = ct[highest] - at_copy[highest];
            wt[highest] = tat[highest] - bt[highest];
            completed[highest] = true;
            completedCount++;
            ganttEnd[ganttCount-1] = time;
            current = -1;
        }
    }

    cout << "\nPID\tAT\tBT\tPR\tCT\tWT\tTAT\n";
    for(int i=0;i<n;i++)
        cout << "P" << pid[i] << "\t" << at_copy[i] << "\t" << bt[i] << "\t" 
             << pr_copy[i] << "\t" << ct[i] << "\t" << wt[i] << "\t" << tat[i] << endl;

    double totalWT=0, totalTAT=0;
    for(int i=0;i<n;i++){ 
        totalWT += wt[i]; 
        totalTAT += tat[i]; 
    }
    cout << "Average WT = " << totalWT/n << ", Average TAT = " << totalTAT/n << endl;

    cout << "\nGantt Chart:\n";
    cout << "|";
    for(int i=0;i<ganttCount;i++) {
        cout << " P" << pid[ganttOrder[i]] << " |";
    }
    cout << endl;
    
    cout << ganttStart[0];
    for(int i=0;i<ganttCount;i++) {
        cout << "   " << ganttEnd[i];
    }
    cout << endl;
}

/* ------------------ Round Robin ------------------ */
void RoundRobin(int bt[], int at[], int n, int tq) {
    cout << "\n------ Round Robin Scheduling ------\n";

    int rem[10], wt[10] = {0}, tat[10], ct[10] = {0}, pid[10], at_copy[10];
    int time = 0, completed = 0;
    
    int queue[100], front = 0, rear = 0;
    bool inQueue[10] = {false};
    
    for(int i = 0; i < n; i++) {
        rem[i] = bt[i];
        pid[i] = i + 1;
        at_copy[i] = at[i];
        wt[i] = 0;
        ct[i] = 0;
    }
    
    int ganttProcess[100], ganttTime[100], ganttIndex = 0;
    
    int indices[10];
    for(int i = 0; i < n; i++) indices[i] = i;
    
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n-i-1; j++) {
            if(at_copy[indices[j]] > at_copy[indices[j+1]]) {
                int temp = indices[j];
                indices[j] = indices[j+1];
                indices[j+1] = temp;
            }
        }
    }
    
    for(int i = 0; i < n; i++) {
        if(at_copy[indices[i]] == 0) {
            queue[rear++] = indices[i];
            inQueue[indices[i]] = true;
        }
    }
    
    if(front == rear) {
        int minAT = 1000;
        for(int i = 0; i < n; i++) {
            if(at_copy[i] < minAT) minAT = at_copy[i];
        }
        time = minAT;
        
        for(int i = 0; i < n; i++) {
            if(at_copy[i] == time && !inQueue[i]) {
                queue[rear++] = i;
                inQueue[i] = true;
            }
        }
    }
    
    while(completed < n) {
        if(front == rear) {
            time++;
            for(int i = 0; i < n; i++) {
                if(at_copy[i] <= time && rem[i] > 0 && !inQueue[i]) {
                    queue[rear++] = i;
                    inQueue[i] = true;
                }
            }
            continue;
        }
        
        int current = queue[front++];
        inQueue[current] = false;
        
        ganttProcess[ganttIndex] = current;
        ganttTime[ganttIndex] = time;
        ganttIndex++;
        
        int execTime = (rem[current] > tq) ? tq : rem[current];
        time += execTime;
        rem[current] -= execTime;
        
        ganttProcess[ganttIndex] = current;
        ganttTime[ganttIndex] = time;
        ganttIndex++;
        
        for(int i = 0; i < n; i++) {
            if(at_copy[i] <= time && rem[i] > 0 && !inQueue[i] && i != current) {
                queue[rear++] = i;
                inQueue[i] = true;
            }
        }
        
        if(rem[current] > 0) {
            queue[rear++] = current;
            inQueue[current] = true;
        } else {
            ct[current] = time;
            tat[current] = ct[current] - at_copy[current];
            wt[current] = tat[current] - bt[current];
            completed++;
        }
    }
    
    cout << "\nPID\tAT\tBT\tCT\tWT\tTAT\n";
    for(int i = 0; i < n; i++) {
        cout << "P" << pid[i] << "\t" << at_copy[i] << "\t" << bt[i] << "\t"
             << ct[i] << "\t" << wt[i] << "\t" << tat[i] << endl;
    }
    
    double totalWT = 0, totalTAT = 0;
    for(int i = 0; i < n; i++) {
        totalWT += wt[i];
        totalTAT += tat[i];
    }
    cout << "Average WT = " << totalWT/n << ", Average TAT = " << totalTAT/n << endl;
    
    cout << "\nGantt Chart:\n";
    cout << "|";
    for(int i = 0; i < ganttIndex; i += 2) {
        cout << " P" << pid[ganttProcess[i]] << " |";
    }
    cout << endl;
    
    cout << ganttTime[0];
    for(int i = 1; i < ganttIndex; i += 2) {
        cout << "  " << ganttTime[i];
    }
    cout << endl;
}

/* ------------------ MAIN ------------------ */
int main() {
    int n, choice, tq, bt[10], at[10], pr[10];

    cout << "Enter number of processes: ";
    cin >> n;

    for(int i=0;i<n;i++){
        cout << "Arrival Time of P" << i+1 << ": ";
        cin >> at[i];
        cout << "Burst Time of P" << i+1 << ": ";
        cin >> bt[i];
        cout << "Priority of P" << i+1 << ": ";
        cin >> pr[i];
        cout << "----------------\n";
    }

    // Arrival time sorting
    /*for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(at[i] > at[j]){
                swap(at[i], at[j]);
                swap(bt[i], bt[j]);
                swap(pr[i], pr[j]);
            }
        }
    }*/

    cout << "\n1.FCFS\n2.SJF\n3.Priority\n4.Round Robin\nChoose: ";
    cin >> choice;

    switch(choice){
        case 1: FCFS(bt, at, n); break;
        case 2: SJF(bt, at, n); break;
        case 3: Priority(bt,at, pr, n); break;
        case 4:
            cout << "Enter Time Quantum: ";
            cin >> tq;
            RoundRobin(bt, at, n, tq);
            break;
        default:
            cout << "Invalid Choice";
    }

    return 0;
}
