import matplotlib.pyplot as plt

class Process:
    def __init__(self, pid, arrival, burst):
        self.pid = pid
        self.arrival = arrival
        self.burst = burst
        self.remaining = burst
        self.completion = 0
        self.start = -1

n = int(input("Enter number of processes: "))
processes = []
for i in range(n):
    pid = f'P{i+1}'
    arrival = int(input(f"Enter arrival time for {pid}: "))
    burst = int(input(f"Enter burst time for {pid}: "))
    processes.append(Process(pid, arrival, burst))

time = 0
completed = 0
gantt = []

while completed < n:
    ready = [p for p in processes if p.arrival <= time and p.remaining > 0]
    
    if ready:
        current = min(ready, key=lambda x: x.remaining)
        if current.start == -1:
            current.start = time
        gantt.append(current.pid)
        current.remaining -= 1
        time += 1
        if current.remaining == 0:
            current.completion = time
            completed += 1
    else:
        gantt.append('Idle')
        time += 1

print("\nProcess\tAT\tBT\tCT\tTAT\tWT")
total_tat = total_wt = 0
for p in processes:
    tat = p.completion - p.arrival
    wt = tat - p.burst
    total_tat += tat
    total_wt += wt
    print(f"{p.pid}\t{p.arrival}\t{p.burst}\t{p.completion}\t{tat}\t{wt}")

print(f"\nAverage TAT: {total_tat/n:.2f}")
print(f"Average WT: {total_wt/n:.2f}")

plt.figure(figsize=(10, 2))
start = 0
for pid in gantt:
    plt.barh(0, 1, left=start, edgecolor='black')
    plt.text(start + 0.5, 0, pid, ha='center', va='center')
    start += 1

plt.yticks([])
plt.xlabel("Time")
plt.title("Gantt Chart - SRTF Scheduling")
plt.show()