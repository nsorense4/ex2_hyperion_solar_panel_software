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

#include "common_defines.h"

#include "stdint.h"

// Halcogen generated SPI driver
#include "spi.h"

// AD7298 Control Register Map
#define AD7298_WRITE        (1U << 15U)
#define AD7298_REPEAT       (1U << 14U)
#define AD7298_CH(x)        (1U << ((13U) - x))
#define AD7298_TSENSE       (1U << 5U)
#define AD7298_EXT_REF      (1U << 2U)
#define AD7298_TSENSE_AVG   (1U << 1U)
#define AD7298_PPD          (1U << 0U)

#define AD7298_RES          4096

// Temperature Sensor (LMT70) constants
#define TEMP_VOLT_MAX       1375        //mV
#define TEMP_VOLT_MIN       302         //mV
#define TEMP_VAL_MAX        150         //celsius
#define TEMP_VAL_MIN        -55         //celsius

typedef struct adc_handler_t ADC_Handler;

struct adc_handler_t{
    //Current value of the ADC control register
    uint16_t  control_reg_val;   

    // SPI data register configuration 
    spiDAT1_t spi_dat_conf;

    // Select Panel
    enum panel_t panel;
};

// Initialize ADC defaults and SPI
void adc_init(ADC_Handler *handl, enum panel_t panel);
void adc_set_control_reg(ADC_Handler *handl, uint8_t repeat,
                                             uint8_t channels,
                                             uint8_t ext_ref,
                                             uint8_t tsense,
                                             uint8_t tsense_avg);

//return the raw value from the adc
void adc_get_raw(ADC_Handler *handl, uint16_t *data, uint8_t *ch);


int16_t adc_conv_to_volt(uint16_t value, int16_t vref);
float adc_conv_to_celsius(uint16_t value, int16_t vref);
int16_t adc_conv_to_current(uint16_t value, int16_t vref);

// convert internal temp sensor value
float adc_get_tsense_temp(uint16_t value, int16_t vref);

// SPI Read/Write functions
void write_spi(ADC_Handler *handl, uint16_t *data, uint32_t len);
void read_spi(ADC_Handler *handl, uint16_t *data, uint32_t len);

#endif