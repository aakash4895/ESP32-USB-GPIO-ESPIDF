# ESP32 USB GPIO Controller

This ESP32 firmware provides a UART-based GPIO control interface that allows remote control of ESP32 GPIO pins through USB serial communication. It's designed to work as the hardware backend for the [ESP32-USB-GPIO-PY](https://github.com/aakash4895/ESP32-USB-GPIO-PY) Python library.

## Overview

This project turns your ESP32 into a GPIO controller that can be controlled via USB serial commands. It continuously monitors all GPIO pins and accepts commands to:

- Initialize GPIO pins with specific configurations
- Set GPIO pin levels (HIGH/LOW)
- Get GPIO pin levels
- Toggle GPIO pins
- Reset GPIO pins to LOW
- Monitor all GPIO pin states in real-time

## Hardware Requirements

- ESP32 development board
- USB cable for communication
- Target hardware connected to ESP32 GPIO pins

## Software Requirements

- ESP-IDF (Espressif IoT Development Framework)
- Python library: [ESP32-USB-GPIO-PY](https://github.com/aakash4895/ESP32-USB-GPIO-PY)

## Features

### Real-time GPIO Monitoring
The firmware continuously reads all GPIO pin states and outputs them in a structured format:
```
IN_GPIO_LEVEL:<max_pin>:<hex_value>
```

### UART Command Interface
Accepts ASCII commands via UART (USB serial) with the following format:

#### GPIO Initialization
```
INIT;<pin>;<mode>;<pullup>;<pulldown>;<interrupt_type>
```
- `pin`: GPIO pin number (0-39)
- `mode`: GPIO mode (0=INPUT, 1=OUTPUT, etc.)
- `pullup`: Pull-up configuration (0=DISABLE, 1=ENABLE)
- `pulldown`: Pull-down configuration (0=DISABLE, 1=ENABLE)
- `interrupt_type`: Interrupt type (0=DISABLE, 1=POSEDGE, etc.)

#### Set GPIO Level
```
SET;<pin>
```
Sets the specified GPIO pin to HIGH (3.3V)

#### Get GPIO Level
```
GET;<pin>
```
Returns the current level of the specified GPIO pin

#### Toggle GPIO Level
```
TOGGLE;<pin>
```
Toggles the current state of the specified GPIO pin

#### Reset GPIO Level
```
RESET;<pin>
```
Sets the specified GPIO pin to LOW (0V)

### Response Format
The firmware responds with structured messages:

- Success: `OK:<pin>`
- Error: `ERROR:<pin>:<error_code>`
- GPIO State: `STATE:<pin>:<level>`
- Real-time monitoring: `IN_GPIO_LEVEL:<max_pin>:<hex_state>`

## Project Structure

```
├── CMakeLists.txt              # Main CMake configuration
├── main/                       # Source code directory
│   ├── CMakeLists.txt         # Main component CMake file
│   ├── main.c                 # Main application logic and command parser
│   ├── gpio_man.c             # GPIO management functions
│   ├── uart_man.c             # UART communication functions
│   └── inc/                   # Header files
│       ├── main.h             # Main header file
│       ├── gpio_man.h         # GPIO management header
│       └── uart_man.h         # UART management header
├── build/                     # Build output directory
└── README.md                  # This file
```

## Usage with Python Library

This firmware is designed to work seamlessly with the [ESP32-USB-GPIO-PY](https://github.com/aakash4895/ESP32-USB-GPIO-PY) Python library. The Python library provides a high-level interface to control the ESP32 GPIO pins through this firmware.

### Python Library Integration
1. Flash this firmware to your ESP32
2. Install the Python library: `pip install esp32-usb-gpio`
3. Connect your ESP32 via USB
4. Use the Python library to control GPIO pins

Example Python usage:
```python
from esp32_usb_gpio import ESP32GPIO

# Create GPIO controller instance
gpio = ESP32GPIO('/dev/ttyUSB0')  # or COM port on Windows

# Initialize a pin as output
gpio.init_pin(2, mode='OUTPUT')

# Set pin high
gpio.set_pin(2, 1)

# Read pin state
state = gpio.get_pin(2)

# Toggle pin
gpio.toggle_pin(2)
```

## Building and Flashing

### Prerequisites
Make sure you have ESP-IDF installed and configured.

### Build the project
```bash
idf.py build
```

### Flash to ESP32
```bash
idf.py flash
```

### Monitor output
```bash
idf.py monitor
```

## Configuration

### UART Settings
- Baud Rate: 115200
- Data Bits: 8
- Stop Bits: 1
- Parity: None
- Flow Control: None

### GPIO Configuration
- All GPIO pins (0-39) are monitored
- Pin configurations are set dynamically via commands
- Default state: All pins uninitialized

## Author

**Aakash Singh**
- Version: 0.1
- Date: July 15, 2025

## Related Projects

- [ESP32-USB-GPIO-PY](https://github.com/aakash4895/ESP32-USB-GPIO-PY) - Python library for controlling this firmware

## License

This project is licensed under the GNU General Public License v3.0 - see below for details:

```
ESP32 USB GPIO Controller
Copyright (C) 2025 Aakash Singh

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```

For the complete license text, see: https://www.gnu.org/licenses/gpl-3.0.html

## Contributing

This project serves as the hardware backend for the ESP32-USB-GPIO-PY Python library. For feature requests or issues related to the Python interface, please refer to the [Python library repository](https://github.com/aakash4895/ESP32-USB-GPIO-PY).
