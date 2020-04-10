/**
 * @file axp192.h
 * @brief Component to work with AXP192
 *
 * Include this header file to use the component.
 *
 * (C) 2019 - Timothee Cruse <timothee.cruse@gmail.com>
 * This code is licensed under the MIT License.
 */

#ifndef _AXP192_H_
#define _AXP192_H_

#include "freertos/FreeRTOS.h"
#include "iot_i2c.h"

typedef int32_t axp192_err_t;

#define AXP192_I2C_ADDRESS          ( 0x34 )

/**
 * @brief   AXP192 FAILURE CODES
 */
#define AXP192_SUCCESS             ( 0 )     /** Operation completed successfully. */
#define AXP192_FAIL                ( 1 )     /** Operation failed. */
#define AXP192_OTHER_ERROR         ( 2 )     /** Other error. */

typedef struct {
    IotI2CHandle_t i2c_handle;
    uint8_t * init_regs;
    uint8_t nb_init_regs;
} axp192_config_t;

/**
 * @brief   Initialize AXP192
 * *
 * @return  AXP192_SUCCESS success
 *          AXP192_FAIL failed
 */
axp192_err_t eAXP192Init( axp192_config_t config );

axp192_err_t eAXP192GetVbat( uint16_t * vbat );
axp192_err_t eAXP192GetVaps( uint16_t * vaps );
axp192_err_t eAXP192SetSleep( void );

axp192_err_t eAXP192SetRegisterBits(uint8_t register_address, uint8_t bits_to_set);
axp192_err_t eAXP192ClearRegisterBits(uint8_t register_address, uint8_t bits_to_clear);

// Group 1: Basic power control )
#define AXP192_REG_INPUT_POWER_STATUS                               ( 0x00 )
#define AXP192_REG_MODE_POWER_CHARGE_STATUS                         ( 0x01 )
#define AXP192_REG_OTG_VBUS_STATUS                                  ( 0x04 )
#define AXP192_REG_DATA_BUFFER_0                                    ( 0x06 )
#define AXP192_REG_DATA_BUFFER_1                                    ( 0x07 )
#define AXP192_REG_DATA_BUFFER_2                                    ( 0x08 )
#define AXP192_REG_DATA_BUFFER_3                                    ( 0x09 )
#define AXP192_REG_DATA_BUFFER_4                                    ( 0x0A )
#define AXP192_REG_DATA_BUFFER_5                                    ( 0x0B )
#define AXP192_REG_EXTEN_DCDC2_SWITCH_CONTROL                       ( 0x10 )    
#define AXP192_REG_DCDC1_DCDC3_LDO2_LDO3_SWITCH_CONTROL             ( 0x12 )
#define AXP192_REG_DCDC2_VOLTAGE_SETTING                            ( 0x23 )
#define AXP192_REG_DCDC2_VOLTAGE_SLOPE_SETTING                      ( 0x25 )
#define AXP192_REG_DCDC1_VOLTAGE_SETTING                            ( 0x26 )
#define AXP192_REG_DCDC3_VOLTAGE_SETTING                            ( 0x27 )
#define AXP192_REG_LDO2_LDO3_VOLTAGE_SETTING                        ( 0x28 )
#define AXP192_REG_VBUS_IPSOUT_PATH_SETTING                         ( 0x30 )
#define AXP192_REG_VOFF_SHUTDOWN_VOLTAGE_SETTING                    ( 0x31 )
#define AXP192_REG_OFF_BATTERY_DETECTION_CHGLED_CONTROL             ( 0x32 )
#define AXP192_REG_CHARGE_CONTROL_1                                 ( 0x33 )
#define AXP192_REG_CHARGE_CONTROL_2                                 ( 0x34 )
#define AXP192_REG_BACKUP_BATTERY_CHARGING_CONTROL                  ( 0x35 )
#define AXP192_REG_PEK_SETTING                                      ( 0x36 )
#define AXP192_REG_DCDC_CONVERTER_OPERATING_FREQUENCY               ( 0x37 )
#define AXP192_REG_LOW_BATTERY_CHARGE_WARNING                       ( 0x38 )
#define AXP192_REG_BATTERY_CHARGING_HIGH_TEMPERATURE_ALARM          ( 0x39 )
#define AXP192_REG_APS_LOW_LEVEL_1                                  ( 0x3A )
#define AXP192_REG_APS_LOW_LEVEL_2                                  ( 0x3B )
#define AXP192_REG_LOW_BATTERY_DISCHARGE_ALARM                      ( 0x3C )
#define AXP192_REG_BATTERY_DISCHARGE_HIGH_TEMPERATURE_ALARM         ( 0x3D )
#define AXP192_REG_DCDC_OPERATION_MODE                              ( 0x80 )
#define AXP192_REG_ADC_ENABLE_1                                     ( 0x82 )
#define AXP192_REG_ADC_ENABLE_2                                     ( 0x83 )
#define AXP192_REG_ADC_SAMPLE_RATE_TS_PIN_CONTROL                   ( 0x84 )
#define AXP192_REG_GPIO_INPUT_RANGE                                 ( 0x85 )
#define AXP192_REG_GPIO1_ADC_IRQ_RISING_THRESHOLD                   ( 0x86 )
#define AXP192_REG_GPIO1_ADC_IRQ_FALLING_THRESHOLD                  ( 0x87 )
#define AXP192_REG_TIMER_CONTROL                                    ( 0x8A )
#define AXP192_REG_VBUS_MONITORING                                  ( 0x8B )
#define AXP192_REG_OVERTEMPERATURE_SHUTDOWN_CONTROL                 ( 0x8F )

