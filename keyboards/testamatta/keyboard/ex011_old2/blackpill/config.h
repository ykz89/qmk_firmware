// Copyright 2023 hide-key (@hide-key)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* PT requires time to 'rise' after IR has been powered on. Read the GPIO input
 * pin only after PT voltage has stabilized. */
#define WAIT_AFTER_COL_SELECT 76
/* PT requires time to 'fall' after IR has been switched off. Wait until
 * voltage across PT has stabilized. Otherwise scanning of next column will be
 * affected. */
#define WAIT_AFTER_COL_UNSELECT 110

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 0

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// #define ENCODER_DIRECTION_FLIP
