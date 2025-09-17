#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <string>
#include "Node.h"
#include "Task.h"
using namespace std;

class LinkedList {
private:
    Node<Task>* head;
    Node<Task>* tail;
    int size;

public:
    LinkedList();               
    ~LinkedList();              

    void insertTask(const Task& task);   
    bool deleteTask(const string& taskID); 
    Task* findTask(const string& taskID);

    bool isEmpty() const;
    int getSize() const;
    void clear();

    Node<Task>* getHead() const { return head; }
};

#endif // LINKEDLIST_H
