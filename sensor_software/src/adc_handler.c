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
 * @file    adc_handler.c
 * @author  Vasu Gupta
 * @date    2020-06-15
 */

#include "common_defines.h"
#include "adc_handler.h"
#include "demux_handler.h"


/**
 * @brief
 * 		Initialize ADC_Handler struct
 * @details
 * 		<more detailed description of the function>
 * @param handl
 * 		Pointer to an ADC_Handler struct
 * @return
 * 		None
 */
void adc_init(ADC_Handler *handl) {
    //Initialize ADC defaults and SPI here
    handl->control_reg_val  = 0;
    
    //Initialize SPI register configuration (Refer to TMS570LS1224 datasheet)
    handl->spi_dat_conf.CS_HOLD = TRUE;
    handl->spi_dat_conf.WDEL    = TRUE;
    handl->spi_dat_conf.DFSEL   = SPI_FMT_0;
    handl->spi_dat_conf.CSNR    = 0xFF;
}

/**
 * @brief
 * 		Set control register bits.
 * @details
 * 		<more detailed description of the function>
 * @param handl
 * 		pointer to ADC_Handler struct
 * @param repeat
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @param channel
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @param ext_ref
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @param tsense
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @param tsense_avg
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @return
 * 		None
 */
void adc_set_control_reg(ADC_Handler *handl, uint8_t repeat,
                                             uint8_t channel,
                                             uint8_t ext_ref,
                                             uint8_t tsense,
                                             uint8_t tsense_avg) 
{
    uint16_t control_reg_value = 0;

    control_reg_value = AD7298_WRITE 
                      | (repeat     * AD7298_REPEAT) 
                      |  AD7298_CH(channel)
                      | (ext_ref    * AD7298_EXT_REF)
                      | (tsense     * AD7298_TSENSE)
                      | (tsense_avg * AD7298_TSENSE_AVG);

    //SET CS PIN LOW
    //send buffer to SPI
    spiTransmitData(SPI_BASE_ADDR, &(handl->spi_dat_conf), 1, &control_reg_value);
    //SET CS PIN HIGH

    handl->control_reg_val = control_reg_value;
    
}

/**
 * @brief
 * 		Returns the conversion results from ADC
 * @details
 * 		<more detailed description of the function>
 * @attention
 * 		<if applicable, any comments or concerns regarding the function>
 * @param handl
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @param data
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @return
 * 		<if applicable, brief description of what is returned by the function>
 */
void adc_get_raw(ADC_Handler *handl, uint16_t *data, uint8_t *ch) 
{  
    uint16_t buffer = 0;

    //SET CS PIN LOW 
    //SPI read into value
    spiReceiveData(SPI_BASE_ADDR, &(handl->spi_dat_conf), 1, &buffer);
    //SET CS PIN HIGH

    *data = buffer & 0x0FFF;
    //get data channel as well.
    *ch   = (buffer >> 12);
}

/**
 * @brief
 * 		<breif (one line) description of the function>
 * @details
 * 		<more detailed description of the function>
 * @attention
 * 		<if applicable, any comments or concerns regarding the function>
 * @param <argument_1>
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @param <argument_2>
 * 		<if applicable, brief (one line) description of one of the function's arguments>
 * @return
 * 		<if applicable, brief description of what is returned by the function>
 */
float adc_get_temp(ADC_Handler *handl, uint16_t value, float vref) {
    float temp_celsius = 0;

    if(value >= 0x800) {
        value  = AD7298_RES - value;
        value *= -1;
    }

    temp_celsius = vref * (((float)value / 10) + 109.3) - 273.15; //from datasheet

    return temp_celsius;
}