// Group 2: GPIO Control )
#define AXP192_REG_GPIO0_CONTROL                                    ( 0x90 )
#define AXP192_REG_GPIO0_LDO_MODE_OUTPUT_VOLTAGE                    ( 0x91 )
#define AXP192_REG_GPIO1_CONTROL                                    ( 0x92 )
#define AXP192_REG_GPIO2_CONTROL                                    ( 0x93 )
#define AXP192_REG_GPIO_2_0_SIGNAL_STATUS                           ( 0x94 )
#define AXP192_REG_GPIO_4_3_FUNCTION_CONTROL                        ( 0x95 )
#define AXP192_REG_GPIO_4_3_SIGNAL_STATUS                           ( 0x96 )
#define AXP192_REG_GPIO_2_0_PULLDOWN_CONTROL                        ( 0x97 )
#define AXP192_REG_PWM1_FREQUENCY                                   ( 0x98 )
#define AXP192_REG_PWM1_DUTY_CYCLE_1                                ( 0x99 )
#define AXP192_REG_PWM1_DUTY_CYCLE_2                                ( 0x9A )
#define AXP192_REG_PWM2_FREQUENCY                                   ( 0x9B )
#define AXP192_REG_PWM2_DUTY_CYCLE_1                                ( 0x9C )
#define AXP192_REG_PWM2_DUTY_CYCLE_2                                ( 0x9D )
#define AXP192_REG_N_RSTO_GPIO5_CONTROL                             ( 0x9E )

// Group 3: Interrupt control )
#define AXP192_REG_IRQ_ENABLE_CONTROL_1                             ( 0x40 )
#define AXP192_REG_IRQ_ENABLE_CONTROL_2                             ( 0x41 )
#define AXP192_REG_IRQ_ENABLE_CONTROL_3                             ( 0x42 )
#define AXP192_REG_IRQ_ENABLE_CONTROL_4                             ( 0x43 )
#define AXP192_REG_IRQ_ENABLE_CONTROL_5                             ( 0x4A )
#define AXP192_REG_IRQ_STATUS_1                                     ( 0x44 )
#define AXP192_REG_IRQ_STATUS_2                                     ( 0x45 )
#define AXP192_REG_IRQ_STATUS_3                                     ( 0x46 )
#define AXP192_REG_IRQ_STATUS_4                                     ( 0x47 )
#define AXP192_REG_IRQ_STATUS_5                                     ( 0x4D )

