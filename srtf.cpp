#include <iostream>
#include <climits>
#include <iomanip>
#include <vector>

using namespace std;

struct Process
{
    int pid;
    int at;
    int bt;
};

int main()
{
    int n;
    cout << "Enter total number of processes: ";
    cin >> n;

    Process proc[n];
    int rt[n];
    int wt[n], tat[n], ct[n];
    float total_wt = 0, total_tat = 0;
    vector<int> timeline; // For Gantt Chart

    for (int i = 0; i < n; i++)
    {
        proc[i].pid = i + 1;
        cout << "Enter AT and BT for Process " << i + 1 << ": ";
        cin >> proc[i].at >> proc[i].bt;
        rt[i] = proc[i].bt;
    }

    int completed = 0, currentTime = 0;
    while (completed != n)
    {
        int shortest = -1;
        int min_rt = INT_MAX;

        for (int j = 0; j < n; j++)
        {
            if ((proc[j].at <= currentTime) && (rt[j] < min_rt) && rt[j] > 0)
            {
                min_rt = rt[j];
                shortest = j;
            }
        }

        if (shortest == -1)
        {
            timeline.push_back(0); // 0 for IDLE
            currentTime++;
        }
        else
        {
            timeline.push_back(proc[shortest].pid);
            rt[shortest]--;

            if (rt[shortest] == 0)
            {
                completed++;
                ct[shortest] = currentTime + 1;
                tat[shortest] = ct[shortest] - proc[shortest].at;
                wt[shortest] = tat[shortest] - proc[shortest].bt;

                total_wt += wt[shortest];
                total_tat += tat[shortest];
            }
            currentTime++;
        }
    }

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << proc[i].pid << "\t" << proc[i].at << "\t"
             << proc[i].bt << "\t" << ct[i] << "\t"
             << tat[i] << "\t" << wt[i] << endl;
    }

    cout << "\n--- Gantt Chart ---" << endl;
    int current_pid = timeline[0];
    int start_time = 0;

    for (int t = 1; t < timeline.size(); t++)
    {
        if (timeline[t] != current_pid)
        {
            cout << start_time << "--" << t << "\t| ";
            if (current_pid == 0)
            {
                cout << "IDLE";
            }
            else
            {
                cout << "P" << current_pid;
            }
            cout << " |" << endl;

            current_pid = timeline[t];
            start_time = t;
        }
    }

    cout << start_time << "--" << timeline.size() << "\t| ";
    if (current_pid == 0)
    {
        cout << "IDLE";
    }
    else
    {
        cout << "P" << current_pid;
    }
    cout << " |" << endl;

    cout << "\nAverage Waiting Time: " << (total_wt / n) << endl;
    cout << "Average Turnaround Time: " << (total_tat / n) << endl;

    return 0;
}
