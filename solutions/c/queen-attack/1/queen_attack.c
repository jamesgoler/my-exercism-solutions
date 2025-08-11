#include "queen_attack.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

const uint8_t CHESSBOARD_LEN = 8;

static inline bool is_valid(position_t queen);

static inline bool is_valid(position_t queen) {
    return queen.row < CHESSBOARD_LEN && queen.column < CHESSBOARD_LEN;
}


attack_status_t can_attack(position_t queen_1, position_t queen_2) {
    if (!is_valid(queen_1) ||
        !is_valid(queen_2) ||
        (queen_1.row == queen_2.row && queen_1.column == queen_2.column))
    {
        return INVALID_POSITION;
    }
    if (queen_1.row == queen_2.row ||
        queen_1.column == queen_2.column ||
        abs(queen_1.row - queen_2.row) == abs(queen_1.column - queen_2.column))
    {    
        return CAN_ATTACK;
    }
    return CAN_NOT_ATTACK;
}


