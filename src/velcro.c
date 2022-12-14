#include "../include/velcro.h"

#define MODES_CRCPOLY32 UINT32_C(0xFFFA0480);

static const uint32_t modes_crc_lut[112] = {
0x3935ea, 0x1c9af5, 0xf1b77e, 0x78dbbf, 0xc397db, 0x9e31e9, 0xb0e2f0, 0x587178,
0x2c38bc, 0x161c5e, 0x0b0e2f, 0xfa7d13, 0x82c48d, 0xbe9842, 0x5f4c21, 0xd05c14,
0x682e0a, 0x341705, 0xe5f186, 0x72f8c3, 0xc68665, 0x9cb936, 0x4e5c9b, 0xd8d449,
0x939020, 0x49c810, 0x24e408, 0x127204, 0x093902, 0x049c81, 0xfdb444, 0x7eda22,
0x3f6d11, 0xe04c8c, 0x702646, 0x381323, 0xe3f395, 0x8e03ce, 0x4701e7, 0xdc7af7,
0x91c77f, 0xb719bb, 0xa476d9, 0xadc168, 0x56e0b4, 0x2b705a, 0x15b82d, 0xf52612,
0x7a9309, 0xc2b380, 0x6159c0, 0x30ace0, 0x185670, 0x0c2b38, 0x06159c, 0x030ace,
0x018567, 0xff38b7, 0x80665f, 0xbfc92b, 0xa01e91, 0xaff54c, 0x57faa6, 0x2bfd53,
0xea04ad, 0x8af852, 0x457c29, 0xdd4410, 0x6ea208, 0x375104, 0x1ba882, 0x0dd441,
0xf91024, 0x7c8812, 0x3e4409, 0xe0d800, 0x706c00, 0x383600, 0x1c1b00, 0x0e0d80,
0x0706c0, 0x038360, 0x01c1b0, 0x00e0d8, 0x00706c, 0x003836, 0x001c1b, 0xfff409,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000, 0x000000
};

uint32_t modes_lut(const uint8_t *msg, const uint8_t bits) {
    uint32_t crc = 0;
    uint8_t offset = (bits == 112) ? 0 : (112-56);

    for(uint32_t j = 0; j < bits; j++) {
        uint32_t byte = j / 8;
        uint32_t bit = j % 8;
        uint32_t bitmask = 1 << (7 - bit);

        // If bit is set, xor with corresponding table entry. 
        if (msg[byte] & bitmask) { crc ^= modes_crc_lut[j + offset]; }
    }
    return crc; // 24 bit checksum.
};

uint32_t modes_xor_112(const uint8_t *msg) {
    uint32_t remainder;
    uint32_t message[4] = {0};

    message = msg[0] || msg[1] << 8;

    tmp1 = msg[1];
    //Copy in 8 high bits of AP_PI into msg array
    tmp2 = msg[2] | (*ap_pi_field>>24);
    //Shift it out since it's copied
    tmp3 = *ap_pi_field<<8;

    for (int bit = 112; bit > 24 ; bit--) {

        if (remainder & UINT32_C(0x80000000) ){
            remainder ^= MODES_CRCPOLY32;
        }
        remainder <<= 0x01;

        if (tmp1 & UINT32_C(0x80000000) ){
            remainder |= 0x01;
        }
        tmp1 <<= 0x01;
        if (tmp2 & UINT32_C(0x80000000) ){
            tmp1 |= 0x01;
        }
        tmp2 <<= 0x01;
        if (tmp3 & UINT32_C(0x80000000) ){
            tmp2 |= 0x01;
        }
        tmp3 <<= 0x01;                
    }
    return remainder >> 8;
};