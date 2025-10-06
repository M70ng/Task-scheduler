#include <iostream>
#include <string>
#include <limits>
#include "Scheduler.h"
#include "Task.h"
using namespace std;

int main() {
    Scheduler scheduler;
    int choice;

    while (true) {
        cout << "\n===== TASK SCHEDULER MENU =====\n"
             << "1) Add a task\n"
             << "2) Delete a task by ID\n"
             << "3) Display all tasks\n"
             << "4) Schedule next task\n"
             << "5) Check for cyclic dependencies\n"
             << "6) Show dependency list\n"
             << "7) Save completed tasks\n"
             << "8) Load tasks\n"
             << "9) Exit\n"
             << "Select: ";

        if (!(cin >> choice)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1–9.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string id, desc, dep;
            int prio, deadline;

            cout << "Task ID: ";
            getline(cin, id);
            cout << "Description: ";
            getline(cin, desc);

            cout << "Priority (1-10): ";
            if (!(cin >> prio) || prio < 1 || prio > 10) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid priority. Must be 1–10.\n";
                continue;
            }

            cout << "Deadline (hours): ";
            if (!(cin >> deadline) || deadline <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid deadline. Must be a positive number.\n";
                continue;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Dependency Task ID (empty for none): ";
            getline(cin, dep);

            Task t(id, desc, prio, deadline, dep);
            scheduler.addTask(t);
            cout << "Task added.\n";
        }
        else if (choice == 2) {
            string id;
            cout << "Task ID to delete: ";
            getline(cin, id);
            scheduler.deleteTask(id);
        }
        else if (choice == 3) {
            scheduler.displayAllTasks();
        }
        else if (choice == 4) {
            scheduler.scheduleNext();
        }
        else if (choice == 5) {
            scheduler.checkCycles();
        }
        else if (choice == 6) {
            string id;
            cout << "Base Task ID: ";
            getline(cin, id);
            scheduler.findDependentTasks(id);
        }
        else if (choice == 7) {
            string path;
            cout << "Output file path: ";
            getline(cin, path);
            scheduler.saveCompletedTasks(path);
        }
        else if (choice == 8) {
            string path;
            cout << "Input file path: ";
            getline(cin, path);
            scheduler.loadTasks(path);
        }
        else if (choice == 9) {
            cout << "Bye.\n";
            break;
        }
        else {
            cout << "Invalid choice. Please select 1–9.\n";
        }
    }

    return 0;
}
