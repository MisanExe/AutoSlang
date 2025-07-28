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

	gpio_set_mode(GPIOB,
	GPIO_MODE_OUTPUT_10_MHZ,
	GPIO_CNF_OUTPUT_PUSHPULL,
	GPIO7
	);

	uart_handle_t uart2_handle;
	UART_init(USART2, &uart2_handle);

	int state = 0;
	int address = 0;
	while(1)
	{
		char msg[250];
		memset(msg, '\0', sizeof(msg));
		for(int i = 0; i <1000000; i++)
		{
			__asm__("nop");
		}

		uint8_t buffer = 0;
		buffer = UART_read(&uart2_handle);
		if(buffer == '\r')
		{
			gpio_toggle(GPIOB, GPIO7);	
		}

		// switch(state)
		// {
		// 	case 0:
		// 		UART_println(&uart2_handle, "Enter command. e.g READ=<address> ");
		// 		UART_writeBytes(&uart2_handle, "COMMAND : ");
		// 		state = 1;
		// 		break;
		// 	case 1: // waiting to read spi from here
		// 		UART_readRecvData(&uart2_handle, msg);

		// 		sscanf(msg, "READ=%x", &address);
		// 		if(address > 0)
		// 		{
		// 			UART_println(&uart2_handle, msg);
		// 			state = 2;
		// 		}
		// 		break;
		// 	case 2: //write to specified address
		// 		spi_write(SPI1, address);
		// 		//wait to receive a message
		// 		int response = spi_read(SPI1);
		// 		if (response > 0 )
		// 		{
		// 			char temp[100];
		// 			sprintf(temp, "From address {%x}, received : %x", address, response);
		// 			UART_println(&uart2_handle, temp);
		// 			state =0;
		// 		}
		// 		break;

		// 	default:
		// 		break;
		// }

	}
}
