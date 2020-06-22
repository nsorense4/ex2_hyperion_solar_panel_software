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
    
}

void tearDown(void)
{
}

void test_adc_volt_conv(void) {
    adc_init(&handle);

    spiTransmitData_ExpectAnyArgsAndReturn(0xFF);
    adc_set_control_reg(&handle, 0, 2, 0, 0, 0);

    uint16_t mock_rx_buffer = 0x07FF; // mock a voltage of 2.5V
    spiReceiveData_ExpectAnyArgsAndReturn(0xFF);
    spiReceiveData_ReturnArrayThruPtr_destbuff(&mock_rx_buffer, 1);
    uint16_t conv_data;
    uint8_t  current_channel;
    adc_get_raw(&handle, &conv_data, &current_channel);

    float sensor_voltage = 0;
    sensor_voltage = adc_conv_to_volt(conv_data, 5);

    TEST_ASSERT_FLOAT_WITHIN(0.005, 2.5, sensor_voltage);
    
    TEST_ASSERT_EQUAL_UINT8(0, current_channel);
}

void test_adc_temp_conv(void) 
{
    adc_init(&handle);

    spiTransmitData_ExpectAnyArgsAndReturn(0xFF);
    adc_set_control_reg(&handle, 0, 2, 0, 0, 0);

    uint16_t mock_rx_buffer = 0x01F0; // mock a voltage of 0.302V
    spiReceiveData_ExpectAnyArgsAndReturn(0xFF);
    spiReceiveData_ReturnArrayThruPtr_destbuff(&mock_rx_buffer, 1);
    uint16_t conv_data;
    uint8_t  current_channel;
    adc_get_raw(&handle, &conv_data, &current_channel);
    
    float sensor_voltage = 0;
    sensor_voltage = adc_conv_to_volt(conv_data, 2.5);
    TEST_ASSERT_FLOAT_WITHIN(0.005, 0.302, sensor_voltage);

    float temp = 0;
    temp = adc_conv_to_celsius(sensor_voltage);
    TEST_ASSERT_FLOAT_WITHIN(0.5, 150, temp);
}
