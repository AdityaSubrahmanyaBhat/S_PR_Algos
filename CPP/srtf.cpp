#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Process
{
public:
    int pId, at, bt;
    bool completed;
};

int* calcWT(vector<Process> proc, int n,int wt[])
{
    int temp_bt[n], min_bt = INT_MAX, cur_time = 0,pCount=0,min=0,completion_time=0;
    for (int i = 0; i < n; i++)
    {
        temp_bt[i] = proc[i].bt;
    }

    while (pCount != n)
    {
        int flag=0;
        for (int i = 0; i < n; i++)
        {
            if (proc[i].at <= cur_time && temp_bt[i] < min_bt && proc[i].completed != true)
            {
                min_bt = proc[i].bt;
                min=i;
                flag=1;
                cout<<i<<endl;
            }
        }
        if (flag == 0) {
            cur_time++;
            continue;
        }
        temp_bt[min]--;
        if (!temp_bt[min])
        {
            proc[min].completed = true;
            pCount++;
            flag=0;
            completion_time = cur_time + 1;
            wt[min] = completion_time -
                           proc[min].bt -
                           proc[min].at;

            if (wt[min] < 0)
                wt[min] = 0;
        }
        min_bt=INT_MAX;
        cur_time++;
    }
    return wt;
}

void calcTAT(vector<Process> proc, int n,
                        int wt[], int tat[])
{
    for (int i = 0; i < n; i++)
    {
        tat[i] = proc[i].bt + wt[i];
    }
}

void SRTF(vector<Process> proc, int n)
{
    int wt[n], tat[n], total_wt = 0,
                       total_tat = 0;

    calcWT(proc, n, wt);
    calcTAT(proc, n, wt, tat);

    cout << "Processes "
         << " Burst time "
         << " Waiting time "
         << " Turn around time\n";


    for (int i = 0; i < n; i++)
    {
        cout << " " << proc[i].pId << "\t\t"
             << proc[i].bt << "\t\t " << wt[i]
             << "\t\t " << tat[i] << endl;
    }

    total_wt = accumulate(wt, wt + n, 0);
    total_tat = accumulate(tat, tat + n, 0);
    cout << "\nAverage waiting time = "
         << (float)total_wt / (float)n << endl;
    cout << "Average turn around time = "
         << (float)total_tat / (float)n << endl;
    ;
}

int main()
{
    Process proc;
    vector<Process> arr;
    int n;
    cout << "Enter n : ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        Process temp;
        cout << "Enter process ID , Burst time and Arrival time for process " << i + 1 << endl;
        for (int j = 0; j < 1; j++)
        {
            cin >> temp.pId;
            cin >> temp.bt;
            cin >> temp.at;
            temp.completed=false;
        }
        arr.push_back(temp);
    }
    SRTF(arr, n);
    return 0;
}
