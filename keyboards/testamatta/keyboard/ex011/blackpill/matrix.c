/*
 * Scan matrix
 * https://github.com/qmk/qmk_firmware/blob/master/docs/custom_matrix.md
 */

#include "quantum.h"
#include "wait.h"
#include "print.h"

// Optical keyboard does not need debounce
// #define DEBOUNCE 0

#ifndef WAIT_AFTER_COL_SELECT
#define WAIT_AFTER_COL_SELECT 100
#endif

#ifdef MATRIX_ROW_PINS
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif
#ifdef MATRIX_COL_PINS
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif

void matrix_init_custom(void) {
    // initialize column pins to be Output and set them LowasdfZqaz
    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        pin_t pin = col_pins[col];
        if (pin != NO_PIN) {
            ATOMIC_BLOCK_FORCEON {
                setPinOutput(pin);
                writePinLow(pin);
            }
        }
    }
    // initialize row pins to be Input
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        pin_t pin = row_pins[row];
        if (pin != NO_PIN) {
            ATOMIC_BLOCK_FORCEON {
#ifdef PT_INPUT_USE_PULLUP
                setPinInputHigh(pin);
#else
                setPinInput(pin);
#endif
            }
        }
    }
    //wait_ms(2000); // 追加！
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        ATOMIC_BLOCK_FORCEON {
            writePinHigh(pin);
        }
        return true;
    }
    return false;
}

static bool unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];
    if (pin != NO_PIN) {
        ATOMIC_BLOCK_FORCEON {
            writePinLow(pin);
        }
        return true;
    }
    return false;
}

__attribute__((weak)) void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {

    if (!select_col(current_col)) {
        dprintf("Error: failed to power on col %d\n", current_col);
        return;
    }

    wait_us(WAIT_AFTER_COL_SELECT);

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        if (row_pins[row_index] == NO_PIN) {
            continue;
        }
        // Check row pin state
        if (readPin(row_pins[row_index]) == 1) {
            // Pin HI, set col bit
            current_matrix[row_index] |= row_shifter;
        } else {
            // Pin LO, clear col bit
            current_matrix[row_index] &= ~row_shifter;
        }
    }

    unselect_col(current_col);

#ifndef WAIT_AFTER_COL_UNSELECT
    waitInputPinDelay();
#else
    wait_us(WAIT_AFTER_COL_UNSELECT);
#endif
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }
    bool changed = memcmp(current_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) {
        memcpy(current_matrix, curr_matrix, sizeof(curr_matrix));
    }

    return (uint8_t)changed;
}
