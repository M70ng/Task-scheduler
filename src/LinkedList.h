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
    LinkedList();               // コンストラクタ
    ~LinkedList();              // デストラクタ

    void insertTask(const Task& task);   // タスク追加
    bool deleteTask(const string& taskID); // タスク削除
    Task* findTask(const string& taskID);  // タスク検索

    bool isEmpty() const;
    int getSize() const;
    void clear();
};

#endif // LINKEDLIST_H
