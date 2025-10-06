 /*
 * Name: Mio Osawa
 * Id: 100405763
 * Instructor: Bita Shadgar
 * Section: 002
 * 
 * Scheduler.cpp
 * Implements the Scheduler class for managing tasks with dependencies and priorities.
 * 
 */

#include "Scheduler.h"
#include <vector>

// =====================================================
// 1. Task Management
// =====================================================
void Scheduler::addTask(const Task& t) {
    taskList.insertTask(t);
}

void Scheduler::deleteTask(const string& taskID) {
    taskList.deleteTask(taskID);
}

void Scheduler::displayAllTasks() {
    TaskIterator it(taskList.getHead());

    while (it.hasNext()) {
        Task current = it.next();
        current.display();
    }
}


// =====================================================
// 2. Checking for Cyclic Dependencies
// =====================================================
bool Scheduler::hasCycleHelper(
    const string& taskID,
    unordered_set<string>& visited,
    unordered_set<string>& recursionStack,
    vector<string>& cyclePath)
{
    if (recursionStack.count(taskID)) {
        cyclePath.push_back(taskID);
        return true;
    }
    if (visited.count(taskID)) return false;

    visited.insert(taskID);
    recursionStack.insert(taskID);

    Node<Task>* node = taskList.findTask(taskID);
    if (node && !node->data.getDependency().empty()) {
        string dep = node->data.getDependency();
        if (hasCycleHelper(dep, visited, recursionStack, cyclePath)) {
            cyclePath.push_back(taskID);
            return true;
        }
    }

    recursionStack.erase(taskID);
    return false;
}

void Scheduler::checkCycles() {
    unordered_set<string> visited, recursionStack;
    Node<Task>* current = taskList.getHead();
    vector<string> cycle;

    while (current) {
        if (hasCycleHelper(current->data.getTaskID(), visited, recursionStack, cycle)) {
            cout << "Cycle detected involving tasks: ";
            for (auto& id : cycle) cout << id << " ";
            cout << endl;

            // remove least-priority (max numeric) task
            string toRemove;
            int maxPriority = -1;
            for (auto& id : cycle) {
                Node<Task>* node = taskList.findTask(id);
                if (node && node->data.getPriority() > maxPriority) {
                    maxPriority = node->data.getPriority();
                    toRemove = id;
                }
            }
            if (!toRemove.empty()) {
                cout << "Removing lowest priority task: " << toRemove << endl;
                taskList.deleteTask(toRemove);
            }
            return;
        }
        current = current->next;
    }

    cout << "No cyclic dependencies detected." << endl;
}

void Scheduler::removeLowestPriorityInCycle(const vector<string>& cyclePath) {
    string lowestTaskID;
    int maxPriority = -1;

    for (const string& id : cyclePath) {
        Node<Task>* node = taskList.findTask(id);
        if (node && node->data.getPriority() > maxPriority) {
            maxPriority = node->data.getPriority();
            lowestTaskID = id;
        }
    }

    if (!lowestTaskID.empty()) {
        cout << "Removing lowest-priority task: " << lowestTaskID
             << " (priority " << maxPriority << ")" << endl;
        taskList.deleteTask(lowestTaskID);
    }
}

// =====================================================
// 3. Scheduling Tasks
// =====================================================


void Scheduler::scheduleNext() {
    cout << "\n--- Scheduling Next Task ---\n";

    // ===== Step 1: Check and resolve cycles =====
    unordered_set<string> visited;
    unordered_set<string> recursionStack;
    Node<Task>* temp = taskList.getHead();
    bool cycleDetected = false;
    vector<string> cyclePath;

    while (temp) {
        if (hasCycleHelper(temp->data.getTaskID(), visited, recursionStack, cyclePath)) {
            cycleDetected = true;
            break;
        }
        temp = temp->next;
    }

    if (cycleDetected) {
        cout << "Cyclic dependency detected. Resolving...\n";
        cout << "Cycle involves tasks: ";
        for (auto& id : cyclePath) cout << id << " ";
        cout << endl;

        // remove lowest-priority task to break the cycle
        removeLowestPriorityInCycle(cyclePath);
        cout << "Cycle resolved. You may re-run scheduling.\n";
        return;
    }

    // ===== Step 2: Build readyQueue =====
    readyQueue.clear();

    Node<Task>* current = taskList.getHead();
    while (current) {
        string dep = current->data.getDependency();
        bool ready = false;

        if (dep.empty()) {
            ready = true;
        } else {
            // if dependency no longer exists (completed), task is ready
            Node<Task>* depNode = taskList.findTask(dep);
            if (!depNode) ready = true;
        }

        if (ready) {
            readyQueue.enqueue(current->data);
        }
        current = current->next;
    }

    if (readyQueue.isEmpty()) {
        cout << "No available tasks to schedule.\n";
        return;
    }

    // ===== Step 3: Schedule next available task =====
    Task nextTask = readyQueue.dequeue();
    cout << "Scheduling task:\n";
    nextTask.display();

    // mark as completed
    completedTasks.enqueue(nextTask);
    cout << "Task marked as completed.\n";

    // remove from main list
    taskList.deleteTask(nextTask.getTaskID());
}


