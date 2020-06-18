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
 * demux.h
 * Noah Rozario
 * 2020/6/17
 */
#ifndef DEMUX_H
#define DEMUX_H

enum panel_CS{ //defining data type panel_CS which represents hyperion panels
    cs_P = 0,
    cs_PD,
    cs_Z,
    cs_SD,
    cs_S,
    cs_N
};
/*
 * demux function:
 * allows user to select specific Hyperion panel ADC using the 74AHC138 demux
 * input argument:
 * -panel_CS panel- variable panel of data type panel_CS which represents the different hyperion panels ex: cs_P, cs_PD etc
 */
void demux(enum panel_CS panel);

#endif
