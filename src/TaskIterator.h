//  Node* current

// Node* head

#ifndef TASKITERATOR_H
#define TASKITERATOR_H

#include "Node.h"
#include "Task.h"

class TaskIterator {
private:
    Node<Task>* current;
    Node<Task>* start;

public:
    TaskIterator(Node<Task>* head);
    bool hasNext() const;
    Task* next();
    void reset();
};

#endif // TASKITERATOR_H