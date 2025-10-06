/*
 * Name: Mio Osawa
 * Id: 100405763
 * Instructor: Bita Shadgar
 * Section: 002
 * 
 * Scheduler.h
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "LinkedList.h"
#include "PriorityQueue.h"
#include "TaskQueue.h"
#include "Stack.h"
#include "Task.h"
#include "TaskIterator.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <unordered_set>
#include <vector>
#include "ExpressionEvaluator.h"
using namespace std;

class Scheduler {
public:
    void addTask(const Task& t);
    void deleteTask(const string& taskID);
    void displayAllTasks();
    void scheduleNext();
    void checkCycles();
    void saveCompletedTasks(const string& filename);
    void loadTasks(const string& filename);
    void findDependentTasksRec(const string& taskID, unordered_set<string>& printed);
    void findDependentTasks(const string& taskID);

private:
    LinkedList<Task> taskList;
    PriorityQueue<Task> readyQueue;
    TaskQueue completedTasks;

    // Recursive helper for cycle detection
    bool hasCycleHelper(const string& taskID,
                        unordered_set<string>& visited,
                        unordered_set<string>& recursionStack,
                        vector<string>& cyclePath);

    // Utility to remove the lowest-priority (numerically highest) task from a detected cycle
    void removeLowestPriorityInCycle(const vector<string>& cyclePath);
};

#endif // SCHEDULER_H