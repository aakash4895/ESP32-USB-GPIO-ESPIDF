/**
 * @file uart_man.c
 * @author Aakash Singh
 * @brief UART management functions for ESP32 USB GPIO Controller
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025 Aakash Singh
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
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