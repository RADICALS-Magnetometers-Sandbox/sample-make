#include <chrono>
#include <thread>

#include "scheduler.h"
#include "comm.h"

extern int create_udp_listener(int);

static Comm *comm = 0;

#define PORT 50000

void timer() {
    using namespace std::chrono_literals;

    while (1) {
        std::this_thread::sleep_for(1000ms);
        fprintf(stderr, "*");
    }
}

void echo(const char *device) {
    uint8_t buf[128];
    int fd = comm->open(device);
    fprintf(stderr, "device %s fd %d\n", device, fd);

    while (1) {
        int len = comm->read(fd, buf, 128);
        if (len <= 0) {
            if (len == 0) {
                return;
            }
            
            fprintf(stderr, "sci read: %s\n", strerror(errno));
            return;
        }
        buf[len] = 0;
        comm->write(fd, buf, len);
    }
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

    std::thread sys_timer(timer);
    std::thread sci_driver(echo, "console");
    std::thread udp_driver(echo, "udp");
    //std::thread udp_driver(udp_input, sockfd);

#if 0
    // Start the tasks
    Task *sci_task = scheduler.create(sci_app);
    Task *udp_task = scheduler.create(udp_app);
    Task *periodic_task = scheduler.create(periodic_app);

    sci_task->start(sci_task);
    udp_task->start(udp_task);
    periodic_task->start(periodic_task);
#endif

    udp_driver.join();
    fprintf(stderr, "udp input closed\n");
    sci_driver.join();
    fprintf(stderr, "sci input closed\n");
    sys_timer.join();
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
