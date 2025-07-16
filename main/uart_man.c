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
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define GPIO_INIT_TAG "INIT"
#define GPIO_SET_LEVEL_TAG "SET"
#define GPIO_GET_LEVEL_TAG "GET"
#define GPIO_RESET_TAG "RESET"

TaskHandle_t uartTaskHandle = NULL;

/**
 * @brief UART task function that runs in a FreeRTOS task
 * 
 * @param pvParameters 
 */
static void uartTask(void *pvParameters)
{
    char dataBuffer[128];
    uint8_t recv_len = 0;

    gpio_config_t _gpio_config;
    uint8_t pin_num;
    char *token = NULL;
    char tag[16];
    // UART task implementation
    while (1) {
        recv_len = uart_read_bytes(UART_NUM, (uint8_t *)dataBuffer, sizeof(dataBuffer) - 1, pdMS_TO_TICKS(100));
        if (recv_len > 0) {
            dataBuffer[recv_len] = '\0'; // Null-terminate the string
            // the recieved data is in ASCII format, so we can print it directly
            // Sample data "INIT;PIN;MODE;PULLUP;PULLDOWN;INTR_TYPE"  "INIT;2;2;0;0;0"
            // Sample data "SET;PIN" "SET;2"
            // Sample data "TOGGLE;PIN" "TOGGLE;2"
            // Sample data "RESET;PIN" "RESET;2"
            // Sample data "GET"
            token = strtok(dataBuffer, ";");
            strcpy(tag, token);
            if (strncmp(tag, "INIT", 4) == 0) {
                // Handle GPIO initialization
                // Parse and initialize GPIO pins as needed
                token = strtok(NULL, ";");
                pin_num = atoi(token);
                _gpio_config.pin_bit_mask = (1ULL << pin_num);
                token = strtok(NULL, ";");
                _gpio_config.mode = (gpio_mode_t)atoi(token);
                if((_gpio_config.mode == GPIO_MODE_OUTPUT || _gpio_config.mode == GPIO_MODE_OUTPUT_OD)) {
                    _gpio_config.pull_up_en = GPIO_PULLUP_DISABLE;
                    _gpio_config.pull_down_en = GPIO_PULLDOWN_DISABLE;
                    _gpio_config.intr_type = GPIO_INTR_DISABLE;
                }
                else{
                    token = strtok(NULL, ";");
                    _gpio_config.pull_up_en = (gpio_pullup_t)atoi(token);
                    token = strtok(NULL, ";");
                    _gpio_config.pull_down_en = (gpio_pulldown_t)atoi(token);
                    token = strtok(NULL, ";");
                    _gpio_config.intr_type = (gpio_int_type_t)atoi(token);
                }
                gpioInit(pin_num, _gpio_config);
            } else if (strncmp(tag, "SET", 3) == 0) {
                // Handle GPIO set level
                token = strtok(NULL, ";");
                pin_num = atoi(token);
                if(isGpioInitialized(pin_num)) {
                    // Set GPIO level
                    esp_err_t err = gpioSetLevel(pin_num, 1);
                }
                // Parse and set GPIO level as needed
            } else if (strncmp(tag, "TOGGLE", 6) == 0) {
                // Handle GPIO Toggle level
                token = strtok(NULL, ";");
                pin_num = atoi(token);
                if(isGpioInitialized(pin_num)) {
                    // Set GPIO level
                    esp_err_t err = gpioToggleLevel(pin_num);
                }
            } else if (strncmp(tag, "GET", 3) == 0) {
                // Handle GPIO get level
                continue;
                // Parse and get GPIO level as needed
            } else if (strncmp(tag, "RESET", 5) == 0) {
                // Handle GPIO reset
                // Reset GPIO pins as needed
                token = strtok(NULL, ";");
                pin_num = atoi(token);
                if(isGpioInitialized(pin_num)) {
                    // Set GPIO level
                    esp_err_t err = gpioSetLevel(pin_num, 0);
                }
            }
        }
    }
}

/**
 * @brief Initialize UART task and create a FreeRTOS task for UART operations
 * 
 */void uartTaskInit(void)
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
    uart_driver_install(UART_NUM, 2048, 0, 0, NULL, 0);
    uart_param_config(UART_NUM, &uart_config);
    
    // Create UART task
    xTaskCreate(uartTask, "uartTask", 2048, NULL, 5, &uartTaskHandle);
}