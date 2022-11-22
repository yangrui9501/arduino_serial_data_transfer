/**
 * @file Serial_Data_Transfer.h
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

class SerialTransfer
{
public:
    SerialTransfer() { }
    enum UART_Data_Status
    {
        DATA_LOST_FINISH_BYTE = -3,
        DATA_LOST_BEGIN_BYTE,
        DATA_NOT_YET_READY,
        OK
    };

    void init(HardwareSerial &_uart_handler, uint32_t _baud_rate, int _num_of_bytes_to_receive);
    int receive(void *_dest);
    void transmit(void *_src, int num_of_bytes_to_transmit);

protected:
    const char start_byte = 's';
    const char finish_byte = 'f';
    HardwareSerial *pUART;    
    int uart_data_status;
    int num_of_bytes_to_receive;
    uint8_t *buf;
};