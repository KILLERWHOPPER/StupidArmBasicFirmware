#ifndef ENUMS_H
#define ENUMS_H
#include "A4988.h"

enum Direction {Left, Right, Up, Down};
struct moving_info{
    A4988 stepper;
    int preset_cycles;
};

#endif