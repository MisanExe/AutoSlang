#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "../inc/uart.h"
#include "../inc/rtc.h"
#include "../inc/logger.h"
#include "../inc/spi.h"
#include <libopencm3/stm32/rcc.h>
#include <stdio.h>

static void rcc_setup(void)
{
	// set clock to run at 48Mhz
	rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
}
int main(void)
{
	rcc_setup();
	
	rcc_periph_clock_enable(RCC_GPIOA);

	gpio_set_mode(GPIOA,
	GPIO_MODE_OUTPUT_10_MHZ,
	GPIO_CNF_OUTPUT_PUSHPULL,
	GPIO7
	);
	uart_handle_t uart2_handle;
	UART_init(USART2, &uart2_handle);

	Rtc_init(0);
	Logger_init();
	Logger_log(INFO,"Initalized spi");
	//Spi_init();

	gpio_set(GPIOA, GPIO7);


	uint32_t previous = Rtc_getTime();
	while(1)
	{
		// for(int i = 0; i <1000000; i++)
		// {
		// 	__asm__("nop");
		// }
		
		//read using spi
		// uint8_t address = 0x55;
		// address |= (1U<<7);
		// spi_write(SPI1, address);
		uint8_t read = spi_read(SPI1);
		
		if( (Rtc_getTime() - previous) % 60 > 1 )
		{
			echo(&uart2_handle);

			char msg[100];
			if(read != 0)
			{
				//sprintf(msg, "Read from address %d: %d",address, read);
				UART_println(&uart2_handle, "Read ");
			}

			// update 
			previous = Rtc_getTime();
			read = 0;
			Logger_log(INFO,"End of main routine");
			
		}

	}
}
