#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
};

void findWaitingTime(const vector<Process>& processes, vector<int>& waitingTime) {
    waitingTime[0] = 0;
    
    for (size_t i = 1; i < processes.size(); i++) {
        waitingTime[i] = waitingTime[i - 1] + processes[i - 1].burstTime;
    }
}
void findTurnaroundTime(const vector<Process>& processes, const vector<int>& waitingTime, vector<int>& turnaroundTime) {
    for (size_t i = 0; i < processes.size(); i++) {
        turnaroundTime[i] = waitingTime[i] + processes[i].burstTime;
    }
}

void findAverageTime(const vector<Process>& processes) {
    vector<int> waitingTime(processes.size(), 0);
    vector<int> turnaroundTime(processes.size(), 0);

findWaitingTime(processes, waitingTime);
    findTurnaroundTime(processes, waitingTime, turnaroundTime);

    float totalWaitingTime = 0, totalTurnaroundTime = 0;
    for (size_t i = 0; i < processes.size(); i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    float averageWaitingTime = totalWaitingTime / processes.size();
    float averageTurnaroundTime = totalTurnaroundTime / processes.size();
 cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (size_t i = 0; i < processes.size(); i++) {
        cout << "P" << processes[i].id << "\t" << processes[i].burstTime << "\t\t" 
             << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
    }

    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
    cout << "Average Turnaround Time: " << averageTurnaroundTime << endl;
}

int main() {
    int n;

    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        processes[i].arrivalTime = 0;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
    }

    findAverageTime(processes);
    return 0;
}

