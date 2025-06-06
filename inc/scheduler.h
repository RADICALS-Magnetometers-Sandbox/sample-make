#pragma once

enum TaskState {
    TASK_INIT = 0,
    TASK_READY = 1,
    TASK_WAIT = 2,
    TASK_PERIODIC = 4,
};
    
typedef void (*TaskFunc) (void*);

class Scheduler;

class Task {
    size_t tid;
    int state;
    TaskFunc func;
    void *funcarg;
    Scheduler *scheduler;

 public:
    Task(int id, TaskFunc f, Scheduler *s) : tid(id), func(f), scheduler(s) {
        state = TASK_INIT;
    } 

    void start(void *arg) {
        funcarg = arg;
        state = TASK_READY;
    }
    void start_periodic(void *arg) {
        funcarg = arg;
        state = TASK_READY | TASK_PERIODIC;
    }

    void wait() { state = TASK_WAIT; }
    void notify() { state = TASK_READY; }
};

const size_t MAX_TASKS = 4;

class Scheduler {
    Task *tasks[MAX_TASKS];

 public:
    Scheduler() { tasks[0] = 0; }

    Task* create(TaskFunc f) {
        for (int i=0; i<MAX_TASKS; i++) {
            if (!tasks[i]) {
                tasks[i] = new Task(i, f, this);
                return tasks[i];
            }
        }
        return 0;
    }
};

                    
        
