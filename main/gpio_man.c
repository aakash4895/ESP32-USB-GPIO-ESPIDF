/**
 * @file gpio_man.c
 * @author Aakash Singh
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include "gpio_man.h"
#include "main.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

TaskHandle_t gpioTaskHandle = NULL;
bool isrInstalled = false;

/**
 * @brief GPIO interrupt service routine handler
 * 
 * @param arg 
 */
static void gpioISRHandler(void *arg)
{
    // TODO: Implement GPIO ISR handler
    gpio_num_t gpio_num = (gpio_num_t)arg;
    // Handle GPIO interrupt
    printf("GPIO %d interrupt occurred\n", gpio_num);
    // Add your interrupt handling code here
}

/**
 * @brief GPIO task function that runs in a FreeRTOS task
 * 
 * @param pvParameters 
 */
static void gpioTask(void *pvParameters)
{
    // GPIO task implementation
    while (1) {
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(pdMS_TO_TICKS(1000));
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief Initialize GPIO task and create a FreeRTOS task for GPIO operations
 * 
 */
void gpioTaskInit(void)
{
    // Create GPIO task
    xTaskCreate(gpioTask, "gpioTask", 2048, NULL, 5, &gpioTaskHandle);
}

/**
 * @brief Deinitialize GPIO task and clean up resources
 * 
 */
void gpioTaskDeinit(void)
{
    // Delete GPIO task if it exists
    if (gpioTaskHandle != NULL) {
        vTaskDelete(gpioTaskHandle);
        gpioTaskHandle = NULL;
    }
}


/**
 * @brief Initialize GPIO pins with specified configuration
 * 
 * @param num GPIO number
 * @param mode GPIO mode (input/output)
 * @param pull_up GPIO pull-up configuration
 * @param pull_down GPIO pull-down configuration
 * @param intr_type GPIO interrupt type
 */
void gpioInit(gpio_num_t num, gpio_mode_t mode, gpio_pullup_t pull_up, gpio_pulldown_t pull_down, gpio_int_type_t intr_type)
{
    // Initialize GPIO pins
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << num),
        .mode = mode,
        .pull_up_en = pull_up,
        .pull_down_en = pull_down,
        .intr_type = intr_type
    };
    gpio_config(&io_conf);

    if(intr_type != GPIO_INTR_DISABLE) {
        // Enable GPIO interrupt if specified
        if (!isrInstalled) {
            gpio_install_isr_service(0);
            isrInstalled = true;
        }
        gpio_isr_handler_add(num, gpioISRHandler, (void *)num);
    }
}

/**
 * @brief Set GPIO level
 * 
 * @param gpio_num GPIO number
 * @param level Level to set (0 or 1)
 * @return esp_err_t Error code
 */
esp_err_t gpioSetLevel(gpio_num_t gpio_num, uint32_t level)
{
    // Set GPIO level
    return gpio_set_level(gpio_num, level);
}

/**
 * @brief Get GPIO level
 * 
 * @param gpio_num GPIO number
 * @return int Level of the GPIO pin (0 or 1)
 */
int gpioGetLevel(gpio_num_t gpio_num)
{
    // Get GPIO level
    return gpio_get_level(gpio_num);
}