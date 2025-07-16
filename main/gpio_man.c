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

static TaskHandle_t gpioTaskHandle = NULL;
static bool isrInstalled = false;
static bool gpioInitialized[GPIO_NUM_MAX] = {false};
static bool gpioOutputState[GPIO_NUM_MAX] = {false};

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
 * @brief Initialize GPIO pins with specified configuration
 * 
 * @param num GPIO number
 * @param gpio_config_t gpio_config_t structure containing GPIO configuration
 * @return esp_err_t Error code
 */
esp_err_t gpioInit(gpio_num_t num, gpio_config_t config)
{
    esp_err_t ret = ESP_OK;
    // Initialize GPIO pins
    gpio_config_t io_conf = {
        .pin_bit_mask = config.pin_bit_mask,
        .mode = config.mode,
        .pull_up_en = config.pull_up_en,
        .pull_down_en = config.pull_down_en,
        .intr_type = config.intr_type
    };
    ret = gpio_config(&io_conf);
    if (ret != ESP_OK) {
        return ret;
    }

    if(config.intr_type != GPIO_INTR_DISABLE) {
        // Enable GPIO interrupt if specified
        if (!isrInstalled) {
            ret = gpio_install_isr_service(0);
            if (ret != ESP_OK) {
                return ret;
            }
            isrInstalled = true;
        }
        ret = gpio_isr_handler_add(num, gpioISRHandler, (void *)num);
        if (ret != ESP_OK) {
            return ret;
        }
    }
    gpioInitialized[num] = true;
    return ret;
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
    if(isGpioInitialized(gpio_num) == false) {
        return ESP_ERR_INVALID_STATE;
    }
    // Set GPIO level
    gpioOutputState[gpio_num] = (level != 0);
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
    if(isGpioInitialized(gpio_num) == false) {
        return ESP_ERR_INVALID_STATE;
    }
    // Get GPIO level
    return gpio_get_level(gpio_num);
}

/**
 * @brief Toggle GPIO level
 * 
 * @param gpio_num 
 * @return esp_err_t Error code
 */
esp_err_t gpioToggleLevel(gpio_num_t gpio_num)
{
    if(isGpioInitialized(gpio_num) == false) {
        return ESP_ERR_INVALID_STATE;
    }
    // Toggle GPIO level
    if (gpioInitialized[gpio_num]) {
        int currentLevel = gpioOutputState[gpio_num];
        gpioOutputState[gpio_num] = !currentLevel; // Update output state
        return gpioSetLevel(gpio_num, !currentLevel);
    } else {
        return ESP_ERR_INVALID_STATE;
    }
}

/**
 * @brief Check if GPIO pin is initialized
 * 
 * @param gpio_num GPIO number
 * @return true if GPIO pin is initialized, false otherwise
 */
bool isGpioInitialized(gpio_num_t gpio_num)
{
    // Check if GPIO pin is initialized
    if (gpio_num < GPIO_NUM_MAX) {
        return gpioInitialized[gpio_num];
    }
    return false;
}