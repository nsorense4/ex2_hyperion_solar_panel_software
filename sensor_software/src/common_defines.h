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

#include "reg_spi.h"

// SPI defines
#define SPI_BASE_ADDR spiREG3

#define HIGH 1
#define LOW  0

// VIN channels on ADC for sensors 
#define ADC_CHANNEL_TEMP_1      0
#define ADC_CHANNEL_TEMP_2      1
#define ADC_CHANNEL_TEMP_3      2
#define ADC_CHANNEL_PD_1        3
#define ADC_CHANNEL_PD_2        4
#define ADC_CHANNEL_PD_3        5
#define ADC_CHANNEL_VOLT        6
#define ADC_CHANNEL_CURRENT     7


enum channel_type_t{
    CHANNEL_TEMP_1 = 0,
    CHANNEL_TEMP_2,
    CHANNEL_TEMP_3,
    CHANNEL_PD_1,
    CHANNEL_PD_2,
    CHANNEL_PD_3,
    CHANNEL_VOLT,
    CHANNEL_CURR,
    CHANNEL_NUM         // Number of ADC channels
};

enum panel_t{
    PANEL_1 = 0,
    PANEL_2,
    PANEL_3,
    PANEL_4,
    PANEL_5,
    PANEL_6,
    PANEL_NUM          // Number of solar panels
};

#endif