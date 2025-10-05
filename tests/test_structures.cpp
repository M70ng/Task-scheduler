/*
 * Test for Stack, Queue, and PriorityQueue
 * Author: Mio Osawa
 */

#include <iostream>
#include "../src/Task.h"
#include "../src/Node.h"
#include "../src/Stack.h"
#include "../src/PriorityQueue.h"
#include "../src/TaskQueue.h"   // ← Queue<T>（一般版）を使う場合のみ。TaskQueueならコメントアウト
using namespace std;

int main() {
    cout << "===== STACK TEST =====" << endl;
    Stack<Task> s;

    s.push(Task("T001", "Write Report", 5, 24, ""));
    s.push(Task("T002", "Research", 2, 48, ""));
    s.push(Task("T003", "Review Notes", 3, 12, ""));

    cout << "Top element: ";
    s.peek().display();

    cout << "\nPopping all elements:\n";
    while (!s.isEmpty()) {
        Task t = s.pop();
        t.display();
    }

    cout << "\n===== QUEUE TEST =====" << endl;
    TaskQueue q;  // または TaskQueue completedTasks;

    q.enqueue(Task("T001", "Write Report", 5, 24, ""));
    q.enqueue(Task("T002", "Research", 2, 48, ""));
    q.enqueue(Task("T003", "Review Notes", 3, 12, ""));

    cout << "Front element: ";
    q.peek().display();

    cout << "\nDequeuing all elements:\n";
    while (!q.isEmpty()) {
        Task t = q.dequeue();
        t.display();
    }

    cout << "\n===== PRIORITY QUEUE TEST =====" << endl;
    PriorityQueue<Task> pq;

    pq.enqueue(Task("T001", "Low priority", 5, 24, ""));
    pq.enqueue(Task("T002", "Medium priority", 3, 36, ""));
    pq.enqueue(Task("T003", "High priority", 1, 48, ""));
    pq.enqueue(Task("T004", "Another medium", 3, 12, ""));

    cout << "Front (highest priority): ";
    pq.peek().display();

    cout << "\nDequeuing all elements:\n";
    while (!pq.isEmpty()) {
        Task t = pq.dequeue();
        t.display();
    }

    cout << "\nAll structure tests completed successfully.\n";
    return 0;
}