// =====================================================
// 4. File I/O for Completed Tasks
// =====================================================
void Scheduler::saveCompletedTasks(const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open file for writing.\n";
        return;
    }

    cout << "\nSaving completed tasks to " << filename << " ...\n";
    TaskQueue temp = completedTasks;
    while (!temp.isEmpty()) {
        Task t = temp.dequeue();
        file << t.getTaskID() << "," << t.getDescription() << ","
             << t.getPriority() << "," << t.getDeadline() << ","
             << t.getDependency() << "\n";
    }
    file.close();
    cout << "Completed tasks saved.\n";
}

void Scheduler::loadTasks(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open file for reading.\n";
        return;
    }

    cout << "\nLoading tasks from " << filename << " ...\n";
    string id, desc, prioExpr, deadlineStr, dep;

    // temporary storage for tasks whose priority is an expression
    struct PendingExpr { string id; string desc; string expr; int deadline; string dep; };
    vector<PendingExpr> tempTasks;

    auto trim = [](const string& s) {
        size_t a = s.find_first_not_of(" \t\r\n");
        size_t b = s.find_last_not_of(" \t\r\n");
        if (a == string::npos) return string();
        return s.substr(a, b - a + 1);
    };

    while (getline(file, id, ',')) {
        getline(file, desc, ',');
        getline(file, prioExpr, ',');
        getline(file, deadlineStr, ',');
        getline(file, dep, ','); // may be empty
        file.ignore(numeric_limits<streamsize>::max(), '\n');

        int deadline = stoi(deadlineStr);

        string prioTrim = trim(prioExpr);
        bool isNumber = false;
        if (!prioTrim.empty()) {
            try {
                size_t idx = 0;
                stod(prioTrim, &idx);
                isNumber = (idx == prioTrim.size());
            } catch (...) {
                isNumber = false;
            }
        }

        if (isNumber) {
            int priorityValue = (int)stod(prioTrim);
            Task t(id, desc, priorityValue, deadline, dep);
            taskList.insertTask(t);
        } else {
            // store for later resolution
            tempTasks.push_back(PendingExpr{ id, desc, prioTrim, deadline, dep });
        }
    }
    file.close();

    // Resolve expression-based priorities now that numeric priorities are loaded
    for (const PendingExpr& p : tempTasks) {
        string expr = p.expr;
        Node<Task>* current = taskList.getHead();
        while (current) {
            string refID = "priority of " + current->data.getTaskID();
            size_t pos = string::npos;
            while ((pos = expr.find(refID)) != string::npos) {
                expr.replace(pos, refID.size(), to_string(current->data.getPriority()));
            }
            current = current->next;
        }

        string postfix = ExpressionEvaluator::infixToPostfix(expr);
        double val = ExpressionEvaluator::evaluatePostfix(postfix);
        Task newTask(p.id, p.desc, (int)val, p.deadline, p.dep);
        taskList.insertTask(newTask);
    }

    cout << "Tasks loaded successfully.\n";
}


// =====================================================
// 5. Finding Dependent Tasks
// =====================================================
void Scheduler::findDependentTasksRec(const string& taskID, unordered_set<string>& visited) {
    if (visited.count(taskID)) return;
    visited.insert(taskID);

    Node<Task>* current = taskList.getHead();
    while (current) {
        if (current->data.getDependency() == taskID) {
            string id = current->data.getTaskID();
            cout << "- " << id << " (" << current->data.getDescription() << ")\n";
            findDependentTasksRec(id, visited);
        }
        current = current->next;
    }
}

void Scheduler::findDependentTasks(const string& taskID) {
    unordered_set<string> visited;
    cout << "\nTasks that depend on [" << taskID << "]:\n";
    findDependentTasksRec(taskID, visited);
    if (visited.size() == 1)
        cout << "No tasks depend on " << taskID << ".\n";
}