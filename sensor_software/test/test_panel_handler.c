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
 * @file    test_panel_handler.c
 * @author  Vasu Gupta
 * @date    2020-06-15
 */


#include "unity.h"
#include "panel_handler.h"
#include "adc_handler.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_CombinedMeasurements(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement CombinedMeasurements");
}

void test_SingleMeasurementsAnyPanel(void)
{


    TEST_IGNORE_MESSAGE("Need to Implement SingleMeasurementsAnyPanel");
}

void test_AllMeasurementsAnyPanel(void)
{
    Mock_Buffer.size = 1;
    Mock_Buffer.value = 0x08CD;

    panel_update_single(PANEL_P);

    float reading_temp_1 = panel_get_reading(PANEL_P, CHANNEL_TEMP_1);

    TEST_ASSERT_FLOAT_WITHIN(0.05, TEMP_VAL_MIN, reading_temp_1);
}

void test_AllMeasurementsAllPanels(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement AllMeasurementsAllPanels");
}