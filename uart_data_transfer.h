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

class UARTDataTransfer
{
public:
    UARTDataTransfer() { }
    enum UART_DATA_STATUS
    {
        DATA_LOST_FINISH_BYTE = -3,
        DATA_LOST_BEGIN_BYTE,
        DATA_NOT_YET_READY,
        DATA_OK
    };

    void init(HardwareSerial &_uart_handler, uint32_t _baud_rate, int _num_of_bytes_to_receive = -1, uint8_t _start_byte = 0xAA, uint8_t _finish_byte = 0xBB);
    int receive(void *_dest);
    void transmit(void *_src, int num_of_bytes_to_transmit);

protected:
    uint8_t start_byte;
    uint8_t finish_byte;
    HardwareSerial *pUART;    
    int uart_data_status;
    int num_of_bytes_to_receive;
    uint8_t *buf;
};