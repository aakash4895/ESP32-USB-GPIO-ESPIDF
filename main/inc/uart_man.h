/**
 * @file uart_man.h
 * @author Aakash Singh
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef UART_MAN_H
#define UART_MAN_H

#include "esp_err.h"
#include "driver/uart.h"


#define UART_NUM UART_NUM_0
#define UART_TX_PIN GPIO_NUM_3
#define UART_RX_PIN GPIO_NUM_1
#define UART_BAUD_RATE 115200

#define UART_MAX_READ_LEN 256

void uartInit(void);

#endif // UART Manager