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
	UartInit(USART2, &uart2_handle);
	LoggerInit();

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


		switch(state)
		{
			case 0:
				UartPrintLn(&uart2_handle,"Enter command in terminal. e.g READ=<address>");
				UartPrint(&uart2_handle, "Command : ");
				state = 1;
				break;
			case 1: // Await response 
				echo(&uart2_handle);
				if(UartReadByte(&uart2_handle) == '\r')	
				{
					state = 2;
				}
				break;
			case 2:
				LoggerLogMsg(INFO, "Test works. Currently in state 2 of state machine");
				state = 0;
			default:
				LoggerLogMsg(WARNING, "State machine in uknown state");
		}
	}
}
