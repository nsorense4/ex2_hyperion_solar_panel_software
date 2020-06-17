/*
 * Copyright (C) 2015  University of Alberta
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
/**
 * @file    adc_handler.h
 * @author  Vasu Gupta
 * @date    2020-06-15
 */


#ifndef ADC_HANDLER_H
#define ADC_HANDLER_H

#include "stdint.h"
#include "mock_spi.h"

// AD7298 Control Register Map
#define AD7298_WRITE        (1U << 15U)
#define AD7298_REPEAT       (1U << 14U)
#define AD7298_CH(x)        (1U << ((13U) - x))
#define AD7298_TSENSE       (1U << 5U)
#define AD7298_EXT_REF      (1U << 2U)
#define AD7298_TSENSE_AVG   (1U << 1U)
#define AD7298_PPD          (1U << 0U)

typedef struct adc_handler_t ADC_Handler;

struct adc_handler_t{
    uint16_t        control_reg_val;   //Current value of the ADC control register
    unsigned int    adc_res;           //Maximum resolution of the ADC
};

// Initialize ADC defaults and SPI
void adc_init(ADC_Handler *handl, unsigned int res);

//return the raw value from the adc
void adc_get_raw(ADC_Handler *handl, uint16_t *data);

float adc_get_temp(ADC_Handler *handl, uint16_t value, float vref);

void adc_set_control_reg(ADC_Handler *handl, unsigned char repeat,
                                             unsigned char channels,
                                             unsigned char ext_ref,
                                             unsigned char tsense,
                                             unsigned char tsense_avg);

//convert raw value to voltage
//unsigned int adc_();

//DEMUX PIN SETTING

#endif