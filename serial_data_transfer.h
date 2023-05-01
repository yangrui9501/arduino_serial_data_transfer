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

    /**
     * @brief Initialize serial data transfer
     *
     * @param _uart_handler Reference of serial port object
     * @param _baud_rate Baud rate of serial
     * @param _config Sets data, parity, and stop bits. For example: SERIAL_8N1
     */
    void init(HardwareSerial& _uart_handler, uint32_t _baud_rate, int _config = SERIAL_8N1);

    /**
     * @brief Begin serial communication
     *
     */
    void begin();

    /**
     * @brief Receive n bytes data
     *
     * @param _dest Destination of data structure
     * @param num_of_bytes_to_receive Number of bytes to receive
     * @return int
     */
    int receive(void* _dest, const int& num_of_bytes_to_receive);

    /**
     * @brief Transmit n bytes data from _src
     *
     * @param _src Source data
     * @param num_of_bytes_to_transmit Number of bytes to transmit
     * @return int
     */
    int transmit(void* _src, const int& num_of_bytes_to_transmit);

    /**
     * @brief Get the serial interface object
     *
     * @return HardwareSerial&
     */
    inline HardwareSerial& get_serial_interface() {
        return *pUART;
    }
    /**
     * @brief Get the uart message
     *
     * @return const char*
     */
    const char* get_uart_msg(void)
    {
        switch (uart_data_status)
        {
        case DATA_NOT_YET_READY:
            return "Data not yet ready";
        case DATA_LOST_BEGIN_BYTE:
            return "Lost the first begin byte";
        case DATA_LOST_FINISH_BYTE:
            return "Lost the second begin byte";
        case DATA_OK:
            return "Data OK";
        }
        return "1";
    }
protected:
    struct
    {
        uint8_t start_bytes[2];
    } frame_start;
    HardwareSerial* pUART;
    uint32_t baud_rate;
    int config;
    int uart_data_status;
};