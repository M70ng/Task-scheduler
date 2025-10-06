/*
 * Name: Mio Osawa
 * Id: 100405763
 * Instructor: Bita Shadgar
 * Section: 002
 */

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "LinkedList.h"
#include "PriorityQueue.h"
#include "TaskQueue.h"
#include "Stack.h"
#include "Task.h"
#include <iostream>
#include <fstream>

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
private:
    LinkedList<Task> taskList;
    PriorityQueue<Task> readyQueue;
    TaskQueue completedTasks;

};
#endif // SCHEDULER_H 