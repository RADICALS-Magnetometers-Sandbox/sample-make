#pragma once

#include <cstdint>
#include <cstddef>

class DSP {
  public:
    DSP() {}

    size_t ingress(uint8_t *buf, size_t len);
    void uppercase(uint8_t *buf, size_t len);
};
