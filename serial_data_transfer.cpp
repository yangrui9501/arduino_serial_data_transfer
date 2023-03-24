#include "serial_data_transfer.h"

void SerialDataTransfer::init(HardwareSerial& _uart_handler, uint32_t _baud_rate, int _config)
{
    pUART = &_uart_handler;
    baud_rate = _baud_rate;
    config = _config;

    frame_start.start_bytes[0] = 0xBB;
    frame_start.start_bytes[1] = 0xAA;
}

void SerialDataTransfer::begin()
{
    pUART->begin(baud_rate, config);
}

int SerialDataTransfer::receive(void* _dest, const int& num_of_bytes_to_receive)
{
    uart_data_status = DATA_NOT_YET_READY;
    while (pUART->available() >= (num_of_bytes_to_receive + 2))
    {
        if ((uint8_t)(pUART->read()) == frame_start.start_bytes[0]) // Check for whether the start byte is correct
        {
            if ((uint8_t)(pUART->read()) == frame_start.start_bytes[1]) // Check for whether the finish byte is correct
            {
                uart_data_status = DATA_OK;

                /* Copy Data */
                pUART->readBytes((uint8_t*)_dest, num_of_bytes_to_receive); // Copy data bytes from serial buffer

            }
            else
            {
                uart_data_status = DATA_LOST_FINISH_BYTE;
            }
        }
        else
        {
            uart_data_status = DATA_LOST_BEGIN_BYTE;
        }
    }
    return uart_data_status;
}

int SerialDataTransfer::transmit(void* _src, const int& num_of_bytes_to_transmit)
{
    if (pUART->availableForWrite() >= num_of_bytes_to_transmit)
    {
        pUART->write(frame_start.start_bytes, 2);
        pUART->write((uint8_t*)_src, num_of_bytes_to_transmit);
        pUART->flush();

        return 0;
    }
    return -1;
}