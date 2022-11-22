#include "serial_data_transfer.h"

void SerialDataTransfer::Init(HardwareSerial &_uart_handler, uint32_t _baud_rate, int _num_of_bytes_to_receive)
{
    pUART = &_uart_handler;
    num_of_bytes_to_receive = _num_of_bytes_to_receive;

    /* Variable Initialization */
    pUART->begin(_baud_rate);
    buf = new uint8_t[_num_of_bytes_to_receive];
}

int SerialDataTransfer::Receive(void *_dest)
{
    uart_data_status = UART_Data_Status::Not_Yet_Ready;
    while (pUART->available() >= (int)(num_of_bytes_to_receive + 2))
    {
        if ((char)(pUART->read()) == start_byte) // Check for whether the start byte is correct
        {
            pUART->readBytes(buf, num_of_bytes_to_receive); // Copy data bytes from serial buffer

            if ((char)(pUART->read()) == finish_byte) // Check for whether the finish byte is correct
            {
                uart_data_status = UART_Data_Status::OK;

                /* Copy Data */
                memcpy(_dest, buf, num_of_bytes_to_receive);
            }
            else
            {
                uart_data_status = UART_Data_Status::Loss_Finish_Byte;
            }
        }
        else
        {
            uart_data_status = UART_Data_Status::Loss_Begin_Byte;
        }
    }
    return uart_data_status;
}

void SerialDataTransfer::Transmit(void *_src, int num_of_bytes_to_transmit)
{
    pUART->write((uint8_t *)&start_byte, 1);
    pUART->write((uint8_t *)_src, num_of_bytes_to_transmit);
    pUART->write((uint8_t *)&finish_byte, 1);
}