print(" SHORTEST JOB FIRST (SJF) SCHEDULING - NON PREEMPTIVE ")

n = int(input("Enter number of processes: "))

print("\nEnter each process as → Name | ArrivalTime | BurstTime (e.g., P1 0 5)\n")

processes = []
for i in range(n):
    pid, at, bt = input(f"Process {i+1}: ").split()
    processes.append([pid, int(at), int(bt), 0, 0, 0])

processes.sort(key=lambda x: x[1])

time = 0
completed = 0
gantt = []

while completed < n:
    ready = [p for p in processes if p[1] <= time and p[3] == 0]
    if not ready:
        time += 1
        continue
    p = min(ready, key=lambda x: x[2])
    gantt.append((time, p[0]))
    time += p[2]
    p[3] = time
    p[4] = p[3] - p[1]
    p[5] = p[4] - p[2]
    completed += 1

print("\nProcess\tAT\tBT\tCT\tTAT\tWT")
for p in processes:
    print(f"{p[0]}\t{p[1]}\t{p[2]}\t{p[3]}\t{p[4]}\t{p[5]}")

avg_tat = sum(p[4] for p in processes) / n
avg_wt = sum(p[5] for p in processes) / n
print(f"\nAverage Turnaround Time: {avg_tat:.2f}")
print(f"Average Waiting Time: {avg_wt:.2f}")

print("\n GANTT CHART ")
for start, pid in gantt:
    print(f"| {pid} ", end="")
print("|")

print("0", end=" ")
for start, pid in gantt:
    end_time = next(p[3] for p in processes if p[0] == pid)
    print(f"  {end_time}", end=" ")
print()