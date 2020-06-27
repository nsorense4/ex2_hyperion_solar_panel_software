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

void test_CalculateAdcVinVoltage(void)
{
    adc_init(&handle, PANEL_P);

    spiTransmitData_ExpectAnyArgsAndReturn(0xFF);
    adc_set_control_reg(&handle, 0, ADC_CHANNEL_VOLT, 0, 0, 0);

    uint16_t mock_rx_buffer = 0x0FFF;
    spiReceiveData_ExpectAnyArgsAndReturn(0xFF);
    spiReceiveData_ReturnArrayThruPtr_destbuff(&mock_rx_buffer, 1);
    uint16_t buffer;
    uint8_t  current_channel;
    adc_get_raw(&handle, &buffer, &current_channel);

    float vin_voltage = 0;
    vin_voltage = adc_calculate_vin(buffer, ADC_VREF);

    TEST_ASSERT_FLOAT_WITHIN(0.001, 2.5, vin_voltage);
}

void test_CalculateSensorVoltage(void) {
    adc_init(&handle, PANEL_P);

    spiTransmitData_ExpectAnyArgsAndReturn(0xFF);
    adc_set_control_reg(&handle, 0, ADC_CHANNEL_VOLT, 0, 0, 0);

    uint16_t mock_rx_buffer = 0x0FFF;
    spiReceiveData_ExpectAnyArgsAndReturn(0xFF);
    spiReceiveData_ReturnArrayThruPtr_destbuff(&mock_rx_buffer, 1);
    uint16_t buffer;
    uint8_t  current_channel;
    adc_get_raw(&handle, &buffer, &current_channel);

    float sensor_voltage = 0;
    sensor_voltage = adc_calculate_sensor_voltage(buffer, ADC_VREF);

    TEST_ASSERT_FLOAT_WITHIN(0.005, VOLT_MAX, sensor_voltage);
    
}

void test_CalculateSensorTemperature(void) 
{
    adc_init(&handle, PANEL_P);

    spiTransmitData_ExpectAnyArgsAndReturn(0xFF);
    adc_set_control_reg(&handle, 0, ADC_CHANNEL_TEMP_1, 0, 0, 0);

    uint16_t mock_rx_buffer = 0x08CD;
    spiReceiveData_ExpectAnyArgsAndReturn(0xFF);
    spiReceiveData_ReturnArrayThruPtr_destbuff(&mock_rx_buffer, 1);
    uint16_t buffer;
    uint8_t  current_channel;
    adc_get_raw(&handle, &buffer, &current_channel);

    float sensor_temperature = 0;
    sensor_temperature = adc_calculate_sensor_temp(buffer, ADC_VREF);

    TEST_ASSERT_FLOAT_WITHIN(0.05, TEMP_VAL_MIN, sensor_temperature);
}

void test_CalculateSensorCurrent(void)
{
    adc_init(&handle, PANEL_P);

    spiTransmitData_ExpectAnyArgsAndReturn(0xFF);
    adc_set_control_reg(&handle, 0, ADC_CHANNEL_VOLT, 0, 0, 0);

    uint16_t mock_rx_buffer = 0x0FFF;
    spiReceiveData_ExpectAnyArgsAndReturn(0xFF);
    spiReceiveData_ReturnArrayThruPtr_destbuff(&mock_rx_buffer, 1);
    uint16_t buffer;
    uint8_t  current_channel;
    adc_get_raw(&handle, &buffer, &current_channel);

    float sensor_current = 0;
    sensor_current = adc_calculate_sensor_current(buffer, ADC_VREF);

    TEST_ASSERT_FLOAT_WITHIN(0.005, CURR_MAX, sensor_current);
}

void test_CalculateSensorPhotodiode(void)
{
    TEST_IGNORE_MESSAGE("Need to implement!");
}