// Group 4: ADC )
#define AXP192_REG_ACIN_VOLTAGE_ADC_DATA_HIGH                       ( 0x56 )
#define AXP192_REG_ACIN_VOLTAGE_ADC_DATA_LOW                        ( 0x57 ) // ???
#define AXP192_REG_ACIN_CURRENT_ADC_DATA_HIGH                       ( 0x58 )
#define AXP192_REG_ACIN_CURRENT_ADC_DATA_LOW                        ( 0x59 )
#define AXP192_REG_VBUS_VOLTAGE_ADC_DATA_HIGH                       ( 0x5A )
#define AXP192_REG_VBUS_VOLTAGE_ADC_DATA_LOW                        ( 0x5B )
#define AXP192_REG_VBUS_CURRENT_ADC_DATA_HIGH                       ( 0x5C )
#define AXP192_REG_VBUS_CURRENT_ADC_DATA_LOW                        ( 0x5D )
#define AXP192_REG_INTERNAL_TEMPERATURE_ADC_DATA_HIGH               ( 0x5E )
#define AXP192_REG_INTERNAL_TEMPERATURE_ADC_DATA_LOW                ( 0x5F )
#define AXP192_REG_TS_ADC_DATA_HIGH =                               ( 0x62 )
#define AXP192_REG_TS_ADC_DATA_LOW =                                ( 0x63 )
#define AXP192_REG_GPIO0_VOLTAGE_ADC_DATA_HIGH =                    ( 0x64 )
#define AXP192_REG_GPIO0_VOLTAGE_ADC_DATA_LOW =                     ( 0x65 )
#define AXP192_REG_GPIO1_VOLTAGE_ADC_DATA_HIGH =                    ( 0x66 )
#define AXP192_REG_GPIO1_VOLTAGE_ADC_DATA_LOW =                     ( 0x67 )
#define AXP192_REG_GPIO2_VOLTAGE_ADC_DATA_HIGH =                    ( 0x68 )
#define AXP192_REG_GPIO2_VOLTAGE_ADC_DATA_LOW =                     ( 0x69 )
#define AXP192_REG_GPIO3_VOLTAGE_ADC_DATA_HIGH =                    ( 0x6A )
#define AXP192_REG_GPIO3_VOLTAGE_ADC_DATA_LOW =                     ( 0x6B )
// Todo:                                                            ( 0x70 to 0x7F )

#define AXP192_REG_BATTERY_CHARGING_COULOMB_COUNTER_DATA_31_24      ( 0xB0 )
#define AXP192_REG_BATTERY_CHARGING_COULOMB_COUNTER_DATA_23_16      ( 0xB1 )
#define AXP192_REG_BATTERY_CHARGING_COULOMB_COUNTER_DATA_15_8       ( 0xB2 )
#define AXP192_REG_BATTERY_CHARGING_COULOMB_COUNTER_DATA_7_0        ( 0xB3 )
#define AXP192_REG_BATTERY_DISCHARGE_COULOMB_COUNTER_DATA_31_24     ( 0xB4 )
#define AXP192_REG_BATTERY_DISCHARGE_COULOMB_COUNTER_DATA_23_16     ( 0xB5 )
#define AXP192_REG_BATTERY_DISCHARGE_COULOMB_COUNTER_DATA_15_8      ( 0xB6 )
#define AXP192_REG_BATTERY_DISCHARGE_COULOMB_COUNTER_DATA_7_0       ( 0xB7 )
#define AXP192_REG_COULOMB_COUNTER_CONTROL                          ( 0xB8 )

#endif // _AXP192_H_
