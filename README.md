# Arduino Library - UART Data Transfer

This is an Arduino library of performing the uart data communication.

## Example: transmitter

```cpp
#include <Arduino.h>
#include <uart_data_transfer.h>

#define HARDWARE_SERIAL_INTERFACE Serial1
#define HARDWARE_SERIAL_BAUD_RATE 115200

UARTDataTransfer uart_transmitter;
typedef struct
{
    float value[10];
    uint8_t byte[sizeof(float) * 10U];
} uart_data_t;
uart_data_t uart_data;

void setup()
{
    uart_transmitter.init(HARDWARE_SERIAL_INTERFACE, HARDWARE_SERIAL_BAUD_RATE);
}

void loop()
{
    uart_transmitter.transmit(uart_data.byte, sizeof(uart_data_t));
    delay(1);
}
```
