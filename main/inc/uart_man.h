/**
 * @file uart_man.h
 * @author Aakash Singh
/**
 * @brief UART Manager Header File
 *
 * This file contains the declarations and documentation for UART management functions,
 * structures, and macros used for serial communication in the project.
 *
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