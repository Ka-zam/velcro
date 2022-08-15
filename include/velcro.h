#ifndef INCLUDED_VELCRO_H
#define INCLUDED_VELCRO_H

#include <stdint.h>

uint32_t modes_lut(const uint8_t *msg, const uint8_t bits);
uint32_t modes_xor_112(const uint8_t *msg);

#endif // INCLUDED_VELCRO_H
