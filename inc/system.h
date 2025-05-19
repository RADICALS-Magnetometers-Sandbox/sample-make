#pragma once

#include <cstdint>
#include <cstddef>

class System {
 public:
    System() {}

    size_t strncpy(uint8_t *dst, const uint8_t *src, size_t len);
};

extern System sys;
