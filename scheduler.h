#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <vector>
#include <string>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
};

void FCFS(std::vector<Process>& processes);
std::vector<Process> parseInput(const std::string& input);

#endif // SCHEDULER_H
