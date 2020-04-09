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

#define AXP192_I2C_ADDRESS          (  )

/**
 * @brief   AXP192 FAILURE CODES
 */
#define AXP192_SUCCESS             ( 0 )     /** Operation completed successfully. */
#define AXP192_FAIL                ( 1 )     /** Operation failed. */
#define AXP192_OTHER_ERROR         ( 2 )     /** Other error. */



/**
 * @brief   Initialize AXP192
 * *
 * @return  AXP192_SUCCESS success
 *          AXP192_FAIL failed
 */
axp192_err_t eAXP192Init( IotI2CHandle_t const handle );

#endif // _AXP192_H_
