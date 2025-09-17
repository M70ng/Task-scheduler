
#include <iostream>
#include "Scheduler.h"

using namespace std;

void showMenu()
{
    cout << "Menu:\n";
    cout << "1. Add Task\n";
    cout << "2. Delete Task\n";
    cout << "3. Display Tasks\n";
    cout << "4. Schedule Next Task\n";
    cout << "5. Check Cycles\n";
    cout << "6. Save Tasks to File\n";
    cout << "7. Load Tasks from File\n";
    cout << "8. Exit\n";
    cout << "Enter Option: ";
}

int main()
{
    Scheduler scheduler;
    int choice;
    while (true)
    {
        showMenu();
        cin >> choice;
        switch (choice)
        {
            case 1: scheduler.addTask(); break;
            case 2: scheduler.deleteTask(); break;
            case 3: scheduler.displayTasks(); break;
            case 4: scheduler.scheduleNext(); break;
            case 5: scheduler.checkCycles(); break;
            case 6: scheduler.saveToFile(); break;
            case 7: scheduler.loadFromFile(); break;
            case 8: cout << "Exiting...\n"; return 0;
        default:
            break;
        }
    }
    return 0;
}