/**
 * @file axp192.c
 * @brief Component to work with AXP192
 *
 * (C) 2020 - Timothee Cruse <timothee.cruse@gmail.com>
 * This code is licensed under the MIT License.
 */

#include "axp192.h"

#include "common_io_helpers.h"

#define LIBRARY_LOG_LEVEL IOT_LOG_DEBUG
#define LIBRARY_LOG_NAME  "axp192"
#include "iot_logging_setup.h"

/*-----------------------------------------------------------*/

static IotI2CHandle_t prvAXP192I2CHandle = NULL;

/*-----------------------------------------------------------*/

/*-----------------------------------------------------------*/

axp192_err_t eAXP192Init( IotI2CHandle_t const handle )
{
    return AXP192_FAIL;
}

/*-----------------------------------------------------------*/



/*-----------------------------------------------------------*/


