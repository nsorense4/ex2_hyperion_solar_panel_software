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
 * @file    demux.c
 * @author  Noah Rozario
 * @date    2020-06-17
 */


#include "gio.h"
#include "demux_handler.h"

/**
 * @brief
 *      Allows user to select specific Hyperion panel ADC using the 74AHC138 demux
 * @param panel
 *      variable panel of data type panel_CS which represents the different hyperion panels ex: cs_P, cs_PD etc
 */
void set_pin(enum panel_CS panel)
{
    gioInit(); //initialising gio ports
    switch(panel)
    {
    case cs_P:
        //enable y2(010)
        //set a0 low
        gioSetBit(gioPORTB,7,1); // set a1 high
        gioSetBit(gioPORTA,3,0); // set a2 low
        break;
    case cs_PD:
        //enable y3(011)
        //set a0 high
        gioSetBit(gioPORTB,7,1); // set a1 high
        gioSetBit(gioPORTA,3,0); // set a2 low
        break;
    case cs_Z:
        //enable y4(100)
        //set a0 low
        gioSetBit(gioPORTB,7,0); // set a1 low
        gioSetBit(gioPORTA,3,1); // set a2 high
        break;
    case cs_SD:
        //enAble y5(101)
        //set a0 high
        gioSetBit(gioPORTB,7,0); // set a1 low
        gioSetBit(gioPORTA,3,1); // set a2 high
        break;
    case cs_S:
        //enable y6(110)
        //set a0 low
        gioSetBit(gioPORTB,7,1); // set a1 high
        gioSetBit(gioPORTA,3,1); // set a2 high
        break;
    case cs_N:
        //enable y7(111)
        //set a0 high
        gioSetBit(gioPORTB,7,1); // set a1 high
        gioSetBit(gioPORTA,3,1); // set a2 high
        break;
    default:
        //enable all pins
        break;
    }
}

