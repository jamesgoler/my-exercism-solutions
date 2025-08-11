#include "variable_length_quantity.h"

static inline int encode_u32(uint32_t integer, uint8_t *output);
static inline int decode_u32(const uint8_t *bytes, const uint8_t *end, uint32_t *output);

static inline int encode_u32(uint32_t integer, uint8_t *output) {
    int bits = 32 - __builtin_clz(integer);
    int count = (bits + 6) / 7;
    if (count == 0) {
        count += 1;
    }
    for (int i = count - 1; i >= 0; i -= 1) {
        uint8_t f7b = integer & 0x7f;
        integer >>= 7;
        output[i] = f7b | 0x80;
    }
    output[count-1] &= 0x7f;
    return count;
}

static inline int decode_u32(const uint8_t *bytes, const uint8_t *end, uint32_t *output) {
    uint32_t result = 0;
    const uint8_t *bptr = bytes;
    while ((*bptr & 0x80) != 0) {
        if (bptr == end) {
            return -1;
        }
        result <<= 7;
        result += *bptr & 0x7f;
        bptr += 1;
    }
    result <<=7;
    result += *bptr;
    *output = result;
    return bptr - bytes + 1;
}

int encode(const uint32_t *integers, size_t integers_len, uint8_t *output) {
    uint8_t *optr = output;
    for (size_t i = 0; i < integers_len; i += 1) {
        optr += encode_u32(integers[i], optr); 
    }
    return optr - output;
}

int decode(const uint8_t *bytes, size_t buffer_len, uint32_t *output) {
    int count = 0;
    const uint8_t *end = bytes + buffer_len;
    while (bytes < end) {
        int byte_count = decode_u32(bytes, end, output++);
        if (byte_count < 0) {
            return -1;
        }
        bytes += byte_count;
        count += 1;
    }
    return count;
}
