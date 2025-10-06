/*
 * Test for Scheduler class
 * Produces non-interactive checks and returns exit code 0 on success.
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>

#include "../src/Scheduler.h"
#include "../src/Task.h"

using namespace std;

string captureOutput(function<void()> fn) {
    streambuf* oldbuf = cout.rdbuf();
    stringstream ss;
    cout.rdbuf(ss.rdbuf());
    fn();
    cout.rdbuf(oldbuf);
    return ss.str();
}

bool contains(const string &s, const string &sub) {
    return s.find(sub) != string::npos;
}

int main() {
    Scheduler scheduler;

    // 1) Load tasks (run from repo root so data/ is relative)
    scheduler.loadTasks("data/tasks.txt");

    // 2) displayAllTasks should contain known task IDs
    string allOutput = captureOutput([&]() { scheduler.displayAllTasks(); });
    if (!contains(allOutput, "Task ID: T001") || !contains(allOutput, "Task ID: T002")) {
        cerr << "FAIL: load/display missing expected tasks.\n";
        return 1;
    }

    // 3) findDependentTasks for T001 should list at least T004
    string deps = captureOutput([&]() { scheduler.findDependentTasks("T001"); });
    if (!contains(deps, "T004")) {
        cerr << "FAIL: findDependentTasks did not list expected dependent T004.\n";
        cerr << deps << endl;
        return 1;
    }

    // 4) checkCycles should report no cycles for this file
    string cycles = captureOutput([&]() { scheduler.checkCycles(); });
    if (!contains(cycles, "No cyclic dependencies detected")) {
        cerr << "FAIL: unexpected cycle detection output:\n" << cycles << endl;
        return 1;
    }

    // 5) scheduleNext -> saveCompletedTasks to a test file -> ensure file contains one completed task id
    string schedOut = captureOutput([&]() { scheduler.scheduleNext(); });
    // Save completed tasks to test file
    string testFile = "data/test_completed.txt";
    scheduler.saveCompletedTasks(testFile);

    ifstream in(testFile);
    if (!in.is_open()) {
        cerr << "FAIL: could not open test completed file after save.\n";
        return 1;
    }
    string line;
    if (!getline(in, line)) {
        cerr << "FAIL: completed file is empty.\n";
        in.close();
        return 1;
    }
    in.close();

    // first token before comma is the completed task ID
    string completedID;
    {
        stringstream ls(line);
        getline(ls, completedID, ',');
    }
    if (completedID.empty()) {
        cerr << "FAIL: could not parse completed task id.\n";
        return 1;
    }

    // After scheduling, ensure the completedID is not present in the in-memory task list
    string after = captureOutput([&]() { scheduler.displayAllTasks(); });
    // Ensure 'Task ID: <completedID>' is not present (avoid matching dependency lines)
    string taskIdPattern = string("Task ID: ") + completedID;
    if (contains(after, taskIdPattern)) {
        cerr << "FAIL: completed task " << completedID << " still present in main list.\n";
        cerr << "Remaining tasks output:\n" << after << endl;
        return 1;
    }

    // 6) Test cycle detection with an artificial cycle
    Scheduler s2;
    Task a("A", "", 1, 0, "B");
    Task b("B", "", 1, 0, "A");
    s2.addTask(a);
    s2.addTask(b);
    string cycleOut = captureOutput([&]() { s2.checkCycles(); });
    if (!contains(cycleOut, "Cycle detected")) {
        cerr << "FAIL: expected cycle detection for s2 but got:\n" << cycleOut << endl;
        return 1;
    }

    cout << "All scheduler tests passed." << endl;
    return 0;
}
