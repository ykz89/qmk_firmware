# Quantum painter
For more information see [QMK docs](https://docs.qmk.fm/#/quantum_painter?id=quantum-painter).
1. ### Enable Quantum painter and set driver
    ```
    QUANTUM_PAINTER_ENABLE = yes
    QUANTUM_PAINTER_DRIVERS += gc9a01_spi
    ```
1. ### Convert image
    ```qmk painter-convert-graphics -f pal16 -i <filename> -d -o ./generated/```
    In this case I used a file "totoro.gif".

1. ### Include converted image in `rules.mk`
   `SRC += generated/totoro.qgf.c`

1. ### Render image or animation 
    ```
    #include "qp.h"
    #include "generated/totoro.qgf.h"
   
    static painter_device_t display;
    static painter_image_handle_t my_image;
    static deferred_token my_anim;
   
    void keyboard_post_init_kb(void) {
        display = qp_gc9a01_make_spi_device(240, 240, LCD_CS_PIN, LCD_DC_PIN, LCD_RST_PIN, 4, 0);         // Create the display
        qp_init(display, QP_ROTATION_0);   // Initialise the display
        qp_clear(display);
        my_image = qp_load_image_mem(gfx_totoro);
        //    qp_drawimage(display, 0, 0, my_image);
        my_anim = qp_animate(display, 0, 0, my_image);
    }
    ```
   
Use `qp_drawimage()` for a still image or `qp_animate()` for an animated image.
 
