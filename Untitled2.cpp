#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int waitingTime;
};

bool sortByPriority(const Process& a, const Process& b) {
    return a.priority < b.priority;
}

void priorityScheduling(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitingTime = 0;
  }
    
    while (completed != n) {
        vector<Process> readyQueue;
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                readyQueue.push_back(processes[i]);
            }
        }
        
        if (!readyQueue.empty()) {
            sort(readyQueue.begin(), readyQueue.end(), sortByPriority);
            
            int selectedId = readyQueue[0].id - 1;
            processes[selectedId].remainingTime--;
            currentTime++;
 for (int i = 0; i < n; i++) {
                if (i != selectedId && processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    processes[i].waitingTime++;
                }
            }
            
            if (processes[selectedId].remainingTime == 0) {
                completed++;
            }
        } else {
            currentTime++;
        }
    }
 float totalWaitingTime = 0;
    cout << "\nProcess\tWaiting Time\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << processes[i].id << "\t" << processes[i].waitingTime << endl;
        totalWaitingTime += processes[i].waitingTime;
    }
    
    float averageWaitingTime = totalWaitingTime / n;
    cout << "\nAverage Waiting Time: " << averageWaitingTime << endl;
}
int main() {
    int n;
    
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        cout << "Enter arrival time for process " << i + 1 << ": ";
        cin >> processes[i].arrivalTime;
        cout << "Enter burst time for process " << i + 1 << ": ";
        cin >> processes[i].burstTime;
        cout << "Enter priority for process " << i + 1 << ": ";
        cin >> processes[i].priority;
    }
    
    priorityScheduling(processes);
    
    return 0;
}