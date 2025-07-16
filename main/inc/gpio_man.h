/**
 * @file gpio_man.h
 * @author Aakash Singh
 * @brief GPIO management functions for ESP32 USB GPIO Controller
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