#include "keyboard.h"

void matrix_init_kb(void) {
    // Keyboard start-up code goes here
    // Runs once when the firmware starts up
    // matrix_init_user();
}

void matrix_scan_kb(void) {
    // Keyboard matrix scan code goes here
    // Runs frequently to update the matrix, tap dances, ...
    // matrix_scan_user();
}

void _board_dfu_dbl_tap(void) {
    // 必要ならばここに実際のダブルタップ機能をサポートするコードを追加します。
    // 現在はダミーの実装です。
}
