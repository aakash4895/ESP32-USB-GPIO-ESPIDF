/**
 * @file gpio_man.h
 * @author Aakash Singh
 * @brief 
 * @version 0.1
 * @date 2025-07-15
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#ifndef GPIO_MAN_H
#define GPIO_MAN_H

#include "esp_err.h"
#include "driver/gpio.h"

#define TEST_GPIO_NUM GPIO_NUM_2

esp_err_t gpioInit(gpio_num_t num, gpio_config_t config);
esp_err_t gpioSetLevel(gpio_num_t gpio_num, uint32_t level);
esp_err_t gpioToggleLevel(gpio_num_t gpio_num);
int gpioGetLevel(gpio_num_t gpio_num);
bool isGpioInitialized(gpio_num_t gpio_num);

#endif // GPIO Manager