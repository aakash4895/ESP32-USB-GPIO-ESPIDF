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

TaskHandle_t mainTaskHandle = NULL;

void app_main(void)
{
    // Initialize UART task
    uartTaskInit();

    // Initialize GPIO task
    gpioTaskInit();

    while(1) {
        // Main loop implementation
        // printf("Main task running...\n");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }

}