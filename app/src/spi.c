#include "../inc/spi.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

// to-do : make code that uses any
// available spi

// Using only spi1 for now
// PA4 : NSS
// PA5 : SCK
// PA6 : MISO
// PA7 : MOSI

void Spi_init(void)
{
    /////////////////////
    //// GPIO settings
    /////////////////////

    // enable Gpio pins to be used
    rcc_periph_clock_enable(RCC_GPIOA);
    // Set NSS, SCK and MISO as af-outputs
    gpio_set_mode(GPIOA, GPIO_MODE_OUTPUT_50_MHZ, GPIO_CNF_OUTPUT_ALTFN_PUSHPULL, GPIO4 | GPIO5 | GPIO7);
    // Set MISO as af-floating-input
    gpio_set_mode(GPIOA, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, GPIO6);

    /////////////////////
    //// SPI settings
    /////////////////////

    // enable spi1 rcc clock
    rcc_periph_clock_enable(RCC_SPI1);
    // use MSB first
    spi_init_master(SPI1, SPI_CR1_BAUDRATE_FPCLK_DIV_128,
                    SPI_CR1_CPOL_CLK_TO_0_WHEN_IDLE,
                    SPI_CR1_CPHA_CLK_TRANSITION_1,
                    SPI_CR1_DFF_8BIT,
                    SPI_CR1_MSBFIRST);

    
}
