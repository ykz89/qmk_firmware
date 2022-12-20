/* Copyright 2022 splitkb.com <support@splitkb.com>
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

// LAYOUT_stack was originally introduced by PR #9365,
// which added it on the keyboard-level `kyria.h`
// while creating the keymap `rmw`.
// This was probably a mistake, but due to backwards
// compatibility we should still provide a way to use it.
//
// If you wish to use LAYOUT_stack in your keymap, just add 
//     #include "kyria_layout_stack.h"
// at the top of your `keymap.c`.
//
// It is a legacy macro which we do not really want to maintain,
// so to avoid having to redefine it for every revision,
// let's just implement it to use the regular LAYOUT macro.
#define LAYOUT_stack(                               \
    L00, L01, L02, L03, L04, L05,                   \
    L12, L13, L14, L15, L16, L17,                   \
    L24, L25, L26, L27, L28, L29, L30, L31,         \
                   L40, L41, L42, L43, L44,         \
                                                    \
                  R06, R07, R08, R09, R10, R11,     \
                  R18, R19, R20, R21, R22, R23,     \
        R32, R33, R34, R35, R36, R37, R38, R39,     \
        R45, R46, R47, R48, R49                     \
) \
LAYOUT( \
    L00, L01, L02, L03, L04, L05,                     R06, R07, R08, R09, R10, R11, \
    L12, L13, L14, L15, L16, L17,                     R18, R19, R20, R21, R22, R23, \
    L24, L25, L26, L27, L28, L29, L30, L31, R32, R33, R34, R35, R36, R37, R38, R39, \
                   L40, L41, L42, L43, L44, R45, R46, R47, R48, R49 \
)
