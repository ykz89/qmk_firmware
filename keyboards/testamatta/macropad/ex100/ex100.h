#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "quantum.h"

#define LAYOUT( \
    k00, k01, k02, \
    k10, k11, k12, \
    k20 \
) \
{ \
    { k00, k01, k02 }, \
    { k10, k11, k12 }, \
    { k20 } \
}

#endif
