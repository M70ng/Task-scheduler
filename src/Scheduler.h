/*
 * Name: Mio Osawa
 * Id: 100405763
 * Instructor: Bita Shadgar
 * Section: 002
 */

 /*
 
Core logic:

Priority queue (sorted/unsorted list) for active tasks.

Queue for completed tasks.

Stack to evaluate priority expressions.

Recursion for dependency checking and listing dependents.

Provides menu functions: add, delete, display, schedule next, check cycles, save/load tasks, exit.

*/

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Task.h"

using namespace std;

class Scheduler {
public:
    void addTask();
    void deleteTask();
    void displayTasks();
    void scheduleNext();
    void checkCycles();
    void saveToFile();
    void loadFromFile();
};
#endif // SCHEDULER_H 