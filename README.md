# Arduino Library - Serial Data Transfer

This library implements the `binary-encoded data` transmitting/receiving based on Arduino `HardwareSerial` APIs. The following demonstrated simple examples of how to use this library to perform the data IO.

Date: November 24, 2021

## Data Transmitter

```cpp
#include <Arduino.h>
#include <serial_data_transfer.h>

#define HARDWARE_SERIAL_INTERFACE Serial1
#define HARDWARE_SERIAL_BAUD_RATE 115200

SerialDataTransfer DataTx;
typedef struct
{
    float data1[3];
    int data2[2];
} uart_data_t;
uart_data_t uart_data;

void setup()
{
    DataTx.init(HARDWARE_SERIAL_INTERFACE, HARDWARE_SERIAL_BAUD_RATE);
}

void loop()
{
    DataTx.transmit(&uart_data sizeof(uart_data_t));
    delay(1);
}
```

## Date Receiver

```cpp
#include <Arduino.h>
#include <serial_data_transfer.h>

#define HARDWARE_SERIAL_INTERFACE Serial1
#define HARDWARE_SERIAL_BAUD_RATE 115200

SerialDataTransfer DataRx;
typedef struct
{
    float data1[3];
    int data2[2];
} uart_data_t;
uart_data_t uart_data;

void setup()
{
    DataRx.init(HARDWARE_SERIAL_INTERFACE, HARDWARE_SERIAL_BAUD_RATE, sizeof(uart_data_t));
}

void loop()
{
    int uart_data_status = DataRx.receive(&uart_data);
    if (uart_data_status == SerialDataTransfer::DATA_OK) // It means the process of binary decoding is successful.
    {
        // Do something if the date is received:
    }

    delay(1);
}
```
