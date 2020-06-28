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
 * @file    panel_handler.c
 * @author  Vasu Gupta
 * @date    2020-06-15
 */


#include "panel_handler.h"
#include "adc_handler.h"

ADC_Handler s_adc_handler;

struct hyperion_all_panel_data{
    float temp_1[PANEL_NUM];
    float temp_2[PANEL_NUM];
    float temp_3[PANEL_NUM];
    float pd_1[PANEL_NUM];
    float pd_2[PANEL_NUM];
    float pd_3[PANEL_NUM];
    float volt[PANEL_NUM];
    float curr[PANEL_NUM];
};

static struct hyperion_all_panel_data All_Panels;

static float get_temp(int channel);
static float get_pd(int channel);
static float get_volt();
static float get_curr();

/**
 * @brief
 * 		Updates all the values for all panels stored in hyperion_panel_data struct
 * @return
 * 		None
 */
void panel_update_all()
{
    //Update all panel data.
    for(int p = 0; p < PANEL_NUM; p++) {
        adc_init(&s_adc_handler, p);

        All_Panels.temp_1[p] = get_temp(ADC_CHANNEL_TEMP_1);
        All_Panels.temp_2[p] = get_temp(ADC_CHANNEL_TEMP_2);
        All_Panels.temp_3[p] = get_temp(ADC_CHANNEL_TEMP_3);
        All_Panels.pd_1[p]   = get_pd(ADC_CHANNEL_PD_1);
        All_Panels.pd_2[p]   = get_pd(ADC_CHANNEL_PD_2);
        All_Panels.pd_3[p]   = get_pd(ADC_CHANNEL_PD_3);
        All_Panels.volt[p]   = get_volt();
        All_Panels.curr[p]   = get_curr();
    }
}

/**
 * @brief
 * 		Updates all the values for a single panel stored in hyperion_panel_data struct
 * @return
 * 		None
 */
void panel_update_single(panel_t panel)
{
    adc_init(&s_adc_handler, panel);

    All_Panels.temp_1[panel] = get_temp(ADC_CHANNEL_TEMP_1);
    All_Panels.temp_2[panel] = get_temp(ADC_CHANNEL_TEMP_2);
    All_Panels.temp_3[panel] = get_temp(ADC_CHANNEL_TEMP_3);
    All_Panels.pd_1[panel]   = get_pd(ADC_CHANNEL_PD_1);
    All_Panels.pd_2[panel]   = get_pd(ADC_CHANNEL_PD_2);
    All_Panels.pd_3[panel]   = get_pd(ADC_CHANNEL_PD_3);
    All_Panels.volt[panel]   = get_volt();
    All_Panels.curr[panel]   = get_curr();
} 

/**
 * @brief
 * 		Returns the desired sensor reading
 * @details
 * 		This function sets the default control register value, 
 *      and the SPI register configuration
 * @param panel
 * 		Select which panel to get reading from:
 *          
 * @param ch
 * 		Select which reading to get:
 *          CHANNEL_TEMP_1 = Temperature Sensor 1
 *          CHANNEL_TEMP_2 = Temperature Sensor 2
 *          CHANNEL_TEMP_3 = Temperature Sensor 3
 *          CHANNEL_PD_1   = Photodiode Sensor 1
 *          CHANNEL_PD_2   = Photodiode Sensor 2
 *          CHANNEL_VOLT   = Voltage Sensor
 *          CHANNEL_CURR   = Current Sensor
 * @return
 * 		Sensor reading
 */
float panel_get_reading(panel_t panel, channel_type_t ch) 
{
    float value = 0;

    switch (ch)
    {
        case CHANNEL_TEMP_1:
            value = All_Panels.temp_1[panel];
            break;

        case CHANNEL_TEMP_2:
            value = All_Panels.temp_2[panel];
            break;

        case CHANNEL_TEMP_3:
            value = All_Panels.temp_3[panel];
            break;

        case CHANNEL_PD_1:
            value = All_Panels.pd_1[panel];
            break;

        case CHANNEL_PD_2:
            value = All_Panels.pd_2[panel];
            break;

        case CHANNEL_PD_3:
            value = All_Panels.pd_3[panel];
            break;

        case CHANNEL_VOLT:
            value = All_Panels.volt[panel];
            break;

        case CHANNEL_CURR:
            value = All_Panels.curr[panel];
            break;
    
        default:
            value = 0;
            break;
    }

    return value;
}

static float get_temp(int channel)
{
    float temp = 0;
    uint16_t buffer;
    uint8_t  current_channel;
    adc_set_control_reg(&s_adc_handler, 
                        0, 
                        channel,
                        0,
                        0,
                        0);

    //call twice because first read is invalid
    adc_get_raw(&s_adc_handler, &buffer, &current_channel);
    adc_get_raw(&s_adc_handler, &buffer, &current_channel);
    temp = adc_calculate_sensor_temp(buffer, ADC_VREF);

    return temp;
}

static float get_volt()
{
    float value = 0;
    uint16_t buffer;
    uint8_t  current_channel;
    adc_set_control_reg(&s_adc_handler, 
                        0, 
                        ADC_CHANNEL_VOLT,
                        0,
                        0,
                        0);

    //call twice because first read is invalid
    adc_get_raw(&s_adc_handler, &buffer, &current_channel);
    adc_get_raw(&s_adc_handler, &buffer, &current_channel);
    value = (float)adc_calculate_sensor_voltage(buffer, ADC_VREF);

    return value;
}

static float get_curr()
{
    float value = 0;
    uint16_t buffer;
    uint8_t  current_channel;
    adc_set_control_reg(&s_adc_handler, 
                        0, 
                        ADC_CHANNEL_CURRENT,
                        0,
                        0,
                        0);

    //call twice because first read is invalid
    adc_get_raw(&s_adc_handler, &buffer, &current_channel);
    adc_get_raw(&s_adc_handler, &buffer, &current_channel);
    value = (float)adc_calculate_sensor_current(buffer, ADC_VREF);

    return value;
}

static float get_pd(int channel)
{
    float value = 0;
    uint16_t buffer;
    uint8_t  current_channel;
    adc_set_control_reg(&s_adc_handler, 
                        0, 
                        channel,
                        0,
                        0,
                        0);

    //call twice because first read is invalid
    adc_get_raw(&s_adc_handler, &buffer, &current_channel);
    adc_get_raw(&s_adc_handler, &buffer, &current_channel);
    value = (float)adc_calculate_sensor_pd(buffer, ADC_VREF);

    return value;
}