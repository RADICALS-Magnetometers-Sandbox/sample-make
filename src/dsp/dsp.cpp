#include <ctype.h>

#include "dsp.h"
#include "system.h"

size_t DSP::ingress(uint8_t *buf, size_t len) {
    const uint8_t *data = (const uint8_t *) &"hello world";
    return sys.strncpy(buf, data, len);
}

void DSP::uppercase(uint8_t *buf, size_t len) {
    for (size_t i=0; i<len; i++) {
        buf[i] = toupper(buf[i]);
    }
}
