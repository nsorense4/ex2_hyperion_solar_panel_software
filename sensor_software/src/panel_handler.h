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

#include "common_defines.h"

#include <stdint.h>


// void panel_init(hyperion_panel *panel);

void panel_update();

float panel_get_reading(enum panel_t, enum channel_type_t);


#endif