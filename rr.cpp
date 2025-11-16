#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct GanttEntry
{
    int pid;
    int start;
    int end;
};

void findTimes(int n, vector<int> &bt, int quantum)
{
    vector<int> rem_bt = bt;

    vector<int> wt(n, 0);
    vector<int> tat(n, 0);
    vector<GanttEntry> gantt_chart;

    int t = 0;

    while (true)
    {
        bool all_done = true;

        for (int i = 0; i < n; i++)
        {
            if (rem_bt[i] > 0)
            {
                all_done = false;
                int start_time = t;

                if (rem_bt[i] <= quantum)
                {
                    t += rem_bt[i];
                    tat[i] = t;
                    rem_bt[i] = 0;
                    gantt_chart.push_back({i + 1, start_time, t});
                }
                else
                {
                    t += quantum;
                    rem_bt[i] -= quantum;
                    gantt_chart.push_back({i + 1, start_time, t});
                }
            }
        }

        if (all_done == true)
        {
            break;
        }
    }

    for (int i = 0; i < n; i++)
    {
        wt[i] = tat[i] - bt[i];
    }

    cout << "\n--- Gantt Chart ---\n\n";
    cout << " ";
    for (const auto &entry : gantt_chart)
    {
        cout << "------ ";
    }
    cout << "\n|";
    for (const auto &entry : gantt_chart)
    {
        cout << "  P" << entry.pid << "  |";
    }
    cout << "\n ";
    for (const auto &entry : gantt_chart)
    {
        cout << "------ ";
    }
    cout << "\n0";
    for (const auto &entry : gantt_chart)
    {
        cout << setw(7) << entry.end;
    }
    cout << "\n\n";

    cout << "----------------------------------------------------------\n";
    cout << "Process\t Burst Time\t Waiting Time\t Turnaround Time\n";
    cout << "----------------------------------------------------------\n";

    float total_wt = 0;
    float total_tat = 0;

    for (int i = 0; i < n; i++)
    {
        total_wt += wt[i];
        total_tat += tat[i];
        cout << " P" << (i + 1) << "\t\t " << bt[i] << "\t\t "
             << wt[i] << "\t\t " << tat[i] << endl;
    }

    cout << "\n----------------------------------------------------------\n";
    cout << "Average Waiting Time: " << fixed << setprecision(2) << (total_wt / n) << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << (total_tat / n) << endl;
}

int main()
{
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<int> burst_time(n);
    for (int i = 0; i < n; i++)
    {
        cout << "Enter burst time for process P" << (i + 1) << ": ";
        cin >> burst_time[i];
    }

    int quantum;
    cout << "Enter time quantum: ";
    cin >> quantum;

    findTimes(n, burst_time, quantum);

    return 0;
}