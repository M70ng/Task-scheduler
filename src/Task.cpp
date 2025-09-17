/*
 * Name: Mio Osawa
 * Id: 100405763
 * Instructor: Bita Shadgar
 * Section: 002
 */

#include "Task.h"
using namespace std;

Task::Task() {
    taskID = "";
    description = "";
    priority = 10; // Default to lowest priority
    deadline = 0;  // No deadline
    dependency = "";
}

Task::Task(string tID, string desc, int prio, int dead, string dep) {
    taskID = tID;
    description = desc;
    priority = prio;
    deadline = dead;
    dependency = dep;
}

string Task::getTaskID() const {
   return taskID;
}


string Task::getDescription() const {
    return description;
}

int Task::getPriority() const {
    return priority;
}

int Task::getDeadline() const {
    return deadline;
}

string Task::getDependency() const {
    return dependency;
}

void Task::setTaskID(string tID) {
    taskID = tID;
}
void Task::setDescription(string desc) {
    description = desc;
}
void Task::setPriority(int prio) {
    priority = prio;
}

void Task::setDeadline(int dead) {
    deadline = dead;
}

void Task::setDependency(string dep) {
    dependency = dep;
}

void Task::display() const {
    cout << "Task ID: " << taskID << endl;
    cout << "Description: " << description << endl;
    cout << "Priority: " << priority << endl;
    cout << "Deadline: " << deadline << endl;
    cout << "Dependency: " << (dependency.empty() ? "None" : dependency) << endl;
}
