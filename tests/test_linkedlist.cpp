/*
 * Test for Node and DoublyLinkedList
 * Author: Mio Osawa
 */

#include <iostream>
#include "../src/Task.h"
#include "../src/Node.h"
#include "../src/LinkedList.h"
using namespace std;

int main() {
    // ---- Step 1: Create list ----
    LinkedList<Task> taskList;

    // ---- Step 2: Add tasks ----
    Task t1("T001", "Write Report", 5, 24, "");
    Task t2("T002", "Research", 2, 48, "");
    Task t3("T003", "Review Notes", 4, 12, "T001");

    taskList.insertTask(t1);
    taskList.insertTask(t2);
    taskList.insertTask(t3);

    cout << "===== All Tasks After Insertion =====" << endl;
    taskList.displayAll();

    // ---- Step 3: Find specific task ----
    cout << "\n===== Finding Task: T002 =====" << endl;
    Node<Task>* found = taskList.findTask("T002");
    if (found)
        found->data.display();
    else
        cout << "Task not found.\n";

    // ---- Step 4: Delete a task ----
    cout << "\n===== Deleting Task: T001 =====" << endl;
    bool deleted = taskList.deleteTask("T001");
    cout << (deleted ? "Deleted successfully.\n" : "Task not found.\n");

    // ---- Step 5: Display list again ----
    cout << "\n===== Remaining Tasks =====" << endl;
    taskList.displayAll();

    // ---- Step 6: Clear list ----
    cout << "\n===== Clearing List =====" << endl;
    taskList.clear();
    cout << (taskList.isEmpty() ? "List is now empty.\n" : "Clear failed.\n");

    return 0;
}
/*
cd "/Users/miosawa/Documents/Langara/Fall 2025/CPSC2150/Assignments/100405763-Asgn1/tests"
g++ test_linkedlist.cpp ../src/Task.cpp -o test_linkedlist
./test_linkedlist
*/