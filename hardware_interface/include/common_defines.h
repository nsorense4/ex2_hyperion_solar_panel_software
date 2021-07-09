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
 * @file    common_defines.h
 * @author  Vasu Gupta
 * @date    2020-06-17
 */

#ifndef COMMON_DEFINES_H
#define COMMON_DEFINES_H

//i2c defines
#define ADC_i2c_PORT            i2cREG1

//ADC Addresses on each panel
#define ADC_SLAVE_ADDR                  0x23
#define PORT_ADC_SLAVE_ADDR             0x20
#define STAR_ADC_SLAVE_ADDR             0x23
#define PORT_DEP_ADC_SLAVE_ADDR         0x22
#define STAR_DEP_ADC_SLAVE_ADDR         0x28
#define ZENITH_ADC_SLAVE_ADDR           0x2E
#define PORT_2U_ADC_SLAVE_ADDR          0x20
#define STAR_2U_ADC_SLAVE_ADDR          0x23
#define PORT_DEP_2U_ADC_SLAVE_ADDR      0x22
#define STAR_DEP_2U_ADC_SLAVE_ADDR      0x28
#define ZENITH_2U_ADC_SLAVE_ADDR        0x2E
#define ARKE_ADC_SLAVE_ADDR             0x2C
#define NADIR_ADC_SLAVE_ADDR            0x2F
#define NADIR_2U_ADC_SLAVE_ADDR         0x2F

#define HIGH                    1
#define LOW                     0
 
#define ADC_VREF                2.5f


 
// VIN channels on ADC for sensors in configuration 1: all 3U panels - see datasheet
#define CONFIG_1_ADC_CHANNEL_TEMP_1      0
#define CONFIG_1_ADC_CHANNEL_TEMP_2      1
#define CONFIG_1_ADC_CHANNEL_TEMP_3      2
#define CONFIG_1_ADC_CHANNEL_PD_1        3
#define CONFIG_1_ADC_CHANNEL_PD_2        4
#define CONFIG_1_ADC_CHANNEL_PD_3        5
#define CONFIG_1_ADC_CHANNEL_VOLT        6
#define CONFIG_1_ADC_CHANNEL_CURRENT     7

// VIN channels on ADC for sensors in configuration 2: ARKE, NADIR, NADIR 2U
#define CONFIG_2_ADC_CHANNEL_TEMP_1      0
#define CONFIG_2_ADC_CHANNEL_PD_1        1

// VIN channels on ADC for sensors in configuration 3: 2U PANELS
#define CONFIG_3_ADC_CHANNEL_TEMP_1      0
#define CONFIG_3_ADC_CHANNEL_TEMP_2      1
#define CONFIG_3_ADC_CHANNEL_PD_1        2
#define CONFIG_3_ADC_CHANNEL_PD_2        3
#define CONFIG_3_ADC_CHANNEL_VOLT        4
#define CONFIG_3_ADC_CHANNEL_CURRENT     5


// Temperature Sensor (LMT70) constants
#define TEMP_VOLT_MAX           1.375f      //V
#define TEMP_VOLT_MIN           0.302f      //V
#define TEMP_VAL_MAX            150         //celsius
#define TEMP_VAL_MIN            -55         //celsius

// Voltage/Current Sensor Constants
#define ADC_VOLT_MAX            2.5f        //V
#define ADC_VOLT_MIN            0           //V
#define VOLT_MAX                16.18f       //V
#define VOLT_MIN                0           //V
#define CURR_MAX                0.588f      //A
#define CURR_MIN                0           //A



typedef enum channel_type_t{
    CHANNEL_TEMP_1 = 0,
    CHANNEL_TEMP_2,
    CHANNEL_TEMP_3,
    CHANNEL_PD_1,
    CHANNEL_PD_2,
    CHANNEL_PD_3,
    CHANNEL_VOLT,
    CHANNEL_CURR,
    CHANNEL_NUM         // Number of ADC channels
}channel_type_t;

typedef enum panel_t{
    PANEL_P = 0,        
    PANEL_PD,
    PANEL_Z,
    PANEL_SD,
    PANEL_S,
    PANEL_N,
    PANEL_NUM           // Number of solar panels
}panel_t;


#endif
