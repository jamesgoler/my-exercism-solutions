#include "robot_simulator.h"

static const robot_position_t OFFSETS[] = {
    { .x = 0, .y = 1 },
    { .x = 1, .y = 0 },
    { .x = 0, .y = -1 },
    { .x = -1, .y = 0 },
};

robot_status_t robot_create(robot_direction_t direction, int x, int y) {
    return (robot_status_t) {
        .direction = direction,
        .position = (robot_position_t) {
            .x = x,
            .y = y,
        }
    };
}

void robot_move(robot_status_t *robot, const char *commands) {
    for (const char *c = commands; *c != '\0'; c += 1) {
        switch (*c) {
            case 'R':
                robot->direction = (robot->direction + 1) % DIRECTION_MAX;
                break;
            case 'L':
                robot->direction = ((robot->direction - 1) + DIRECTION_MAX) % DIRECTION_MAX;
                break;
            case 'A':
                robot->position.x += OFFSETS[robot->direction].x;
                robot->position.y += OFFSETS[robot->direction].y;
                break;
        }
    }
}
