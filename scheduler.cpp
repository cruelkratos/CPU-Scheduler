#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int waitingTime;
    int turnAroundTime;
};

std::vector<Process> parseInput(const std::string& input) {
    std::vector<Process> processes;
    std::stringstream ss(input);
    std::string processString;

    while (std::getline(ss, processString, ';')) {
        std::stringstream ps(processString);
        std::string token;
        Process process;

        std::getline(ps, token, ',');
        process.id = std::stoi(token);
        std::getline(ps, token, ',');
        process.arrivalTime = std::stoi(token);
        std::getline(ps, token, ',');
        process.burstTime = std::stoi(token);
        std::getline(ps, token, ',');
        process.priority = std::stoi(token);

        processes.push_back(process);
    }

    return processes;
}

void FCFS(std::vector<Process>& processes) {
    int n = processes.size();
    int currentTime = 0;

    for (int i = 0; i < n; ++i) {
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnAroundTime - processes[i].burstTime;

        currentTime += processes[i].burstTime;
    }
}

void roundRobin(std::vector<Process>& processes, int timeQuantum) {
    std::queue<Process> readyQueue;
    int currentTime = 0;
    int remainingTime[processes.size()];

    for (size_t i = 0; i < processes.size(); ++i) {
        remainingTime[i] = processes[i].burstTime;
    }

    int index = 0;
    while (true) {
        bool done = true;

        for (size_t i = 0; i < processes.size(); ++i) {
            if (remainingTime[i] > 0) {
                done = false;

                if (remainingTime[i] > timeQuantum) {
                    currentTime += timeQuantum;
                    remainingTime[i] -= timeQuantum;
                } else {
                    currentTime += remainingTime[i];
                    processes[i].completionTime = currentTime;
                    remainingTime[i] = 0;
                }
            }
        }

        if (done)
            break;
    }
}

void shortestJobFirst(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.burstTime < b.burstTime;
    });

    int currentTime = 0;
    for (size_t i = 0; i < processes.size(); ++i) {
        processes[i].waitingTime = currentTime;
        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
    }
}

void priorityScheduling(std::vector<Process>& processes) {
    std::sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.priority < b.priority;
    });

    int currentTime = 0;
    for (size_t i = 0; i < processes.size(); ++i) {
        processes[i].waitingTime = currentTime;
        currentTime += processes[i].burstTime;
        processes[i].completionTime = currentTime;
        processes[i].turnAroundTime = processes[i].completionTime - processes[i].arrivalTime;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "Usage: scheduler.exe <algorithm> <input>" << std::endl;
        return 1;
    }

    std::string algorithm = argv[1];
    std::string input = argv[2];

    std::vector<Process> processes = parseInput(input);

    if (algorithm == "FCFS") {
        FCFS(processes);
    } else if (algorithm == "RR") {
        roundRobin(processes, 2);
    } else if (algorithm == "SJF") {
        shortestJobFirst(processes);
    } else if (algorithm == "Priority") {
        priorityScheduling(processes);
    } else {
        std::cerr << "Invalid algorithm choice\n";
        return 1;
    }

    std::cout << "[";
    for (size_t i = 0; i < processes.size(); ++i) {
        std::cout << "{"
                  << "\"id\":" << processes[i].id << ","
                  << "\"arrivalTime\":" << processes[i].arrivalTime << ","
                  << "\"burstTime\":" << processes[i].burstTime << ","
                  << "\"priority\":" << processes[i].priority << ","
                  << "\"completionTime\":" << processes[i].completionTime << ","
                  << "\"waitingTime\":" << processes[i].waitingTime << ","
                  << "\"turnAroundTime\":" << processes[i].turnAroundTime
                  << "}";
        if (i < processes.size() - 1) {
            std::cout << ",";
        }
    }
    std::cout << "]";
    std::cout.flush();
    return 0;
}
