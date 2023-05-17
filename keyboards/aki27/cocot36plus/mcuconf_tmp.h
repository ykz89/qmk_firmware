#include_next "mcuconf.h"

/* OLED */

#ifdef OLED_ENABLE
#    undef RP_I2C_USE_I2C0
#    define RP_I2C_USE_I2C0 FALSE
#    undef RP_I2C_USE_I2C1
#    define RP_I2C_USE_I2C1 TRUE
#    define I2C_DRIVER I2CD2
#    define I2C1_SDA_PIN GP6
#    define I2C1_SCL_PIN GP7
#endif


/* Trackball */

#ifdef POINTING_DEVICE_ENABLE
#    undef RP_SPI_USE_SPI0
#    define RP_SPI_USE_SPI0 FALSE
#    undef RP_SPI_USE_SPI1
#    define RP_SPI_USE_SPI1 TRUE
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN GP2
#    define SPI_MISO_PIN GP4
#    define SPI_MOSI_PIN GP3
#endif

