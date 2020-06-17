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

void panel_init(hyperion_panel *panel) {

}

/* returns temperature value from specified temp sensor(1...3)
 * 
 * 
 * 
 * 
 */
// unsigned int get_temp(hyperion_panel *panel) {
    
//     adc_get_temp(&s_adc_handler);
// }


// //returns voltage value from sensor
// unsigned int get_volt(hyperion_panel *panel);

// //return current value from sensor
// unsigned int get_curr(hyperion_panel *panel);

// unsigned int get_val(hyperion_panel *panel, enum channel_type_t num);