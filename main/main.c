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
    
    // Initialize GPIO pins
    gpioInit(TEST_GPIO_NUM, GPIO_MODE_OUTPUT, GPIO_PULLUP_ENABLE, GPIO_PULLDOWN_DISABLE, GPIO_INTR_DISABLE);
    
    
    while(true){
        // Set GPIO level to high
        gpioSetLevel(TEST_GPIO_NUM, 1);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
        
        // Set GPIO level to low
        gpioSetLevel(TEST_GPIO_NUM, 0);
        vTaskDelay(pdMS_TO_TICKS(1000)); // Delay for 1 second
    }

}