#include "dsp.h"

extern "C" {
    #include "hal.h"
}

static DSP dsp;
static const size_t BUF_LEN = 128;

int main (int argc, char **argv) {
    uint8_t buf[BUF_LEN];

    size_t len = dsp.ingress(buf, BUF_LEN);
    dsp.uppercase(buf, len);

    hal_puts((const char *) buf);
    return 0;
}
