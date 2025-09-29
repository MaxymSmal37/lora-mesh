/* 
 * File:   error.h
 * Author: maxymsmal
 *
 * Created on September 28, 2025, 23:37 PM
 */
#ifndef _ERROR_LOC_H_
#define _ERROR_LOC_H_

#include "stdint.h"
#define ERROR_ENABLE_BLINK

void togle_error_led(void);

void handle_sys_error(void);

void error_routine(uint8_t error_code);

void print_error(uint8_t error);

#endif //_ERROR_LOC_H_