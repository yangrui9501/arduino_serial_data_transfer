/**
 * @file SerialDataTransfer.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-10-25
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <Arduino.h>

class SerialDataTransfer
{
public:
    SerialDataTransfer() {}
    enum SERIAL_DATA_STATUS
    {
        DATA_LOST_FINISH_BYTE = -3,
        DATA_LOST_BEGIN_BYTE,
        DATA_NOT_YET_READY,
        DATA_OK
    };

    void init(HardwareSerial &_uart_handler, uint32_t _baud_rate, int _format = SERIAL_8N1, uint8_t _start_byte = 0xAA, uint8_t _finish_byte = 0xBB);
    int set_rx_buffer(size_t _dest_package_size);
    int receive(void *_dest);
    int transmit(void *_src, int num_of_bytes_to_transmit);
    HardwareSerial &get_serial_obj()
    {
        return *pUART;
    }
protected:
    uint8_t start_byte;
    uint8_t finish_byte;
    HardwareSerial *pUART;
    int uart_data_status;
    int num_of_bytes_to_receive;
    uint8_t *buf;
};