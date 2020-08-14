#include "stm8l10x.h"
#include "uart.h"

void UartInit() {
    UartDeinit();
    /* Tx/Rx baud rate = f MASTER / UART_DIV
    * 115200 = 2 * 10^6 / x
    * x = 17.36 = 0x11
    */
    USART->BRR2 = 0x01;
    USART->BRR1 = 0x01;
    USART->CR2 |= USART_CR2_TEN | USART_CR2_REN;
    USART->CR1 &= (uint8_t)(~USART_CR1_USARTD);

}

void UartDeinit() {
    USART->CR1 = USART_CR1_RESET_VALUE;
    USART->CR2 = USART_CR2_RESET_VALUE;
    USART->CR3 = USART_CR3_RESET_VALUE;
    USART->CR4 = USART_CR4_RESET_VALUE;


    USART->CR1 |= USART_CR1_USARTD;
}
