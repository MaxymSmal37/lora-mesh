/* 
 * File:   error.h
 * Author: maxymsmal
 *
 * Created on September 29, 2025, 00:02 PM
 */
#ifndef _ERROR_PUB_H_
#define _ERROR_PUB_H_

#include "stdint.h"
enum {
    APP_UNDEFINED_ERROR = 0,
    APP_SPI_ERROR,
    APP_UNDEFINED_SX1278_MODULE,
    APP_LORA_READ_ERROR = 50,
    APP_LORA_WRITE_ERROR
};

void set_error(uint8_t error_code);

#endif // _ERROR_PUB_H_