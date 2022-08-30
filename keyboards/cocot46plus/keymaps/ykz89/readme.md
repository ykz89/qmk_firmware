# Cocot46plus `ykz89` keymap

This keymap is based on the `via` keymap of bastardkb/charybdis/3x5.

The Cocot46plus `ykz89` keymap is based on a COLEMAK layout with [home row mods](https://precondition.github.io/home-row-mods) and [Miryoku-inspired layers](https://github.com/manna-harbour/miryoku), and some features and changes specific to the Charybdis and then applied to the cocot46plus.

This keymap is created for an RP2040 and is not tested with AVR.
## Customizing the keymap

### Dynamic DPI scaling

Use the following keycodes to change the default DPI of 750:

-   `POINTER_DEFAULT_DPI_FORWARD`: increases the DPI with 250; decreases when shifted;
-   `POINTER_DEFAULT_DPI_REVERSE`: decreases the DPI with 250; increases when shifted.

There's a maximum of 4 possible values for the sniping mode DPI. 

Use the following keycodes to change the sniping mode DPI with a default of 400:

-   `POINTER_SNIPING_DPI_FORWARD`: increases the DPI with 100; decreases when shifted;
-   `POINTER_SNIPING_DPI_REVERSE`: decreases the DPI with 100; increases when shifted.

There's a maximum of 4 possible values for the sniping mode DPI.

The default DPI and increments can be configured in `cocot46plus.c`

### Drag-scroll

Use the `DRAGSCROLL_MODE` keycode to enable drag-scroll on hold. Use the `DRAGSCROLL_TOGGLE` keycode to enable/disable drag-scroll on key press.

### Sniping

Use the `SNIPING_MODE` keycode to enable sniping mode on hold. Use the `SNIPING_TOGGLE` keycode to enable/disable sniping mode on key press.


## Indicator LEDs

The indicator LEDs match the layer colors of the following layout:

## Layout

![Keymap layout (generated with keyboard-layout-editor.com)](https://i.imgur.com/uhOgWUe.png)
