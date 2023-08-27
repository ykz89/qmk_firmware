#ifndef EX100_H
#define EX100_H

#include "quantum.h"

void ex100_adc_setup(void);
uint16_t ex100_analogRead(uint32_t pin);

#define LAYOUT( \
    K00, K01, K02, \
    K10, K11, K12, \
    K21  \
) { \
    { K00, K01, K02 }, \
    { K10, K11, K12 }, \
    { K21 }  \
}

#endif
