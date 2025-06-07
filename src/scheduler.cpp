#include <chrono>
#include <thread>
#include <future>

#include "scheduler.h"
#include "comm.h"

using namespace std::chrono_literals;

extern int create_udp_listener(int);

static Comm *comm = 0;

#define PORT 50000

int timer() {

    while (1) {
        std::this_thread::sleep_for(1000ms);
        fprintf(stderr, "*");
    }
    return 0;
}

int echo(const char *device) {
    uint8_t buf[128];
    int fd = comm->open(device);
    fprintf(stderr, "device %s fd %d\n", device, fd);

    while (1) {
        int len = comm->read(fd, buf, 128);
        if (len <= 0) {
            if (len == 0) {
                return -1;
            }
            
            fprintf(stderr, "sci read: %s\n", strerror(errno));
            return -2;
        }
        comm->write(fd, buf, len);
    }
    return 0;
}

static Scheduler scheduler;

void sci_app(void*);
void udp_app(void*);
void periodic_app(void*);

int main() {
    // Start the "hardware": the timer and two input listeners

    int sockfd = create_udp_listener(PORT);
    if (sockfd < 0) {
        return 1;
    }

    comm = new Comm(sockfd);

    std::future<int> t = std::async(std::launch::async, timer);
    std::future<int> c = std::async(std::launch::async, echo, "console");
    std::future<int> u = std::async(std::launch::async, echo, "udp");

#if 0
    // Start the tasks
    Task *sci_task = scheduler.create(sci_app);
    Task *udp_task = scheduler.create(udp_app);
    Task *periodic_task = scheduler.create(periodic_app);

    sci_task->start(sci_task);
    udp_task->start(udp_task);
    periodic_task->start(periodic_task);
#endif

    int rc = t.get();
    rc = c.get();
    rc = u.get();
    return 0;
}

void sci_app(void *t) {
    Task *task = (Task *) t;
    task->wait();
}

void udp_app(void *t) {
    Task *task = (Task *) t;
    task->wait();
}

void periodic_app(void *t) {
    Task *task = (Task *) t;
    task->wait();
}
