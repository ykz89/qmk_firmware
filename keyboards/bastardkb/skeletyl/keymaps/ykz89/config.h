/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/**
 * Configure the global tapping term (default: 200ms).
 * If you have a lot of accidental mod activations, crank up the tapping term.
 *
 * See docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-term
 */
#ifndef TAPPING_TERM
#    define TAPPING_TERM 250
#endif // TAPPING_TERM

/**
 * Enable rapid switch from tap to hold.  Disable auto-repeat when pressing key
 * twice, except for one-shot keys.
 *
 * See docs.qmk.fm/using-qmk/software-features/tap_hold#tapping-force-hold
 */
#define TAPPING_FORCE_HOLD

/*
 * Tap-or-Hold decision modes.
 *
 * Note that the following flags behave differently when combined (ie. when 2 or
 * more are enabled).
 *
 * See bit.ly/tap-or-hold for a visual explanation of the following tap-or-hold
 * decision modes.
 */

/**
 * Faster tap-hold trigger.
 *
 * Without `PERMISSIVE_HOLD`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 e🠕 Mod(a)🠕 ➞ ae
 * With `PERMISSIVE_HOLD`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 e🠕 Mod(a)🠕 ➞ Mod+e
 *
 * See docs.qmk.fm/using-qmk/software-features/tap_hold#permissive-hold
 */
#define PERMISSIVE_HOLD

/**
 * Prevent normal rollover on alphas from accidentally triggering mods.
 *
 * Ignores key presses that interrupt a mod-tap.  Must-have for Home Row mod.
 *
 * Without `IGNORE_MOD_TAP_INTERRUPT`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 Mod(a)🠕 e🠕 ➞ Mod+e
 * With `IGNORE_MOD_TAP_INTERRUPT`, within `TAPPING_TERM`:
 *   Mod(a)🠗 e🠗 Mod(a)🠕 e🠕 ➞ ae
 *
 * See docs.qmk.fm/using-qmk/software-features/tap_hold#ignore-mod-tap-interrupt
 */
#define IGNORE_MOD_TAP_INTERRUPT
//#define RETRO_TAPPING
#define AUTO_SHIFT_TIMEOUT TAPPING_TERM
#define AUTO_SHIFT_NO_SETUP

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define SPLINKY_BETA_PINOUT
