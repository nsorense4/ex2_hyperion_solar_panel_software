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
 * 		This function sets the default control register value, 
 *      and the SPI register configuration
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
 * 		Set and send control register bits to the ADC
 * @details
 * 		Refer to page 16 of AD7298 datasheet for more details
 * @param handl
 * 		Pointer to ADC_Handler struct
 * @param repeat
 * 		1 = Enable
 *      0 = Disable
 * @param channel
 * 		Select which channel to enable (0-7)
 *      Accepted values: 0-7
 * @param ext_ref
 *      Enable/Disable the use of external reference.
 * 		1 = Enable
 *      0 = Disable
 * @param tsense
 *      Enable/Disable (internal) temperature conversion
 * 		1 = Enable
 *      0 = Disable
 * @param tsense_avg
 *      Enable/Disable temperature sensor averaging function
 * 		1 = Enable
 *      0 = Disable
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
 * 		The ADC returns a 16-bit value, in which the 4 MSB are channel address bits,
 *      and the remaining 12 is the raw ADC value
 * @param handl
 * 		Pointer to ADC_Handler struct
 * @param data
 * 		Buffer for storing ADC raw value
 * @param ch
 * 		Buffer for storing which channel the value was received from.
 * @return
 * 		None
 */
void adc_get_raw(ADC_Handler *handl, uint16_t *data, uint8_t *ch) 
{  
    uint16_t buffer = 0;

    //SET CS PIN LOW 
    //SPI read into value
    spiReceiveData(SPI_BASE_ADDR, &(handl->spi_dat_conf), 1, &buffer);
    //SET CS PIN HIGH

    
    *data = buffer & 0x0FFF;
    
    //get current data channel as well.
    *ch   = (buffer >> 12);
}

/**
 * @brief
 * 		Converts the given raw ADC value to volts (relative to reference voltage).
 * @param handl
 * 		Pointer to ADC_Handler struct
 * @param value
 * 		The raw ADC value
 *      This value can be retrieved using adc_get_raw(..)
 * @param vref
 * 		The value of reference voltage provided to the ADC module
 *      Refer to AD7298 datasheet.
 * @return
 * 		Value in volts.
 */
float adc_conv_to_volt(ADC_Handler *handl, uint16_t value, float vref) {
    float volts = 0;

    // from AD7298 datasheet
    volts = ((float)value * vref) / AD7298_RES;

    return volts;
}

/**
 * @brief
 * 		Converts given raw ADC temperature value to celsius (relative tp reference voltage)
 * @details
 * 		The raw ADC value is retrieved from the TSENSE channel on the ADC
 *      Refer to AD7298 datasheet.
 * @attention
 * 		This function is to be used only if 'TSENSE' on the ADC is enabled.
 * @param handl
 * 		Pointer to ADC_Handler struct
 * @param value
 * 		The raw ADC temperature value
 *      This value can be retrieved usig adc_get_raw(..) and when 'TSENSE' is enabled
 *      by setting the control register
 * @param vref
 * 		The value of reference voltage provided to the ADC module
 *      Refer to AD7298 datasheet.
 * @return
 * 		Temperature value in celsius
 */
float adc_get_tsense_temp(ADC_Handler *handl, uint16_t value, float vref) {
    float temp_celsius = 0;

    if(value >= 0x800) {
        value  = AD7298_RES - value;
        value *= -1;
    }

    // from AD7298 datasheet
    temp_celsius = vref * (((float)value / 10) + 109.3) - 273.15; 

    return temp_celsius;
}

