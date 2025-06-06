#pragma once

#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

const size_t MAX_DEVICES = 3;

class Device {
public:
    Device(const char *name) : name(name) {}

    const char *name;

    virtual int read(uint8_t *buf, int len) = 0;
    virtual int write(uint8_t *buf, int len) = 0;
};

class TtyDevice : public Device {
    int rfd, wfd;

public:
    TtyDevice(const char *name) : Device(name) {
        if (strcmp(name, "console")) {
            rfd = STDIN_FILENO;
            wfd = STDOUT_FILENO;
        }
    }

    virtual int read(uint8_t *buf, int buflen) {
        int count = ::read(rfd, buf, buflen);
        if (count == -1) count = -errno;
        return count;
    }

    virtual int write(uint8_t *buf, int buflen) {
        int count = ::write(wfd, buf, buflen);
        if (count == -1) count = -errno;
        return count;
    }
};

class UdpDevice : public Device {
    int sock;
    struct sockaddr_in cliaddr;
    socklen_t clilen;

public:
    UdpDevice(int sockfd) : Device("udp") {
        sock = sockfd;
        memset(&cliaddr, 0, sizeof(cliaddr));
    }

    virtual int read(uint8_t *buf, int buflen) {
        clilen = sizeof(cliaddr);
        ssize_t count = recvfrom(sock, buf, buflen, MSG_WAITALL,
                                 (struct sockaddr *) &cliaddr, &clilen);
        if (count == -1) count = -errno;
        return count;
    }

    virtual int write(uint8_t *buf, int len) {
        ssize_t count = sendto(sock, buf, count, 0,
                       (const sockaddr *) &cliaddr, clilen);
        if (count == -1) count = -errno;
        return count;
    }
};

class Comm {
    Device* devices[MAX_DEVICES];

public:
    Comm(int sockfd) {
        devices[0] = new TtyDevice("console");
        devices[1] = new UdpDevice(sockfd);
        devices[2] = 0;
    }

    int open(const char *name) {
        for (int i=0; devices[i]; i++) {
            if (strcmp(devices[i]->name, name) == 0) {
                return i;
            }
        }
        return -1;
    }

    int read(int fd, uint8_t *buf, int len) {
        return devices[fd]->read(buf, len);
    }

    int write(int fd, uint8_t *buf, int len) {
        return devices[fd]->write(buf, len);
    }
};
