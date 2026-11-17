#include "intergalactic_transmission.h"

#define WRONG_PARITY -1

static inline uint8_t get_high(uint8_t data, uint8_t bits);
static inline uint8_t get_low(uint8_t data, uint8_t bits);
static inline uint8_t add_partiy_bit(uint8_t data);
static inline uint8_t calculate_partiy_bit(uint8_t data);
static inline int check_partiy_bit(uint8_t data);

static inline uint8_t get_high(uint8_t data, uint8_t bits)
{
    return data >> (8-bits);
}

static inline uint8_t get_low(uint8_t data, uint8_t bits)
{
    return data & ((1U << bits) - 1);
}

static inline uint8_t add_partiy_bit(uint8_t data)
{
    return (data << 1) | calculate_partiy_bit(data);
}

static inline uint8_t calculate_partiy_bit(uint8_t data)
{
    return __builtin_popcount(data) % 2;
}

static inline int check_partiy_bit(uint8_t data)
{
    return get_low(data, 1) == calculate_partiy_bit(get_high(data, 7))
        ? 0
        : WRONG_PARITY;
}

int transmit_sequence(uint8_t *buffer, const uint8_t *message,
                      int message_length)
{
    if (!buffer || !message || message_length <= 0)
        return 0;

    // for each 7 bits become a byte, pads the last byte.
    int buffer_length = (message_length * 8 + 6) / 7;

    uint8_t residual = 0;
    uint8_t residual_length = 0;
    for (int i = 0; i < message_length; i += 1) {
        if (residual_length == 7) {
            *(buffer++) = add_partiy_bit(residual);
            residual_length = 0;
            residual = 0;
        }

        *(buffer++) = add_partiy_bit(
            (residual << (7-residual_length)) | get_high(message[i], 7-residual_length)
        );

        residual_length += 1;
        residual = get_low(message[i], residual_length);
    }

    *(buffer++) = add_partiy_bit(residual << (7-residual_length));

    return buffer_length;
}

int decode_message(uint8_t *buffer, const uint8_t *message, int message_length)
{
    if (!buffer || message_length < 0)
        return WRONG_PARITY;

    if (!message || message_length == 0)
        return 0;

    // each byte will become 7 bits data, then reform.
    int buffer_length = (message_length * 7) / 8;

    uint8_t residual = 0;
    uint8_t residual_length = 0;
    for (int i = 0; i < message_length; i += 1) {
        if (check_partiy_bit(message[i]) == WRONG_PARITY)
            return WRONG_PARITY;

        if (residual_length == 0) {
            residual = get_high(message[i], 7);
            residual_length = 7;
            continue;
        }

        *(buffer++) = (residual << (8-residual_length)) | get_high(message[i], 8-residual_length);

        residual_length -= 1;
        residual = get_low(message[i] >> 1, residual_length);
    }

    return buffer_length;
}
