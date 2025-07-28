#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/usart.h>
#include "buffer.h"
#include <string.h>

#ifndef _UART_C
#define _UART_C

typedef enum 
{
    IDLE,       // Idle state
    TRANSMIT,   // Transmitting data
    RECEIVED,   // Received data

}uart_state_enum;

typedef enum
{
    UART1_INDEX,
    UART2_INDEX,
    UART3_INDEX,
}uart_index_enum;

typedef struct{
    uint32_t uart;             // Points to the uart port to be used
    uint32_t pTx;              // Points to the uart tx pin 
    uint32_t pRx;              // Points to the uart rx pin
    uart_state_enum state;     // Current state of the uart channel
    uart_index_enum uartIndex; // Index of selected uart
}uart_handle_t;


/*
*@brief
*@param 
*@return    
*/
void UartInit(uint32_t uart, uart_handle_t *handle);
/*
*@brief
*@param 
*@return    
*/
void UartWrite(uart_handle_t *handle, uint8_t data);
/*
*@brief
*@param 
*@return    
*/
void UartWriteBytes(uart_handle_t *handle, const char *data);
/*
*@brief
*@param 
*@return    
*/
void UartReceiveBytes(uart_handle_t *handle, char *data);
/*
*@brief
*@param 
*@return    
*/
void UartPrint(uart_handle_t *handle, const char *data);
/*
*@brief
*@param 
*@return    
*/
void UartPrintLn(uart_handle_t *handle, const char *data);
/*
*@brief
*@param 
*@return    
*/
uint8_t UartReadByte(uart_handle_t *handle);
/*
*@brief
*@param 
*@return    
*/
void echo(uart_handle_t *handle);


#endif