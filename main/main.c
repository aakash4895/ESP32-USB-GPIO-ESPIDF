/**
 * @file main.c
 * @author Aakash Singh
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "main.h"
#include "gpio_man.h"
#include "uart_man.h"

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
#define GPIO_RESET_LEVEL_TAG "RESET"
#define GPIO_TOGGLE_LEVEL_TAG "TOGGLE"

#define GPIO_OK "OK"
#define GPIO_ERROR "ERROR"
#define GPIO_STATE "STATE"
#define GPIO_INTR "INTR"
#define GPIO_INTR_CLEAR "INTR_CLEAR"
#define GPIO_INTR_GET "INTR_GET"
#define GPIO_IN "IN_GPIO_LEVEL"

TaskHandle_t mainTaskHandle = NULL;

static void appTask(void *pvParameters);

void app_main(void)
{
    // Initialize UART
    uartInit();

    // Initialize Main Task
    xTaskCreate(appTask, "app_task", 5*1024, NULL, 5, &mainTaskHandle);
    if (mainTaskHandle == NULL) {
        printf("Failed to create main task\n");
    }

    while(1) {
        // Main loop implementation
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }

}

/**
 * @brief App task function that runs in a FreeRTOS task
 * 
 * @param pvParameters 
 */
static void appTask(void *pvParameters)
{
    esp_err_t ret;

    char dataBuffer[UART_MAX_READ_LEN];
    uint8_t recv_len = 0;

    gpio_config_t _gpio_config;
    uint8_t pin_num=0;
    char *token = NULL;
    char tag[16];
    uint64_t ioOutput = 0;
    
    // UART task implementation
    while (1) {
        for(int i=0; i< GPIO_NUM_MAX; i++) {
            int level = gpio_get_level((gpio_num_t)i);
            // Update output state
            if (level == 1) {
                ioOutput |= (1ULL << i);
            } else {
                ioOutput &= ~(1ULL << i);
            }
        }
        printf(GPIO_IN":%d:0x%" PRIx64 "\n",GPIO_NUM_MAX-1, ioOutput);
        // Read data from UART, blocking until data is available for 100ms
        memset(dataBuffer, 0, sizeof(dataBuffer)); // Clear the buffer
        memset(tag, 0, sizeof(tag)); // Clear the tag buffer
        recv_len = uart_read_bytes(UART_NUM, (uint8_t *)dataBuffer, UART_MAX_READ_LEN - 1, pdMS_TO_TICKS(100));
        if (recv_len > 0) {
            ret = ESP_ERR_INVALID_STATE;
            dataBuffer[recv_len] = '\0'; // Null-terminate the string
            // the recieved data is in ASCII format, so we can print it directly
            // Sample data "INIT;PIN;MODE;PULLUP;PULLDOWN;INTR_TYPE"  "INIT;2;2;0;0;0"
            // Sample data "SET;PIN" "SET;2"
            // Sample data "TOGGLE;PIN" "TOGGLE;2"
            // Sample data "RESET;PIN" "RESET;2"
            // Sample data "GET"
            token = strtok(dataBuffer, ";");
            strcpy(tag, token);
            if (strncmp(tag, GPIO_INIT_TAG, 4) == 0) {
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
                ret = gpioInit(pin_num, _gpio_config);
            } else if (strncmp(tag, GPIO_SET_LEVEL_TAG, 3) == 0) {
                // Handle GPIO set level
                token = strtok(NULL, ";");
                pin_num = atoi(token);
                // Set GPIO level
                ret = gpioSetLevel(pin_num, 1);
            } else if (strncmp(tag, GPIO_TOGGLE_LEVEL_TAG, 6) == 0) {
                // Handle GPIO Toggle level
                token = strtok(NULL, ";");
                pin_num = atoi(token);
                ret = gpioToggleLevel(pin_num);
            } else if (strncmp(tag, GPIO_GET_LEVEL_TAG, 3) == 0) {
                // Handle GPIO get level
                token = strtok(NULL, ";");
                pin_num = atoi(token);
                // Set GPIO level
                int level = gpioGetLevel(pin_num);
                ret = (level==ESP_ERR_INVALID_STATE) ? ESP_ERR_INVALID_STATE : ESP_OK;

            } else if (strncmp(tag, GPIO_RESET_LEVEL_TAG, 5) == 0) {
                // Handle GPIO reset
                // Reset GPIO pins as needed
                token = strtok(NULL, ";");
                pin_num = atoi(token);
                // Set GPIO level
                ret = gpioSetLevel(pin_num, 0);
            }
            if(ret!=ESP_OK){
                printf(GPIO_ERROR":%d:%d\n", pin_num, ret);
                continue;
            }
            if (strncmp(tag, GPIO_GET_LEVEL_TAG, 3) == 0) {
                // If it is a GET command, print the level
                int level = gpioGetLevel(pin_num);
                if (level == ESP_ERR_INVALID_STATE) {
                    printf(GPIO_ERROR":%d:%d\n", pin_num, level);
                } else {
                    printf(GPIO_STATE":%d:%d\n", pin_num, level);
                }
            } else {
                // Print success message for other commands
                printf(GPIO_OK":%d\n", pin_num);
            }
        }
    }
}