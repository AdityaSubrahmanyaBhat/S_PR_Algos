#include <iostream>
#include <vector>
#include <numeric>
#include <limits> 

using namespace std;

class Process
{
public:
    int processID, arrivalTime, burstTime;
    bool completed;
};

void calcWT(vector<Process> process, int n, int waitingTimeArray[], int responseTimeArray[])
{
    int tempBurstTimeArray[n], minBurstTime = INT16_MAX, currentTime = 0, processCount = 0, min = 0, completionTime = 0;
    for (int i = 0; i < n; i++)
    {
        tempBurstTimeArray[i] = process[i].burstTime;
    }

    while (processCount != n)
    {
        int flag = 0;
        for (int i = 0; i < n; i++)
        {
            if (process[i].arrivalTime <= currentTime && tempBurstTimeArray[i] < minBurstTime && process[i].completed != true)
            {

                minBurstTime = process[i].burstTime;
                min = i;
                flag = 1;
            }
        }
        if (responseTimeArray[min] == INT16_MIN && flag)
        {
            responseTimeArray[min] = currentTime - process[min].arrivalTime;
        }
        if (flag == 0)
        {
            currentTime++;
            continue;
        }
        tempBurstTimeArray[min]--;
        if (!tempBurstTimeArray[min])
        {
            process[min].completed = true;
            processCount++;
            flag = 0;
            completionTime = currentTime + 1;
            waitingTimeArray[min] = completionTime -
                               process[min].burstTime -
                               process[min].arrivalTime;

            if (waitingTimeArray[min] < 0)
                waitingTimeArray[min] = 0;
        }
        minBurstTime = INT16_MAX;
        currentTime++;
    }
}

void calcTAT(vector<Process> process, int n,
             int waitingTimeArray[], int turnAroundTimeArray[])
{
    for (int i = 0; i < n; i++)
    {
        turnAroundTimeArray[i] = process[i].burstTime + waitingTimeArray[i];
    }
}

void SRTF(vector<Process> process, int n)
{
    int waitingTimeArray[n], turnAroundTimeArray[n], responseTimeArray[n], total_wt,
        total_tat, total_rt;
    fill(responseTimeArray, responseTimeArray + n, INT16_MIN);
    calcWT(process, n, waitingTimeArray, responseTimeArray);
    calcTAT(process, n, waitingTimeArray, turnAroundTimeArray);
    cout << "Process "
         << "   Burst time "
         << "      Waiting time "
         << " Turn around time "
         << " Response Time" << endl;

    for (int i = 0; i < n; i++)
    {
        cout << "   " << process[i].processID << "\t\t"
             << process[i].burstTime << "\t\t " << waitingTimeArray[i]
             << "\t\t " << turnAroundTimeArray[i] << "\t\t " << responseTimeArray[i] << endl;
    }
    total_rt = accumulate(responseTimeArray, responseTimeArray + n, 0);
    total_wt = accumulate(waitingTimeArray, waitingTimeArray + n, 0);
    total_tat = accumulate(turnAroundTimeArray, turnAroundTimeArray + n, 0);
    cout << "\nAverage waiting time = " << total_wt << "/" << n << " = "
         << (float)total_wt / (float)n << endl;
    cout << "Average turn around time = " << total_tat << "/" << n << " = "
         << (float)total_tat / (float)n << endl;
    cout << "Average response time = " << total_rt << "/" << n << " = "
         << (float)total_rt / (float)n << endl;
    ;
}

int main()
{
    Process process;
    vector<Process> process_vector;
    int n;
    cout << "Enter the number of processes : ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Process temp;
        cout << "Enter Arrival time and Burst time for process " << i + 1 << endl;
        for (int j = 0; j < 1; j++)
        {
            temp.processID = i + 1;
            cin >> temp.arrivalTime;
            cin >> temp.burstTime;
            temp.completed = false;
        }
        process_vector.push_back(temp);
    }
    SRTF(process_vector, n);
    return 0;
}
