/**
 * @file uart_man.c
 * @author Aakash Singh
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "uart_man.h"
#include "gpio_man.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

/**
 * @brief Initialize UART operations
 * 
 */
void uartInit(void)
{
    // Configure UART parameters
    uart_config_t uart_config = {
        .baud_rate = UART_BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    
    // Install UART driver
    uart_driver_install(UART_NUM, UART_MAX_READ_LEN, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
}