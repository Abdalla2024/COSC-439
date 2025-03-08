class Process:
    def __init__(self, pid, arrival_time, burst_time):
        self.pid = pid
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_burst_time = burst_time
        self.start_time = -1
        self.finish_time = -1
        self.turnaround_time = 0
        self.waiting_time = 0

def shortest_job_first(processes):
    # Sort processes based on arrival time and burst time
    processes.sort(key=lambda x: (x.arrival_time, x.burst_time))

    current_time = 0
    completed_processes = 0

    # Loop until all processes are completed
    while completed_processes < len(processes):
        min_remaining_burst_time = float('inf')
        selected_process = None

        # Find process with shortest remaining burst time
        for process in processes:
            if process.arrival_time <= current_time and process.remaining_burst_time > 0:
                if process.remaining_burst_time < min_remaining_burst_time:
                    min_remaining_burst_time = process.remaining_burst_time
                    selected_process = process

        # If no process is selected, increment current time
        if selected_process is None:
            current_time += 1
            continue

        # Mark start time if not already marked
        if selected_process.start_time == -1:
            selected_process.start_time = current_time

        # Execute the selected process for one time unit
        selected_process.remaining_burst_time -= 1
        current_time += 1

        # If process is completed, calculate turnaround and waiting time
        if selected_process.remaining_burst_time == 0:
            selected_process.finish_time = current_time
            selected_process.turnaround_time = selected_process.finish_time - selected_process.arrival_time
            selected_process.waiting_time = selected_process.turnaround_time - selected_process.burst_time
            completed_processes += 1

    # Print turnaround time and waiting time for each process
    print("Process ID\tTurnaround Time\t\tWaiting Time")
    for process in processes:
        print("P{}\t\t{}\t\t\t{}".format(process.pid, process.turnaround_time, process.waiting_time))

if __name__ == "__main__":
    n = int(input("Enter the number of processes: "))
    processes = []
    for i in range(n):
        pid = i + 1
        arrival_time = int(input("Enter arrival time for P{}: ".format(pid)))
        burst_time = int(input("Enter burst time for P{}: ".format(pid)))
        processes.append(Process(pid, arrival_time, burst_time))

    shortest_job_first(processes)
