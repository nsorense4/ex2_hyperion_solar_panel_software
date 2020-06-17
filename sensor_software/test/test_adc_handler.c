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
 * @file    test_adc_handler.c
 * @author  Vasu Gupta
 * @date    2020-06-15
 */


#include "unity.h"

#include "adc_handler.h"
#include "mock_spi.h"

ADC_Handler handle;

void setUp(void)
{
    adc_init(&handle, 4096);
}

void tearDown(void)
{
}

void test_adc_handler_getVal(void) 
{

    float temp = 0;
    uint16_t val = 0;

    adc_set_control_reg(&handle, 0,
                                 1,
                                 0,
                                 0,
                                 0);

    adc_get_raw(&handle, &val);

    temp = adc_get_temp(&handle, val, 2.5);

    //TEST_ASSERT_EQUAL_HEX16(0x7FFF, val);
    TEST_ASSERT_EQUAL_FLOAT(25.0, temp);
}
