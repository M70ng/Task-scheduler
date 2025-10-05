#ifndef TASKITERATOR_H
#define TASKITERATOR_H

#include <iostream>
#include "Node.h"
#include "Task.h"
using namespace std;

class TaskIterator {
private:
    Node<Task>* current;
    Node<Task>* start;

public:
    TaskIterator(Node<Task>* head);
    bool hasNext() const;
    Task next();
    void reset();
    bool isEnd() const; 
};

TaskIterator::TaskIterator(Node<Task>* head) : current(head), start(head) {}

bool TaskIterator::hasNext() const {
    return current != nullptr;
}

Task TaskIterator::next() {
    if (!current) {
        cerr << "Iterator error: no more elements.\n";
        return Task();
    }
    Task data = current->data;
    current = current->next;
    return data;
}

void TaskIterator::reset() {
    current = start;
}

bool TaskIterator::isEnd() const {
    return current == nullptr;
}

#endif // TASKITERATOR_H