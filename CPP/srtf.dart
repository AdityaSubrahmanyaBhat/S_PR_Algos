import 'dart:io';

class Process
{
    late int processID, arrivalTime, burstTime;
    late bool completed;
}

void calcWT(List<Process> process, int n, List<int> waitingTimeArray, List<int> responseTimeArray)
{
    List<int> tempBurstTimeArray=[];
    int minBurstTime = 999999, currentTime = 0, processCount = 0, min = 0, completionTime = 0;
    for (int i = 0; i < n; i++)
    {
        tempBurstTimeArray.add( process[i].burstTime);
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
        if (responseTimeArray[min] == -99999999)
        {
            responseTimeArray[min] = currentTime - process[min].arrivalTime;
        }
        if (flag == 0)
        {
            currentTime++;
            continue;
        }
        tempBurstTimeArray[min]--;
        if (tempBurstTimeArray[min]==0)
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
        minBurstTime = 9999999;
        currentTime++;
    }
}

void calcTAT(List<Process> process, int n,
             List<int> waitingTimeArray, List<int> turnAroundTimeArray)
{
    for (int i = 0; i < n; i++)
    {
        turnAroundTimeArray.add( process[i].burstTime + waitingTimeArray[i]);
    }
}

void SRTF(List<Process> process, int n)
{
    List<int> waitingTimeArray=[], turnAroundTimeArray=[], responseTimeArray=[];
    late int total_wt,
        total_tat, total_rt;
    // responseTimeArray.fillRange(0,n-1 ,-99999999);
    calcWT(process, n, waitingTimeArray, responseTimeArray);
    calcTAT(process, n, waitingTimeArray, turnAroundTimeArray);
    print("Process    Burst time       Waiting time  Turn around time  Response Time" );

    for (int i = 0; i < n; i++)
    {
        print("    ${process[i].processID} \t\t");
print("${process[i].burstTime} \t\t  ${waitingTimeArray[i]} \t\t ${turnAroundTimeArray[i]} \t\t ${responseTimeArray[i]} ");
    }

    responseTimeArray.forEach((element) =>total_rt+=element);
    waitingTimeArray.forEach((element) =>total_wt+=element);
    turnAroundTimeArray.forEach((element) =>total_tat+=element);
    print("\nAverage waiting time = ${total_wt}/ $n  = ${total_wt /n}" );
    print("\nAverage turn around time = ${total_tat}/ $n  = ${total_tat /n}" );
    print("\nAverage response time = ${total_rt}/ $n  = ${total_rt /n}" );
}

int main()
{
    List<Process> process_vector=[];
    print("Enter the number of processes : ");
    int? n = int.parse(stdin.readLineSync()!);
    for (int i = 0; i < n; i++)
    {
        Process temp=Process();
        print("Enter Arrival time and Burst time for process ${i + 1} : ");
        for (int j = 0; j < 1; j++)
        {
            temp.processID = i + 1;
            temp.arrivalTime = int.parse(stdin.readLineSync()!);
            temp.burstTime = int.parse(stdin.readLineSync()!);
            temp.completed = false;
        }
        process_vector.add(temp);
    }
    for(int i=0;i<n;i++){
      print(process_vector[i].burstTime);
    }
     SRTF(process_vector, n);
    return 0;
}
