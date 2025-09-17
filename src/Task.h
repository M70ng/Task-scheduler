/*
 * Name: Mio Osawa
 * Id: 100405763
 * Instructor: Bita Shadgar
 * Section: 002
 */

#ifndef TASK_H
#define TASK_H

#include <string>
#include <iostream> 

using namespace std;

class Task {
private:
    string taskID;
    string description;
    int priority; // 1 (highest) to 10 (lowest)
    int deadline;
    string dependency; // taskID of the task that must be completed before this one
public:
    Task();
    Task(string tID, string desc, int prio, int dead, string dep);
    string getTaskID() const;
    string getDescription() const;
    int getPriority() const;
    int getDeadline() const;
    string getDependency() const;
    void setTaskID(string tID);
    void setDescription(string desc);
    void setPriority(int prio);
    void setDeadline(int dead);
    void setDependency(string dep);
    void display() const;
};
#endif // TASK_H