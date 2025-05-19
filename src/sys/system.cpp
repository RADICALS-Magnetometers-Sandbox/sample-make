#include "system.h"

System sys;

size_t System::strncpy(uint8_t *dst, const uint8_t *src, size_t len) {
    size_t i = 0;
    while (i<len) {
        if (!src[i]) {
            dst[i] = 0;
            break;
        }
        dst[i] = src[i];
        ++i;
    }
    return i;
}
