- Task Scheduler

How to build (macOS / zsh):

```bash
mkdir -p bin
clang++ -std=c++17 src/*.cpp -o bin/scheduler
```

Or with g++:

```bash
mkdir -p bin
g++ -std=c++17 src/*.cpp -o bin/scheduler
```

How to run:

```bash
./bin/scheduler
```

Quick steps to try it:
- Run program
- Press 8 and type `data/tasks.txt` to load sample tasks
- Press 3 to list tasks
- Press 4 to schedule the next task
- Press 7 to save completed tasks (give a file name like `completed.txt`)
- Press 9 to exit

Input file format (example line):
```
T001,Write Proposal,4,36,,,
```
Fields: TaskID, Description, Priority (or expression), Deadline, Dependency, ...

If something breaks:
- Make sure `clang++`/`g++` is installed (install Xcode command line tools if needed)
- Make `bin/scheduler` executable: `chmod +x bin/scheduler`

That's it.
