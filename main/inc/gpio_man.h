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

void gpioTaskInit(void);
void gpioTaskDeinit(void);
void gpioInit(gpio_num_t num, gpio_mode_t mode, gpio_pullup_t pull_up, gpio_pulldown_t pull_down, gpio_int_type_t intr_type);
esp_err_t gpioSetLevel(gpio_num_t gpio_num, uint32_t level);
int gpioGetLevel(gpio_num_t gpio_num);

#endif // GPIO Manager