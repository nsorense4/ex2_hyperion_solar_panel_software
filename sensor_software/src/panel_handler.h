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
 * @file    panel_handler.h
 * @author  Vasu Gupta
 * @date    2020-06-15
 */


#ifndef PANEL_HANDLER_H
#define PANEL_HANDLER_H

#include "adc_handler.h"

#include <stdint.h>

enum channel_type_t{
    CHANNEL_TEMP_1 = 0,
    CHANNEL_TEMP_2,
    CHANNEL_TEMP_3,
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

typedef struct hyp_panel_t hyperion_panel;

struct hyp_panel_t{
    //

};

void panel_init(hyperion_panel *panel);

//returns temperature value from specified temp sensor(1...3)
unsigned int get_temp(hyperion_panel *panel);

//returns voltage value from sensor
unsigned int get_volt(hyperion_panel *panel);

//return current value from sensor
unsigned int get_curr(hyperion_panel *panel);

unsigned int get_val(hyperion_panel *panel, enum channel_type_t num);


#endif